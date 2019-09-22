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
 * File:   AttributeAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 22, 2019, 10:39 AM
 */

#ifndef LLVM_BLISS_ATTRIBUTEAST_H
#define LLVM_BLISS_ATTRIBUTEAST_H

#include "AST/ConstantAST.h"

using namespace std;

namespace bliss
{

    /*
     * 9.15 A Summary of Attribute Usage
     *
     *                      allocation-unit
     *                      |   extension-attribute
     *                      |   |   structure-attribute
     *                      |   |   |   field-attribute
     *                      |   |   |   |   alignment-attribute
     *                      |   |   |   |   |   initial-attribute
     *                      |   |   |   |   |   |   preset-attribute
     *                      |   |   |   |   |   |   |   psect-allocation-attribute
     *                      |   |   |   |   |   |   |   |   volatile-attribute
     *                      |   |   |   |   |   |   |   |   |   no-value-attribute
     *                      |   |   |   |   |   |   |   |   |   |   linkage-attribute
     *                      |   |   |   |   |   |   |   |   |   |   |   range-attribute
     *                      |   |   |   |   |   |   |   |   |   |   |   |   addressing-mode-attribute
     *                      |   |   |   |   |   |   |   |   |   |   |   |   |   weak-attribute
     *                      |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * OWN                  X   X   X   X   X   X   X   X   X   .   .   .   X   .
     * GLOBAL               X   X   X   X   X   X   X   X   X   .   .   .   X   X
     * FORWARD              X   X   X   X   .   .   .   X   X   .   .   .   X   .
     * EXTERNAL             X   X   X   X   .   .   .   X   X   .   .   .   X   X
     *
     * LOCAL                X   X   X   X   X   X   X   .   X   .   .   .   .   .
     * STACKLOCAL           X   X   X   X   X   X   X   .   X   .   .   .   .   .
     * REGISTER             X   X   X   X   .   X   X   .   .   .   .   .   .   .
     * GLOBAL REGISTER      X   X   X   X   .   X   X   .   .   .   .   .   .   .
     * EXTERNAL REGISTER    X   X   X   X   .   X   X   .   .   .   .   .   .   .
     *
     * MAP                  X   X   X   X   .   .   .   .   X   .   .   .   .   .
     *
     * BIND                 X   X   X   X   .   .   .   .   X   .   .   .   .   .
     * GLOBAL BIND          X   X   X   X   .   .   .   .   X   .   .   .   .   X
     *
     * ROUTINE              .   .   .   .   .   .   .   X   .   X   X   .   X   .
     * GLOBAL ROUTINE       .   .   .   .   .   .   .   X   .   X   X   .   X   X
     * FORWARD ROUTINE      .   .   .   .   .   .   .   X   .   X   X   .   X   .
     * EXTERNAL ROUTINE     .   .   .   .   .   .   .   X   .   X   X   .   X   X
     *
     * BIND ROUTINE         .   .   .   .   .   .   .   .   .   X   X   .   .   .
     * GLOBAL BIND ROUTINE  .   .   .   .   .   .   .   .   .   X   X   .   .   X
     *
     * LITERAL              .   .   .   .   .   .   .   .   .   .   .   X   .   .
     * GLOBAL LITERAL       .   .   .   .   .   .   .   .   .   .   .   X   .   X
     * EXTERNAL LITERAL     .   .   .   .   .   .   .   .   .   .   .   X   .   X
     */

    /*
     *            +- allocation-unit
     *            |  extension-attribute
     *            |  structure-attribute
     *            |  field-attribute
     *            |  alignment-attribute
     *            |  initial-attribute
     * attribute -+  preset-attribute
     *            |  psect-allocation
     *            |  volatile-attribute
     *            |  no-value-attribute
     *            |  linkage-attribute
     *            |  range-attribute
     *            |  address-mode-attribute
     *            +- weak-attribute
     *
     * volatile-attribute --- VOLATILE
     *
     * no-value-attribute --- NOVALUE
     *
     * weak-attribute --- WEAK
     */
    class AttributeAST : public BaseAST
    {
        private:
        bool _volatile;
        bool no_value;
        bool weak;
    };

    /*
     *                  +- BYTE
     * allocation-unit -+  WORD
     *                  |  LONG
     *                  +- QUAD
     */
    class AllocationUnitAST : public AttributeAST
    {
    public:
        typedef enum
        {
            Quad,
            Long,
            Word,
            Byte,
            Other       // Used to set the default alignment for structures
        } AttrAllocUnit;

        private:
        uint64_t size;
        AttrAllocUnit type;
    };

