/*
 * Copyright (C) 2019 Jonathan D. Belanger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Lexer/Parser.h"

/*
 * CurTok/getNextToken - Provide a simple token buffer.  CurTok is the current
 * token the parser is looking at.  getNextToken reads another token from the
 * lexer and updates CurTok with its results.
 */
static int CurTok;
static int getNextToken()
{
    return CurTok = gettok();
}

/*
 * BinopPrecedence - This holds the precedence for each binary operator that is
 * defined.
 */
static std::map<char, int> BinopPrecedence;

/* GetTokPrecedence - Get the precedence of the pending binary operator token. */
static int Parser::GetTokPrecedence()
{
    if (!isascii(CurTok))
    {
        return -1;
    }

    /*  Make sure it's a declared binop. */
    int TokPrec = BinopPrecedence[CurTok];
    if (TokPrec <= 0)
    {
        return -1;
    }
    return TokPrec;
}

/* LogError* - These are little helper functions for error handling. */
std::unique_ptr<ExprAST> Parser::LogError(const char *Str)
{
    fprintf(stderr, "Error: %s\n", Str);
    return nullptr;
}

std::unique_ptr<PrototypeAST> Parser::LogErrorP(const char *Str)
{
    LogError(Str);
    return nullptr;
}

static std::unique_ptr<ExprAST> Parser::ParseExpression();

/* numberexpr ::= number */
static std::unique_ptr<ExprAST> Parser::ParseNumberExpr()
{
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken(); /*  consume the number */
    return std::move(Result);
}

/* parenexpr ::= '(' expression ')' */
static std::unique_ptr<ExprAST> Parser::ParseParenExpr()
{
    getNextToken(); /*  eat (. */
    auto V = ParseExpression();
    if (!V)
    {
        return nullptr;
    }

    if (CurTok != ')')
    {
        return LogError("expected ')'");
    }
    getNextToken(); /*  eat ). */
    return V;
}

/* 
 * identifierexpr
 *    ::= identifier
 *    ::= identifier '(' expression*
 */
