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
 * File:   CodeGen.h
 * Author: Jonathan D. Belanger
 *
 * Created on August 20, 2019, 8:52 AM
 */

#ifndef LLVM_BLISS_CODEGEN_H
#define LLVM_BLISS_CODEGEN_H

#include "Basic/CommonInclude.h"

namespace bliss
{
    class CodeGen
    {
        private:
        LLVMContext TheContext;
        IRBuilder<> Builder(TheContext);
        std::unique_ptr<Module> TheModule;
        std::map<std::string, AllocaInst *> NamedValues;
        std::map<std::string, std::unique_ptr<PrototypeAST>> FunctionProtos;

        public:
        Value *LogErrorV(const char *Str);
        Function *getFunction(std::string Name);
        AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,
                                           const std::string &VarName);
    };
}

#endif /* LLVM_BLISS_CODEGEN_H */
