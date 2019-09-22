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
 * File:   ControlAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 14, 2019, 5:28 PM
 */

#ifndef LLVM_BLISS_CONTROLAST_H
#define LLVM_BLISS_CONTROLAST_H

#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{

    /*
     *                     +- conditional-expression
     *                     |  case-expression
     * control-expression -+  select-expression
     *                     |  loop-expression
     *                     |  exit-expression
     *                     +- return-expression
     */
    class ControlExprAST : public ExprAST
    {
        public:
        ControlExprAST(void *Val) : Val(Val) {}

        private:
        void* Val;
    };

    /*
     * conditional-expression -+- IF test THEN consequence ELSE alternative
     *                         +- IF test THEN consequence
     *
     * test --------+
     * consequence  +- expression
     * alternative -+
     */
    class ConditionalExprAST : public ControlExprAST
    {
    };

    /*
     * case-expression --- CASE case-index FROM low-bound TO high-bound
     *                          SET
     *                          case-line...
     *                          TES
     *
     * case-line --- [case-label, ...]: case-action;
     *
     *             +- single-value
     * case-label -+  low-value TO high-value
     *             |  INRANGE
     *             +- OUTRANGE
     *
     * case-index --+- expression
     * case-action -+
     *
     * low-bound    +
     * high-bound   |
     * single-value +- compile-time-constant-expression
     * low-value    |
     * high-value --+
     */
    class CaseExprAST : public ControlExprAST
    {
    };

    /*
     * select-expression -+- SELECT | SELECTA | SELECTU ---------+- select-index OF
     *                    +- SELECTONE | SELECTONEA | SELECTONEU +
     *                          SET
     *                          select-line...
     *                          TES
     *
     * select-line --- [select-label, ...]: select-action;
     *
     *               +- selector
     * select-label -+  low-selector TO high-selector
     *               | OTHERWISE
     *               + ALWAYS
     *
     * select-index --+
     * select-action  |
     * selector       +- expression
     * low-selector   |
     * high-selector -+
     */
    class SelectExprAST : public ControlExprAST
    {
    };

    /*
     * loop-expression -+- indexed-loop-expression
     *                  +- tested-loop-expression
     *
     */
    class LoopExprAST : public ControlExprAST
    {
        private:
        ExprAST LoopBody;
    };

    /*
     * indexed-loop-expression -+- INCR | INCRA | INCRU -+- loop-index
     *                          +- DECR | DECRA | DESCU -+
     *                              FROM initial -+--+- TO final -+--+- BY step
     *                              nothing ------+  +- nothing --+  +- nothing
     *                                  DO loop-body
     *
     * loop-index --- name
     *
     * loop-body -+
     * initial    +- expression
     * final      |
     * step ------+
     */
    class IndexLoopExprAST : public LoopExprAST
    {
    };

    /*
     * tested-loop-expression -+- pre-tested-loop
     *                         +- post-tested-loop
     *
     * pre-tested-loop -+- WHILE -+- test DO loop-body
     *                  +- UNTIL -+
     *
     * post-tested-loop --- DO loop-body -+- WHILE -+- test
     *                                    +- UNTIL -+
     */
    class TestedLoopExprAST : public LoopExprAST
    {
    };

    /*
     * exit-expression -+- leave-expression
     *                  +- exit-loop-expression
     *
     * leave-expression --- LEAVE label -+- WITH exit-value
     *                                   +- nothing
     *
     * exit-loop-expression --- EXITLOOP -+- exit-value
     *                                    +- nothing
     *
     * exit-value --- expression
     */
    class ExitExprAST : public ControlExprAST
    {
    };

    /*
     * return-expression --- RETURN -+- returned-value
     *                               +- nothing
     *
     * returned-value --- expression
     */
    class ReturnExprAST : public ControlExprAST
    {
    };
}

#endif /* LLVM_BLISS_CONTROLAST_H */
