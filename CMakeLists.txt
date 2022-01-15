cmake_minimum_required(VERSION 3.12.0)
project(portal)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(restclient-cpp CONFIG REQUIRED)

set(SOURCE_FILES
    src/Main.cpp
    "src/utils/WindowsConsoleInitialize.cpp"
    "src/services/ProgramOptionsService.cpp"
)

set(HEADER_FILES
    "src/utils/WindowsConsoleInitialize.hpp"
    "src/services/ProgramOptionsService.hpp"
    "src/Constants/Versions.hpp"
)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${PROJECT_NAME} PRIVATE "/ZI")
  target_link_options(${PROJECT_NAME} PRIVATE "/SAFESEH:NO")
endif()

target_link_libraries(
    ${PROJECT_NAME}
    Boost::boost
    Boost::program_options
    fmt::fmt
    nlohmann_json::nlohmann_json
    restclient-cpp
)