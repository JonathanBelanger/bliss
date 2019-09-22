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
 * File:   ConstantAST.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 21, 2019, 4:40 PM
 */

#ifndef LLVM_BLISS_CONSTANTAST_H
#define LLVM_BLISS_CONSTANTAST_H

#include "AST/ExprAST.h"

using namespace std;

namespace bliss
{
    /*
     * compile-time-constant-expression --- expression
     *
     * Restrictions:
     *
     *  A compile-time constant expression must be one of the following
     *  expressions:
     *      1. A numeric-literal.
     *      2. A string-literal.
     *      3. A name that satisfies the following conditions:
     *          a. It is declared in any bound-declaration except an EXTERNAL
     *             literal-declaration (as described in Chapter 14).
     *          b. It is bound to a value that is given by a compile-time
     *             constant expression.
     *      4. A structure-reference that yields a compile-time constant
     *         expression when it is expanded (as described in Chapter 11).
     *      5. A block that has a compile-time constant expression (and nothing
     *         else) as its body.
     *      6. An operator-expression that satisfies the following conditions:
     *          a. It is not a fetch-expression or an assignment-expression.
     *          b. It has a compile-time constant expression as each of its
     *             operands.
     *      7. An operator-expression that has the following form:
     *          e1 -+- rela -+- e2
     *              +-  -  --+
     *         In these forms, rela is one of the relational operators for
     *         addresses (EQLA,NEQA, and so on). Both e1 and e2 must be
     *         link-time constant expressions; furthermore, their values must
     *         be addresses that are relative to the same program section,
     *         external data segment, or external routine name.
     *      8. An executable-function that satisfies the following conditions:
     *          a. It is the ABS function, the SIGN function, or one of the
     *             max or min functions.
     *          b. It has a compile-time constant expression as each of its
     *             parameters.
     *      9. A supplementary-function that satisfies certain restrictions.
     *         Those restrictions are not given here but instead appear as part
     *         of the definition of each supplementary-function. (For example,
     *         Section 20.2.1.1 states that the CH$ALLOCATION function is a
     *         compile-time constant expression if its parameters are
     *         compile-time constant expressions.)
     *     10. A conditional-expression that satisfies the following
     *         conditions:
     *          a. It has a test that is a compile-time constant expression.
     *          b. It has a consequence or alternative that is a compile-time
     *             constant expression, depending on whether the test is
     *             satisfied or fails.
     *     11. A case-expression that satisfies the following conditions:
     *          a. It has a case-index that is a compile-time constant
     *             expression.
     *          b. It has at least one case-action that is a compile-time
     *             constant expression; namely, that case-action that is chosen
     *             by the value of the case-ind
     */
    class CompileTimeConstantExpr : public ExprAST
    {
    };

    /*
     * compile-time-constant-expression --- expression
     *
     * Restrictions:
     *
     *  These restrictions apply to an expression after any macro-calls in the
     *  expression have been expanded.
     *
     *  A link-time constant expression must be one of the following
     *  expressions:
     *      1. A compile-time-constant-expression.
     *      2. A PLIT.
     *      3. A name that is declared as one of the following:
     *          a. OWN, GLOBAL, EXTERNAL, or FORWARD. (These are used for names
     *             of permanently allocated data segments.)
     *          b. ROUTINE, GLOBAL ROUTINE, EXTERNAL ROUTINE, or FORWARD
     *             ROUTINE. (These are used for names of routine segments.)
     *          c. EXTERNAL LITERAL. (This is used for names of literals that
     *             are bound in other modules.)
     *      4. A name that satisfies the following conditions:
     *          a. It is declared by a bound-declaration (as described in
     *             Chapter 14).
     *          b. It is bound to a value that is given by a
     *             link-time-constant-expression.
     *      5. A structure-reference that yields a link-time constant
     *         expression when it is expanded (as described in Chapter 11).
     *      6. A block that has a link-time constant expression (and nothing
     *         else) as its body.
     *      7. An operator-expression that has the following form:
     *          e1 -+- + -+- e2
     *              +- - -+
     *         In these forms, e1 must be a link-time constant expression and
     *         e2 must be a compile-time constant expression.
     *      8. An operator-expression that has the following form:
     *          e1 -+- rela -+- e2
     *              +-  -  --+
     *         In these forms, rela is one of the relational operators for
     *         addresses (EQLA, NEQA, and so on). Both e1 and e2 must be
     *         link-time constant expressions; furthermore, their values must
     *         be addresses that are relative to the same program section,
     *         external data segment, or external routine name.
     *      9. A supplementary-function that satisfies certain restrictions.
     *         Those restrictions are not given here but appear as part of the
     *         definition of each supplementary function. (For example, Section
     *         20.2.2.1 states that the CH$PTR function is a link-time constant
     *         expression if its first parameter is a link-time constant
     *         expression and its remaining parameters are compile-time
     *         constant expressions.)
     */
    class LinkTimeConstantExpr : public ExprAST
    {
    };
}

#endif /* LLVM_BLISS_CONSTANTAST_H */
