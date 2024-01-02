#include <iostream>
#include <kyrename.hpp>
#include <stdexcept>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

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
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Try '" << argv[0] << " --help' for more information." << std::endl;
    }

    return 0;
}