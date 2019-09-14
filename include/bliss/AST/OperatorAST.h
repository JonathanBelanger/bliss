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
 * File:   OperatorAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 14, 2019, 5:28 PM
 */

#ifndef LLVM_BLISS_OPERATORAST_H
#define LLVM_BLISS_OPERATORAST_H

#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{

    /*
     * Every operator has one of the following forms:
     *
     *      prefix-operator rhs
     *      lhs infix-operator rhs
     *
     *                                                  Direction of
     *                                                  Association
     *                                                  ------------
     *                      +- . rhs                    <---
     *                      |
     *                      |  + -+- rhs                <---
     *                      |  - -+
     *                      |
     *                      |  lhs ^ rhs                --->
     *                      |
     *                      |       +- MOD -+
     *                      |  lhs -+  *    +- rhs      --->
     *                      |       +- / ---+
     *                      |
     * operator-expression -+  lhs -+- + -+- rhs        --->
     *                      |       +- - -+
     *                      |
     *                      |       +- EQL[ UA] -+
     *                      |       |  NEQ[ UA]  |
     *                      |  lhs -+  LSS[ UA]  +- rhs --->
     *                      |       |  LEQ[ UA]  |
     *                      |       |  GTR[ UA]  |
     *                      |       +- GEQ[ UA] -+
     *                      |
     *                      |  NOT rhs                  <---
     *                      |
     *                      |  lhs AND rhs              --->
     *                      |
     *                      |  lhs OR rhs               --->
     *                      |
     *                      |  lhs -+- EQV -+- rhs      --->
     *                      |       +- XOR -+
     *                      |
     *                      +- lhs = rhs                <---
     *
     *        +- primary
     * lhs -+-+  operator-expression
     * rhs -+ +- executable-function
     */
    class OperatorExprAST : public ExprAST
    {
        public:
        OperatorExprAST(void *Val) : Val(Val) {}

        private:
        void *Val;
    };
}

#endif /* LLVM_BLISS_OPERATORAST_H */
