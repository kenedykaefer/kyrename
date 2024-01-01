#include <kyrename.hpp>
#include <unordered_map>
#include <string>
#include <cwctype>
#include <unordered_set>
#include <stdexcept>

/**
 * @brief Removes accents from a given wide string.
 * 
 * This function takes a wide string as input and removes any accents from it.
 * Accented characters are replaced with their non-accented counterparts.
 * The modified string is returned as a new wide string.
 * 
 * @param str The wide string from which to remove accents.
 * @return The modified wide string without accents.
 */
std::wstring ky::remove_accents(std::wstring const& str)
{

    static std::unordered_map<wchar_t, wchar_t> accentuation = {
        // A, a
        {L'Á', L'A'}, {L'À', L'A'}, {L'Â', L'A'}, {L'Ã', L'A'}, {L'Ä', L'A'}, {L'Å', L'A'},
        {L'á', L'a'}, {L'à', L'a'}, {L'â', L'a'}, {L'ã', L'a'}, {L'ä', L'a'}, {L'å', L'a'},
        // E, e
        {L'É', L'E'}, {L'È', L'E'}, {L'Ê', L'E'}, {L'Ë', L'E'},
        {L'é', L'e'}, {L'è', L'e'}, {L'ê', L'e'}, {L'ë', L'e'},
        // I, i
        {L'Í', L'I'}, {L'Ì', L'I'}, {L'Î', L'I'}, {L'Ï', L'I'},
        {L'í', L'i'}, {L'ì', L'i'}, {L'î', L'i'}, {L'ï', L'i'},
        // O, o
        {L'Ó', L'O'}, {L'Ò', L'O'}, {L'Ô', L'O'}, {L'Õ', L'O'}, {L'Ö', L'O'}, {L'Ø', L'O'},
        {L'ó', L'o'}, {L'ò', L'o'}, {L'ô', L'o'}, {L'õ', L'o'}, {L'ö', L'o'}, {L'ø', L'o'},
        // U, u
        {L'Ú', L'U'}, {L'Ù', L'U'}, {L'Û', L'U'}, {L'Ü', L'U'},
        {L'ú', L'u'}, {L'ù', L'u'}, {L'û', L'u'}, {L'ü', L'u'},
        // C, c
        {L'Ç', L'C'},
        {L'ç', L'c'},
        // N, n
        {L'Ñ', L'N'},
        {L'ñ', L'n'},
        // Y, y
        {L'Ÿ', L'Y'},
        {L'ÿ', L'y'},
    };

    std::wstring new_str;
    new_str.reserve(str.size());

    for (auto const& c : str)
    {
        auto it = accentuation.find(c);
        new_str.push_back(it == accentuation.end() ? c : it->second);
    }

    return new_str;
}   // remove_accents

/**
 * @brief Converts a given string to lowercase.
 *
 * @param str The string to be converted.
 * @return The lowercase version of the input string.
 */
std::wstring ky::to_lower(std::wstring const& str)
{
    std::wstring new_str;
    new_str.reserve(str.size());

    for (auto const& c : str)
    {
        new_str.push_back(std::towlower(c));
    }

    return new_str;
}   // to_lower

/**
 * @brief Converts a wide string to an alphanumeric string by removing non-alphanumeric characters.
 * 
 * @param str The wide string to convert.
 * @param separator The character to use as a separator between alphanumeric characters.
 * @return The converted alphanumeric string.
 */
std::wstring ky::to_alphanum(std::wstring const& str, wchar_t const separator)
{
    std::wstring new_str;
    new_str.reserve(str.size());

    for (auto const& c : str)
    {
        if (std::iswalnum(c) || c == separator)
        {
            new_str.push_back(c);
        }
    }

    return new_str;
}   // to_alphanum

/**
 * @brief Normalizes the separator in a given string.
 * 
 * This function replaces occurrences of specified separators in the input string with a specified separator.
 * 
 * @param str The input string to be normalized.
 * @param separator The separator to be used for normalization.
 * @param separators_to_replace Optional. The list of separators to be replaced. Default value is ",.?;:[]{}|()-_".
 * @return The normalized string.
 */
std::wstring ky::normalize_separator(std::wstring const& str, wchar_t const separator, std::wstring const& separators_to_replace)
{
    std::wstring new_str;
    new_str.reserve(str.size());

    std::unordered_set<wchar_t> separators = {separators_to_replace.begin(), separators_to_replace.end()};

    bool last_char_was_separator = true;

    for (auto const& c : str)
    {
        if (separators.find(c) != separators.end())
        {
            if (!last_char_was_separator)
            {
                new_str.push_back(separator);
                last_char_was_separator = true;
            }
        }
        else
        {
            new_str.push_back(c);
            last_char_was_separator = false;
        }
    }

    // Remove trailing separator
    if (!new_str.empty() && new_str.back() == separator)
    {
        new_str.pop_back();
    }

    return new_str;
}   // normalize_separator

std::vector<ky::file_name> ky::get_files(std::vector<fs::path> const& paths)
{
    std::vector<ky::file_name> files;

    for (auto const& path : paths)
    {
        if (path.native().back() == fs::path::preferred_separator)
        {
            throw std::invalid_argument("Path cannot end with a separator: " + path.string());
        }
        
        if (path.filename() == ".")
        {
            fs::path parent_path = path.parent_path();

            if (parent_path.empty())
            {
                parent_path = fs::current_path();
            }

            if (!fs::exists(parent_path))
            {
                throw std::invalid_argument("Path does not exist: " + parent_path.string());
            }

            if (!fs::is_directory(parent_path))
            {
                throw std::invalid_argument("Path is not a directory: " + parent_path.string());
            }

            for (auto const& entry : fs::directory_iterator(parent_path))
            {
                ky::file_name file;
                file.path = entry.path();
                file.filename = entry.path().stem().wstring();
                file.extension = entry.path().extension().wstring();
                file.hidden_file = file.filename.front() == L'.';
                files.push_back(file);
            }
        }
        else
        {
            if (!fs::exists(path))
            {
                throw std::invalid_argument("Path does not exist: " + path.string());
            }

            ky::file_name file;
            file.path = path;
            file.filename = path.stem().wstring();
            file.extension = path.extension().wstring();
            file.hidden_file = file.filename.front() == L'.';
            files.push_back(file);
        }
    }

    return files;
}

ky::file_name ky::normalize_name(ky::file_name name, ky::normalize_name_options const& options)
{
    if (options.accents)
    {
        name.filename = ky::remove_accents(name.filename);
    }

    if (options.lower)
    {
        name.filename = ky::to_lower(name.filename);
        name.extension = ky::to_lower(name.extension);
    }

    if (options.alphanum)
    {
        name.filename = ky::to_alphanum(name.filename, options.separator);
    }

    name.filename = ky::normalize_separator(name.filename, options.separator);

    return name;
}   // normalize_name
