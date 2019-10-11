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
 * File:   ModuleAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 28, 2019, 5:54 PM
 */

#ifndef LLVM_BLISS_MODULEAST_H
#define LLVM_BLISS_MODULEAST_H

#include "AST/SpecialAST.h"

using namespace std;

namespace bliss
{

    /*
     * module --- MODULE module-head = module-body ELUDOM
     *
     * module-head --- module-name -+- ( module-switch, ... )
     *                              +- nothing
     *
     * module-name --- name
     *
     * module-body --- block
     *
     * module-switch -+- on-off-switch
     *                +- special-switch
     *
     *                +- CODE | NOCODE
     *                |  DEBUG | NODEBUG
     *                |  ERRS | NOERRS
     * on-off-switch -+  OPTIMIZE | NOOPTIMIZE
     *                |  SAFE | NOSAFE
     *                |  UNAMES | NOUNAMES
     *                +- ZIP | NOZIP
     *
     *                 +- common-switch
     * special-switch -+  bliss-32-switch
     *                 +- bliss-64-switch
     *
     *                +- IDENT = quoted-string
     *                |  LANGUAGE ( language-list, ... )
     *                |  LINKAGE ( linkage-name)
     * common-switch -+  LIST ( list-options )
     *                |  STRUCTURE -+- ( structure-attribute )
     *                |             +- nothing
     *                |  MAIN = routine-name
     *                |  OPTLEVEL = 0 | 1 | 2 | 3
     *                +- VERSION = quoted-string
     *
     */
    class ModuleAST : public BaseAST
    {
        public:
            ModuleAST(const string &Name) : Name(Name) {}

        private:
            string Name;
            SwitchesDeclAST switches;
    };
}

#endif /* LLVM_BLISS_MODULEAST_H */
