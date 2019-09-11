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
#include "Lexer/Lexer.h"

using namespace std;
using namespace bliss;

KeywordTable keywords[] =
{
    _KWD_TABLE(ALLOCATION, Lexer::LTKeyword, true),
    _KWD_TABLE(ASCIC, Lexer::LTKeyword, true),
    _KWD_TABLE(ASCID, Lexer::LTKeyword, true),
    _KWD_TABLE(ASCII, Lexer::LTKeyword, true),
    _KWD_TABLE(ASCIZ, Lexer::LTKeyword, true),
    _KWD_TABLE(ASSIGN, Lexer::LTKeyword, true),
    _KWD_TABLE(B, Lexer::LTKeyword, true),
    _KWD_TABLE(BLISS, Lexer::LTKeyword, true),
    _KWD_TABLE(BLISS32, Lexer::LTKeyword, true),
    _KWD_TABLE(BLISS64, Lexer::LTKeyword, true),
    _KWD_TABLE(BPADDR, Lexer::LTKeyword, true),
    _KWD_TABLE(BPUNIT, Lexer::LTKeyword, true),
    _KWD_TABLE(BPVAL, Lexer::LTKeyword, true),
    _KWD_TABLE(C, Lexer::LTKeyword, true),
    _KWD_TABLE(CHAR, Lexer::LTKeyword, true),
    _KWD_TABLE(CHARCOUNT, Lexer::LTKeyword, true),
    _KWD_TABLE(COUNT, Lexer::LTKeyword, true),
    _KWD_TABLE(CTCE, Lexer::LTKeyword, true),
    _KWD_TABLE(DECIMAL, Lexer::LTKeyword, true),
    _KWD_TABLE(DECLARED, Lexer::LTKeyword, true),
    _KWD_TABLE(ELSE, Lexer::LTKeyword, true),
    _KWD_TABLE(ERROR, Lexer::LTKeyword, true),
    _KWD_TABLE(ERRORMACRO, Lexer::LTKeyword, true),
    _KWD_TABLE(EXACTSTRING, Lexer::LTKeyword, true),
    _KWD_TABLE(EXITITERATION, Lexer::LTKeyword, true),
    _KWD_TABLE(EXITMACRO, Lexer::LTKeyword, true),
    _KWD_TABLE(EXPAND, Lexer::LTKeyword, true),
    _KWD_TABLE(EXPLODE, Lexer::LTKeyword, true),
    _KWD_TABLE(FI, Lexer::LTKeyword, true),
    _KWD_TABLE(FIELDEXPAND, Lexer::LTKeyword, true),
    _KWD_TABLE(IDENTICAL, Lexer::LTKeyword, true),
    _KWD_TABLE(IF, Lexer::LTKeyword, true),
    _KWD_TABLE(INFORM, Lexer::LTKeyword, true),
    _KWD_TABLE(ISSTRING, Lexer::LTKeyword, true),
    _KWD_TABLE(LENGTH, Lexer::LTKeyword, true),
    _KWD_TABLE(LTCE, Lexer::LTKeyword, true),
    _KWD_TABLE(MESSAGE, Lexer::LTKeyword, true),
    _KWD_TABLE(NAME, Lexer::LTKeyword, true),
    _KWD_TABLE(NBITS, Lexer::LTKeyword, true),
    _KWD_TABLE(NBITSU, Lexer::LTKeyword, true),
    _KWD_TABLE(NULL, Lexer::LTKeyword, true),
    _KWD_TABLE(NUMBER, Lexer::LTKeyword, true),
    _KWD_TABLE(O, Lexer::LTKeyword, true),
    _KWD_TABLE(P, Lexer::LTKeyword, true),
    _KWD_TABLE(PRINT, Lexer::LTKeyword, true),
    _KWD_TABLE(QUOTE, Lexer::LTKeyword, true),
    _KWD_TABLE(QUOTENAME, Lexer::LTKeyword, true),
    _KWD_TABLE(REF, Lexer::LTKeyword, true),
    _KWD_TABLE(REMAINING, Lexer::LTKeyword, true),
    _KWD_TABLE(REMOVE, Lexer::LTKeyword, true),
    _KWD_TABLE(REQUIRE, Lexer::LTKeyword, true),
    _KWD_TABLE(S, Lexer::LTKeyword, true),
    _KWD_TABLE(SBTTL, Lexer::LTKeyword, true),
    _KWD_TABLE(SIZE, Lexer::LTKeyword, true),
    _KWD_TABLE(STRING, Lexer::LTKeyword, true),
    _KWD_TABLE(SWITCHES, Lexer::LTKeyword, true),
    _KWD_TABLE(T, Lexer::LTKeyword, true),
    _KWD_TABLE(THEN, Lexer::LTKeyword, true),
    _KWD_TABLE(TITLE, Lexer::LTKeyword, true),
    _KWD_TABLE(UNQUOTE, Lexer::LTKeyword, true),
    _KWD_TABLE(UPVAL, Lexer::LTKeyword, true),
    _KWD_TABLE(VARIANT, Lexer::LTKeyword, true),
    _KWD_TABLE(WARN, Lexer::LTKeyword, true),
    _KWD_TABLE(X, Lexer::LTKeyword, true),
    KWD_TABLE(ABS,Lexer::LTPredeclared, false),
    KWD_TABLE(ABSOLUTE, Lexer::LTKeyword, false),
    KWD_TABLE(ACTUALCOUNT, Lexer::LTPredeclared, true),
    KWD_TABLE(ACTUALPARAMETER, Lexer::LTPredeclared, true),
    KWD_TABLE(ADDRESSING_MODE, Lexer::LTKeyword, true),
    KWD_TABLE(ALIGN, Lexer::LTKeyword, true),
    KWD_TABLE(ALWAYS, Lexer::LTKeyword, true),
    KWD_TABLE(AND, Lexer::LTKeyword, true),
    KWD_TABLE(ARGPTR, Lexer::LTPredeclared, true),
    KWD_TABLE(ASSEMBLY, Lexer::LTKeyword, false),
    KWD_TABLE(BEGIN, Lexer::LTKeyword, true),
    KWD_TABLE(BINARY, Lexer::LTKeyword, false),
    KWD_TABLE(BIND, Lexer::LTKeyword, true),
    KWD_TABLE(BIT, Lexer::LTKeyword, true),
    KWD_TABLE(BITVECTOR, Lexer::LTPredeclared, false),
    KWD_TABLE(BLISS, Lexer::LTPredeclared, false),
    KWD_TABLE(BLISS32, Lexer::LTKeyword, false),
    KWD_TABLE(BLISS64, Lexer::LTKeyword, false),
    KWD_TABLE(BLOCK, Lexer::LTPredeclared, false),
    KWD_TABLE(BLOCKVECTOR, Lexer::LTPredeclared, false),
    KWD_TABLE(BUILTIN, Lexer::LTKeyword, true),
    KWD_TABLE(BY, Lexer::LTKeyword, true),
    KWD_TABLE(BYTE, Lexer::LTKeyword, true),
    KWD_TABLE(CALL, Lexer::LTKeyword, false),
    KWD_TABLE(CASE, Lexer::LTKeyword, true),
    KWD_TABLE(CH$A_RCHAR, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$A_WCHAR, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$ALLOCATION, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$COMPARE, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$COPY, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$DIFF, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$EQL, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$FAIL, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$FILL, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$FIND_CH, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$FIND_NOT_CH, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$FIND_SUB, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$GEQ, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$GTR, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$LEQ, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$LSS, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$MOVE, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$NEQ, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$PLUS, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$PTR, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$RCHAR, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$RCHAR_A, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$SIZE, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$TRANSLATE, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$TRANSTABLE, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$WCHAR, Lexer::LTPredeclared, false),
    KWD_TABLE(CH$WCHAR_A, Lexer::LTPredeclared, false),
    KWD_TABLE(CODE, Lexer::LTKeyword, false),
    KWD_TABLE(CODECOMMENT, Lexer::LTKeyword, true),
    KWD_TABLE(COMMENTARY, Lexer::LTKeyword, false),
    KWD_TABLE(COMPILETIME, Lexer::LTKeyword, true),
    KWD_TABLE(CONCATENATE, Lexer::LTKeyword, false),
    KWD_TABLE(DEBUG, Lexer::LTKeyword, false),
    KWD_TABLE(DECR, Lexer::LTKeyword, true),
    KWD_TABLE(DECRA, Lexer::LTKeyword, true),
    KWD_TABLE(DECRU, Lexer::LTKeyword, true),
    KWD_TABLE(DO, Lexer::LTKeyword, true),
    KWD_TABLE(ELSE, Lexer::LTKeyword, true),
    KWD_TABLE(ELUDOM, Lexer::LTKeyword, true),
    KWD_TABLE(ENABLE, Lexer::LTKeyword, true),
    KWD_TABLE(END, Lexer::LTKeyword, true),
    KWD_TABLE(EQL, Lexer::LTKeyword, true),
    KWD_TABLE(EQLA, Lexer::LTKeyword, true),
    KWD_TABLE(EQLU, Lexer::LTKeyword, true),
    KWD_TABLE(EQV, Lexer::LTKeyword, true),
    KWD_TABLE(ERRS, Lexer::LTKeyword, false),
    KWD_TABLE(EXECUTE, Lexer::LTKeyword, false),
    KWD_TABLE(EXITLOOP, Lexer::LTKeyword, true),
    KWD_TABLE(EXPAND, Lexer::LTKeyword, false),
    KWD_TABLE(EXTERNAL, Lexer::LTKeyword, true),
    KWD_TABLE(FIELD, Lexer::LTKeyword, true),
    KWD_TABLE(FORWARD, Lexer::LTKeyword, true),
    KWD_TABLE(FROM, Lexer::LTKeyword, true),
    KWD_TABLE(GENERAL, Lexer::LTKeyword, false),
    KWD_TABLE(GEQ, Lexer::LTKeyword, true),
    KWD_TABLE(GEQA, Lexer::LTKeyword, true),
    KWD_TABLE(GEQU, Lexer::LTKeyword, true),
    KWD_TABLE(GLOBAL, Lexer::LTKeyword, true),
    KWD_TABLE(GTR, Lexer::LTKeyword, true),
    KWD_TABLE(GTRA, Lexer::LTKeyword, true),
    KWD_TABLE(GTRU, Lexer::LTKeyword, true),
    KWD_TABLE(IDENT, Lexer::LTKeyword, false),
    KWD_TABLE(IF, Lexer::LTKeyword, true),
    KWD_TABLE(INCR, Lexer::LTKeyword, true),
    KWD_TABLE(INCRA, Lexer::LTKeyword, true),
    KWD_TABLE(INCRU, Lexer::LTKeyword, true),
    KWD_TABLE(INITIAL, Lexer::LTKeyword, true),
    KWD_TABLE(INRANGE, Lexer::LTKeyword, true),
    KWD_TABLE(INTERRUPT, Lexer::LTKeyword, false),
    KWD_TABLE(IOPAGE, Lexer::LTKeyword, true),
    KWD_TABLE(IOT, Lexer::LTKeyword, false),
    KWD_TABLE(JSB, Lexer::LTKeyword, false),
    KWD_TABLE(KEYWORDMACRO, Lexer::LTKeyword, true),
    KWD_TABLE(LABEL, Lexer::LTKeyword, true),
    KWD_TABLE(LANGUAGE, Lexer::LTKeyword, false),
    KWD_TABLE(LEAVE, Lexer::LTKeyword, true),
    KWD_TABLE(LEQ, Lexer::LTKeyword, true),
    KWD_TABLE(LEQA, Lexer::LTKeyword, true),
    KWD_TABLE(LEQU, Lexer::LTKeyword, true),
    KWD_TABLE(LIBRARY, Lexer::LTKeyword, true),
    KWD_TABLE(LINKAGE, Lexer::LTKeyword, true),
    KWD_TABLE(LIST, Lexer::LTKeyword, false),
    KWD_TABLE(LITERAL, Lexer::LTKeyword, true),
    KWD_TABLE(LOCAL, Lexer::LTKeyword, true),
    KWD_TABLE(LONG, Lexer::LTKeyword, true),
    KWD_TABLE(LONG_RELATIVE, Lexer::LTKeyword, false),
    KWD_TABLE(LSS, Lexer::LTKeyword, true),
    KWD_TABLE(LSSA, Lexer::LTKeyword, true),
    KWD_TABLE(LSSU, Lexer::LTKeyword, true),
    KWD_TABLE(MACRO, Lexer::LTKeyword, true),
    KWD_TABLE(MAIN, Lexer::LTKeyword, false),
    KWD_TABLE(MAP, Lexer::LTKeyword, true),
    KWD_TABLE(MAX, Lexer::LTPredeclared, false),
    KWD_TABLE(MAXA, Lexer::LTPredeclared, false),
    KWD_TABLE(MAXU, Lexer::LTPredeclared, false),
    KWD_TABLE(MIN, Lexer::LTPredeclared, false),
    KWD_TABLE(MINA, Lexer::LTPredeclared, false),
    KWD_TABLE(MINU, Lexer::LTPredeclared, false),
    KWD_TABLE(MOD, Lexer::LTKeyword, true),
    KWD_TABLE(MODULE, Lexer::LTKeyword, true),
    KWD_TABLE(NEQ, Lexer::LTKeyword, true),
    KWD_TABLE(NEQA, Lexer::LTKeyword, true),
    KWD_TABLE(NEQU, Lexer::LTKeyword, true),
    KWD_TABLE(NOASSEMBLY, Lexer::LTKeyword, false),
    KWD_TABLE(NOBINARY, Lexer::LTKeyword, false),
    KWD_TABLE(NOCODE, Lexer::LTKeyword, false),
    KWD_TABLE(NOCOMMENTARY, Lexer::LTKeyword, false),
    KWD_TABLE(NODEBUG, Lexer::LTKeyword, false),
    KWD_TABLE(NODEFAULT, Lexer::LTKeyword, false),
    KWD_TABLE(NOERRS, Lexer::LTKeyword, false),
    KWD_TABLE(NOEXECUTE, Lexer::LTKeyword, false),
    KWD_TABLE(NOEXPAND, Lexer::LTKeyword, false),
    KWD_TABLE(NOLIBRARY, Lexer::LTKeyword, false),
    KWD_TABLE(NONEXTERNAL, Lexer::LTKeyword, false),
    KWD_TABLE(NOOBJECT, Lexer::LTKeyword, false),
    KWD_TABLE(NOOPTIMIZE, Lexer::LTKeyword, false),
    KWD_TABLE(NOPIC, Lexer::LTKeyword, false),
    KWD_TABLE(NOPRESERVE, Lexer::LTKeyword, false),
    KWD_TABLE(NOREAD, Lexer::LTKeyword, false),
    KWD_TABLE(NOREQUIRE, Lexer::LTKeyword, false),
    KWD_TABLE(NOSAFE, Lexer::LTKeyword, false),
    KWD_TABLE(NOSHARE, Lexer::LTKeyword, false),
    KWD_TABLE(NOSOURCE, Lexer::LTKeyword, false),
    KWD_TABLE(NOSYMBOLIC, Lexer::LTKeyword, false),
    KWD_TABLE(NOT, Lexer::LTKeyword, true),
    KWD_TABLE(NOTRACE, Lexer::LTKeyword, false),
    KWD_TABLE(NOTUSED, Lexer::LTKeyword, false),
    KWD_TABLE(NOUNAMES, Lexer::LTKeyword, false),
    KWD_TABLE(NOVALUE, Lexer::LTKeyword, true),
    KWD_TABLE(NOWRITE, Lexer::LTKeyword, false),
    KWD_TABLE(NOZIP, Lexer::LTKeyword, false),
    KWD_TABLE(NULLPARAMETER, Lexer::LTPredeclared, true),
    KWD_TABLE(OBJECT, Lexer::LTKeyword, false),
    KWD_TABLE(OF, Lexer::LTKeyword, true),
    KWD_TABLE(OPTIMIZE, Lexer::LTKeyword, false),
    KWD_TABLE(OPTLEVEL, Lexer::LTKeyword, false),
    KWD_TABLE(OR, Lexer::LTKeyword, true),
    KWD_TABLE(OTHERWISE, Lexer::LTKeyword, true),
    KWD_TABLE(OUTRANGE, Lexer::LTKeyword, true),
    KWD_TABLE(OVERLAY, Lexer::LTKeyword, false),
    KWD_TABLE(OWN, Lexer::LTKeyword, true),
    KWD_TABLE(PIC, Lexer::LTKeyword, false),
    KWD_TABLE(PLIT, Lexer::LTKeyword, true),
    KWD_TABLE(PRESERVE, Lexer::LTKeyword, false),
    KWD_TABLE(PRESET, Lexer::LTKeyword, true),
    KWD_TABLE(PSECT, Lexer::LTKeyword, true),
    KWD_TABLE(READ, Lexer::LTKeyword, false),
    KWD_TABLE(RECORD, Lexer::LTKeyword, true),
    KWD_TABLE(REF, Lexer::LTKeyword, true),
    KWD_TABLE(REP, Lexer::LTKeyword, true),
    KWD_TABLE(REQUIRE, Lexer::LTKeyword, true),
    KWD_TABLE(RETURN, Lexer::LTKeyword, true),
    KWD_TABLE(ROUTINE, Lexer::LTKeyword, true),
    KWD_TABLE(SAFE, Lexer::LTKeyword, false),
    KWD_TABLE(SELECT, Lexer::LTKeyword, true),
    KWD_TABLE(SELECTA, Lexer::LTKeyword, true),
    KWD_TABLE(SELECTONE, Lexer::LTKeyword, true),
    KWD_TABLE(SELECTONEA, Lexer::LTKeyword, true),
    KWD_TABLE(SELECTONEU, Lexer::LTKeyword, true),
    KWD_TABLE(SELECTU, Lexer::LTKeyword, true),
    KWD_TABLE(SET, Lexer::LTKeyword, true),
    KWD_TABLE(SETUNWIND, Lexer::LTPredeclared, false),
    KWD_TABLE(SHARE, Lexer::LTKeyword, false),
    KWD_TABLE(SHOW, Lexer::LTKeyword, true),
    KWD_TABLE(SIGN, Lexer::LTPredeclared, false),
    KWD_TABLE(SIGNAL, Lexer::LTPredeclared, false),
    KWD_TABLE(SIGNAL_STOP, Lexer::LTPredeclared, false),
    KWD_TABLE(SIGNED, Lexer::LTKeyword, true),
    KWD_TABLE(SOURCE, Lexer::LTKeyword, false),
    KWD_TABLE(STACKLOCAL, Lexer::LTKeyword, true),
    KWD_TABLE(STANDARD, Lexer::LTKeyword, false),
    KWD_TABLE(STRUCTURE, Lexer::LTKeyword, true),
    KWD_TABLE(SWITCHES, Lexer::LTKeyword, true),
    KWD_TABLE(SYMBOLIC, Lexer::LTKeyword, false),
    KWD_TABLE(TES, Lexer::LTKeyword, true),
    KWD_TABLE(THEN, Lexer::LTKeyword, true),
    KWD_TABLE(TO, Lexer::LTKeyword, true),
    KWD_TABLE(TRACE, Lexer::LTKeyword, false),
    KWD_TABLE(UNAMES, Lexer::LTKeyword, false),
    KWD_TABLE(UNDECLARE, Lexer::LTKeyword, true),
    KWD_TABLE(UNSIGNED, Lexer::LTKeyword, true),
    KWD_TABLE(UNTIL, Lexer::LTKeyword, true),
    KWD_TABLE(UPLIT, Lexer::LTKeyword, true),
    KWD_TABLE(VECTOR, Lexer::LTPredeclared, false),
    KWD_TABLE(VERSION, Lexer::LTKeyword, false),
    KWD_TABLE(VOLATILE, Lexer::LTKeyword, true),
    KWD_TABLE(WEAK, Lexer::LTKeyword, true),
    KWD_TABLE(WHILE, Lexer::LTKeyword, true),
    KWD_TABLE(WITH, Lexer::LTKeyword, true),
    KWD_TABLE(WORD, Lexer::LTKeyword, true),
    KWD_TABLE(WORD_RELATIVE, Lexer::LTKeyword, false),
    KWD_TABLE(XOR, Lexer::LTKeyword, true),
    KWD_TABLE(ZIP, Lexer::LTKeyword, false)
};

