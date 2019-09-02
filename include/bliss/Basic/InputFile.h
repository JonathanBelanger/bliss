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
 * File:   InputFile.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 1, 2019, 4:48 PM
 */
#ifndef LLVM_BLISS_INPUTFILE_H
#define LLVM_BLISS_INPUTFILE_H

#include "Basic/CommonInclude.h"
#include "Basic/InputChar.h"

#define INPUT_CHAR_DEPTH 2

using namespace std;

namespace bliss
{

    /*
     * This class is used to read characters from an input file and process them for
     * returning back to the caller (for further processing).
     */
    class InputFile
    {
        public:
            /* CONSTRUCTORS */
            InputFile(string fn);
            InputFile(InputFile const&) = delete;               // Prevent copy constructor
            InputFile& operator=(InputFile const&) = delete;    // Prevent assignment

            /* DESTRUCTOR */
            ~InputFile();

            /* GETTERS */
            
            /**
             * Get the next character from the input file.  This is actually the previous
             * character, as we always read one character ahead from the file.
             *
             *  NOTE: This call is destructive, in that a read in character cannot be 
             *  unread.
             *
             * @return A pointer to an InputChar class.
             */
            InputChar *getNextChar();

            /**
             * Peak at the next character read from the input file that will be returned
             * on the next call to getNetChar().
             *
             *  NOTE: This call is non-destructive, in the successive calls without a
             *  prior call to getNextChar() will return the same character information.
             *
             * @return A pointer to an InputChar class
             */
            InputChar *peakNextChar();

            /**
             * The function is called to return an indicator that the input file was
             * successfully opened.
             *
             * @return A boolean value indicating that the file was successfully opened
             *         (true) or not (false).
             */
            bool getOpened() { return opened; }

            /**
             * This function is called to return an indicator that the end of file has
             * been read in and returned on a call to getNextChar().
             *
             * @return A boolean value indicating that the EOF has been reached and    
             *         processed (true) or not (false).
             */
            bool getEOF() {return atEOF; }

        private:
            /* SETTERS */

            /**
             * This is a private function to read in a character from the input file and
             * determine its Character Classification.
             *
             * @param where - An integer value indicating where in the charVec the next
             *                character information should be saved.
             */
            void initChars(int where);

            /* CLASS DATA */
            ifstream *inputStream;                              // Input file
            std::array<InputChar *, INPUT_CHAR_DEPTH> charVec;  // Character info vector
            bool atEOF;                                         // EOF processed
            bool opened;                                        // File opened
            bool nextLine;                                      // Increment line counter on next read
            int index;                                          // Index for next character
            uint32_t line;                                      // Current line in the file
            uint32_t column;                                    // Current column in the file
            uint32_t offset;                                    // Current offset in the file
    };
}

#endif /* LLVM_BLISS_INPUTFILE_H */
