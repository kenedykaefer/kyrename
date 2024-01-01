#include <iostream>
#include <kyrename.hpp>
#include <stdexcept>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

void print_names_with_new_names(std::vector<ky::file_name> const &names, std::vector<ky::file_name> const &new_names)
{
    std::cout << "Old name\tNew name" << std::endl;
    std::cout << "--------\t--------" << std::endl;

    for (size_t i = 0; i < names.size(); ++i)
    {
        std::wcout << names[i].filename << names[i].extension << "\t\t";
        if (names[i].hidden_file)
        {
            std::wcout << L".";
        }
        std::wcout << new_names[i].filename << new_names[i].extension << std::endl;
    }
}

int main(int argc, char **argv)
{
    try
    {
        if (argc < 2)
        {
            throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <path>");
        }

        std::vector<fs::path> paths;

        for (int i = 1; i < argc; ++i)
        {
            paths.push_back(fs::path(argv[i]));
        }

        std::vector<ky::file_name> names = ky::get_files(paths);
        std::vector<ky::file_name> new_names;

        for (auto const &name : names)
        {
            ky::file_name new_name = ky::normalize_name(name, {true, true, true, L'_'});
            new_names.push_back(new_name);
        }

        print_names_with_new_names(names, new_names);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Try '" << argv[0] << " --help' for more information." << std::endl;
    }

    return 0;
}