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
    inputFilename = fn;
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
    char c = inputStream->get();
    InputChar::CharClass cClass;

    if (inputStream->eof() == true)
    {
        c = '\0';
        cClass = InputChar::CCEndOfFile;
    }
    else
    {
        offset++;   // Count every character read, except EOF.

        /*
         * If this is the first character read, set the line and
         * column to 1.  If the last character read was a LF, VT,
         * or FF and the current character is not CR, then increment
         * the line and set the column to 1.  Otherwise, increment
         * the column.
         */
        if (line == 0)
        {
            line = column = 1;
        }
        else if ((nextLine == true) && (c != 0x0d))
        {
            line++;
            column = 1;
            nextLine = false;
        }
        else
        {
            column++;
        }
        nextLine = ((c >= 0x0a) && (c <= 0x0c));
        switch(c)
        {
            /* (Horizontal) Tab */
            case 0x09:
                cClass = InputChar::CCNonprintHT;
                break;

            /* Line Feed */
            case 0x0a:
                cClass = InputChar::CCLinemarkLF;
                break;

             /* Virtical Tab */
            case 0x0b:
                cClass = InputChar::CCLinemarkVT;
                break;

            /* Form Feed */
            case 0x0c:
                cClass = InputChar::CCLinemarkFF;
                break;

            /* Carriage Return */
            case 0x0d:
                cClass = InputChar::CCLinemarkCR;
                break;

            case ' ':
                cClass = InputChar::CCNonprintSP;
                break;

            /* $ _ % ! ' */
            case '!':   case '$':   case '%':   case '\'':  case '_':
                cClass = InputChar::CCPrintSpecial;
                break;

            /* . ^ * / + - = , ; : ( ) [ ] < > */
            case '(':   case ')':   case '*':   case '+':   case ',':
            case '-':   case '.':   case '/':   case ':':   case ';':
            case '<':   case '=':   case '>':   case '[':   case ']':
            case '^':
                cClass = InputChar::CCPrintDelim;
                break;

            /* " & ? @ \ ` { | } ~ */
            case '"':   case '&':   case '?':   case '@':   case '\\':
            case '`':   case '{':   case '|':   case '}':   case '~':
                cClass = InputChar::CCPrintFree;
                break;

            /* A B C ... Z   a b c ... z */
            case 'A':   case 'B':   case 'C':   case 'D':   case 'E':
            case 'F':   case 'G':   case 'H':   case 'I':   case 'J':
            case 'K':   case 'L':   case 'M':   case 'N':   case 'O':
            case 'P':   case 'Q':   case 'R':   case 'S':   case 'T':
            case 'U':   case 'V':   case 'W':   case 'X':   case 'Y':
            case 'Z':   case 'a':   case 'b':   case 'c':   case 'd':
            case 'e':   case 'f':   case 'g':   case 'h':   case 'i':
            case 'j':   case 'k':   case 'l':   case 'm':   case 'n':
            case 'o':   case 'p':   case 'q':   case 'r':   case 's':
            case 't':   case 'u':   case 'v':   case 'w':   case 'x':
            case 'y':   case 'z':
                cClass = InputChar::CCPrintLetter;
                break;

            /* 0 1 2 ... 9 */
            case '0':   case '1':   case '2':   case '3':   case '4':
            case '5':   case '6':   case '7':   case '8':   case '9':
                cClass = InputChar::CCPrintDigit;
                break;

            default:
                cClass = InputChar::CCUnknown;
                break;
        }
    }
    charVec[where]->setCharInfo(c, cClass, line, column, offset);
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

            /*
             * If pushBackChar() was called, then don't bother reading in the
             * next character from the file.  We already have what we need.
             */
            if (pushCalled == false)
            {
                initChars(index);
            }
            else
            {
                pushCalled = false;
            }
        }
        else
        {
            atEOF = true;
        }
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

/**
 * Push back the character just read from the input file that was returned
 * on the call to getNetChar().
 *
 *  NOTE: This call is destructive, in that the read in characters vector
 *  is updated to point to the previously read character.  The character is
 *  already in the stack, we are just resetting the index.
 *
 * @return A pointer to an InputChar class
 */
void InputFile::pushBackChar()
{

    /*
     * If this function was previously called, or no characters have been read
     * in, then don't do anything and just return.
     */
    if ((pushCalled == false) && (index != -1))
    {

        /*
         * If the index is equal to 0, then set it to the maximum.  Otherwise,
         * subtract one and set the pushCalled flag.
         */
        index = (index == 0 ? INPUT_CHAR_DEPTH : index) - 1;
        pushCalled = true;
    }
    return;
}
