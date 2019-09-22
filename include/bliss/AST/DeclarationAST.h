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
 * File:   DeclarationAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 22, 2019, 10:31 AM
 */

#ifndef LLVM_BLISS_DECLARATIONAST_H
#define LLVM_BLISS_DECLARATIONAST_H

#include "AST/AttributeAST.h"

using namespace std;

namespace bliss
{

    /*
     *              +- data-declaration
     *              |  structure-declaration
     *              |  field-declaration
     *              |  routine-declaration
     *              |  linkage-declaration
     *              |  enable-declaration
     *              |  bound-declaration
     * declaration -+  compile-time-declaration
     *              |  macro-declaration
     *              |  require-declaration
     *              |  library-declaration
     *              |  psect-declaration
     *              |  switches-declaration
     *              |  label-declaration
     *              |  builtin-declaration
     *              +- undeclare-declaration
     */
    class DeclarationAST : public BaseAST
    {
    };

}

#endif /* LLVM_BLISS_DECLARATIONAST_H */
