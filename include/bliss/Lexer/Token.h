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
 * File:   Token.h
 * Author: Jonathan D. Belanger
 *
 * Created on August 19, 2019, 12:37 PM
 */

#ifndef LLVM_BLISS_TOKEN_H
#define LLVM_BLISS_TOKEN_H

namespace bliss
{
    enum Tokens
    {
        tok_eof = -1,

        /* commands */
        tok_def = -2,
        tok_extern = -3,

        /* primary */
        tok_identifier = -4,
        tok_number = -5,

        /* control */
        tok_if = -6,
        tok_then = -7,
        tok_else = -8,
        tok_for = -9,
        tok_in = -10,

        /* operators */
        tok_binary = -11,
        tok_unary = -12,

        /* var definition */
        tok_var = -13
    };

    class Token
    {
        private:
        std::string IdentifierStr;
        double NumVal;

        public:
        Token();
        ~Token();
        Tokens gettok();
    };
}

#endif /* LLVM_BLISS_TOKEN_H */

