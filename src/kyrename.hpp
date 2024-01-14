#ifndef KYRENAME_HPP
#define KYRENAME_HPP

#include <string_toolkit.hpp>
#include <filesystem>
#include <set>
#include <stdexcept>

namespace ky
{
    namespace fs = std::filesystem;

    class kyrename
    {
    public:
        kyrename();
        void add_path(const fs::path &path);
        void print_paths() const;

        void disable_all_rename_options();
        void enable_remove_accents();
        void enable_to_lower();
        void enable_only_alphanum();
        void enable_normalize_separator(wchar_t const separator = L'_');

    private:
        enum class rename_options
        {
            none = 0,
            remove_accents = 1,
            to_lower = 2,
            only_alphanum = 4,
            normalize_separator = 8
        };

        unsigned int m_rename_options;
        wchar_t m_separator;
        std::set<fs::path> m_paths;
    };

} // namespace ky

#endif // KYRENAME_HPP