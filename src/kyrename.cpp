#include <unordered_map>
#include <string>

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
std::wstring remove_accents(std::wstring const& str)
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