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

        fs::path path = argv[1];

        if (path == "." || path == "./")
        {
            path = fs::current_path();

            std::vector<ky::file_name> names;

            for (auto const &entry : fs::directory_iterator(path))
            {
                ky::file_name name;
                name.filename = entry.path().stem().wstring();
                name.extension = entry.path().extension().wstring();
                name.hidden_file = entry.path().filename().wstring().front() == L'.';

                names.push_back(name);
            }

            ky::normalize_name_options options;
            options.accents = true;
            options.lower = true;
            options.alphanum = true;
            options.separator = L'_';

            std::vector<ky::file_name> new_names;

            for (auto const &name : names)
            {
                new_names.push_back(ky::normalize_name(name, options));
            }

            print_names_with_new_names(names, new_names);


        }
        else
        {
            throw std::invalid_argument("Only the current directory is supported at the moment.");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Try '" << argv[0] << " --help' for more information." << std::endl;
    }

    return 0;
}