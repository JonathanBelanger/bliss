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
 * File:   Reader.cpp
 * Author: Jonathan D. Belanger
 *
 *  V01.000 Jonathan D. Belanger    August 31, 2019, 3:02 PM
 *  Initially created.
 *
 *  V01.001 Jonathan D. Belanger    September 1, 2019, 1:55 PM
 *  Introduced the following classes:
 *      InputChar - contains information about a single character, including
 *                  its character class.
 *      InputFile - contains the code to read a single character from a file
 *                  and return it back to the caller.  Also, handles character
 *                  classification and end of file detection.
 *      FileManager - contains the code to be able to open multiple files and
 *                  close them in the reverse order in which they were opened.
 *  The next step will be to move these into their own include and module
 *  files.
 */
#include "Basic/FileManager.h"

using namespace std;
using namespace bliss;

FileManager* FileManager::fmp = NULL;

/*
 * This function is called to test the input file processing and character 
 * classification code.
 */
int main(int argc, char** argv)
{
    FileManager *fileMgr = FileManager::get();
    InputFile *in = nullptr;

    in = fileMgr->pushFile("/home/belanger/projects/bliss/tests/lexical/lexfuncs1.bli");
 
    if (in != nullptr)
    {
        while(!in->getEOF())
        {
            InputChar *c = in->getNextChar();
            if (isprint(c->getChar()))
            {
                cout << "'" << c->getChar() << "' -- ";
            }
            else
            {
                cout << to_string(c->getChar()) << " -- ";
            }
            switch(c->getClass())
            {
                case InputChar::CCPrintLetter:
                    cout << "Letters";
                    break;

                case InputChar::CCPrintDigit:
                    cout << "Digits";
                    break;

                case InputChar::CCPrintDelim:
                    cout << "Delimiters";
                    break;

                case InputChar::CCPrintSpecial:
                    cout << "Special";
                    break;

                case InputChar::CCPrintFree:
                    cout << "Free";
                    break;

                case InputChar::CCNonprintSP:
                    cout << "Blank";
                    break;

                case InputChar::CCNonprintHT:
                    cout << "Tab";
                    break;

                case InputChar::CCLinemarkVT:
                    cout << "Linemark -- VT";
                    break;

                case InputChar::CCLinemarkFF:
                    cout << "Linemark -- FF";
                    break;

                case InputChar::CCLinemarkLF:
                    cout << "Linemark -- LF";
                    break;

                case InputChar::CCLinemarkCR:
                    cout << "Linemark -- CR";
                    break;

                case InputChar::CCEndOfFile:
                    cout << "End Of File";
                    break;

                case InputChar::CCUnknown:
                default:
                    cout << "*** Unknown ***";
                    break;
            }
            cout << "\n";
        }
    }
    fileMgr->popFile();

    return 0;
}