/* CONSTRUCTOR */
Lexer::Lexer(KeywordTable *kwt, size_t kwtSize)
{

    /*
     * Set the pointer to the keyword table.  This will be used to process the
     * input files.
     */
    table = kwt;
    tableSize = kwtSize;
    return;
}

/**
 * This function is called to move to the next lexeme in the current
 * input file.  The previous lexeme information is overwritten and
 * no longer available.
 *
 *  NOTE: Calling this function may get to an end of file prior to
 *        completely reading in the next lexeme.  The function will
 *        select a reasonable lexeme type and return with a true.
 *        The next call will return the false value.
 *
 * @return true - if a lexeme was successfully read in
 *         false - if an end of file was reached (file fully
 *                 processed).
 */
bool
Lexer::getNext()
{
    FileManager *fileMgr = FileManager::get();
    InputFile *in = fileMgr->getCurrentFile();
    InputChar *c;
    InputChar::CharClass cc;
    bool done = in->getEOF();
    bool retVal = false;
    bool started = false;

    /*
     * We are starting out and need to get to the first non-space character.
     */
    while (!done && !started)
    {
        c = in->peakNextChar();
        cc = c->getClass();
        switch (cc)
        {

            /*
             * All the following are non-space characters.
             */
            case InputChar::CCPrintLetter:
            case InputChar::CCPrintDigit:
            case InputChar::CCPrintDelim:
            case InputChar::CCPrintSpecial:
            case InputChar::CCPrintFree:
                started = true;
                break;

            /*
             * An end-of-file at this point means that we are all done.
             * Process the end-of-file and indicate that we are all done in
             * here.
             */
            case InputChar::CCEndOfFile:
                c = in->getNextChar();
                done = true;
                break;

            /*
             * Everything else is a space character.
             */
            default:
                c = in->getNextChar();
                break;
        }
    }

    /*
     * We either got to the first non-space character or end-of-file.  If the
     * former, then start the processing to get the next lexeme.  If the
     * latter, then there is nothing else to process.  The value of retVal
     * already indicates that we are at the end of file (false).
     */
    if (!done)
    {

        /*
         * Let's take a look at the first character and decide where we go from
         * here.
         *
         * NOTE: At this point, end-of-file is not possible.
         */
        c = in->peakNextChar();
        cc = c->getClass();
        switch (cc)
        {

            // This is the start of a keyword
            case InputChar::CCPrintLetter:

                /*
                 * The keyword parser expects to find the first character of
                 * the keyword to be in the valueChar location.  We do this
                 * because keywords starting with a '%' are processed below
                 * and require looking at more than just the next character.
                 */
                c = in->getNextChar();
                valueChar = c->getChar();
                retVal = parseKeyword(in);
                break;

            // This is the start of a decimal literal
            case InputChar::CCPrintDigit:
                retVal = parseDecimalLiteral(in);
                break;

            /*
             * This is the start of one of the following:
             *  - operator
             *  - punctuation mark
             */
            case InputChar::CCPrintDelim:
                c = in->getNextChar();
                switch (c->getChar())
                {
                    case '.':
                    case '^':
                    case '*':
                    case '/':
                    case '+':
                    case '-':
                    case '=':
                        valueChar = c->getChar();
                        type = LTOperator;
                        break;

                    default:
                        valueChar = c->getChar();
                        type = LTPunctuation;
                        break;
                }
                retVal = true;
                break;

            /*
             * This is the start of one of the following:
             *  - quoted string
             *  - embedded comment
             *  - end of macro
             *  - start of keyword
             *  - trailing comment
             */
            case InputChar::CCPrintSpecial:
                switch (c->getChar())
                {

                    // Quoted string.
                    case '\'':
                        retVal = parseQuotedString(in);
                        break;

                    /*
                     * One of:
                     *  - the start of embedded comment '%('
                     *  - the end of a macro
                     *  - the start of a keyword
                     */
                    case '%':

                        /*
                         * We have to parse a bit further and look at the
                         * character after the percent, in order to know
                         * with what we are dealing.  Save the '%' in the
                         * valueChar location, the called parsing code or
                         * caller will expect to find it there.
                         */
                        c = in->getNextChar();
                        valueChar = c->getChar();
                        c = in->peakNextChar();
                        cc = c->getClass();

                        /*
                         * If the next character after the '%' is a letter,
                         * or dollar-sign '$', or underscore '_', then we
                         * have a keyword.
                         */
                        if ((cc == InputChar::CCPrintLetter) ||
                            ((cc == InputChar::CCPrintSpecial) &&
                             ((c->getChar() == '$') ||
                              (c->getChar() == '_'))))
                        {
                            retVal = parseKeyword(in);
                        }

                        /*
                         * If the next character after the '%' is an open
                         * parenthesis, then we have the start of an
                         * embedded comment.
                         */
                        else if ((cc == InputChar::CCPrintDelim) &&
                                 (c->getChar() == '('))
                        {
                            retVal = parseEmbeddedComment(in);
                        }

                        /*
                         * If the next character after the '%' is anything
                         * else, including end-of-file, then return the
                         * implementation specific indication that the
                         * lexeme is a percent sign.  The code processing
                         * the lexemes will know what to do with this.
                         */
                        else
                        {
                            type = LTPercentSign;
                            retVal = true;
                        }
                        break;

                    // Keyword
                    case '$':
                    case '_':

                        /*
                         * The keyword parser expects to find the first character of
                         * the keyword to be in the valueChar location.  We do this
                         * because keywords starting with a '%' are processed above
                         * and require looking at more than just the next character.
                         */
                        c = in->getNextChar();
                        valueChar = c->getChar();
                        retVal = parseKeyword(in);
                        break;

                    // Trailing comment
                    case '!':
                        retVal = parseTrailingComment(in);
                        break;

                    // Syntax error
                    default:

                        /*
                         * Swallow the next character in hopes that we can
                         * recover and continue parsing.
                         */
                        c = in->getNextChar();
                        cerr << "Syntax error (2) at line " << c->getLine() <<
                                ", column " << c->getColumn() <<
                                " in " << in->getFilename() <<
                                ", unrecognized character, ";
                        if (isprint(c->getChar()))
                        {
                            cerr << "'" << c->getChar() << "'";
                        }
                        else
                        {
                            cerr << to_string(c->getChar());
                        }
                        cerr << "\n";
                        retVal = true;
                        break;
                }
                break;

            // Syntax error
            default:

                /*
                 * Swallow the next character in hopes that we can
                 * recover and continue parsing.
                 */
                c = in->getNextChar();
                cerr << "Syntax error (1) at line " << c->getLine() <<
                        ", column " << c->getColumn() <<
                        " in " << in->getFilename() <<
                        ", unrecognized character, ";
                if (isprint(c->getChar()))
                {
                    cerr << "'" << c->getChar() << "'";
                }
                else
                {
                    cerr << to_string(c->getChar());
                }
                cerr << "\n";
                retVal = true;
                break;
        }
    }

    /*
     * retVal will be set to false if we reached end-of-file.
     */
    return retVal;
}

