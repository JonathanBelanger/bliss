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
 * File:   ExprAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 14, 2019, 2:42 PM
 */

#ifndef LLVM_BLISS_EXPRAST_H
#define LLVM_BLISS_EXPRAST_H

#include "AST/BaseAST.h"

using namespace std;

namespace bliss
{

    /*
     * ExprAST - Base class for all expression nodes.
     *
     *              +- primary
     *  expression -+  operator-expression
     *              |  executable-function
     *              +- control-expression
     */
    class ExprAST : public BaseAST
    {
    };
}

#endif /* LLVM_BLISS_EXPRAST_H */
