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
 * File:   SpecialAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 28, 2019, 5:46 PM
 */

#ifndef LLVM_BLISS_SPECIALAST_H
#define LLVM_BLISS_SPECIALAST_H

#include "AST/DeclarationAST.h"

using namespace std;

namespace bliss
{

    /*
     * psect-declaration --- PSECT psect-item, ... ;
     *
     * psect-item --- storage-class = psect-name -+- ( psect-attribute, ... )
     *                                            +- nothing
     *
     *                +- OWN
     *                |  GLOBAL
     * storage-class -+  PLIT
     *                |  CODE
     *                +- NODEFAULT
     *
     * psect-name --- name
     *
     *                  +- WRITE | NOWRITE
     *                  |  EXECUTE | NOEXECUTE
     *                  |  OVERLAY | NOOVERLAY
     *                  |  READ | NOREAD
     * psect-attribute -+  SHARE | NOSHARE
     *                  |  PIC | NOPIC
     *                  |  LOCAL | GLOBAL
     *                  |  VECTOR
     *                  |  alignment-attribute
     *                  +- addressing-mode-attribute
     */
    class PsectDeclAST : public DeclarationAST
    {
    };

    /*
     * switches-declaration --- SWITCHES switch-item, ... ;
     *
     * switch-item -+- on-off-switch-item
     *              +- special-switch-item
     *
     *                     +- ERRS | NOERRS
     *                     |  OPTIMIZE | NOOPTIMIZE
     * on-off-switch-item -+  SAFE | NOSAFE
     *                     |  UNAMES | NOUNAMES
     *                     +- ZIP | NOZIP
     *
     *                      +- ADDRESSING_MODE ( mode-spec, ... )
     *                      |  LANGUAGE ( language-list )
     * special-switch-item -+  LINKAGE ( linkage-name )
     *                      |  LIST ( list-option, ... )
     *                      +- STRUCTURE -+- ( structure-attribute )
     *                                    +- nothing
     *
     *                +- COMMON
     * language-list -+  language-name
     *                +- nothing
     *
     * language-name -+- BLISS32
     *                +- BLISS64
     *
     * linkage-name --- name
     *
     *              +- SOURCE | NOSOURCE
     *              |  REQUIRE | NOREQUIRE
     *              |  EXPAND | NOEXPAND
     *              |  TRACE | NOTRACE
     * list-option -+  LIBRARY | NOLIBRARY
     *              |  OBJECT | NOOBJECT
     *              |  ASSEMBLY | NOASSEMBLY
     *              |  SYMBOLIC | NOSYMBOLIC
     *              |  BINARY | NOBINARY
     *              +- COMMENTARY | NOCOMMENTARY
     *
     * mode-spec -+- EXTERNAL ----+-- mode
     *            +- NONEXTERNAL -+
     *
     *       +- GENERAL
     * mode -+  ABSOLUTE
     *       |  LONG_RELATIVE
     *       +- WORD_RELATIVE
     */
    class SwitchesDeclAST : public DeclarationAST
    {
    };

    /*
     * built-in-declaration --- BUILTIN built-in-name, ... ;
     *
     * built-in-name --- name
     */
    class BuiltInAST : public DeclarationAST
    {
    };

    /*
     * label-declaration --- LABEL label-name, ... ;
     *
     * label-name --- name
     */
    class LabelAST : public DeclarationAST
    {
    };

    /*
     * undeclare-declaration --- UNDECLARE undeclare-name, ... ;
     *
     * undeclare-name --- name
     */
    class UndeclareAST : public DeclarationAST
    {
    };
}

#endif /* LLVM_BLISS_SPECIALINAST_H */
