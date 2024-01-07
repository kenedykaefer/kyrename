#ifndef STRING_TOOLKIT_HPP
#define STRING_TOOLKIT_HPP

#include <string>

namespace ky
{
    std::wstring remove_accents(std::wstring const &str);
    std::wstring to_lower(std::wstring const &str);
    std::wstring to_alphanum(std::wstring const &str, wchar_t const separator);
    std::wstring normalize_separator(std::wstring const &str, wchar_t const separator, std::wstring const &separators_to_replace = L" ,.?;:[]{}|()-_");
}

#endif // STRING_TOOLKIT_HPP
