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

/* 
 * File:   Parser.h
 * Author: Jonathan D. Belanger
 *
 * Created on August 20, 2019, 7:32 AM
 */

#ifndef LLVM_BLISS_PARSER_H
#define LLVM_BLISS_PARSER_H

namespace bliss
{
    class Parser
    {
        private:
        std::map<char, int> BinopPrecedence;

        public:
        
        int GetTokPrecedence();
        int getNextToken();
        std::unique_ptr<ExprAST> LogError(const char *Str);
        std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);
        std::unique_ptr<ExprAST> ParseNumberExpr();
        std::unique_ptr<ExprAST> ParseParenExpr();
        std::unique_ptr<ExprAST> ParseIdentifierExpr();
        std::unique_ptr<ExprAST> ParseIfExpr();
        std::unique_ptr<ExprAST> ParseForExpr();
        std::unique_ptr<ExprAST> ParseVarExpr();
        std::unique_ptr<ExprAST> ParsePrimary();
        std::unique_ptr<ExprAST> ParseUnary();
        std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
                                               std::unique_ptr<ExprAST> LHS);
        std::unique_ptr<ExprAST> ParseExpression();
        std::unique_ptr<PrototypeAST> ParsePrototype();
        std::unique_ptr<FunctionAST> ParseDefinition();
        std::unique_ptr<FunctionAST> ParseTopLevelExpr();
        std::unique_ptr<PrototypeAST> ParseExtern();
    };
}


#endif /* LLVM_BLISS_PARSER_H */

