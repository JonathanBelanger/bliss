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

#include "bliss/Lexer/Token.h"

using namespace llvm;
using namespace bliss;

/* gettok - Return the next token from standard input. */
static int Token::gettok()
{
    static int LastChar = ' ';

    /*  Skip any whitespace. */
    while (isspace(LastChar))
    {
        LastChar = getchar();
    }

    if (isalpha(LastChar)) /*  identifier: [a-zA-Z][a-zA-Z0-9]* */
    {
        IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
        {
            IdentifierStr += LastChar;
        }

        if (IdentifierStr == "def")
        {
            return tok_def;
        }
        if (IdentifierStr == "extern")
        {
            return tok_extern;
        }
        if (IdentifierStr == "if")
        {
            return tok_if;
        }
        if (IdentifierStr == "then")
        {
            return tok_then;
        }
        if (IdentifierStr == "else")
        {
            return tok_else;
        }
        if (IdentifierStr == "for")
        {
            return tok_for;
        }
        if (IdentifierStr == "in")
        {
            return tok_in;
        }
        if (IdentifierStr == "binary")
        {
            return tok_binary;
        }
        if (IdentifierStr == "unary")
        {
            return tok_unary;
        }
        if (IdentifierStr == "var")
        {
            return tok_var;
        }
        return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') /*  Number: [0-9.]+ */
    {
        std::string NumStr;
        do
        {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    if (LastChar == '#')
    {
        /*  Comment until end of line. */
        do
        {
            LastChar = getchar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
        {
            return gettok();
        }
    }

    /*  Check for end of file.  Don't eat the EOF. */
    if (LastChar == EOF)
    {
        return tok_eof;
    }

    /*  Otherwise, just return the character as its ascii value. */
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}
