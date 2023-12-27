#include <iostream>
#include <kyrename.hpp>
#include <stdexcept>

int main(int argc, char** argv)
{
    try
    {
        if (argc < 2)
        {
            throw std::invalid_argument("Usage: " + std::string(argv[0]) + " [options] <file> [<file> ...]");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Try '" << argv[0] << " --help' for more information." << std::endl;
    }
    
    return 0;
}