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
 * File:   Lexer.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 1, 2019, 5:37 PM
 */
#ifndef LLVM_BLISS_LEXEMES_H
#define LLVM_BLISS_LEXEMES_H

#include "Basic/CommonInclude.h"
#include "Basic/FileManager.h"
#include "FrontEnd/Keyword.h"

using namespace std;

namespace bliss
{
    class Lexer
    {
        public:
        enum LexemeType
        {
            LTUnknown = 0,
            LTKeyword,
            LTPredeclared,
            LTExplicitDeclared,
            LTDecimalLiteral,
            LTQuotedString,
            LTOperator,
            LTPunctuation,
            LTLinemark,
            LTTrailingComment,
            LTEmbeddedComment,
            LTPercentSign   // This is not in the LRM, but used to terminate macros
        };

        /**
         * This function is called to return the address of the one and only Lexer.
         * If one has not been instantiated, this call will do so.  If one has been
         * instantiated, then the parameters are ignored.
         *
         * @return A pointer to the Lexer class.
         */
        static Lexer *get()
        {
            if (lex == nullptr)
            {
                lex = new Lexer();
            }
            return lex;
        }

        /* GETTERS */

        /**
         * This function is called to return the LexemeType of the current
         * lexeme being processed.
         *
         * @return One of the LexemeType enumerated values.
         */
        LexemeType
        getType() { return type; }

        /**
         * This function is called to return the KWD::Keyword value for the
         * current lexeme.  This is valid if the LexemeType is either
         * LTKeyword or LTPredeclared.
         *
         * @return One of the KWD::Keyword enumerate values.
         */
        KWD::Keyword
        getKeyword() { return keyword; }

        /**
         * This function is called to return the boolean value for the
         * current keyword being reserved or not.
         *
         * @return true to indicate a reserved keyword
         *         false to indicate not a reserved keyword
         */
        bool
        getReserved() { return reserved; }

        /**
         * This function is called to get the string associated with the
         * current lexeme.  This is valid if the LexemeType is either
         * LTExplicitDeclared Or LTQuotedString.
         *
         * @return A string value for the quoted string.
         */
        string
        getString() { return valueStr; }

        /**
         * This function is called to get the value associated with the current
         * lexeme.  This is valid if the LexemeType is LTDecimalLiteral.
         *
         * @return A 64-bit decimal value.
         */
        uint64_t
        getValue() { return value; }

        /**
         * This function is called to get the character associated with the
         * current lexeme.  This is valid if the LexemeType is either
         * LTOperator or LTPunctuation.
         *
         * @return An ASCII coded character.
         */
        char
        getChar() { return valueChar; }

        /* SETTERS */

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
        getNext();

        /* MISCELLANEOUS */

        /**
         * This function is called to dump the contents of the KeywordTable
         * to standard out.
         */
        void
        dumpTable();

        private:

        /* CONSTRUCTORS */
        Lexer();                                    // Private constructor
        Lexer(Lexer const&) = delete;               // Prevent copy constructor
        Lexer& operator=(Lexer const&) = delete;    // Prevent assignment

        /* DESTRUCTORS */
        ~Lexer(){};

        /**
         * This function is called when a keyword Lexeme is being parsed.
         *
         * @param in - InputFile handle
         * @return true - if a lexeme was successfully read in
         *         false - if an end of file was reached (file fully
         *                 processed).
         */
        bool
        parseKeyword(InputFile *in);

        /**
         * This function is called when a Decimal Literal Lexeme is being
         * parsed.
         *
         * @param in - InputFile handle
         * @return true - if a lexeme was successfully read in
         *         false - if an end of file was reached (file fully
         *                 processed).
         */
        bool
        parseDecimalLiteral(InputFile *in);

        /**
         * This function is called when a Quoted String Lexeme is being parsed.
         *
         * @param in - InputFile handle
         * @return true - if a lexeme was successfully read in
         *         false - if an end of file was reached (file fully
         *                 processed).
         */
        bool
        parseQuotedString(InputFile *in);

        /**
         * This function is called when a Trailing Comment Lexeme is being
         * parsed.
         *
         * @param in - InputFile handle
         * @return true - if a lexeme was successfully read in
         *         false - if an end of file was reached (file fully
         *                 processed).
         */
        bool
        parseTrailingComment(InputFile *in);

        /**
         * This function is called when an Embedded Comment Lexeme is being
         * parsed.
         *
         * @param in - InputFile handle
         * @return true - if a lexeme was successfully read in
         *         false - if an end of file was reached (file fully
         *                 processed).
         */
        bool
        parseEmbeddedComment(InputFile *in);

        /* CLASS DATA */
        static Lexer *lex;
        LexemeType type;
        KWD::Keyword keyword;
        string valueStr;
        uint64_t value;
        char valueChar;
        bool reserved;
        struct _keywordTable *table;
        size_t tableSize;
    };
    typedef struct _keywordTable
    {
        string keywordStr;
        KWD::Keyword keyword;
        Lexer::LexemeType keywordVal;
        bool reserved_builtin;
    } KeywordTable;
}

/*
 * The following macros are used to file in the KeywordTable.  The first
 * field is the name of the keyword, which will be converted to a string.
 * The second field is the KWD::Keyword enumeration associated with the
 * keyword.  The final field is an indicator the a KWD::Keyword is reserved
 * or KWD::Predefined is for a builtin.
 */
#define KWD_TABLE(x, y, z) { #x, KWD::x, y, z }
#define _KWD_TABLE(x, y, z) { string("%" #x), KWD::_##x, y, z }

#endif /* LLVM_BLISS_LEXEMES_H */
