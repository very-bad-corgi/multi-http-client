cmake_minimum_required(VERSION 3.5)

project(multi-http-client LANGUAGES CXX)

# Conan переопределит компилятор и версию c++ для сборки зависимостей, 
#   поэтому вынесем его до определения этих параметров всего проекта
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake OPTIONAL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
#set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang++")

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

find_package(fmt REQUIRED)
find_package(CURL REQUIRED)
find_package(inih REQUIRED)
find_package(Boost REQUIRED COMPONENTS
  system
  thread
  date_time
  iostreams
  chrono
)
include_directories(${Boost_INCLUDE_DIRS})

###
### Source code
include_directories(
  include/core/
  include/handlers/
)
file(GLOB_RECURSE SOURCE_CODE 
  src/*.cpp include/*.h
)

###
### Target file
add_executable(${PROJECT_NAME} ${SOURCE_CODE})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} ${CURL_LIBRARIES} fmt::fmt inih::inih Boost::system Boost::thread)

###
### Need for QtCreator
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
