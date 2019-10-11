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
 * File:   PrimaryAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 14, 2019, 4:42 PM
 */

#ifndef LLVM_BLISS_PRIMARYAST_H
#define LLVM_BLISS_PRIMARYAST_H

#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{

    /*
     *          +- numeric-literal
     *          |  string-literal
     *          |  plit
     *          |  name
     * primary -+  block
     *          |  structure-reference
     *          |  routine-call
     *          |  field-reference
     *          +- code-comment
     */
    class PrimaryExprAST : public ExprAST
    {
        public:
        virtual ~PrimaryExprAST() {}
    };

    /*
     *                  +- decimal-literal
     * numeric-literal -+  integer-literal
     *                  |  character-code-literal
     *                  +- float-literal
     *
     * decimal-literal --- decimal-digit...
     *
     * decimal-digit --- 0..9
     *
     *                  +- %B -------+
     * integer-literal -+  %O        +- ' opt-sign integer-digit... '
     *                  |  %DECIMAL  |
     *                  +- %X -------+
     *
     *           +- +       (positive)
     * opt-sign -+  -       (negative)
     *           +- nothing (positive)
     *
     * integer-digit --- 0..9 A..F
     *
     * character-coded-literal - %C ' quoted-character '
     *
     *                +- single-precision-float-literal
     * float-literal -+  double-precision-float-literal
     *                |  extended-exponent-double-precision-float-literal
     *                +- extended-exponent-extended-precision-float-literal
     *
     * single-precision-float-literal -+- %E -+- ' mantissa -+- E exponent -+- '
     *                                 +- %T -+              +- nothing ----+
     *
     * double-precision-float-literal -+- %D -+- ' mantissa -+- E exponent -+- '
     *                                 +- %S -+              +- nothing ----+
     *
     * extended-exponent-double-precision-float-literal -+- %G -+- ' mantissa -+- Q exponent -+- '
     *                                                   +- %? -+              +- nothing ----+
     *
     * extended-exponent-extended-precision-float-literal -- %H ' mantissa -+- Q exponent -+- '
     *                                                                      +- nothing ----+
     *
     *                        +- decimal-digits
     * mantissa --- opt-sign -+  decimal-digits .
     *                        |  . decimal-digits
     *                        +- decimal-digits . decimal-digits
     *
     * exponent -- opt-sign decimal-digits
     */
    class NumericLiteral : public PrimaryExprAST
    {
        public:
        NumericLiteral(float TVal) : TVal(TVal) {}
        NumericLiteral(double SVal) : SVal(SVal) {}
        NumericLiteral(long double XVal) : XVal(XVal) {}
        NumericLiteral(uint64_t IVal) : IVal(IVal) {}
        NumericLiteral(char CVal) : CVal(CVal) {}

        private:
        float TVal;
        double SVal;
        long double XVal;
        uint64_t IVal;  // For both decimal- and integer-literals
        char CVal;
    };

    /*
     * string-literal -+- string-type   -+- quoted-string
     *                 +- nothing       -+
     *
     *              +- %ASCII
     *              |  %ASCIZ
     * string-type -+  %ASCIC
     *              |  %ASCID
     *              +- %P
     *
     * quoted-string --- ' quoted-character... '
     *
     *                   +- printing-character-except-apostrophe
     * quoted-character -+  blank
     *                   |  tab
     *                   +- ''  (escape sequence for an apostrophe)
     * printing-character --- ASCII 33 through ASCII 126, inclusive
     * blank --- ASCII 32
     * tab --- ASCII 9
     * apostrophe --- ASCII 39
     */
    class StringLiteral : public PrimaryExprAST
    {
        public:
        StringLiteral(string Str) : Str(Str) {}
        StringLiteral(DSC64_DESCRIPTOR StrDSC) : StrDSC(StrDSC) {}

        private:
        string Str;
        DSC64_DESCRIPTOR StrDSC;
    };

    /*
     *                   +- allocation-unit ---------------- +
     * plit -+- PLIT --+-+  psect-allocation                 +- ( plit-item )
     *       +- UPLIT -+ |  psect-allocation allocation-unit |
     *                   +- nothing -------------------------+
     *
     *                  +- QUAD
     *                  |  LONG
     * allocation-unit -+  WORD
     *                  +- BYTE
     *
     * psect-allocation --- PSECT ( psect-name )
     *
     * psec-name --- name
     *
     *            +- plit-group
     * plit-item -+  plit-expression
     *            +- plit-string
     *
     *             +- allocation-unit -------------------+
     * plit-group -+  REP replicator OF                  +- ( plit-item, ... )
     *             +- REP replicator OF allocation-unit -+
     *
     * replicator --- compile-time-constant-expression
     *
     * plit-expression --- link-time-constant-expression
     *
     * plit-string --- string-literal
     */
    class Plit : public PrimaryExprAST
    {
    };

    /*
     *                        +- + letter
     *       +- letter -----+ |  | digit
     * name -+  dollar      +-+ -+ dollar
     *       +- underscore -+ |  + underscore
     *                        +- nothing
     *
     * letter --- A..Z a..Z
     *
     * digit --- 0..9
     *
     * dollar --- $
     *
     * underscore --- _
     */
    class Name : public PrimaryExprAST
    {
        public:
        Name(string Str) : Str(Str) {}

        private:
        string Str;
    };

    /*
     * block -+- labeled-block
     *        +- unlabeled-block
     *
     * labeled-block --- {label:}... unlabeled-block
     *
     * label --- name
     *
     * unlabeled-block -+- BEGIN block-body END
     *                  +- ( block-body )
     *
     *             +-+- declaration ...
     *             | +- nothing
     *             |
     * block-body -+-+- block-action ...
     *             | +- nothing
     *             |
     *             +-+- block-value
     *               +- nothing
     *
     * block-action --- expression ;
     *
     * block-value --- expression
     */
    class Block : public PrimaryExprAST
    {
    };

    /*
     *                      +- ordinary-structure-reference
     * structure-reference -+  default-structure-reference
     *                      +- general-structure-reference
     *
     * ordinary-structure-reference --- segment-name [ access-actual, ... ]
     *
     * segment-name --- name
     *
     *                +- field-name
     * access-actual -+  expression
     *                +- nothing
     *
     * default-structure-reference --- address [ access-actual, ... ]
     *
     * address -+- primary
     *          +- executable-function
     *
     * general-structure-reference --- structure-name [ access-part -+- ; allocation-actual, ... -+- ]
     *                                                               +- nothing ------------------+
     *
     * access-part --- segment-expression -+- , access-actual
     *                                     +- nothing
     *
     * segment-expression -+- expression
     *                     +- nothing
     */
    class Structure : public PrimaryExprAST
    {
    };

    /*
     * routine-call -+- ordinary-routine-call
     *               +- general-routine-call
     */
    class RoutineAST : public PrimaryExprAST
    {
    };

    /*
     * ordinary-routine-call --- routine-designator ( -+- input-actual-parameter, ... -+--+- ; output-actual-parameter, ... -+- )
     *                                                 +- nothing ---------------------+  +- nothing ------------------------+
     *
     * routine-designator --- primary
     *
     * input-actual-parameter -+- expression
     *                         +- nothing
     *
     * output-actual-parameter -+- expression
     *                          +- nothing
     */
    class OrdinaryRoutineAST : public RoutineAST
    {
    };

    /*
     * general-routine-call --- linkage-name ( routine-address --
     *                              -+- , input-actual-parameter, ... -+--+- ; output-actual-parameter, ... -+- )
     *                               +- nothing -----------------------+  +- nothing ------------------------+
     *
     * routine-address --- expression
     */
    class GeneralRoutineAST : public RoutineAST
    {
    };

    /*
     * field-reference --- address -+- field-selector
     *                              +- nothing
     *
     * field-selector --- < position, size -+- , sign-extension-flag -+- >
     *                                      +- nothing ---------------+
     *
     * position -+- expression
     * size -----+
     *
     * sing-extension-flag --- compile-time-constant-expression
     */
    class Field : public PrimaryExprAST
    {
    };

    /*
     * code-comment --- CODECOMMENT quoted-string,... : block
     */
    class CodeComment : public PrimaryExprAST
    {
        public:
        CodeComment(string Str) : Str(Str) {}

        private:
        string Str;
    };
}

#endif /* LLVM_BLISS_PRIMARYAST_H */
