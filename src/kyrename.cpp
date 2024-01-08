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

    if (std::find(m_paths.begin(), m_paths.end(), path) == m_paths.end())
    {
        m_paths.push_back(path);
    }
}

void ky::kyrename::print_paths() const
{
    for (const auto &path : m_paths)
    {
        std::wcout << path.wstring() << std::endl;
    }
}