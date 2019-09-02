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
            char getChar() { return inChar; }

            /**
             * This function is called to get the line number from where the
             * character was read.
             * 
             * @return ASCII coded character
             */
            uint32_t getLine() { return inLine; }

            /**
             * This function is called to get the column number from where the
             * character was read.
             * 
             * @return ASCII coded character
             */
            uint32_t getColumn() { return inColumn; }

            /**
             * This function is called to get the offset from start of file
             * where the character was read.
             * 
             * @return ASCII coded character
             */
            uint32_t getOffset() { return inOffset; }

            /**
             * This function is called to get the character class associated with the
             * character read from the file.
             *
             * @return An enumeration specifying the character class
             */
            CharClass getClass() { return inCharClass; }

            /* SETTERS */

            /**
             * This function is called to save information about the character read
             * from the file.
             *
             * @param nextChar - ASCII coded character
             * @param nextCharClass - the Character Classification for nextChar
             * @param line - line in the file where nextChar was read
             * @param column - column (offset from start of line) in the file where
             *                 nextChar was read
             * @param offset - offset, from start of file, where the nextChar was read
             */
            void setCharInfo(char nextChar,
                             CharClass nextCharClass,
                             uint32_t line,
                             uint32_t column,
                             uint32_t offset)
            {
                inChar = nextChar;
                inCharClass = nextCharClass;
                inLine = line;
                inColumn = column;
                inOffset = offset;
            }

            /* CONSTRUCTORS */
            InputChar(){};
            InputChar(InputChar const&) = delete;               // Prevent copy constructor
            InputChar& operator=(InputChar const&) = delete;    // Prevent assignment

            /* DESTRUCTORS */
            ~InputChar(){};

        private:
            /* CLASS DATA */
            char inChar;            // ASCII coded character read from the file.
            CharClass inCharClass;  // Character classification enumeration
            uint32_t inLine;
            uint32_t inColumn;
            uint32_t inOffset;
    };
}

#endif /* LLVM_BLISS_INPUTCHAR_H */
