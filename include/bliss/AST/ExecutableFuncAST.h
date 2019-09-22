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

#ifndef LLVM_BLISS_EXECUTABLEFUNCAST_H
#define LLVM_BLISS_EXECUTABLEFUNCAST_H

#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{

    /*
     * executable-function --- executable-function-name ( -+- actual-parameter, ... -+- )
     *                                                     +- nothing ---------------+
     *
     * executable-function-name -+- name
     *                           +- % name
     *
     * actual-parameter --- expression
     */
    class ExecutableFuncAST : public ExprAST
    {
        public:
        ExecutableFuncAST(void *Val) : Val(Val) {}

        private:
        void *Val;
    };
}


#endif /* LLVM_BLISS_EXECUTABLEFUNCAST_H */