static std::unique_ptr<ExprAST> Parser::ParseIdentifierExpr()
{
    std::string IdName = IdentifierStr;

    getNextToken(); /*  eat identifier. */

    if (CurTok != '(') /*  Simple variable ref. */
    {
        return std::make_unique<VariableExprAST>(IdName);
    }

    /*  Call. */
    getNextToken(); /*  eat ( */
    std::vector<std::unique_ptr<ExprAST>> Args;
    if (CurTok != ')')
    {
        while (true)
        {
            if (auto Arg = ParseExpression())
            {
                Args.push_back(std::move(Arg));
            }
            else
            {
                return nullptr;
            }

            if (CurTok == ')')
            {
                break;
            }

            if (CurTok != ',')
            {
                return LogError("Expected ')' or ',' in argument list");
            }
            getNextToken();
        }
    }

    /*  Eat the ')'. */
    getNextToken();

    return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

/* ifexpr ::= 'if' expression 'then' expression 'else' expression */
static std::unique_ptr<ExprAST> Parser::ParseIfExpr()
{
    getNextToken(); /*  eat the if. */

    /*  condition. */
    auto Cond = ParseExpression();
    if (!Cond)
    {
        return nullptr;
    }

    if (CurTok != tok_then)
    {
        return LogError("expected then");
    }
    getNextToken(); /*  eat the then */

    auto Then = ParseExpression();
    if (!Then)
    {
        return nullptr;
    }

    if (CurTok != tok_else)
    {
        return LogError("expected else");
    }

    getNextToken();

    auto Else = ParseExpression();
    if (!Else)
    {
        return nullptr;
    }

    return std::make_unique<IfExprAST>(std::move(Cond), std::move(Then),
                                       std::move(Else));
}

/* forexpr ::= 'for' identifier '=' expr ',' expr (',' expr)? 'in' expression */
static std::unique_ptr<ExprAST> Parser::ParseForExpr()
{
    getNextToken(); /*  eat the for. */

    if (CurTok != tok_identifier)
    {
        return LogError("expected identifier after for");
    }

    std::string IdName = IdentifierStr;
    getNextToken(); /*  eat identifier. */

    if (CurTok != '=')
    {
        return LogError("expected '=' after for");
    }
    getNextToken(); /*  eat '='. */

    auto Start = ParseExpression();
    if (!Start)
    {
        return nullptr;
    }
    if (CurTok != ',')
    {
        return LogError("expected ',' after for start value");
    }
    getNextToken();

    auto End = ParseExpression();
    if (!End)
    {
        return nullptr;
    }

    /*  The step value is optional. */
    std::unique_ptr<ExprAST> Step;
    if (CurTok == ',')
    {
        getNextToken();
        Step = ParseExpression();
        if (!Step)
        {
            return nullptr;
        }
    }

    if (CurTok != tok_in)
    {
        return LogError("expected 'in' after for");
    }
    getNextToken(); /*  eat 'in'. */

    auto Body = ParseExpression();
    if (!Body)
    {
        return nullptr;
    }

    return std::make_unique<ForExprAST>(IdName, std::move(Start), std::move(End),
                                        std::move(Step), std::move(Body));
}

/* 
 * varexpr ::= 'var' identifier ('=' expression)?
 *                   (',' identifier ('=' expression)?)* 'in' expression
 */
static std::unique_ptr<ExprAST> Parser::ParseVarExpr()
{
    getNextToken(); /*  eat the var. */

    std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> VarNames;

    /*  At least one variable name is required. */
    if (CurTok != tok_identifier)
    {
        return LogError("expected identifier after var");
    }

    while (true)
    {
        std::string Name = IdentifierStr;
        getNextToken(); /*  eat identifier. */

        /*  Read the optional initializer. */
        std::unique_ptr<ExprAST> Init = nullptr;
        if (CurTok == '=')
        {
            getNextToken(); /*  eat the '='. */

            Init = ParseExpression();
            if (!Init)
            {
                return nullptr;
            }
        }

        VarNames.push_back(std::make_pair(Name, std::move(Init)));

        /*  End of var list, exit loop. */
        if (CurTok != ',')
        {
            break;
        }
        getNextToken(); /*  eat the ','. */

        if (CurTok != tok_identifier)
        {
            return LogError("expected identifier list after var");
        }
    }

    /*  At this point, we have to have 'in'. */
    if (CurTok != tok_in)
    {
        return LogError("expected 'in' keyword after 'var'");
    }
    getNextToken(); /*  eat 'in'. */

    auto Body = ParseExpression();
    if (!Body)
    {
        return nullptr;
    }

    return std::make_unique<VarExprAST>(std::move(VarNames), std::move(Body));
}

/*
 * primary
 *    ::= identifierexpr
 *    ::= numberexpr
 *    ::= parenexpr
 *    ::= ifexpr
 *    ::= forexpr
 *    ::= varexpr
 */
static std::unique_ptr<ExprAST> Parser::ParsePrimary()
{
    switch (CurTok)
    {
        default:
            return LogError("unknown token when expecting an expression");

        case tok_identifier:
            return ParseIdentifierExpr();

        case tok_number:
            return ParseNumberExpr();

        case '(':
            return ParseParenExpr();

        case tok_if:
            return ParseIfExpr();

        case tok_for:
            return ParseForExpr();

        case tok_var:
            return ParseVarExpr();
    }
}

/*
 * unary
 *   ::= primary
 *   ::= '!' unary
 */
static std::unique_ptr<ExprAST> Parser::ParseUnary()
{
    /*  If the current token is not an operator, it must be a primary expr. */
    if (!isascii(CurTok) || CurTok == '(' || CurTok == ',')
    {
        return ParsePrimary();
    }

    /*  If this is a unary operator, read it. */
    int Opc = CurTok;
    getNextToken();
    if (auto Operand = ParseUnary())
    {
        return std::make_unique<UnaryExprAST>(Opc, std::move(Operand));
    }
    return nullptr;
}

/* 
 * binoprhs
 *   ::= ('+' unary)*
 */
static std::unique_ptr<ExprAST> Parser::ParseBinOpRHS(int ExprPrec,
                                              std::unique_ptr<ExprAST> LHS)
{
    /*  If this is a binop, find its precedence. */
    while (true)
    {
        int TokPrec = GetTokPrecedence();

        /*
         * If this is a binop that binds at least as tightly as the current binop,
         *  consume it, otherwise we are done.
         */
        if (TokPrec < ExprPrec)
        {
            return LHS;
        }

        /*  Okay, we know this is a binop. */
        int BinOp = CurTok;
        getNextToken(); /*  eat binop */

        /*  Parse the unary expression after the binary operator. */
        auto RHS = ParseUnary();
        if (!RHS)
        {
            return nullptr;
        }

        /*
         * If BinOp binds less tightly with RHS than the operator after RHS, let 
         *  the pending operator take RHS as its LHS.
         */
        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec)
        {
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS)
            {
                return nullptr;
            }
        }

        /*  Merge LHS/RHS. */
        LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}

