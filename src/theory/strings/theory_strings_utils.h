/*********************                                                        */
/*! \file theory_strings_utils.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Util functions for theory strings.
 **
 ** Util functions for theory strings.
 **/

#include "cvc4_private.h"

#ifndef CVC4__THEORY__STRINGS__THEORY_STRINGS_UTILS_H
#define CVC4__THEORY__STRINGS__THEORY_STRINGS_UTILS_H

#include <vector>

#include "expr/node.h"

namespace CVC4 {
namespace theory {
namespace strings {
namespace utils {

/**
 * Make the conjunction of nodes in a. Removes duplicate conjuncts, returns
 * true if a is empty, and a single literal if a has size 1.
 */
Node mkAnd(const std::vector<Node>& a);

/**
 * Adds all (non-duplicate) children of <k> applications from n to conj. For
 * example, given (<k> (<k> A B) C A), we add { A, B, C } to conj.
 */
void flattenOp(Kind k, Node n, std::vector<Node>& conj);

/**
 * Gets the "vector form" of term n, adds it to c.
 *
 * For example:
 * when n = str.++( x, y ), c is { x, y }
 * when n = str.++( x, str.++( y, z ), w ), c is { x, str.++( y, z ), w )
 * when n = x, c is { x }
 *
 * Also applies to regular expressions (re.++ above).
 */
void getConcat(Node n, std::vector<Node>& c);

/**
 * Make the concatentation from vector c
 * The kind k is either STRING_CONCAT or REGEXP_CONCAT.
 */
Node mkConcat(Kind k, const std::vector<Node>& c);

/**
 * Returns the rewritten form of the string concatenation of n1 and n2.
 */
Node mkNConcat(Node n1, Node n2);

/**
 * Returns the rewritten form of the string concatenation of n1, n2 and n3.
 */
Node mkNConcat(Node n1, Node n2, Node n3);

/**
 * Returns the rewritten form of the string concatenation of nodes in c.
 */
Node mkNConcat(const std::vector<Node>& c);

/**
 * Returns the rewritten form of the length of string term t.
 */
Node mkNLength(Node t);

/**
 * Get constant component. Returns the string constant represented by the
 * string or regular expression t. For example:
 *   "ABC" -> "ABC", (str.to.re "ABC") -> "ABC", (str.++ x "ABC") -> null
 */
Node getConstantComponent(Node t);

/**
 * Get constant prefix / suffix from expression. For example, if isSuf=false:
 *   "ABC" -> "ABC"
 *   (str.++ "ABC" x) -> "ABC"
 *   (str.to.re "ABC") -> "ABC"
 *   (re.++ (str.to.re "ABC") ...) -> "ABC"
 *   (re.in x (str.to.re "ABC")) -> "ABC"
 *   (re.in x (re.++ (str.to.re "ABC") ...)) -> "ABC"
 *   (str.++ x "ABC") -> null
 *   (re.in x (re.++ (re.* "D") (str.to.re "ABC"))) -> null
 */
Node getConstantEndpoint(Node e, bool isSuf);

/**
 * Given a vector of regular expression nodes and a start index that points to
 * a wildcard, returns true if the wildcard is unbounded (i.e. it is followed
 * by an arbitrary number of `re.allchar`s and then an `re.*(re.allchar)`. If
 * the start index is not a wilcard or the wildcards are not followed by
 * `re.*(re.allchar)`, the function returns false.
 *
 * @param rs The vector of regular expression nodes
 * @param start The start index to consider
 * @return True if the wilcard pointed to by `start` is unbounded, false
 *         otherwise
 */
bool isUnboundedWildcard(const std::vector<Node>& rs, size_t start);

/**
 * Returns true iff the given regular expression only consists of re.++,
 * re.allchar, (re.* re.allchar), and str.to.re of string literals.
 *
 * @param r The regular expression to check
 * @return True if the regular expression is simple
 */
bool isSimpleRegExp(Node r);

/**
 * Helper function that takes a regular expression concatenation and
 * returns the components of the concatenation. Letters of string literals
 * are treated as individual components.
 *
 * @param r The regular expression
 * @param result The resulting components
 */
void getRegexpComponents(Node r, std::vector<Node>& result);

}  // namespace utils
}  // namespace strings
}  // namespace theory
}  // namespace CVC4

#endif
