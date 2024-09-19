
### Find in OS
find_package(Boost REQUIRED COMPONENTS
  system
  thread
  date_time
  iostreams
  chrono
)
include_directories(${Boost_INCLUDE_DIRS})

### By Conan
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