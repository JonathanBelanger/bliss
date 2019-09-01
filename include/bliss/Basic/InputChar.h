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
 * File:   InputChar.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 1, 2019, 4:37 PM
 */
#ifndef LLVM_BLISS_INPUTCHAR_H
#define LLVM_BLISS_INPUTCHAR_H

#include "Basic/CommonInclude.h"

namespace bliss
{
    
    /*
     * This class is used to store information about a character read in from an input file.
     */
    class InputChar
    {
        public:

            /*
             * This enumeration is used to classify the characters read in from the file.
             * This list is based on BLISS LRM Section 2.1.1 (pages 2-1 through 2-2).
             */
            enum CharClass
            {
                CCUnknown,
                CCPrintLetter,
                CCPrintDigit,
                CCPrintDelim,
                CCPrintSpecial,
                CCPrintFree,
                CCNonprintSP,
                CCNonprintHT,
                CCLinemarkVT,
                CCLinemarkFF,
                CCLinemarkLF,
                CCLinemarkCR,
                CCEndOfFile
            };

            /* GETTERS */
            
            /**
             * This function is called to get the character read from the file.
             * 
             * @return ASCII coded character
             */
            char getChar() { return c; }

            /**
             * This function is called to get the character class associated with the
             * character read from the file.
             *
             * @return An enumeration specifying the character class
             */
            CharClass getClass() { return cc; }

            /* SETTERS */
            
            /**
             * This function is called to save a character read from the file.
             *
             * @param nextChar - ASCII coded character
             */
            void setChar(char nextChar) { c = nextChar; }

            /**
             * This function is called to save the character class for the character
             * read from the file.
             *
             * @param nextCC - Character classification enumeration value
             */
            void setClass(CharClass nextCC) { cc = nextCC; }

            /* CONSTRUCTORS */
            InputChar(){};
            InputChar(InputChar const&) = delete;               // Prevent copy constructor
            InputChar& operator=(InputChar const&) = delete;    // Prevent assignment

            /* DESTRUCTORS */
            ~InputChar(){};

        private:
            /* CLASS DATA */
            char c;             // ASCII coded character read from the file.
            CharClass cc;       // Character classification enumeration
    };
}

#endif /* LLVM_BLISS_INPUTCHAR_H */
