#include <iostream>
#include <kyrename.hpp>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    try
    {
        if (argc < 2)
        {
            throw std::invalid_argument("Usage: kyrename [options] <path> [<path> ...]");
        }

        ky::kyrename rename;

        for (int i = 1; i < argc; ++i)
        {
            rename.add_path(argv[i]);
        }

        rename.print_paths();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Try '" << argv[0] << " --help' for more information." << std::endl;
    }

    return 0;
}