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
 * File:   Lexemes.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 1, 2019, 5:37 PM
 */
#ifndef LLVM_BLISS_LEXEMES_H
#define LLVM_BLISS_LEXEMES_H

#include "Basic/CommonInclude.h"

using namespace std;
namespace bliss
{
    class Lexeme
    {
        public:
        enum LexemeClassifier
        {
            LCUnknown,
            LCKeywords,
            LCPredeclared,
            LCExplicitDecl,
            LCDecimalLiteral,
            LCQuotedString,
            LCOperators,
            LCPunctuation
        };
    };
}

#endif /* LLVM_BLISS_LEXEMES_H */
