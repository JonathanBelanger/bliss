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
 * File:   RoutineAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 28, 2019, 8:19 AM
 */

#ifndef LLVM_BLISS_ROUTINEAST_H
#define LLVM_BLISS_ROUTINEAST_H

#include "AST/DeclarationAST.h"
#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{

    /*
     *                      +- ordinary-routine-declaration
     * routine-declaration -+  global-routine-declaration
     *                      |  forward-routine-declaration
     *                      +- external-routine-declaration
     *
     * ordinary-routine-declaration --- nothing -+- ROUTINE routine-definition, ...;
     * global-routine-declaration --- GLOBAL ----+
     *
     *                                      +- ( input-list ) ------------- -+
     * routine-definition --- routine-name -+  ( ; output-list )             +--+- : routine-attribute... -+- = routine-body
     *                                      |  ( input-list ; output-list )  |  +- nothing ----------------+
     *                                      +- nothing ----------------------+
     *
     * routine-name --- name
     *
     * input-list --- input-formal-parameter, ...
     *
     * output-list --- output-formal-parameter, ...
     *
     * input-formal-parameter --+- formal-item
     * output-formal-parameter -+
     *
     * formal-item --- formal-name -+- : formal-attribute-list
     *                              +- nothing
     *
     * formal-name --- name
     *
     * formal-attribute-list --- map-declaration-attribute ...
     *
     *                            +- allocation-unit
     *                            |  extension-attribute
     * map-declaration-attribute -+  structure-attribute
     *                            |  field-attribute
     *                            +- volatile-attribute
     *
     *                    +- novalue-attribute
     *                    |  linkage-attribute
     * routine-attribute -+  psect-allocation
     *                    |  addressing-mode-attribute
     *                    +- weak-attribute
     *
     * routine-body --- expression
     */
    class RoutineDeclAST : public DeclarationAST
    {
        public:
            RoutineDeclAST(bool globalDeclaration = false);

        private:
            bool global;
    };

    /*
     * forward-routine-declaration --- FORWARD ROUTINE forward-routine-item, ...;
     *
     * forward-routine-item --- routine-name -+- : fwd-routine-attribute ...
     *                                        +- nothing
     *
     *                        +- novalue-attribute
     * fwd-routine-attribute -+  linkage-attribute
     *                        |  psect-allocation
     *                        +- addressing-mode-attribute
     *
     * routine-name --- name
     */
    class FwdRoutineDeclAST : public DeclarationAST
    {
    };

    /*
     * external-routine-declaration --- EXTERNAL ROUTINE external-routine-item, ...;
     *
     * external-routine-item --- routine-name -+- : ext-routine-attribute ...
     *                                         +- nothing
     *
     *                        +- novalue-attribute
     *                        |  linkage-attribute
     * ext-routine-attribute -+  psect-allocation
     *                        |  addressing-mode-attribute
     *                        +- weak-attribute
     *
     * routine-name --- name
     */
    class ExtRoutineDeclAST : public DeclarationAST
    {
    };
}

#endif /* LLVM_BLISS_ROUTINEAST_H */
