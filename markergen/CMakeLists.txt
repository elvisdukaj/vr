cmake_minimum_required(VERSION 3.11)

set(HEADERS_FILES "include/options.hpp")
set(SOURCE_FILES "src/options.cpp" "src/main.cpp")
set(SOURCES ${HEADERS_FILES} ${SOURCE_FILES} ${RESOURCES_FILES})

add_executable(markergen ${SOURCES})

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

target_include_directories(markergen  PRIVATE include)
target_compile_features(markergen  PRIVATE cxx_std_17)
target_link_libraries(markergen
PUBLIC
    Boost::boost
    Boost::program_options
    ${OpenCV_LIBS}
    )
