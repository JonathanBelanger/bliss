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
 * File:   LinkageAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 28, 2019, 11:40 AM
 */

#ifndef LLVM_BLISS_LINKAGEAST_H
#define LLVM_BLISS_LINKAGEAST_H

#include "AST/DeclarationAST.h"

using namespace std;

namespace bliss
{

    /*
     * linkage-declaration --- LINKAGE linkage-definition, ...;
     *
     * linkage-definition --- linkage-name = linkage-type --
     *              -- ( -+- input-parameter-location, ... -+--+- ; output-parameter-location, ... ) -+--+- : linkage-option, ...
     *                    +- nothing -----------------------+  +- nothing ----------------------------+  +- nothing
     *
     *               +- CALL
     * linkage-type -+  JSB
     *               +- INTERRUPT
     *
     *                           +- REGISTER = register-number
     * input-parameter-location -+  STANDARD
     *                           +- nothing
     *
     * output-parameter-location --- REGISTER = register-number
     *
     *                 +- GLOBAL ( global-register-segment, ...)
     * linkage-option -+  +- PRESERVE ---+
     *                 +--+  NOPRESERVE -+- ( register-number, ... )
     *                    +- NOTUSED ----+
     *
     * global-register-segment --- global-register-name = register-number
     *
     * global-register-name -+- name
     * linkage-name ---------+
     *
     * register-number --- compile-time-constant-expression
     */
    class LinkageDeclAST : public DeclarationAST
    {
    };

    /*
     * Predeclared linkage functions:
     *  ACTUALCOUNT()
     *      Restriction: Must be declared BUILTIN within the body of a routine whose linkage-attribute is defined with certain
     *                   linkage-types.
     *      Value: Return the number of actual-parameters passed to the routine using STANDARD parameter-locations.  Parameters
     *             pass using REGISTER parameter-locations are not included in the returned value.
     *  ACTUALPATAMETER(ii)
     *      Restriction: The first restriction for ACTUALPARAMGER is the same as ACTUALCOUNT.  The value of ii must be in the
     *                   range of 1 to ACTUALCOUNT().
     *      Value: Return the value of the ii-th actual-parameter that was passed using STANDARD parameter-locations; parameters
     *             passed using REGISTER parameter-locations are not obtainable with this function.
     *  ARGPTR()
     *      Restriction: The restriction for ARGPTR is the same as for ACTUALCOUNT.
     *      Value: Return the address of the argument block.
     *
     *  NULLPARAMETER(ii)
     *      Restriction: If ii is not a formal-name, then it is interpreted as an expression and the value of ii must then be
     *                   greater than or equal to 1.
     *      Value: Returns true if the value of the ii-th actual-parameter was null or omitted.
     */
}

#endif /* LLVM_BLISS_LINKAGEAST_H */
