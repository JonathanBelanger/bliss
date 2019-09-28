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
 * File:   BindingAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 28, 2019, 3:30 PM
 */

#ifndef LLVM_BLISS_BINDINGAST_H
#define LLVM_BLISS_BINDINGAST_H

#include "AST/AttributeAST.h"
#include "AST/DeclarationAST.h"
#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{

    /*
     *                    +- literal-declaration
     * bound-declaration -+  external-literal-declaration
     *                    |  bind-data-declaration
     *                    +- bind-routine-declaration
     */
    class BindDeclAST : public DeclarationASt
    {
    };

    /*
     * literal-declaration -+- LITERAL --------+- literal-item, ...;
     *                      +- GLOBAL LITERAL -+
     *
     * literal-item --- literal-name = literal-value -+- : literal-attribute...
     *                                                +- nothing
     *
     * literal-name --- name
     *
     * literal-value --- compile-time-constant-expression
     *
     * literal-attribute -+- range-attribute
     *                    +- weak-attribute
     *
     * Predeclared Literals
     *
     *  -------     ------      ------      ----------------------------------
     *              32-bit      64-bit
     *  Name        Value       Value       Significance
     *  -------     ------      ------      ----------------------------------
     *  %BPVAL      32          64          Bits per BLISS value (fullword)
     *  %BPUNIT     8           8           Bits per smallest addressable unit
     *  %BPADDR     32          64          Bits per address value
     *  %UPVAL      4           8           Addressable units per BLISS value
     *                                      (%BPVAL / %BPUNIT)
     *  -------     ------      ------      ----------------------------------
     */
    class LiteralDeclAST : public BindDeclAST
    {
    };

    /*
     * external-literal-declaration --- EXTERNAL LITERAL external-literal-item, ...;
     *
     * external-literal-item --- literal-name -+- : literal-attribute
     *                                         +- nothing
     */
    class ExternLiteralDeclAST : public BindDeclAST
    {
    };

    /*
     * bind-data-declaration -+- BIND -+- bind-data-item, ...;
     *
     * bind-data-item --- bind-data-name = data-name-value -+- : bind-data-attribute...
     *                                                      +- nothing
     *
     * bind-data-name --- name
     *
     * bind-data-value --- expression
     *
     *                      +- allocation-unit
     *                      |  extension-attribute
     * bind-data-attribute -+  structure-attribute
     *                      |  field-attribute
     *                      |  volatile-attribute
     *                      +- weak-attribute
     */
    class BindDataDeclAST : public BindDeclAST
    {
    };

    /*
     * bind-routine-declaration -+- BIND ROUTINE --------+- bind-routine-item, ...;
     *                           +- GLOBAL BIND ROUTINE -+
     *
     * bind-routine-item --- bind-routine-name = routine-name-value -+- : bind-routine-attribute...
     *                                                               +- nothing
     *
     * bind-routine-name --- name
     *
     * routine-name-value --- expression
     *
     *                         +- novalue-attribute
     * bind-routine-attribute -+  linkage-attribute
     *                         +- weak-attribute
     */
    class BindRoutineDeclAST : public BindDeclAST
    {
    };
}

#endif /* LLVM_BLISS_BINDINGAST_H */
