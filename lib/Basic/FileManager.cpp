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
 * @return A pointer to the InputFile class for this input file, or nullptr
 *         if the file open failed.
 */
InputFile *FileManager::pushFile(std::string fileName)
{
    InputFile *retVal = new InputFile(fileName);

    if(retVal->getOpened())
    {
        files.push_back(retVal);
    }
    else
    {
        delete retVal;
        retVal = nullptr;
    }

    return retVal;
}

/**
 * This function is called to pop off a file from the stack and delete the
 * InputFile (closing the file).
 */
void FileManager::popFile()
{
    InputFile *file = files.back();
    files.pop_back();
    delete file;
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