/**
 * This function is called to dump the contents of the KeywordTable
 * to standard out.
 */
void Lexer::dumpTable()
{
    for (int ii = 0; ii < KWD_MAX; ii++)
    {
        cout << ii <<
                ": " <<
                keywords[ii].keywordStr <<
                "(" <<
                keywords[ii].keyword <<
                ", " <<
                keywords[ii].keywordVal <<
                ", " <<
                (keywords[ii].reserved_builtin ? "True" : "False") <<
                ")\n";
    }
    return;
}

/**
 * This function is called when a keyword Lexeme is being parsed.
 *
 * @param in - InputFile handle
 * @return true - if a lexeme was successfully read in
 *         false - if an end of file was reached (file fully processed).
 */
bool
Lexer::parseKeyword(InputFile *in)
{
    bool retVal = false;
    bool done = false;
    bool lookup = false;
    InputChar *c;
    InputChar::CharClass cc;
    // TODO: We need a string that we can store an all uppercase version of the keyword.

    /*
     * There are three kinds of keyword lexemes.  They are:
     *
     *  LTKeyword
     *  LTPredeclared
     *  LTExplicitDeclared
     *
     * At this point we know we have one of them, but are not sure which.  We
     * extract the lexeme and then look it up in the keyword table to determine
     * which.
     *
     * Additionally, there are reserved and unreserved keywords.  Reserved
     * keywords cannot be used as Explicit Declared.  Unreserved keywords can.
     *
     * Pre-declared keywords are ones created by the compiler.  These can also
     * be replaced by Explicit Declared.
     *
     * TODO: We need to keep track of all Explicitly Declared keywords so that
     *       we can determined which is which when processing keywords.
     *
     * NOTE: When an Unreserved or Predeclared keyword are encountered, it
     *       could be because they are going to be overridden.  Since we are
     *       never sure until it is overridden, this code will return what it
     *       does know for these.  Once overridden, then we can return that
     *       knowledge.
     *
     * At this point, we have no idea what kind of keyword we have.
     */
    valueStr = valueChar;
    while (!done)
    {
        c = in->peakNextChar();
        cc = c->getClass();
        switch (cc)
        {
            case InputChar::CCPrintLetter:
            case InputChar::CCPrintDigit:
                c = in->getNextChar();
                valueStr += c->getChar();
                // TODO: We need to upcase the characer into the all uppercase keyword string
                break;

            case InputChar::CCPrintDelim:
            case InputChar::CCNonprintSP:
            case InputChar::CCNonprintHT:
            case InputChar::CCLinemarkVT:
            case InputChar::CCLinemarkFF:
            case InputChar::CCLinemarkLF:
            case InputChar::CCLinemarkCR:
            case InputChar::CCEndOfFile:
                retVal = done = lookup = true;
                break;

            case InputChar::CCPrintSpecial:
                if ((c->getChar() == '$') ||
                    (c->getChar() == '_'))
                {
                    c = in->getNextChar();
                    valueStr += c->getChar();
                    // TODO: add to the all uppercase keyword string (no need to upcase).
                }
                else if (c->getChar() == '!')
                {
                    retVal = done = lookup = true;
                }
                else if (c->getChar() == '%')
                {
                    c = in->getNextChar();
                    c = in->getNextChar();
                    cc = c->getClass();
                    if ((cc == InputChar::CCPrintDelim) &&
                        (c->getChar() == '('))
                    {
                        in->pushBackChar(); // push back the "%" character.
                        retVal = done = lookup = true;
                    }
                }
                else
                {
                    cerr << "Syntax error (11) at line " << c->getLine() <<
                            ", column " << c->getColumn() <<
                            " in " << in->getFilename() <<
                            ", expected character, ";
                    if (isprint(c->getChar()))
                    {
                        cerr << "'" << c->getChar() << "'";
                    }
                    else
                    {
                        cerr << to_string(c->getChar());
                    }
                    cerr << "\n";
                    retVal = done = true;
                }
                break;

            case InputChar::CCUnknown:
                c = in->getNextChar();
                /* FALLTHROUGH */

            case InputChar::CCPrintFree:
                cerr << "Syntax error (12) at line " << c->getLine() <<
                        ", column " << c->getColumn() <<
                        " in " << in->getFilename() <<
                        ", expected character, ";
                if (isprint(c->getChar()))
                {
                    cerr << "'" << c->getChar() << "'";
                }
                else
                {
                    cerr << to_string(c->getChar());
                }
                cerr << "\n";
                retVal = done = true;
                break;
        }
    }

    /*
     * If we have something to look up in the keyword table, then do so now.
     */
    if (lookup)
    {
        size_t top = 0;
        size_t bottom = tableSize;
        size_t lookingAt = ((bottom - top) / 2) + top;
        bool found = false;

        done = false;
        while(!done)
        {
            // TODO: We need to use the all uppercase keyword string in the compare.
            int cmp = valueStr.compare(table[lookingAt].keywordStr);

            cout << "Comparing " << valueStr << " to " << table[lookingAt].keywordStr;
            if (cmp < 0)
            {
                cout << " less than";
                bottom = lookingAt;
            }
            else if (cmp > 0)
            {
                cout << " greater than";
                top = lookingAt + 1;
            }
            else
            {
                cout << " equal";
                done = found = true;
            }
            lookingAt = ((bottom - top) / 2) + top;
            if (top >= bottom)
            {
                done = true;
            }
        }

        if (found == false)
        {
            type = LTExplicitDeclared;
            keyword = KWD::__MAX_ITEMS;
            reserved = false;
        }
        else
        {
            type = table[lookingAt].keywordVal;
            keyword = table[lookingAt].keyword;
            reserved = table[lookingAt].reserved_builtin;
        }
    }
    return retVal;
}

