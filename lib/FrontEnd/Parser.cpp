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
#include "FrontEnd/Parser.h"

using namespace std;
using namespace bliss;

/*
 * The top-level structure is the MODULE, which is terminated by ELUDOM.
 *
 *  module --- MODULE module-head = module-body ELUDOM
 */
void Parser::handleModule()
{
    if (lexer->getNext())             // eat the MODULE
    {
        if (lexer->getType() != Lexer::LTExplicitDeclared)
        {
            cerr << "Expected module-name\n";
            return;
        }
        auto module = handleModuleHead();

        if (module)
        {
            auto block = handleModuleBody();
            cerr << "Parsed a MODULE...ELUDOM\n";
        }
        else
        {
            cerr << "Failed to parse a MODULE\n";
        }
    }
    else
    {
        cerr << "Unexpected end-of-file\n";
    }
    return;
}

/*
 * This function is responsible for parsing the module-head.
 *
 *  module-head --- module-name -+- ( module-switch, ... )
 *                               +- nothing
 *
 *  @return pointer to ModuleAST.
 */
std::unique_ptr<ModuleAST> Parser::handleModuleHead()
{
    while (true)
    {
        Lexer::LexemeType type = lexer->getType();

        if ((type == Lexer::LTTrailingComment) ||
            (type == Lexer::LTEmbeddedComment))
        {
            if (lexer->getNext())
            {
                continue;
            }
            return nullptr;
        }
        else if (type == Lexer::LTExplicitDeclared)
        {
            auto module = llvm::make_unique<ModuleAST>(lexer->getString());
            if (module)
            {

                /*
                 * If moving on to the next lexeme returns an EOF
                 * indicator, then there is nothing more to do here.
                 * Return what we have back to the caller.
                 */
                if (lexer->getNext())                   // eat the module name
                {
                    if ((lexer->getType() == Lexer::LTOperator) &&
                        (lexer->getChar() == '='))
                    {
                        lexer->getNext();               // eat the equal sign
                    }
                    else if ((lexer->getType() == Lexer::LTPunctuation) &&
                             (lexer->getChar() == '('))
                    {
                        cout << "Need to process module switches\n";
                    }
                    else
                    {
                        cerr << "Unexpected lexical, " << lexer->getType() << "\n";
                    }
                }
                return std::move(module);
            }
            else
            {
                cerr << "Failed to allocate a MODULE AST\n";
                return nullptr;
            }
        }
        else
        {
            cerr << "Expected module-name\n";
            return nullptr;
        }
    }
}

/*
 * This function is responsible for parsing the module-body
 *
 *  module-body --- block
 *
 * @return pointer to BlockAST.
 */
std::unique_ptr<BlockAST> Parser::handleModuleBody()
{
    while(true)
    {
        switch (lexer->getType())
        {
            case Lexer::LTEmbeddedComment:
            case Lexer::LTTrailingComment:
                break;

            case Lexer::LTPunctuation:
                if (lexer->getChar() == '(')
                {
                    cout << "Got open parenthesis '('\n";
                    return handleBlock();
                }
                else
                {
                    cerr << "Got unexpected punctuation, " << lexer->getChar() << "\n";
                }
                break;

            case Lexer::LTKeyword:
                switch (lexer->getKeyword())
                {
                    case KWD::BEGIN:
                    cout << "Got BEGIN\n";
                        return handleBlock();

                    case KWD::ELUDOM:
                        lexer->getNext();               // eat the ELUDOM
                        return nullptr;

                    default:
                        cout << "Got an unexpected keyword, " << lexer->getString() << "\n";
                        return nullptr;
                }
                break;

            default:
                cout << "Got and unexpected lexical: " << lexer->getType() << "\n";
                return nullptr;
        }
        if (lexer->getNext() == false)
        {
            return nullptr;
        }
    }
}

/*
 * This function is responsible for parsing the block.  A block is either
 * labeled or unlabeled.
 *
 *  block -+- labeled-block
 *         +- unlabeled-block
 *
 * labeled-block --- {label: }... unlabeled-block
 *
 * unlabeled-block -+- BEGIN block-body END
 *                  +- ( block-body )
 */
std::unique_ptr<BlockAST> Parser::handleBlock()
{
    bool beginFound = lexer->getType() == Lexer::LTKeyword;

    if (lexer->getNext())
    {
        cout << "Got the start of the module block\n";
        if (lexer->getType() == Lexer::LTKeyword)
        {
            cout << "Got keyword " << lexer->getString() << "\n";
            if (lexer->getKeyword() == KWD::END)
            {
                lexer->getNext();                       // eat the END
                if (beginFound)
                {
                    return nullptr;
                }
                else
                {
                    cerr << "module block started with ( terminated with END\n";
                }
            }
            else
            {
                cerr << "unexpected keyword found, " << lexer->getString() << "\n";
            }
        }
        else if (lexer->getType() == Lexer::LTPunctuation)
        {
            cout << "Got punctuation '" << lexer->getChar() << "'\n";
            if (lexer->getChar() == ')')
            {
                lexer->getNext();                       // eat the ')'
                if (beginFound)
                {
                    cerr << "module block started with BEGIN terminated with ')'\n";
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {
                cerr << "unexpected punctuation found, '" << lexer->getChar() << "'\n";
            }
        }
        else
        {
            cerr << "unexpected lexeme in module block processing, " << lexer->getType() << "\n";
        }
    }
    else
    {
        cerr << "Unexpected end-of-file detected\n";
    }
    return nullptr;
}
