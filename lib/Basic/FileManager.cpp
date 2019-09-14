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
#include "Basic/FileManager.h"

using namespace std;
using namespace bliss;

/**
 * This function is called to open a file and push it onto the stack.
 *
 * @param fileName - The file to be opened
 * @return - true if a file was successfully opened and pushed onto the stack
 *         - false is there was an error opening the file.
 */
bool FileManager::pushFile(std::string fileName)
{
    InputFile *in = new InputFile(fileName);
    bool retVal;

    if (in->getOpened())
    {
        files.push_back(in);
        retVal = true;
    }
    else
    {
        delete in;
        in = nullptr;
        retVal = false;
    }

    return retVal;
}

/**
 * This function is called to pop off a file from the stack and delete the
 * InputFile (closing the file).
 *
 * @return - true if a file was successfully popped off the stack and closed.
 *         - false if there were no more files to be popped off the stack.
 */
bool FileManager::popFile()
{
    bool retVal = false;

    /*
     * If there is anything else on the stack, then pop it off and close it.
     * Set the return to true.
     */
    if (files.size() > 0)
    {
        InputFile *file = files.back();
        files.pop_back();
        delete file;
        retVal = true;
    }

    return retVal;
}

/**
 * Get the current file being processed off the top of the list.
 *
 * @return
 */
InputFile *FileManager::getCurrentFile()
{
    InputFile *file = files.back();

    return file;
}