/**
 * This function is called when a Decimal Literal Lexeme is being parsed.
 *
 * @param in - InputFile handle
 * @return true - if a lexeme was successfully read in
 *         false - if an end of file was reached (file fully processed).
 */
bool
Lexer::parseDecimalLiteral(InputFile *in)
{
    bool retVal = false;
    bool done = false;
    InputChar *c;
    InputChar::CharClass cc;
    uint64_t tmpValue;

    /*
     * Decimal literals have the form of:
     *  0
     *  23000
     *
     * One or more spaces must appear between two lexemes if each lexeme is any
     * one of the following:
     *  - A name
     *  - A keyword
     *  - A decimal-literal
     * This rule requires the use of spaces wherever two lexemes would
     * otherwise merge to form a single, longer lexeme.
     *
     * Either way, we know we are returning a decimal literal.
     */
    type = LTDecimalLiteral;
    c = in->getNextChar();
    tmpValue = value = '0' - c->getChar();
    while (!done)
    {
        c = in->peakNextChar();
        cc = c->getClass();
        switch (cc)
        {
            case InputChar::CCPrintDigit:
                c = in->getNextChar();
                tmpValue = (value * 10) + '0' - c->getChar();
                if (tmpValue < value)
                {
                    cerr << "Syntax error (7) at line " << c->getLine() <<
                            ", column " << c->getColumn() <<
                            " in " << in->getFilename() <<
                            ", decimal literal overflow.\n";
                    retVal = done = true;
                }
                value = tmpValue;
                break;

            case InputChar::CCLinemarkCR:
            case InputChar::CCLinemarkFF:
            case InputChar::CCLinemarkLF:
            case InputChar::CCLinemarkVT:
            case InputChar::CCNonprintHT:
            case InputChar::CCNonprintSP:
            case InputChar::CCEndOfFile:
                retVal = done = true;
                break;

            case InputChar::CCPrintLetter:
            case InputChar::CCPrintFree:
            case InputChar::CCPrintDelim:

                /*
                 * Swallow the next character in hopes that we can recover and
                 * continue parsing.  We are not going to consider this done.
                 * Just throw this character away and move on to the next.
                 */
                c = in->getNextChar();
                cerr << "Syntax error (8) at line " << c->getLine() <<
                        ", column " << c->getColumn() <<
                        " in " << in->getFilename() <<
                        ", unrecognized character, ";
                if (isprint(c->getChar()))
                {
                    cerr << "'" << c->getChar() << "'";
                }
                else
                {
                    cerr << to_string(c->getChar());
                }
                cerr << "\n";
                retVal = done = true;
                break;

            case InputChar::CCPrintSpecial:
                if (c->getChar() == '%')
                {
                    c = in->getNextChar();
                    cc = c->getClass();
                    if ((cc == InputChar::CCPrintDelim) &&
                        (c->getChar() == '('))
                    {

                        /*
                         * The character just processed was a `%` and the next
                         * character is a '(', for an embedded comment, push
                         * the '%' back and indicate that we are done.
                         */
                        in->pushBackChar();
                    }
                }
                else if (c->getChar() != '!')
                {

                    /*
                     * Swallow the next character in hopes that we can recover and
                     * continue parsing.  We are not going to consider this done.
                     * Just throw this character away and move on to the next.
                     */
                    c = in->getNextChar();
                    cerr << "Syntax error (9) at line " << c->getLine() <<
                            ", column " << c->getColumn() <<
                            " in " << in->getFilename() <<
                            ", unrecognized character, ";
                    if (isprint(c->getChar()))
                    {
                        cerr << "'" << c->getChar() << "'";
                    }
                    else
                    {
                        cerr << to_string(c->getChar());
                    }
                    cerr << "\n";
                }
                retVal = done = true;
                break;

            case InputChar::CCUnknown:

                /*
                 * Swallow the next character in hopes that we can recover and
                 * continue parsing.  Just throw this character away and
                 * consider ourselves done.
                 */
                c = in->getNextChar();
                cerr << "Syntax error (10) at line " << c->getLine() <<
                        ", column " << c->getColumn() <<
                        " in " << in->getFilename() <<
                        ", unrecognized character, ";
                if (isprint(c->getChar()))
                {
                    cerr << "'" << c->getChar() << "'";
                }
                else
                {
                    cerr << to_string(c->getChar());
                }
                cerr << "\n";
                retVal = done = true;
                break;
        }
    }
    return retVal;
}

