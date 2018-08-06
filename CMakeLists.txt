cmake_minimum_required(VERSION 3.15)

project(metamorphosis)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(SOURCE_FILES
        src/base_name.hpp
        src/base_number.cpp
        src/base_number.hpp
        src/file_target.cpp
        src/file_target.hpp
        src/image_target.cpp
        src/image_target.hpp
        src/main.cpp
        src/program.cpp
        src/program.hpp
        src/sort_policie.hpp
)

add_executable(metamorphosis ${SOURCE_FILES})
target_link_libraries(metamorphosis -ljpeg -lpng -lspeed -lstdc++fs)
install(TARGETS metamorphosis DESTINATION bin)
