#include <kyrename.hpp>
#include <iostream>
#include <algorithm>

ky::kyrename::kyrename()
{
}

void ky::kyrename::add_path(const fs::path &path)
{
    if (!fs::exists(path))
    {
        throw std::invalid_argument("Path " + path.string() + " does not exist.");
    }

    fs::path canonicalPath = fs::canonical(path);

    if (canonicalPath == fs::current_path())
    {
        throw std::invalid_argument("Cannot rename current directory.");
    }

    if (canonicalPath == fs::current_path().parent_path())
    {
        throw std::invalid_argument("Cannot rename parent directory.");
    }

    m_paths.insert(canonicalPath);
}

void ky::kyrename::print_paths() const
{
    for (const auto &path : m_paths)
    {
        std::wcout << path.wstring() << std::endl;
    }
}

void ky::kyrename::disable_all_rename_options()
{
    m_rename_options = static_cast<unsigned int>(rename_options::none);
}

void ky::kyrename::enable_remove_accents()
{
    m_rename_options |= static_cast<unsigned int>(rename_options::remove_accents);
}

void ky::kyrename::enable_to_lower()
{
    m_rename_options |= static_cast<unsigned int>(rename_options::to_lower);
}

void ky::kyrename::enable_only_alphanum()
{
    m_rename_options |= static_cast<unsigned int>(rename_options::only_alphanum);
}

void ky::kyrename::enable_normalize_separator(wchar_t const separator)
{
    m_rename_options |= static_cast<unsigned int>(rename_options::normalize_separator);
    m_separator = separator;
}
