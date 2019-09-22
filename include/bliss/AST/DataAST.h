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
 * File:   DataAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 22, 2019, 11:56 AM
 */

#ifndef LLVM_BLISS_DATAAST_H
#define LLVM_BLISS_DATAAST_H

#include "AST/DeclarationAST.h"
#include "AST/AttributeAST.h"

using namespace std;

namespace bliss
{

    /*
     *                   +- own-declaration
     *                   |  global-declaration
     *                   |  forward-declaration
     * data-declaration -+  external-declaration
     *                   |  local-declaration
     *                   |  stack-local-declaration
     *                   |  register-declaration
     *                   +- map-declaration
     */
    class DataDeclarationAST : public DeclarationAST
    {
    };

    /*
     * own-declaration --- OWN own-item, ... ;
     *
     * own-item --- own-name -+- : own-attribute...
     *                        +- nothing
     *
     * own-name --- name
     *
     *                +- allocation-unit
     *                |  extension-attribute
     *                |  structure-attribute
     *                |  field-attribute
     * own-attribute -+  alignment-attribute
     *                |  initial-attribute
     *                |  preset-attribute
     *                |  psect-allocation
     *                +- volatile-attribute
     */
    class OwnDeclarationAST : public DataDeclarationAST
    {
    };

    /*
     * global-declaration --- GLOBAL global-item, ... ;
     *
     * global-item --- global-name -+- : global-attribute...
     *                              +- nothing
     *
     * global-name --- name
     *
     *                  +- allocation-unit
     *                  |  extension-attribute
     *                  |  structure-attribute
     *                  |  field-attribute
     * global-attribute-+  alignment-attribute
     *                  |  initial-attribute
     *                  |  preset-attribute
     *                  |  psect-attribute
     *                  |  volatile-attribute
     *                  +- weak-attribute
     */
    class GlobalDeclarationAST : public DataDeclarationAST
    {
    };

    /*
     * forward-declaration --- FORWARD forward-item, ... ;
     *
     * forward-item --- forward-name -+- : forward-attribute
     *                                +- nothing
     *
     * forward-name --- name
     *
     *                    +- allocation-unit
     *                    |  extension-attribute
     *                    |  structure-attribute
     * forward-attribute -+  field-attribute
     *                    |  psect-attribute
     *                    |  volatile-attribute
     *                    +- addressing-mode-attribute
     */
    class ForwardDeclarationAST : public DataDeclarationAST
    {
    };

    /*
     * external-declaration --- EXTERNAL external-item, ... ;
     *
     * external-item --- external-name -+- : external-attribute
     *                                  +- nothing
     *
     * external-name --- name
     *
     *                     +- allocation-unit
     *                     |  extension-attribute
     *                     |  structure-attribute
     * external-attribute -+  field-attribute
     *                     |  psect-attribute
     *                     |  volatile-attribute
     *                     |  addressing-mode-attribute
     *                     +- weak-attribute
     */
    class ExternalDeclarationAST : public DataDeclarationAST
    {
    };

    /*
     * local-declaration --- LOCAL local-item, ... ;
     * stack-local-declaration --- STACKLOCAL local-item, ... ;
     *
     * local-item --- local-name -+- : local-attribute...
     *                            +- nothing
     *
     * local-name --- name
     *
     *                  +- allocation-unit
     *                  |  extension-attribute
     *                  |  structure-attribute
     * local-attribute -+  field-attribute
     *                  |  alignment-attribute
     *                  |  initial-attribute
     *                  |  preset-attribute
     *                  +- volatile-attribute
     */
    class LocalDeclarationAST : public DataDeclarationAST
    {
        private:
        bool stack_local;
    };

    /*
     * register-declaration --- REGISTER register-item, ... ;
     * external-register-declaration --- EXERNAL REGISTER register-item, ... ;
     *
     * register-item --- register-name -+- = register-number -+--+- : register-attribute
     *                                  +- nothing -----------+  +- nothing
     *
     * register-name --- name
     *
     * register-number --- compile-time-constant-expression
     *
     *                     +- allocation-unit
     *                     |  extension-attribute
     * register-attribute -+  structure-attribute
     *                     |  field-attribute
     *                     |  initial-attribute
     *                     +- preset-attribute
     */
    class RegisterDeclarationAST : public DataDeclarationAST
    {
        private:
        bool external;
    };

    /*
     * global-register-declaration --- GLOBAL REGISTER register-item, ... ;
     *
     * register-item --- register-name --- = register-number --+- : register-attribute
     *                                                         +- nothing
     */
    class GlobalRegisterDeclarationAST : public RegisterDeclarationAST
    {
    };

    /*
     * map-declaration --- MAP map-item, ... ;
     *
     * map-item --- map-name : map-attribute
     *
     * map-name --- name
     *
     *                +- allocation-unit
     *                |  extension-attribute
     * map-attribute -+  structure-attribute
     *                |  field-attribute
     *                +- volatile-attribute
     */
    class MapDeclarationAST : public DataDeclarationAST
    {
    };
}

#endif /* LLVM_BLISS_DATAAST_H */
