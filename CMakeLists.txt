cmake_minimum_required(VERSION 3.15)

# The following is a hack to allow setting a policy BEFORE the project
# directive. Indeed, this policy is only available for CMake 3.15+ and
# is required for Windows only (this enables the usage of the 
# MSVC_RUNTIME_LIBRARY property).
# Since I do not want to require CMake 3.15 for everyone (this would 
# prevent many users to use their distro-packaged version of CMake)
# The disadvantage is that this hinders cross-compilation and requires 
# that host and target are the same.
message( "CMAKE_HOST_SYSTEM_NAME = ${CMAKE_HOST_SYSTEM_NAME}")
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
  cmake_policy(SET CMP0091 NEW)
endif()

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CRT_LINKAGE static)

project(salimPlugin)

if(STATIC_BUILD)
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_STATIC_RUNTIME ON)
  set(Boost_USE_MULTITHREADED ON)
endif()

find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(jsoncpp CONFIG REQUIRED)

# This is for debugging purposes...
message("jsoncpp_lib     = ${jsoncpp_lib}")
message("Boost_LIBRARIES = ${Boost_LIBRARIES}")

add_library(salimPlugin SHARED salimPlugin.cpp)
target_include_directories(salimPlugin PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../orthanc/Plugins/Include)

target_link_libraries(salimPlugin PRIVATE jsoncpp_lib)
target_link_libraries(salimPlugin PRIVATE ${Boost_LIBRARIES})

set_property(TARGET salimPlugin PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