/**
 * This function is called when a Quoted String Lexeme is being parsed.
 *
 * @param in - InputFile handle
 * @return true - if a lexeme was successfully read in
 *         false - if an end of file was reached (file fully processed).
 */
bool
Lexer::parseQuotedString(InputFile *in)
{
    bool retVal = false;
    bool done = false;
    bool haveQuote = true;
    InputChar *c = in->getNextChar();  // swallow first single quote
    InputChar::CharClass cc;

    /*
     * The quoted string starts and ends with a single quote character ('), and
     * can contain any character class, except unknown and end-of-file.  While
     * processing, if a single quote is followed by a single quote, then the
     * first quote is dropped, the second quote retained, and the quoted string
     * is not yet ended.  This allows for sequences and return values as
     * follows:
     *
     *  "'He said, ''Go!'''" which equals "He said, 'Go!'"
     *
     *  (double quotes used for clarity)
     *
     * Either way, we know we are returning a quote string.
     */
    type = LTQuotedString;

    /*
     * Loop until we have everything we came looking to get.
     */
    while (!done)
    {
        c = in->peakNextChar();
        cc = c->getClass();
        if (cc == InputChar::CCUnknown)
        {

            /*
             * Swallow the next character in hopes that we can recover and
             * continue parsing.  We are not going to consider this done.
             * Just throw this character away and move on to the next.
             */
            c = in->getNextChar();
            cerr << "Syntax error (3) at line " << c->getLine() <<
                    ", column " << c->getColumn() <<
                    " in " << in->getFilename() <<
                    ", unrecognized character, ";
            if (isprint(c->getChar()))
            {
                cerr << "'" << c->getChar() << "'";
            }
            else
            {
                cerr << to_string(c->getChar());
            }
            cerr << "\n";
        }
        else if (cc == InputChar::CCEndOfFile)
        {

            /*
             * Apparently, the next character is an end-of-file, and we have
             * not completed reading in the quoted string.  Return what we
             * have, as if it were completed.  NOTE: We don't read in the
             * end-of-file here, we'll leave that for later.
             */
            retVal = done = true;
        }
        else
        {

            /*
             * OK, we have something we can use.  If this is a single quote,
             * then we are either done here and can swallow it, or we have an
             * escaped single quote.
             */
            if ((cc == InputChar::CCPrintSpecial) && (c->getChar() == '\''))
            {

                /*
                 * Get the character for processing.
                 */
                c = in->getNextChar();

                /*
                 * If the previous character we processed was a single quote,
                 * then this is an escaped one.  Add it to the quoted string
                 * and clear the haveQuote flag.
                 */
                if (haveQuote)
                {
                    valueStr += c->getChar();
                    haveQuote = false;
                }
                else
                {
                    retVal = done = true;
                }
            }
            else
            {

                /*
                 * Everything else is simply added to the end of the quoted
                 * string.
                 */
                c = in->getNextChar();
                valueStr += c->getChar();
                haveQuote = false;
            }
        }
    }
    return retVal;
}

