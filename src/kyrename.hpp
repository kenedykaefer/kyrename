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

    private:
        std::set<fs::path> m_paths;
    };

} // namespace ky

#endif // KYRENAME_HPP