    /*
     * extension-attribute -+- SIGNED
     *                      +- UNSIGNED
     */
    class ExtensionAttrAST : public AttributeAST
    {
        public:
        typedef enum
        {
            Unsigned,
            Signed
        } AttrExtension;

        private:
        AttrExtension ext;
    };

    /*
     * structure-attribute -+- REF -----+- structure-name -+--+- [allocation-actual, ... ]
     *                      +- nothing -+                     +- nothing
     *
     * structure-name --- name
     *
     *                    +- compile-time-constant-expression
     * allocation-actual -+  allocation-unit
     *                    |  extension-attribute
     *                    +- nothing
     */
    class StructureAttrAST : public AttributeAST
    {
    };

    /*
     * field-attribute --- FIELD ( -+- field-name -----+- , ... )
     *                              +- field-set-name -+
     *
     * field-name     -+- name
     * field-set-name -+
     */
    class FieldAttrAST : public AttributeAST
    {
        private:
        string name;
    };

    /*
     * alignment-attribute --- ALIGN ( boundary )
     *
     * boundary --- compile-time-constant-expression
     */
    class AlignmentAttrAST : public AttributeAST
    {
        public:
        typedef enum
        {
            Byte,
            Word,
            Long,
            Quad
        } AlignmentAttr;
        bool set(uint64_t boundary)
        {
            bool retVal = true;

            switch (boundary)
            {
                case 0:
                    align = Byte;
                    break;

                case 1:
                    align = Word;
                    break;

                case 2:
                    align = Long;
                    break;

                case 4:
                    align = Quad;
                    break;

                default:
                    align = Quad;
                    retVal = false;
                    break;
            }
            return retVal;
        }

        private:
        void setDefault(AllocationUnitAST::AttrAllocUnit type)
        {
            switch (type)
            {
                case AllocationUnitAST::Other:
                case AllocationUnitAST::Quad:
                    align = Quad;
                    break;

                case AllocationUnitAST::Long:
                    align = Long;
                    break;

                case AllocationUnitAST::Word:
                    align = Word;
                    break;

                case AllocationUnitAST::Byte:
                    align = Byte;
                    break;
            }
        }
        AlignmentAttr align;
    };

    /*
     * initial-attribute --- INITIAL ( initial-item, ... )
     *
     *               +- initial-group
     * initial-item -+  initial-expression
     *               +- initial-string
     *
     * initial-group -+- allocation-unit
     *                +- REP replicator OF -+- allocation-unit -+- ( initial-item, ... )
     *                                      +- nothing ---------+
     *
     * replicator --- compile-time-constant-expression
     *
     * initial-expression --- expression
     *
     * initial-string --- string-literal
     */
    class InitialAttrAST : public AttributeAST
    {
    };

    /*
     * preset-attribute --- PRESET ( preset-item, ... )
     *
     * preset-item --- [ ctoe-access-actual, ... ] = preset-value
     *
     * ctoe-access-actual -+- compile-time-constant-expression
     *                     +- field-name
     *
     * preset-value --- expression(1)
     *
     * (1): For OWN and GLOBAL declarations the preset-value must be a
     *      link-time constant expression. For LOCAL, STACKLOCAL, REGISTER,
     *      GLOBAL REGISTER, and EXTERNAL REGISTER declarations the
     *      preset-value can be an executable expression.
     */
    class PresetAttrAST : public AttributeAST
    {
    };

    /*
     * psect-allocation --- PSECT ( psect-name )
     *
     * psect-name --- name
     */
    class PsectAllocationAST : public AttributeAST
    {
    };

    /*
     * linkage-attribute --- linkage-name
     *
     * linkage-name --- name
     */
    class LinkageAttrAST : public AttributeAST
    {
    };

    /*
     * range-attribute -+- SIGNED ---+- ( bit-count )
     *                  +- UNSIGNED -+
     *
     * bit-count --- compile-time-constant-expression
     */
    class RangeAttrAST : public AttributeAST
    {
        private:
        ExtensionAttrAST extension;
    };

    /*
     *                            +- GENERAL
     *                            |  ABSOLUTE
     * addressing-mode-attribute -+  LONG_RELATIVE
     *                            |  WORD_RELATIVE
     *                            +- QUAD_RELATIVE
     */
    class AddrModeAST : public AttributeAST
    {
        public:
        typedef enum
        {
            QuadRelative,
            LongRelative,
            WordRelative,
            Absolute,
            General
        } AddressingMode;

        private:
        AddressingMode mode;
    };
}

#endif /* LLVM_BLISS_ATTRIBUTEAST_H */
