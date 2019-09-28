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
 * File:   LexicalAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 28, 2019, 4:09 PM
 */

#ifndef LLVM_BLISS_LEXICALAST_H
#define LLVM_BLISS_LEXICALAST_H

#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{

    /*
     * lexical-expression -+- primitive
     *                     +- non-primitive
     */
    class LexicalExprAST : public ExprAST
    {
    };

    /*
     *            +- delimiter
     *            |  keyword
     * primitive -+  name
     *            |  numeric-literal
     *            +- string-literal
     */
    class PrimitiveLexicalAST : public LexicalExprAST
    {
    };

    /*                 +- lexical-function
     *                 |  lexical-conditional
     *  non-primitive -+  macro-call
     *                 |  require-declaration
     *                 +- library-declaration
     *
     *                                             +- ( lexical-actual-parameter, ... )
     * lexical-function --- lexical-function-name -+  lexeme
     *                                             +- nothing
     *
     * lexical-function-name --- % name
     *
     * lexical-actual-parameter -+- lexeme...
     *                           +- nothing
     *
     * Specific Lexical-Functions
     *
     *  String-Functions:           %STRING         %EXACTSTRING    %CHAR           %CHARCOUNT
     *  Delimiter-Functions:        %EXPLODE        %REMOVE
     *  Name-Functions:             %NAME           %QUOTENAME
     *  Sequence-Test-Functions:    %NULL           %IDENTICAL
     *  Expression-Test-Functions:  %ISSTRING       %CTCE           %LTCE
     *  Bits-Functions:             %NBITSU         %NBITS
     *  Allocation-Functions:       %ALLOCATION     %SIZE
     *  FieldExpand-Function:       %FIELDEXPAND
     *  Calculation-Functions       %ASSIGN         %NUMBER
     *  Compiler-State-Functions:   %DECLARED       %SWITCHES       %BLISS          %VARIANT
     *  Advisory-Functions:         %ERROR          %WARN           %INFORM         %PRINT          %MESSAGE        %ERRORMACRO
     *  Titling-Functions:          %TITLE          %SBTTL
     *  Quote-Functions:            %QUOTE          %UNQUOTE        %EXPAND
     *  Macro-Functions:            %REMAINING      %LENGTH         %COUNT          %EXITITERATION  %EXITMACRO
     *  Require-Function:           %REQUIRE
     */
    class LexicalFunctionAST : public LexicalExprAST
    {
    };

    /*
     * lexical-conditional --- %IF lexical-test %THEN lexical-consequence -+- %ELSE lexical-alternative -+- %FI
     *                                                                     +- nothing -------------------+
     *
     * lexical-test --- compile-time-constant-expression
     *
     * lexical-consequence -+--+- lexeme...
     * lexical-alternative -+  +- nothing
     */
    class LexicalConditionalAST : public LexicalExprAST
    {
    };
}

#endif /* LLVM_BLISS_LEXICALAST_H */
