#ifndef KYRENAME_HPP
#define KYRENAME_HPP

#include <string>
#include <filesystem>
#include <vector>

namespace ky
{
    namespace fs = std::filesystem;
    struct normalize_name_options
    {
        bool accents;
        bool lower;
        bool alphanum;
        wchar_t separator;
    };

    class FileSystemItem
    {
    public:
        FileSystemItem(fs::path const &path);
        std::wstring remove_accents(std::wstring const &str);
        std::wstring to_lower(std::wstring const &str);
        std::wstring to_alphanum(std::wstring const &str, wchar_t const separator);
        std::wstring normalize_separator(std::wstring const &str, wchar_t const separator, std::wstring const &separators_to_replace = L" ,.?;:[]{}|()-_");
        void normalize_name(normalize_name_options const &options);
        
    private:
        fs::path parent_path;
        fs::path file_name;
        fs::path new_file_name;
    }; 
    
} // namespace ky

#endif // KYRENAME_HPP