add_library(libKyRename kyrename.cpp)
target_include_directories(libKyRename PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(string_toolkit string_toolkit.cpp)
target_include_directories(string_toolkit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(kyrename main.cpp)
target_link_libraries(kyrename libKyRename)