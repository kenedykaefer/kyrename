find_package(Catch2 3 REQUIRED)

add_executable(string_toolkit_tests string_toolkit_tests.cpp)

target_link_libraries(string_toolkit_tests PRIVATE Catch2::Catch2WithMain string_toolkit)