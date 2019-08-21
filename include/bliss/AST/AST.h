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
 * File:   AST.h
 * Author: Jonathan D. Belanger
 *
 * Created on August 19, 2019, 12:48 PM
 */

#ifndef LLVM_BLISS_AST_H
#define LLVM_BLISS_AST_H

namespace bliss
{

    /* ExprAST - Base class for all expression nodes. */
    class ExprAST
    {
        public:
        virtual ~ExprAST() = default;

        virtual Value *codegen() = 0;
    };

    /* NumberExprAST - Expression class for numeric literals like "1.0". */
    class NumberExprAST : public ExprAST
    {
        double Val;

        public:
        NumberExprAST(double Val) : Val(Val) {}

        Value *codegen() override;
    };

    /* VariableExprAST - Expression class for referencing a variable, like "a". */
    class VariableExprAST : public ExprAST
    {
        std::string Name;

        public:
        VariableExprAST(const std::string &Name) : Name(Name) {}

        Value *codegen() override;
        const std::string &getName() const { return Name; }
    };

    /* UnaryExprAST - Expression class for a unary operator. */
    class UnaryExprAST : public ExprAST
    {
        char Opcode;
        std::unique_ptr<ExprAST> Operand;

        public:
        UnaryExprAST(char Opcode, std::unique_ptr<ExprAST> Operand)
              : Opcode(Opcode), Operand(std::move(Operand)) {}

        Value *codegen() override;
    };

    /* BinaryExprAST - Expression class for a binary operator. */
    class BinaryExprAST : public ExprAST
    {
        char Op;
        std::unique_ptr<ExprAST> LHS, RHS;

        public:
        BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                      std::unique_ptr<ExprAST> RHS)
            : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

        Value *codegen() override;
    };

    /* CallExprAST - Expression class for function calls. */
    class CallExprAST : public ExprAST
    {
        std::string Callee;
        std::vector<std::unique_ptr<ExprAST>> Args;

        public:
        CallExprAST(const std::string &Callee,
                    std::vector<std::unique_ptr<ExprAST>> Args)
              : Callee(Callee), Args(std::move(Args)) {}

        Value *codegen() override;
    };

    /* IfExprAST - Expression class for if/then/else. */
    class IfExprAST : public ExprAST
    {
        std::unique_ptr<ExprAST> Cond, Then, Else;

        public:
        IfExprAST(std::unique_ptr<ExprAST> Cond, std::unique_ptr<ExprAST> Then,
                  std::unique_ptr<ExprAST> Else)
              : Cond(std::move(Cond)), Then(std::move(Then)), Else(std::move(Else)) {}

        Value *codegen() override;
    };

    /* ForExprAST - Expression class for for/in. */
    class ForExprAST : public ExprAST
    {
        std::string VarName;
        std::unique_ptr<ExprAST> Start, End, Step, Body;

        public:
        ForExprAST(const std::string &VarName, std::unique_ptr<ExprAST> Start,
                   std::unique_ptr<ExprAST> End, std::unique_ptr<ExprAST> Step,
                   std::unique_ptr<ExprAST> Body)
              : VarName(VarName), Start(std::move(Start)), End(std::move(End)),
              Step(std::move(Step)), Body(std::move(Body)) {}

        Value *codegen() override;
    };

    /* VarExprAST - Expression class for var/in */
    class VarExprAST : public ExprAST
    {
        std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> VarNames;
        std::unique_ptr<ExprAST> Body;

        public:
        VarExprAST(
              std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> VarNames,
              std::unique_ptr<ExprAST> Body)
              : VarNames(std::move(VarNames)), Body(std::move(Body)) {}

        Value *codegen() override;
    };

    /*
     * PrototypeAST - This class represents the "prototype" for a function,
     * which captures its name, and its argument names (thus implicitly the number
     * of arguments the function takes), as well as if it is an operator.
     */
    class PrototypeAST
    {
        std::string Name;
        std::vector<std::string> Args;
        bool IsOperator;
        unsigned Precedence; /*  Precedence if a binary op. */

        public:
        PrototypeAST(const std::string &Name, std::vector<std::string> Args,
                     bool IsOperator = false, unsigned Prec = 0)
            : Name(Name), Args(std::move(Args)), IsOperator(IsOperator),
              Precedence(Prec) {}

        Function *codegen();
        const std::string &getName() const { return Name; }

        bool isUnaryOp() const { return IsOperator && Args.size() == 1; }
        bool isBinaryOp() const { return IsOperator && Args.size() == 2; }

        char getOperatorName() const
        {
            assert(isUnaryOp() || isBinaryOp());
            return Name[Name.size() - 1];
        }

        unsigned getBinaryPrecedence() const { return Precedence; }
    };

    /* FunctionAST - This class represents a function definition itself. */
    class FunctionAST
    {
        std::unique_ptr<PrototypeAST> Proto;
        std::unique_ptr<ExprAST> Body;

        public:
        FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                    std::unique_ptr<ExprAST> Body)
            : Proto(std::move(Proto)), Body(std::move(Body)) {}

        Function *codegen();
    };
}

#endif /* LLVM_BLISS_AST_H */

