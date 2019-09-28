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
 * File:   ConditionHandlingAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 28, 2019, 5:15 PM
 */

#ifndef LLVM_BLISS_CONDITIONHANDLINGAST_H
#define LLVM_BLISS_CONDITIONHANDLINGAST_H

#include "AST/DeclarationAST.h"

using namespace std;

namespace bliss
{

    /*
     * enable-declaration --- ENABLE routine-name -+- (enable-actual, ... )
     *                                             +- nothing
     *
     *                +- own-name
     * enable-actual -+  global-name
     *                |  forward-name
     *                +- local-name
     *
     * routine-name -+
     * own-name      |
     * global-name   +- name
     * forward-name  |
     * local-name ---+
     */
    class EnableDeclAST : public DeclarationAST
    {
    };
}

#endif /* LLVM_BLISS_CONDITIONHANDLINGAST_H */
