/*
 * The MIT License
 *
 * Copyright 2017-2018 azarias.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * File:   FunctionalUtils.hpp
 * Author: azarias
 *
 * Created on 3/6/2018
 */
#pragma once

#include <functional>
#include <type_traits>

namespace  mp
{
/**
 * used to turn a labmda function
 * into a std::function
 */
namespace detail
{
    template < typename T > struct deduce_type ;

    template < typename RETURN_TYPE, typename CLASS_TYPE, typename... ARGS >
    struct deduce_type< RETURN_TYPE(CLASS_TYPE::*)(ARGS...) const >
    {
        using type = std::function< RETURN_TYPE(ARGS...) > ;
    };
}

template < typename CLOSURE >
auto to_f( const CLOSURE& fn )
{
    return typename detail::deduce_type< decltype( &CLOSURE::operator() ) >::type(fn) ;
}


}
