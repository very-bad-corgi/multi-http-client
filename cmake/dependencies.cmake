 
#find_package(CURL REQUIRED)

find_package(Boost REQUIRED COMPONENTS
  system
  thread
  date_time
  iostreams
  chrono
)
include_directories(${Boost_INCLUDE_DIRS})
# find_package(Boost 1.70.0 COMPONENTS system system-config filesystem REQUIRED)
# find_package(Boost 1.70.0 COMPONENTS asio chrono date_time atomic atomic-config REQUIRED)
