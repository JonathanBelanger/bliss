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
 * File:   FileManager.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 1, 2019, 5:00 PM
 */
#ifndef LLVM_BLISS_FILEMANAGER_H
#define LLVM_BLISS_FILEMANAGER_H

#include "Basic/CommonInclude.h"
#include "Basic/InputFile.h"

namespace bliss
{

    /*
     * This class is used to manage all the input files.  As a file is processed, a language
     * keyword may cause another input file to be read in.  This manages these files in
     * a file vector, which has files pushed on and popped off of it.
     *
     * This is a singleton class.  Only one is ever created, and indirectly through the
     * get() method.
     */
    class FileManager
    {
        public:

            /**
             * This function is called to return the address of the one and only FileManager.
             * If one has not been instantiated, this call will do so.
             * @return A pointer to the FileManager class.
             */
            static FileManager *get()
            {
                if (fmp == nullptr)
                {
                    fmp = new FileManager();
                }
                return fmp;
            }

            /* SETTERS */

            /**
             * This function is called to open a file and push it onto the stack.
             *
             * @param fileName - The file to be opened
             * @return A pointer to the InputFile class for this input file, or nullptr
             *         if the file open failed.
             */
            InputFile *pushFile(std::string fileName);

            /**
             * This function is called to pop off a file from the stack and delete the
             * InputFile (closing the file).
             */
            void popFile();

            /* GETTERS */

        private:
            /* CONSTRUCTORS */
            FileManager(){};                                        // Private constructor
            FileManager(FileManager const&) = delete;               // Prevent copy constructor
            FileManager& operator=(FileManager const&) = delete;    // Prevent assignment

            /* DESTRUCTORS */
            ~FileManager(){};

            /* CLASS DATA */
            static FileManager *fmp;        // A pointer to the File Manager
            vector<InputFile *> files;      // A vector of opened files.
    };
}

#endif /* LLVM_BLISS_FILEMANAGER_H */
