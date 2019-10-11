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
#include "Driver/Driver.h"
#include "Basic/FileManager.h"
#include "FrontEnd/Lexer.h"
#include "FrontEnd/Parser.h"

using namespace std;
using namespace bliss;

FileManager* FileManager::fmp = nullptr;
Lexer *Lexer::lex = nullptr;
Parser *Parser::parse = nullptr;

/* CONSTRUCTOR */
Driver::Driver()
{
    fileNames.erase(fileNames.begin(), fileNames.end());
    fileMgr = FileManager::get();
    lex = Lexer::get();
    parse = Parser::get(lex);
    return;
}

/* DESTRUCTOR */
Driver::~Driver()
{
    return;
}

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
 * @return A pointer to the Driver class.
 */
Driver *Driver::get(vector<string> *files)
{

    /*
     * If we have not set the pointer to the driver class, then go and
     * try to create one now.
     */
    if (driver == nullptr)
    {
        driver = new Driver();

        /*
         * If we successfully set the pointer to the new driver class,
         * and one or more files were supplied on the call, then set
         * the files to be compiled.
         */
        if ((driver != nullptr) && (files != nullptr) && (files->size() > 0))
        {

            /*
             * If any of the files do not exist, or any of them do not
             * allow reading, then destroy the driver class we just
             * created and return a nullptr to the caller.
             */
            if (driver->setFiles(files) == false)
            {
                delete driver;
                Driver::driver = nullptr;
                driver = nullptr;

            }
        }
    }
    return driver;
}

/**
 * This function is called to set the file names to be processed, in order.
 *
 * @param files - the list of files to be compiled
 * @return true - if the files exist and can be read
 *         false - if one or more files does not exist or cannot be read.
 */
bool Driver::setFiles(vector<string> *files)
{
    bool retVal = true;

    /*
     * If no files were discovered, then there is nothing more to do.
     */
    if ((files == nullptr) || (files->size() == 0))
    {
        cerr << "%BLISS-F-NOFILESPEC, No files were specified to be compiled\n";
        retVal = false;
    }

    /*
     * OK, we have what appears to be a vector of file names.  Let's check them out.
     */
    else
    {
        struct stat statBuf;
        string errorStr;
        bool firstError = true;     // We have not written out any errors, yet.
        bool foundError = false;    // We have not found an error on a file, yet.
        bool checkErrno = false;    // We do not have an error value in errno, yet.

        /*
         * Iterate through each file in the vector.
         */
        for (vector<string>::iterator it = files->begin(); it != files->end(); ++it)
        {
            errorStr = "BLISS-E-";      // Set the error message prefix.

            /*
             * Check the status of the file.  If this errors, we'll convert errno to
             * an error message.
             */
            if (stat(it->c_str(), &statBuf) < 0)
            {
                retVal = false;
                foundError = true;
                checkErrno = true;
            }

            /*
             * OK, the file appears to exist, let's look at it a bit deeper.
             */
            else
            {

                /*
                 * If it is not a regular file, then generate the error string.
                 * There is nothing more to do with this file.
                 */
                if (S_ISREG(statBuf.st_mode) == false)
                {
                    retVal = false;
                    foundError = true;
                    errorStr.append("REGFILE, File is not a regular file, ").append(*it);
                }

                /*
                 * OK, the file exists and it is a regular file, see if we have read
                 * access to it.  If not, we'll convert errno to an error message.
                 */
                else if (access(it->c_str(), R_OK) < 0)
                {
                    retVal = false;
                    foundError = true;
                    checkErrno = true;
                }
            }

            /*
             * We got an error from either stat() or access().  Determine which one it was
             */
            if (checkErrno == true)
            {
                switch(errno)
                {
                    case EACCES:
                        errorStr.append("NOACCESS, Access to the file, or search permissions ")
                                .append("is denied for ").append(*it);
                        break;

                    case ELOOP:
                        errorStr.append("TOOMANYSYM, Too many symbolic links encountered ")
                                .append("while traversing the path, ").append(*it);
                        break;

                    case ENAMETOOLONG:
                        errorStr.append("TOOLONG, ").append(*it).append(" is too long");
                        break;

                    case ENOENT:
                    case ENOTDIR:
                        errorStr.append("PATHERR, A component of file path, ").append(*it)
                                .append(", does not exist, or is an empty string.");
                        break;

                    default:
                        errorStr.append("UNKFILERR, Unknown file error, ").append(*it);
                        break;
                }
            }
            if (foundError == true)
            {
                string firstChar;

                if (firstError == true)
                {
                    firstChar = "%";
                    firstError = false;
                }
                else
                {
                    firstChar = "-";
                }
                cerr << firstChar << errorStr << "\n";
                foundError = false;
            }

            /*
             * OK, we have a good file.
             */
            else
            {
                fileNames.push_back(*it);
            }
        }
    }

    /*
     * If we are returning an indicator that there was an issue with one or more of
     * the files, then cleanup the fileNames vector.
     */
    if (retVal == false)
    {
        while (fileNames.empty() == false)
        {
            vector<string>::iterator it = fileNames.begin();

            fileNames.erase(it);
        }
    }
    return retVal;
}

/**
 * This function is the one that does all the work.  It loops until it has
 * processed each of the files in the vector of filenames.
 */
void Driver::mainLoop()
{

    /*
     * Loop through each of the files, in order.
     */
    for (vector<string>::iterator it = fileNames.begin(); it != fileNames.end(); ++it)
    {

        /*
         * push the file onto the FileManager's file vector.  If successful, begin
         * compiling.
         */
        if (fileMgr->pushFile(*it) == true)
        {
            while(lex->getNext())
            {
                switch (lex->getType())
                {
                    case Lexer::LTUnknown:
                        cout << "Not expecting Unknown\n";
                        break;

                    case Lexer::LTKeyword:
                        switch (lex->getKeyword())
                        {
                            case KWD::MODULE:
                                parse->handleModule();
                                break;

                            default:
                                cout << "Not expecting a Keyword " << lex->getString() << "\n";
                                break;
                        }
                        break;

                    case Lexer::LTPredeclared:
                        cout << "Not expecting a Predeclared\n";
                        break;

                    case Lexer::LTExplicitDeclared:
                        cout << "Not expecting an Explicit Declared\n";
                        break;

                    case Lexer::LTDecimalLiteral:
                        cout << "Not expecting a Decimal Literal\n";
                        break;

                    case Lexer::LTQuotedString:
                        cout << "Not expecting a Quoted String\n";
                        break;

                    case Lexer::LTOperator:
                        cout << "Not expecting an Operator\n";
                        break;

                    case Lexer::LTPunctuation:
                        cout << "Not expecting a Punctuation\n";
                        break;

                    case Lexer::LTLinemark:
                        cout << "Not expecting a Line Mark\n";
                        break;

                    case Lexer::LTTrailingComment:
                    case Lexer::LTEmbeddedComment:
                        break;

                    case Lexer::LTPercentSign:
                        cout << "Not expecting a Percent Sign\n";
                        break;
                }
            }
            fileMgr->popFile();
        }
        else
        {
            cerr << "Unable to add file, " << *it << ", to the files to be compiled\n";
            break;
        }
    }
    return;
}
