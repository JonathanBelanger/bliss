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
 * File:   BaseAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 21, 2019, 3:43 PM
 */

#ifndef LLVM_BLISS_BASEAST_H
#define LLVM_BLISS_BASEAST_H

using namespace std;

namespace bliss
{

    /*
     * This structure is to hold the starting and ending line and column
     * information associated with a particular AST node.
     */
    typedef struct
    {
        uint32_t startLine;
        uint32_t startColumn;
        uint32_t endLine;
        uint32_t endColumn;
    } SourceLocation;

    /*
     * These structures define the various layouts of the descriptor structure.
     * The first one is the 32-bit version of the descriptor, and is used when
     * compiling for a 32-bit operating system.  The second one is the 64-bit
     * version, and is used when compiling for a 64-bit operating system.
     */
    typedef struct
    {
        uint16_t dsc_l_length;
        uint8_t dsc_w_type;
        uint8_t dsc_w_class;
        uint32_t dsc_a_pointer;
    } DSC32_DESCRIPTOR;
    typedef struct
    {
        uint32_t dsc_l_length;
        uint16_t dsc_w_dtype;
        uint16_t dsc_w_class;
        uint64_t dsc_a_pointer;
    } DSC64_DESCRIPTOR;

    /*
     * BaseAST - Base class for all other Abstract Syntax Tree classes (ASTs).
     */
    class BaseAST
    {
        public:
        virtual ~BaseAST() {}

        /*
         * This function is called to return the line and column number ranges
         * associated with this AST node.
         *
         * @return - a pointer to a structure containing the starting/ending
         *           line/column numbers associated with the current AST node.
         */
        SourceLocation *getLocation() { return &Loc; }

        private:
        SourceLocation Loc;
    };
}

#endif /* LLVM_BLISS_BASEAST_H */
