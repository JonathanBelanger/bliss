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
 * File:   StructureAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 22, 2019, 1:02 PM
 */

#ifndef LLVM_BLISS_STRUCTUREAST_H
#define LLVM_BLISS_STRUCTUREAST_H

#include "AST/DeclarationAST.h"

using namespace std;

namespace bliss
{

    /*
     * field-reference --- address -+- field-selector
     *                              +- nothing
     *
     * address -+- primary
     *          +- executable-function
     *
     * field-selector --- < position , size -+- , sign-extension-flag -+- >
     *                                       +- nothing ---------------+
     *
     * position -+- expression
     * size -----+
     *
     * sign-extension-flag --- compile-time-constant-expression
     */
    class FieldReferenceAST : public DeclarationAST
    {
    };

    /*
     * structure-declaration --- STRUCTURE structure-definition, ... ;
     *
     * structure-definition -- structure-name [ -+- access-formal -+--+- : allocation-formal -+- ] =
     *                                           +- nothing -------+  +- nothing -------------+
     *
     *                              -+- [ structure-size ] -+- structure-body
     *                               +- nothing ------------+
     *
     * allocation-formal --- allocation-name -+- = allocation default
     *                                        +- nothing
     *
     * structure-size -+- expression
     * structure-body -+
     *
     * structure-name --+
     * access-formal    +- name
     * allocation-name -+
     *
     * allocation-default -- compile-time-constant-expression
     */
    class StructureDeclarationAST : public DeclarationAST
    {
    };

    /*
     * field-declaration --- FIELD -+- field-set-definition -+- , ... ;
     *                              +- field-definition -----+
     *
     * field-set-definition --- field-set-name = SET field-definition, ... TES
     *
     * field-definition --- field-name = [ field-component, ... ]
     *
     * field-set-name -+- name
     * field-name -----+
     *
     * field-component --- compile-time-constant-expression
     */
    class FieldDeclarationAST : public DeclarationAST
    {
    };

    /*
     *                      +- ordinary-structure-reference
     * structure-reference -+  default-structure-reference
     *                      +- general-structure-reference
     *
     * ordinary-structure-reference --- segment-name [ access-actual, ... ]
     *
     * segment-name --- name
     *
     *                +- field-name
     * access-actual -+  expression
     *                +- nothing
     */
    class OrdinaryStructReferenceAST : public DeclarationAST
    {
    };

    /*
     * default-structure-reference --- address [ access-actual, ... ]
     */
    class DefaultStructReferenceAST : public DeclarationAST
    {
    };

    /*
     * general-structure-reference --- structure-name [ access-part -+- : allocation-actual, ... -+- ]
     *                                                               +- nothing ------------------+
     *
     * access-part --- segment-expression -+- , access-actual, ...
     *                                     +- nothing
     *
     * segment-expression -+- expression
     *                     +- nothing
     */
    class GeneralStructReferenceAST : public DeclarationAST
    {
    };

    /*
     * Predeclared Structures
     *
     * VECTOR       - A vector of signed or unsigned elements of uniform size (BYTE, WORD, LONG, or QUAD)
     * BITVECTOR    - A vector of 1 bit element
     * BLOCK        - A sequence of varying-sized fields
     * BLOCKBYTE    - This structure is functionally equivalent to BLOCK[,BYTE]
     * BLOCKVECTOR  - A vector of BLOCKs
     */
    class BlockDeclarationAST : public DeclarationAST
    {
        private:
        map<> fields;
    };
    class VectorDeclarationAST : public DeclarationAST
    {
        private:
        vector<> elements;
        uint64_t element_size;
    };
    class BitVectorDeclarationAST : public DeclarationAST
    {
        private:
        vector<> bits;
        uint64_t numberOfBits;
        uint64_t size;  // in Bytes
    };
}

#endif /* LLVM_BLISS_STRUCTUREAST_H */
