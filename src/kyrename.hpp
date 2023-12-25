#ifndef KYRENAME_HPP
#define KYRENAME_HPP

#include <string>

std::wstring remove_accents(std::wstring const& str);
std::wstring to_lower(std::wstring const& str);
std::wstring to_alphanum(std::wstring const& str, wchar_t const separator);

#endif // KYRENAME_HPP