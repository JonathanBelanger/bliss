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
 * File:   Lister.h
 * Author: Jonathan D. Belanger
 *
 * Created on October 6, 2019, 10:02 AM
 */

/*
 * This header file should not be included by itself.  It should only be included
 * in CommonInclude.  Check that this is the case.  Otherwise, generate an error.
 */
#ifndef ALLOW_LISTER_INCLUDE
#error "Lister.h should never be included directly."
#endif

#ifndef LLVM_BLISS_LISTER_H
#define LLVM_BLISS_LISTER_H

using namespace std;

namespace bliss
{
    class Lister
    {

        /**
         * This function is called to return the address of the one and only Lister.
         * If one has not been instantiated, this call will do so.  If one has been
         * instantiated, then it is just returned.
         *
         * @return A pointer to the Parser class.
         */
        static Lister *get()
        {
            if (list == nullptr)
            {
                list = new Lister();
            }
            return list;
        }

        /**
         * Open a listing file.  This must be done before any input files are read,
         * if we are generating a listing.  There is only 1 listing file for each
         * input file specified on the command line.  REQUIRE files may be output
         * in a listing file, but in the listed file for the top most parent input
         * file containing the REQUIRE statement.
         *
         * @param listingFile - a string specifying the listing file to be written.
         * @return true - the listing file has been successfully opened for write.
         *         false - a failure occurred when attempting to open the listing
         *                 file for write.
         */
        bool open(string listingFile);

        /**
         * This function is called to increment the depth.  The depth is incremented
         * when starting a new block.
         */
        void incrDepth() { depth++; return; };

        /**
         * This function is called to decrement the depth.  The depth is decremented
         * when ending a block.
         */
        void decrDepth() { depth++; return; };

        /**
         * This function is called to add a new character to the end of the current
         * listingLine.
         *
         * TODO: Need to determine when to move to the next line in the listing file.
         *
         * @param c - An ASCII character value to be added to the listing file.
         */
        void addChar(char c);

        private:

        /* CONSTRUCTORS */
        Lister()                                    // Private constructor
        {
            depth = 0;
            currentLine = currentColumn = 0;
            listingLine.assign("");
            return;
        };
        Lister(Lister const&) = delete;             // Prevent copy constructor
        Lister& operator=(Lister const&) = delete;  // Prevent assignment

        /* DESTRUCTORS */
        ~Lister(){};

        /* CLASS DATA */
        static Lister *list;
        ofstream listingStream;
        uint32_t depth;
        uint32_t currentLine;
        uint32_t currentColumn;
        string listingLine;
    };
}

#endif /* LLVM_BLISS_LISTER_H */
