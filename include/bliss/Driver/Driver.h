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
 * File:   Driver.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 29, 2019, 10:15 AM
 */

#ifndef LLVM_BLISS_DRIVER_H
#define LLVM_BLISS_DRIVER_H

#include "Basic/CommonInclude.h"
#include "Basic/FileManager.h"
#include "FrontEnd/Lexer.h"
#include "FrontEnd/Parser.h"

using namespace std;

namespace bliss
{
    class Driver
    {
        public:

        /**
         * This function is called to return the address of the one and only Driver.
         * If one has not been instantiated, this call will do so.  If one has been
         * instantiated, then the parameter is ignored.  If the parameter is not
         * specified or a nullptr when instantiating the class, then the next call
         * will need to be to setFiles to supply the file names, one or more, to be
         * compiled.
         *
         * @param files - a vector of strings containing zero or more file names to
         *                be compiled.
         * @return A pointer to the Driver class, if successfully created and
         *         initialized.
         */
        static Driver *get(vector<string> *files = nullptr);

        /**
         * This function is called to set the file names to be processed, in order.
         *
         * @param files - the list of files to be compiled
         * @return true - if the files exist and can be read
         *         false - if one or more files does not exist or cannot be read.
         */
        bool setFiles(vector<string> *files);

        /**
         * This function is the one that does all the work.  It loops until it has
         * processed each of the files in the vector of filenames.
         */
        void mainLoop();

        private:

        /* CONSTRUCTORS */
        Driver();                                   // Private constructor
        Driver(Driver const&) = delete;             // Prevent copy constructor
        Driver& operator=(Driver const&) = delete;  // Prevent assignment

        /* DESTRUCTORS */
        ~Driver();

        /* CLASS DATA */
        static Driver *driver;
        FileManager *fileMgr;
        Lexer *lex;
        Parser *parse;
        vector<string> fileNames;
    };
}

#endif /* LLVM_BLISS_DRIVER_H */