/*
 * expression
 *    ::= unary binoprhs
 */
static std::unique_ptr<ExprAST> Parser::ParseExpression()
{
    auto LHS = ParseUnary();
    if (!LHS)
    {
        return nullptr;
    }

  return ParseBinOpRHS(0, std::move(LHS));
}

/* prototype
 *   ::= id '(' id* ')'
 *   ::= binary LETTER number? (id, id)
 *   ::= unary LETTER (id)
 */
static std::unique_ptr<PrototypeAST> Parser::ParsePrototype()
{
    std::string FnName;

    unsigned Kind = 0; /*  0 = identifier, 1 = unary, 2 = binary. */
    unsigned BinaryPrecedence = 30;

    switch (CurTok)
    {
        default:
            return LogErrorP("Expected function name in prototype");

        case tok_identifier:
            FnName = IdentifierStr;
            Kind = 0;
            getNextToken();
            break;

        case tok_unary:
            getNextToken();
            if (!isascii(CurTok))
            {
                return LogErrorP("Expected unary operator");
            }
            FnName = "unary";
            FnName += (char)CurTok;
            Kind = 1;
            getNextToken();
            break;

        case tok_binary:
            getNextToken();
            if (!isascii(CurTok))
            {
                return LogErrorP("Expected binary operator");
            }
            FnName = "binary";
            FnName += (char)CurTok;
            Kind = 2;
            getNextToken();

            /*  Read the precedence if present. */
            if (CurTok == tok_number)
            {
                if (NumVal < 1 || NumVal > 100)
                {
                    return LogErrorP("Invalid precedence: must be 1..100");
                }
                BinaryPrecedence = (unsigned)NumVal;
                getNextToken();
            }
            break;
    }

    if (CurTok != '(')
    {
        return LogErrorP("Expected '(' in prototype");
    }

    std::vector<std::string> ArgNames;
    while (getNextToken() == tok_identifier)
    {
        ArgNames.push_back(IdentifierStr);
    }
    if (CurTok != ')')
    {
        return LogErrorP("Expected ')' in prototype");
    }

    /*  success. */
    getNextToken(); /*  eat ')'. */

    /*  Verify right number of names for operator. */
    if (Kind && ArgNames.size() != Kind)
    {
        return LogErrorP("Invalid number of operands for operator");
    }

    return std::make_unique<PrototypeAST>(FnName, ArgNames, Kind != 0,
                                          BinaryPrecedence);
}

/* definition ::= 'def' prototype expression */
static std::unique_ptr<FunctionAST> Parser::ParseDefinition()
{
    getNextToken(); /*  eat def. */
    auto Proto = ParsePrototype();
    if (!Proto)
    {
        return nullptr;
    }

    if (auto E = ParseExpression())
    {
      return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }
    return nullptr;
}

/* toplevelexpr ::= expression */
static std::unique_ptr<FunctionAST> Parser::ParseTopLevelExpr()
{
    if (auto E = ParseExpression())
    {
        /*  Make an anonymous proto. */
        auto Proto = std::make_unique<PrototypeAST>("__anon_expr",
                                                    std::vector<std::string>());
        return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }
    return nullptr;
}

/* external ::= 'extern' prototype */
static std::unique_ptr<PrototypeAST> Parser::ParseExtern()
{
    getNextToken(); /*  eat extern. */
    return ParsePrototype();
}
