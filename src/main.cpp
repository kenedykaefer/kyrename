#include <iostream>
#include <kyrename.hpp>

int main(int argc, char** argv)
{
    std::wstring str = L"Hello, World!";
    std::wcout << str << std::endl;
    std::wcout << to_lower(str) << std::endl;
    return 0;
}