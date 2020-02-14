// -*- C++ -*-
//===-- memory_impl.h -----------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef __PSTL_memory_impl_H
#define __PSTL_memory_impl_H

#include <iterator>

#include "unseq_backend_simd.h"

namespace __pstl
{
namespace internal
{

//------------------------------------------------------------------------
// uninitialized_move
//------------------------------------------------------------------------

template <class _ForwardIterator, class _OutputIterator>
_OutputIterator
brick_uninitialized_move(_ForwardIterator __first, _ForwardIterator __last, _OutputIterator __result,
                         /*vector=*/std::false_type) noexcept
{
    typedef typename std::iterator_traits<_OutputIterator>::value_type _ValueType2;
    for (; __first != __last; ++__first, ++__result)
    {
        ::new (std::addressof(*__result)) _ValueType2(std::move(*__first));
    }
    return __result;
}

template <class _ForwardIterator, class _OutputIterator>
_OutputIterator
brick_uninitialized_move(_ForwardIterator __first, _ForwardIterator __last, _OutputIterator __result,
                         /*vector=*/std::true_type) noexcept
{
    typedef typename std::iterator_traits<_OutputIterator>::value_type __ValueType2;
    typedef typename std::iterator_traits<_ForwardIterator>::reference _ReferenceType1;
    typedef typename std::iterator_traits<_OutputIterator>::reference _ReferenceType2;

    return unseq_backend::simd_walk_2(
        __first, __last - __first, __result,
        [](_ReferenceType1 __x, _ReferenceType2 __y) { ::new (std::addressof(__y)) __ValueType2(std::move(__x)); });
}

} // namespace internal
} // namespace __pstl

#endif /* __PSTL_memory_impl_H */
