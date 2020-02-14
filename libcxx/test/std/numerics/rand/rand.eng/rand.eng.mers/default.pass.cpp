//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <random>

// template <class UIntType, size_t w, size_t n, size_t m, size_t r,
//           UIntType a, size_t u, UIntType d, size_t s,
//           UIntType b, size_t t, UIntType c, size_t l, UIntType f>
// class mersenne_twister_engine;

// explicit mersenne_twister_engine();

#include <random>
#include <sstream>
#include <cassert>

#include "test_macros.h"

void
test1()
{
    std::mt19937 e1;
    std::mt19937 e2(std::mt19937::default_seed);
    assert(e1 == e2);
    assert(e1() == 3499211612u);
}

void
test2()
{
    std::mt19937_64 e1;
    std::mt19937_64 e2(std::mt19937_64::default_seed);
    assert(e1 == e2);
    assert(e1() == 14514284786278117030ull);
}

int main(int, char**)
{
    test1();
    test2();

  return 0;
}
