#ifndef KYRENAME_HPP
#define KYRENAME_HPP

#include <string>
#include <filesystem>
#include <vector>

namespace ky
{
    namespace fs = std::filesystem;

    std::wstring remove_accents(std::wstring const &str);
    std::wstring to_lower(std::wstring const &str);
    std::wstring to_alphanum(std::wstring const &str, wchar_t const separator);
    std::wstring normalize_separator(std::wstring const &str, wchar_t const separator, std::wstring const &separators_to_replace = L" ,.?;:[]{}|()-_");

    class kyrename
    {
    public:
        kyrename(std::vector<fs::path> const &paths);

    private:
        class FileSystem
        {
        public:
            virtual ~FileSystem() = default;
        };

        class FileSystemItem : public FileSystem
        {
        public:
            FileSystemItem(fs::path const &item_path);

        private:
            fs::path m_item_path;
        };

        class FileSystemCollection : public FileSystem
        {
        public:
            FileSystemCollection(fs::path const &directory_path);

        private:
            fs::path m_directory_path;
            std::vector<FileSystemItem> m_items;
        };

        std::vector<std::unique_ptr<FileSystem>> m_file_systems;
    };

} // namespace ky

#endif // KYRENAME_HPP