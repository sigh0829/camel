///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2014 Dimitry Ishenko
// Distributed under the GNU GPL v2. For full terms please visit:
// http://www.gnu.org/licenses/gpl.html
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef STREAM_H
#define STREAM_H

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "convert.h"

#include <string>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief operator<<
///
/// stream-like operator<< for std::string with conversion
///
template<typename T>
std::string& operator<<(std::string& stream, const T& value)
{
    stream+= convert::to<std::string>(value);
    return stream;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief operator<<
///
/// stream-like operator<< for std::string with conversion (rvalue version)
///
template<typename T>
std::string&& operator<<(std::string&& stream, const T& value)
{
    stream+= convert::to<std::string>(value);
    return std::move(stream);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#endif