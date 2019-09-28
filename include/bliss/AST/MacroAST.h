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
 * File:   MacroAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 28, 2019, 4:41 PM
 */

#ifndef LLVM_BLISS_MACROAST_H
#define LLVM_BLISS_MACROAST_H

#include "AST/DeclarationAST.h"
#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{

    /*
     * macro-declaration -+- positional-macro-declaration
     *                    +- keyword-macro-declaration
     *
     * Pre-declared Macros
     *  Name            32-bit          64-bit
     *  %BLISS32[] =    %REMAINING %;   %;
     *  %BLISS64[] =    %;              %REMAINING %;
     */
    class MacroDeclAST : public DeclarationAST
    {
    };

    /*
     * positional-macro-declaration --- MACRO positional-macro-definition, ...;
     *
     *                              +- simple-macro-definition
     * positional-macro-definition -+  conditional-macro-definition
     *                              +- iterative-macro-definition
     *
     * simple-macro-definition --- macro-name -+- ( macro-formal-name, ... ) -+- macro-body %
     *                                         +- nothing --------------------+
     *
     * conditional-macro-definition --- macro-name -+- ( macro-formal-name, ... ) -+- [] = macro-body %
     *                                              +- nothing --------------------+
     *
     * iterative-macro-definition --- macro-name -+- ( fixed-formal-name, ... ) -+- [ iterative-formal-name, ... ] = macro-body %
     *                                            +- nothing --------------------+
     *
     * macro-name ---=----+
     * macro-formal-name  +- name
     * fixed-formal-name -+
     *
     * macro-body -+- lexeme...
     *             +- nothing
     */
    class PositionalMacroDeclAST : public MacroDeclAST
    {
    };

    /*
     * keyword-macro-declaration --- KEYWORDMACRO keyword-macro-definition, ... ;
     *
     * keyword-macro-definition --- macro-name ( keyword-pair, ... ) = macro-body %
     *
     * keyword-pair --- keyword-formal-name -+- = default-actual
     *                                       +- nothing
     *
     * keyword-formal-name --- name
     *
     * default-actual -+- lexeme...
     *                 +- nothing
     */
    class KeywordMacroDeclAST : public MacroDeclAST
    {
    };

    /*
     * macro-call -+- positional-macro-call
     *             +- keyword-macro-call
     */
    class MacroCallAST : public ExprAST
    {
    };

    /*                                       +- ( macro-actuals )
     * positional-macro-call --- macro-name -+  [ macro-actuals ]
     *                                       |  < macro-actuals >
     *                                       +- nothing
     *
     * macro-actuals -+- macro-actual-parameter, ...
     *                +- nothing
     *
     * macro-actual-parameter -+- lexeme ...
     *                         +- nothing
     */
    class PositionalMacroCallAST : public MacroCallAST
    {
    };

    /*                                    +- ( keyword-assignments )
     * keyword-macro-call --- macro-name -+  [ keyword-assignments ]
     *                                    +  < keyword-assignments >
     *
     * keyword-assignments -+- keyword-assignment, ...
     *                      +- nothing
     *
     * keyword-assignment --- keyword-formal-name = macro-actual-parameter
     */
    class KeywordMacroCallAST : public MacroCallAST
    {
    };
}

#endif /* LLVM_BLISS_MACROAST_H */
