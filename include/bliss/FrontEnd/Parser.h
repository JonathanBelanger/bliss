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
 * File:   Parser.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 14, 2019, 12:23 PM
 */

#ifndef LLVM_BLISS_PARSER_H
#define LLVM_BLISS_PARSER_H

#include "Basic/CommonInclude.h"
#include "Basic/FileManager.h"
#include "FrontEnd/Keyword.h"
#include "FrontEnd/Lexer.h"
#include "AST/ExprAST.h"
#include "AST/PrimaryAST.h"
#include "AST/OperatorAST.h"
#include "AST/ExecutableFuncAST.h"
#include "AST/ControlAST.h"
#include "AST/ModuleAST.h"
#include "AST/BlockAST.h"

using namespace std;

namespace bliss
{
    class Parser
    {
        public:

        /**
         * This function is called to return the address of the one and only Parser.
         * If one has not been instantiated, this call will do so.  If one has been
         * instantiated, then it is just returned.
         *
         * @param lex - A pointer to the lexer that will be used.
         * @return A pointer to the Parser class.
         */
        static Parser *get(Lexer *lex)
        {
            if (parse == nullptr)
            {
                parse = new Parser(lex);
            }
            return parse;
        }

        /*
         * The top-level structure is the MODULE, which is terminated by ELUDOM.
         */
        void handleModule();
        std::unique_ptr<ModuleAST> handleModuleHead();
        std::unique_ptr<BlockAST> handleModuleBody();
        std::unique_ptr<BlockAST> handleBlock();

        private:

        /* CONSTRUCTORS */
        Parser(Lexer *lex)                          // Private constructor
        {
            lexer = lex;
            return;
        };
        Parser(Parser const&) = delete;             // Prevent copy constructor
        Parser& operator=(Parser const&) = delete;  // Prevent assignment

        /* DESTRUCTORS */
        ~Parser(){};

        /* CLASS DATA */
        static Parser *parse;
        Lexer *lexer;
    };
}

#endif /* LLVM_BLISS_PARSER_H */