/**
 * This function is called when a Trailing Comment Lexeme is being parsed.
 *
 * @param in - InputFile handle
 * @return true - if a lexeme was successfully read in
 *         false - if an end of file was reached (file fully processed).
 */
bool
Lexer::parseTrailingComment(InputFile *in)
{
    bool retVal = false;
    bool done = false;
    InputChar *c;
    InputChar::CharClass cc;

    /*
     * A trailing comment is an exclamation character followed by the remainder
     * of the line on which the comment begins.  The end-of-line is determined
     * by a linemark.  A linemark is a line-feed (LF), vertical-tab (VT), or
     * form-feed(FF) and may be preceded or succeeded by a carriage-return
     * (CR).  The linemark combination will be swallowed.  All other characters
     * are added to the comment sting, including the exclamation point (!)
     *
     * Either way, we know we are returning a trailing comment.
     */
    type = LTTrailingComment;

    while (!done)
    {
        c = in->getNextChar();
        cc = c->getClass();

        /*
         * Is it a carriage-return linemark?
         */
        if (cc == InputChar::CCLinemarkCR)
        {
            c = in->peakNextChar(); // look at the next character
            cc = c->getClass();

            /*
             * If it is another of the linemarks, then swallow it as well.
             */
            if ((cc == InputChar::CCLinemarkFF) ||
                (cc == InputChar::CCLinemarkLF) ||
                (cc == InputChar::CCLinemarkVT))
            {
                c = in->getNextChar();
            }
            retVal = done = true;
        }

        /*
         * Is it a form-feed, line-feed, or vertical-tab?
         */
        else if ((cc == InputChar::CCLinemarkFF) ||
                 (cc == InputChar::CCLinemarkLF) ||
                 (cc == InputChar::CCLinemarkVT))
        {
            c = in->peakNextChar(); // look at the next character
            cc = c->getClass();

            /*
             * If it is a carriage-return linemark, then swallow it as well.
             */
            if (cc == InputChar::CCLinemarkCR)
            {
                c = in->getNextChar();
            }
            retVal = done = true;
        }
        else if (cc == InputChar::CCUnknown)
        {

            /*
             * Swallow the next character in hopes that we can recover and
             * continue parsing.  We are not going to consider this done.
             * Just throw this character away and move on to the next.
             */
            c = in->getNextChar();
            cerr << "Syntax error (4) at line " << c->getLine() <<
                    ", column " << c->getColumn() <<
                    " in " << in->getFilename() <<
                    ", unrecognized character, ";
            if (isprint(c->getChar()))
            {
                cerr << "'" << c->getChar() << "'";
            }
            else
            {
                cerr << to_string(c->getChar());
            }
            cerr << "\n";
        }
        else
        {

            /*
             * OK, add this character to the lexeme value string.
             */
            valueStr += c->getChar();

            /*
             * Before we move on, check that the next character is not an
             * end-of-file.  If it is, then we are done.
             */
            c = in->peakNextChar();
            cc = c->getClass();
            if (cc == InputChar::CCEndOfFile)
            {
                retVal = done = true;
            }
        }
    }
    return retVal;
}

