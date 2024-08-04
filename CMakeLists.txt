cmake_minimum_required(VERSION 3.5)

project(multi-http-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
#include(conanbuildinfo.cmake)
#conan_basic_setup()

include(cmake/dependencies.cmake)

include_directories(include)
file(GLOB_RECURSE SOURCE_CODE src/*.cpp include/*.h)

add_executable(${PROJECT_NAME} ${SOURCE_CODE})

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES} Boost::system Boost::thread)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
