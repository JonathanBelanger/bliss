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
#include "Basic/InputFile.h"

using namespace std;
using namespace bliss;

/*
 * CONSTRUCTOR
 */
InputFile::InputFile(string fn)
{
    inputStream = new ifstream(fn.c_str());
    opened = inputStream->is_open();
    if (opened)
    {
        index = -1;
        for(int ii = 0; ii < INPUT_CHAR_DEPTH; ii++)
        {
            charVec[ii] = new InputChar;
        }
    }
    return;
}

/*
 * DESTRUCTOR
 */
InputFile::~InputFile()
{
    if (opened)
    {
        inputStream->close();
        for(int ii = 0; ii < INPUT_CHAR_DEPTH; ii++)
        {
            delete charVec[ii];
        }
    }
    return;
}
/**
 * This is a private function to read in a character from the input file and
 * determine its Character Classification.
 *
 * @param where - An integer value indicating where in the charVec the next
 *                character information should be saved.
 */
void InputFile::initChars(int where)
{
    charVec[where]->setChar(inputStream->get());
    if (inputStream->eof() == true)
    {
        charVec[where]->setChar('\0');
        charVec[where]->setClass(InputChar::CCEndOfFile);
    }
    else if (isalpha(charVec[where]->getChar()))
    {
        charVec[where]->setClass(InputChar::CCPrintLetter);
    }
    else if (isdigit(charVec[where]->getChar()))
    {
        charVec[where]->setClass(InputChar::CCPrintDigit);
    }
    else if ((charVec[where]->getChar() == '.') || (charVec[where]->getChar() == '^') ||
             (charVec[where]->getChar() == '*') || (charVec[where]->getChar() == '/') ||
             (charVec[where]->getChar() == '+') || (charVec[where]->getChar() == '-') ||
             (charVec[where]->getChar() == '=') || (charVec[where]->getChar() == ',') ||
             (charVec[where]->getChar() == ';') || (charVec[where]->getChar() == ':') ||
             (charVec[where]->getChar() == '(') || (charVec[where]->getChar() == ')') ||
             (charVec[where]->getChar() == '[') || (charVec[where]->getChar() == ']') ||
             (charVec[where]->getChar() == '<') || (charVec[where]->getChar() == '>'))
    {
        charVec[where]->setClass(InputChar::CCPrintDelim);
    }
    else if ((charVec[where]->getChar() == '$') || (charVec[where]->getChar() == '_') ||
             (charVec[where]->getChar() == '%') || (charVec[where]->getChar() == '!') ||
             (charVec[where]->getChar() == '\''))
    {
        charVec[where]->setClass(InputChar::CCPrintSpecial);
    }
    else if ((charVec[where]->getChar() == '"') || (charVec[where]->getChar() == '&') ||
             (charVec[where]->getChar() == '?') || (charVec[where]->getChar() == '@') ||
             (charVec[where]->getChar() == '\\') || (charVec[where]->getChar() == '`') ||
             (charVec[where]->getChar() == '{') || (charVec[where]->getChar() == '|') ||
             (charVec[where]->getChar() == '}') || (charVec[where]->getChar() == '~'))
    {
        charVec[where]->setClass(InputChar::CCPrintFree);
    }
    else if (charVec[where]->getChar() == ' ')
    {
        charVec[where]->setClass(InputChar::CCNonprintSP);
    }
    else if (charVec[where]->getChar() == 0x09)
    {
        charVec[where]->setClass(InputChar::CCNonprintHT);
    }
    else if (charVec[where]->getChar() == 0x0b)
    {
        charVec[where]->setClass(InputChar::CCLinemarkVT);
    }
    else if (charVec[where]->getChar() == 0x0c)
    {
        charVec[where]->setClass(InputChar::CCLinemarkFF);
    }
    else if (charVec[where]->getChar() == 0x0a)
    {
        charVec[where]->setClass(InputChar::CCLinemarkLF);
    }
    else if (charVec[where]->getChar() == 0x0d)
    {
        charVec[where]->setClass(InputChar::CCLinemarkCR);
    }
    else
    {
        charVec[where]->setClass(InputChar::CCUnknown);
    }
    return;
}
            
/**
 * Get the next character from the input file.  This is actually the previous
 * character, as we always read one character ahead from the file.
 *
 *  NOTE: This call is destructive, in that a read in character cannot be 
 *  unread.
 *
 * @return A pointer to an InputChar class.
 */
InputChar *InputFile::getNextChar()
{
    int retIndex = index;

    if ((opened == true) && (atEOF == false))
    {
        if (retIndex == -1)
        {
            int ii;

            for(ii = 0; ii < INPUT_CHAR_DEPTH; ii++)
            {
                initChars(ii);
            }
            retIndex = 0;
            index = 1;
        }
        else if (charVec[retIndex]->getClass() != InputChar::CCEndOfFile)
        {
            index++;
            index %= INPUT_CHAR_DEPTH;
            initChars(index);
        }
    }
    if (charVec[retIndex]->getClass() == InputChar::CCEndOfFile)
    {
        atEOF = true;
    }
    return charVec[retIndex];
}

/**
 * Peak at the next character read from the input file that will be returned
 * on the next call to getNetChar().
 *
 *  NOTE: This call is non-destructive, in the successive calls without a
 *  prior call to getNextChar() will return the same character information.
 *
 * @return A pointer to an InputChar class
 */
InputChar *InputFile::peakNextChar()
{
    return charVec[index];
}
