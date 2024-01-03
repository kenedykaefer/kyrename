#include <kyrename.hpp>
#include <unordered_map>
#include <string>
#include <cwctype>
#include <unordered_set>

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
std::wstring ky::remove_accents(std::wstring const &str)
{

    static std::unordered_map<wchar_t, wchar_t> accentuation = {
        // A, a
        {L'Á', L'A'},
        {L'À', L'A'},
        {L'Â', L'A'},
        {L'Ã', L'A'},
        {L'Ä', L'A'},
        {L'Å', L'A'},
        {L'á', L'a'},
        {L'à', L'a'},
        {L'â', L'a'},
        {L'ã', L'a'},
        {L'ä', L'a'},
        {L'å', L'a'},
        // E, e
        {L'É', L'E'},
        {L'È', L'E'},
        {L'Ê', L'E'},
        {L'Ë', L'E'},
        {L'é', L'e'},
        {L'è', L'e'},
        {L'ê', L'e'},
        {L'ë', L'e'},
        // I, i
        {L'Í', L'I'},
        {L'Ì', L'I'},
        {L'Î', L'I'},
        {L'Ï', L'I'},
        {L'í', L'i'},
        {L'ì', L'i'},
        {L'î', L'i'},
        {L'ï', L'i'},
        // O, o
        {L'Ó', L'O'},
        {L'Ò', L'O'},
        {L'Ô', L'O'},
        {L'Õ', L'O'},
        {L'Ö', L'O'},
        {L'Ø', L'O'},
        {L'ó', L'o'},
        {L'ò', L'o'},
        {L'ô', L'o'},
        {L'õ', L'o'},
        {L'ö', L'o'},
        {L'ø', L'o'},
        // U, u
        {L'Ú', L'U'},
        {L'Ù', L'U'},
        {L'Û', L'U'},
        {L'Ü', L'U'},
        {L'ú', L'u'},
        {L'ù', L'u'},
        {L'û', L'u'},
        {L'ü', L'u'},
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

    for (auto const &c : str)
    {
        auto it = accentuation.find(c);
        new_str.push_back(it == accentuation.end() ? c : it->second);
    }

    return new_str;
} // remove_accents

/**
 * @brief Converts a given string to lowercase.
 *
 * @param str The string to be converted.
 * @return The lowercase version of the input string.
 */
std::wstring ky::to_lower(std::wstring const &str)
{
    std::wstring new_str;
    new_str.reserve(str.size());

    for (auto const &c : str)
    {
        new_str.push_back(std::towlower(c));
    }

    return new_str;
} // to_lower

/**
 * @brief Converts a wide string to an alphanumeric string by removing non-alphanumeric characters.
 *
 * @param str The wide string to convert.
 * @param separator The character to use as a separator between alphanumeric characters.
 * @return The converted alphanumeric string.
 */
std::wstring ky::to_alphanum(std::wstring const &str, wchar_t const separator)
{
    std::wstring new_str;
    new_str.reserve(str.size());

    for (auto const &c : str)
    {
        if (std::iswalnum(c) || c == separator)
        {
            new_str.push_back(c);
        }
    }

    return new_str;
} // to_alphanum

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
std::wstring ky::normalize_separator(std::wstring const &str, wchar_t const separator, std::wstring const &separators_to_replace)
{
    std::wstring new_str;
    new_str.reserve(str.size());

    std::unordered_set<wchar_t> separators = {separators_to_replace.begin(), separators_to_replace.end()};

    bool last_char_was_separator = true;

    for (auto const &c : str)
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
} // normalize_separator

ky::kyrename::kyrename(std::vector<fs::path> const &paths)
{
    for (auto &const_path : paths)
    {
        if (!fs::exists(const_path))
        {
            throw std::invalid_argument("Path " + const_path.string() + " does not exist.");
        }
        
        fs::path path = const_path;

        if (path.native().back() == fs::path::preferred_separator)
        {
            path = path.parent_path();
        }

        if (path.filename() == ".")
        {
            m_file_systems.push_back(std::make_unique<FileSystemCollection>(path.parent_path()));
        } 
        else
        {
            m_file_systems.push_back(std::make_unique<FileSystemItem>(path));
        }
    }
} // kyrename::kyrename

ky::kyrename::FileSystemCollection::FileSystemCollection(fs::path const &directory_path)
{
    if (!fs::is_directory(directory_path))
    {
        throw std::invalid_argument("Path " + directory_path.string() + " is not a directory.");
    }

    m_directory_path = directory_path;

    for (auto const &entry : fs::directory_iterator(directory_path))
    {
        m_items.push_back(FileSystemItem(entry.path()));
    }
} // kyrename::FileSystemCollection::FileSystemCollection
