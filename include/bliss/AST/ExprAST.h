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
 * File:   ExprAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 14, 2019, 2:42 PM
 */

#ifndef LLVM_BLISS_EXPRAST_H
#define LLVM_BLISS_EXPRAST_H

using namespace std;

namespace bliss
{
    typedef struct
    {
        uint32_t startLine;
        uint32_t startColumn;
        uint32_t endLine;
        uint32_t endColumn;
    } SourceLocation;
    typedef struct
    {
        uint32_t dsc_l_length;
        uint16_t dsc_w_type;
        uint16_t dsc_w_class;
        char *dsc_a_pointer;
    } ASCID;

    /*
     * ExprAST - Base class for all expression nodes.
     *
     *              +- primary
     *  expression -+  operator-expression
     *              |  executable-function
     *              +- control-expression
     */
    class ExprAST
    {
        public:
        virtual ~ExprAST() {}

        /**
         * This function is called to return the location information for the
         * AST Node.
         *
         * @return - a pointer to a structure containing the starting/ending
         *           line/column numbers.
         */
        SourceLocation *getLocation() { return &Loc; }

        private:
        SourceLocation Loc;
    };
}

#endif /* LLVM_BLISS_EXPRAST_H */
