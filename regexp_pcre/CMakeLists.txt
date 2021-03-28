cmake_minimum_required(VERSION 3.16)
project(regexp_pcre)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++-11)
set(CMAKE_C_COMPILER clang-11)

set(CMAKE_CXX_FLAGS "-Ofast -mllvm -polly -fPIE")
set(CMAKE_C_FLAGS "-Ofast -mllvm -polly -fPIE")

include_directories(include)
execute_process(COMMAND conan install ${CMAKE_CURRENT_SOURCE_DIR}/ -if=${CMAKE_BINARY_DIR}/ -pr=default)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
include_directories(${CONAN_INCLUDE_DIRS})

#add_executable(regexp_pcre main.cpp )
#target_link_libraries(regexp_pcre -lstdc++ CONAN_PKG::jsoncpp CONAN_PKG::pcre)
add_library(regexp_pcre_lib lib.cpp )
target_link_libraries(regexp_pcre_lib -lstdc++ ${CONAN_LIBS})

install(TARGETS ${PROJECT_NAME}_lib DESTINATION .)
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION ../../../../include/)