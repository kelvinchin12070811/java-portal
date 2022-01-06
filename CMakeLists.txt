cmake_minimum_required(VERSION 3.10.0)
project(protal)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS off)

set(SOURCE_FILES
	src/Main.cpp
)

set(HEADER_FILES
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${PROJECT_NAME} PRIVATE "/ZI")
  target_link_options(${PROJECT_NAME} PRIVATE "/SAFESEH:NO")
endif()