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
#include "FrontEnd/Lexer.h"

using namespace std;
using namespace bliss;

FileManager* FileManager::fmp = nullptr;
Lexer *Lexer::lex = nullptr;

/*
 * This function is called to test the input file processing and character
 * classification code.
 */
int main(int argc, char** argv)
{
    FileManager *fileMgr = FileManager::get();
    Lexer *lex = Lexer::get();

    if (fileMgr->pushFile("/home/belanger/projects/bliss/tests/lexical/lexfuncs1.bli") ==
            true)
    {
        while(lex->getNext())
        {
            switch(lex->getType())
            {
                case Lexer::LTUnknown:
                    cout << "Got an unknown Lexeme:\n" <<
                            "  c:      " << lex->getChar() << "\n" <<
                            "  string: " << lex->getString() << "\n" <<
                            "  value:  " << lex->getValue() << "\n";
                    break;

                case Lexer::LTKeyword:
                    cout << "Got a keyword:\n" <<
                            "  keyword:  " << lex->getKeyword() << "\n" <<
                            "  reserved: " << (lex->getReserved() ? "True\n" : "False\n") <<
                            "  string:   " << lex->getString() << "\n";
                    break;

                case Lexer::LTPredeclared:
                    cout << "Got a predeclared keyword:\n" <<
                            "  keyword:  " << lex->getKeyword() << "\n" <<
                            "  reserved: " << (lex->getReserved() ? "True\n" : "False\n") <<
                            "  string:   " << lex->getString() << "\n";
                    break;

                case Lexer::LTExplicitDeclared:
                    cout << "Got an explicit declared keyword:\n" <<
                            "  keyword:  " << lex->getKeyword() << "\n" <<
                            "  reserved: " << (lex->getReserved() ? "True\n" : "False\n") <<
                            "  string:   " << lex->getString() << "\n";
                    break;

                case Lexer::LTDecimalLiteral:
                    cout << "Got a decimal literal:\n" <<
                            "  value: " << lex->getValue() << "\n";
                    break;

                case Lexer::LTQuotedString:
                    cout << "Got a quoted string:\n" <<
                            "  value: " << lex->getString() << "\n";
                    break;

                case Lexer::LTOperator:
                    cout << "Got an operator:\n" <<
                            "  char: " << lex->getChar() << "\n";
                    break;

                case Lexer::LTPunctuation:
                    cout << "Got a punctuation:\n" <<
                            "  char: " << lex->getChar() << "\n";
                    break;

                case Lexer::LTLinemark:
                    cout << "Got a line mark:\n";
                    break;

                case Lexer::LTTrailingComment:
                    cout << "Got a trailing comment:\n" <<
                            "  string: " << lex->getString() << "\n";
                    break;

                case Lexer::LTEmbeddedComment:
                    cout << "Got a embedded comment:\n" <<
                            "  string: " << lex->getString() << "\n";
                    break;

                case Lexer::LTPercentSign:
                    cout << "Got a percent sign:\n" <<
                            "  char: " << lex->getChar() << "\n";
                    break;
            }
        }
        fileMgr->popFile();
    }

    return 0;
}
