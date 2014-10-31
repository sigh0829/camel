///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014 Dimitry Ishenko
// Distributed under the GNU GPL v2. For full terms please visit:
// http://www.gnu.org/licenses/gpl.html
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef UTILITY_H
#define UTILITY_H

///////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <memory>
#include <algorithm>
#include <cctype>
#include <type_traits>
#include <cstdlib>

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace app
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
struct charpp_deleter
{
    void operator()(char* args[]) noexcept
    {
        if(args)
        {
            for(char** ri= args; *ri; ++ri) free(*ri);
            free(args);
        }
    }
};

///
/// \brief charpp_ptr
///
/// Smart pointer to a NULL-terminated array of char* pointers.
/// These pointers are used, for example, by execve to pass arguments
/// and environment.
///
/// app::arguments and app::environ classes can return charpp_ptr through
/// to_charpp function.
///
typedef std::unique_ptr<char*[], charpp_deleter> charpp_ptr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief clone
///
/// Returns smart char* pointer with copy of the contents of std::string
/// for temporary use in functions requiring char*.
///
inline std::unique_ptr<char[]> clone(const std::string& value)
{
    std::unique_ptr<char[]> buffer(new char[value.size()+1]);

    value.copy(buffer.get(), value.size());
    buffer[value.size()]=0;

    return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
inline bool isspace(char c)
{
    return std::isspace(static_cast<unsigned char>(c));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename String>
inline std::string trim_left(String&& x)
{
    static_assert(std::is_convertible<String, std::string>::value, "String must be convertible to std::string");

    std::string s(std::forward<std::string>(x));
    s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), app::isspace));

    return s;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename String>
inline std::string trim_right(String&& x)
{
    static_assert(std::is_convertible<String, std::string>::value, "String must be convertible to std::string");

    std::string s(std::forward<std::string>(x));
    s.erase(std::find_if_not(s.rbegin(), s.rend(), app::isspace).base(), s.end());

    return s;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename String>
inline std::string trim(String&& x)
{
    static_assert(std::is_convertible<String, std::string>::value, "String must be convertible to std::string");
    return trim_left(trim_right(x));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#endif // UTILITY_H
