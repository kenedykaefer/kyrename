#ifndef KYRENAME_HPP
#define KYRENAME_HPP

#include <string>

namespace ky
{
    struct normalize_name_options
    {
        bool accents;
        bool lower;
        bool alphanum;
        wchar_t separator;
    };

    struct file_name
    {
        std::wstring filename;
        std::wstring extension;
        bool hidden_file;
    };

    std::wstring remove_accents(std::wstring const &str);
    std::wstring to_lower(std::wstring const &str);
    std::wstring to_alphanum(std::wstring const &str, wchar_t const separator);
    std::wstring normalize_separator(std::wstring const &str, wchar_t const separator, std::wstring const &separators_to_replace = L" ,.?;:[]{}|()-_");
    file_name normalize_name(file_name name, normalize_name_options const &options);
} // namespace ky

#endif // KYRENAME_HPP