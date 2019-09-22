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
 * File:   BlockAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 21, 2019, 5:00 PM
 */

#ifndef LLVM_BLISS_BLOCKAST_H
#define LLVM_BLISS_BLOCKAST_H

#include "AST/BaseAST.h"

using namespace std;

namespace bliss
{

    /*
     * block -+- labeled-block
     *        +- unlabeled-block
     *
     * unlabeled-block -+- BEGIN block-body END
     *                  +- block-body
     *
     * block-body -+- declaration
     *             +- nothing
     *                  -+- block-action ...
     *                   +- nothing
     *                  -+- block-value
     *                   +- nothing
     *
     * block-action -+- expression
     * block-value --+
     */
    class BlockAST : public BaseAST // AKA: The unlabeled-block
    {
    };

    /*
     * labeled-block --- label:... unlabeled-block
     */
    class LabeledBlockAST : public BlockAST
    {
        private:
        string label;   // could be a vector of strings
    };
}

#endif /* LLVM_BLISS_BLOCKAST_H */