/**
 * This function is called when an Embedded Comment Lexeme is being parsed.
 *
 * @param in - InputFile handle
 * @return true - if a lexeme was successfully read in
 *         false - if an end of file was reached (file fully processed).
 */
bool
Lexer::parseEmbeddedComment(InputFile *in)
{
    bool retVal = false;
    bool done = false;
    InputChar *c;
    InputChar::CharClass cc;

    /*
     * An embedded comment, beginning with the character sequence "%(", is
     * terminated by the very next occurrence of the sequence ")%". This means
     * that the embedded comment cannot be nested. Also, the sequence ")%" is a
     * valid though ill-advised form of ending of a macro definition (see
     * Bliss LRM Section 16.2).  Thus an extensive embedded comment could be
     * inadvertently terminated by the occurrence of ")%" in a macro
     * declaration where the ‘‘%’’ character was intended to terminate a macro
     * definition. For these reasons the embedded comment should be used with
     * care. Also, avoid using it to comment out a body of code.
     *
     * Unlike the trailing comment, the first character of the beginning
     * sequence, "%", is in the ValueChar field.  Get it out of there and add
     * it to the valueStr, then proceed to read in characters until the
     * trailing sequence ")%".
     *
     * Either way, we know we are returning an embedded comment.
     */
    type = LTEmbeddedComment;
    valueStr += valueChar;

    /*
     * Also, go get the "(" of the beginning sequence.
     */
    c = in->getNextChar();
    valueStr += c->getChar();

    /*
     * Loop until we see the trailing ")%".
     */
    while (!done)
    {
        c = in->peakNextChar();
        cc = c->getClass();

        /*
         * It is a syntax error if the file ends before the trailing sequence
         * has been processed.  We are not going to process the end-of-file,
         * yet.
         */
        if (cc == InputChar::CCEndOfFile)
        {
            cerr << "Syntax error (5) at line " << c->getLine() <<
                    ", column " << c->getColumn() <<
                    " in " << in->getFilename() <<
                    ", end-of-file detected before embedded comment closed.\n";
            retVal = done = true;
        }
        else if ((cc == InputChar::CCPrintDelim) &&
                 (c->getChar() == ')'))
        {
            c = in->getNextChar();
            valueStr += c->getChar();
            c = in->peakNextChar();
            cc = c->getClass();
            if ((cc == InputChar::CCPrintSpecial) &&
                (c->getChar() == '%'))
            {
                c = in->getNextChar();
                valueStr += c->getChar();
                retVal = done = true;
            }
        }
        else if (cc == InputChar::CCUnknown)
        {

            /*
             * Swallow the next character in hopes that we can recover and
             * continue parsing.  We are not going to consider this done.
             * Just throw this character away and move on to the next.
             */
            c = in->getNextChar();
            cerr << "Syntax error (6) at line " << c->getLine() <<
                    ", column " << c->getColumn() <<
                    " in " << in->getFilename() <<
                    ", unrecognized character, ";
            if (isprint(c->getChar()))
            {
                cerr << "'" << c->getChar() << "'";
            }
            else
            {
                cerr << to_string(c->getChar());
            }
            cerr << "\n";
        }
        else
        {

            /*
             * We don't really care what it is, just get and save it.
             */
            c = in->getNextChar();
            valueStr += c->getChar();
        }
    }
    return retVal;
}
