/*
 Copyright (C) 2010 Kristian Duske

 Permission is hereby granted, free of charge, to any person obtaining a copy of this
 software and associated documentation files (the "Software"), to deal in the Software
 without restriction, including without limitation the rights to use, copy, modify, merge,
 publish, distribute, sublicense, and/or sell copies of the Software, and to permit
 persons to whom the Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <string_view>

namespace kdl::ci
{

/**
 * Compares the given strings in natural order: a run of digits compares by its numeric
 * value, so "tex16" sorts before "tex128". All other characters compare without case
 * sensitivity.
 *
 * This wraps strnatcmp from Martin Pool's natsort, see
 * https://sourcefrog.net/projects/natsort/. Two of its rules can be surprising:
 *
 * - A run of digits with a leading '0' compares as a fraction, so "wall08" sorts before
 *   "wall1". This orders version numbers such as "1.001" correctly.
 * - Whitespace is skipped, so "my mod" and "mymod" compare equal.
 *
 * Because of these rules, different strings can compare equal. Use string_less_natural
 * if you need a total order.
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return -1 if s1 is less than s2, +1 if s1 is greater than s2, 0 if they are equal
 */
int str_compare_natural(std::string_view s1, std::string_view s2);

/**
 * Orders strings by str_compare_natural. Ties between different strings are broken by
 * the exact strings, so this is a total order.
 */
struct string_less_natural
{
  bool operator()(std::string_view lhs, std::string_view rhs) const;
};

} // namespace kdl::ci
