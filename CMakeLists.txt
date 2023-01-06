cmake_minimum_required(VERSION 3.14) # GoogleTest requires CMake>= 3.14 and at least C++14
set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME RngStreams) # definitions for the project 
project(${PROJECT_NAME})


option(RngStreams_BUILD_SHARED_LIBS "Compile RngStreams as a shared library" ON)
if(RngStreams_BUILD_SHARED_LIBS)
  add_library(${PROJECT_NAME}
    SHARED
      src/share/RngStream.cpp
      src/share/RngStream.h
  )
  message(STATUS "Configuring ${PROJECT_NAME} shared library")
else()
  add_library(${PROJECT_NAME}
    STATIC
      src/share/RngStream.cpp
      src/share/RngStream.h
  )
  message(STATUS "Configuring ${PROJECT_NAME} static library")
endif()
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Configurations
if(CMAKE_CONFIGURATION_TYPES)
  # i.e. Visual Studio or Xcode Definition of available build configurations,
  # Release and Debug.
  set(CMAKE_CONFIGURATION_TYPES "Release;Debug")
else()
  # For single configuration generators, default build type is Release.
  set(default_build_type "Release")
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(
      STATUS
        "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE
        "${default_build_type}"
        CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
  endif()
  message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()


# ###################################################
# ## OPTION 1: Fetch the googleTest code online 
# ###################################################
# # Needed to change default about timestamps in the downloaded stuff
# if(POLICY CMP0135) 
#   cmake_policy(SET CMP0135 NEW)
# 	set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
# endif()

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)
# find_package(PkgConfig)
# pkg_search_module(GTEST REQUIRED gtest_main)
# ###################################################
# ## END OPTION 1: Fetch the googleTest code online 
# ###################################################


###################################################
## OPTION 2: Clone the google test repo locally 
#  git clone https://github.com/google/googletest
###################################################
# add_subdirectory(googletest) # add googletest subdirectory
# include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>
###################################################
## END OPTION 2: Clone the google test repo locally 
###################################################

###################################################
## OPTION 3: Use the system installed google test 
###################################################
find_package(GTest REQUIRED)

include_directories(src/share) # this is so we can #include "classX.hpp"

# this builds the executable with the main entry in main()
add_executable(${PROJECT_NAME}_exec 
  src/main.cpp 
  src/share/RngStream.cpp      # EDIT THIS 
)

enable_testing()
add_executable(${PROJECT_NAME}_test 
  src/share/RngStream.cpp 
  tests/utest-RngStream_original.cpp 
  tests/utest-RngStream_augmentations.cpp  # EDIT THIS
)

target_link_libraries(${PROJECT_NAME}_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test )


include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG>
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG>
)

install(FILES src/share/RngStream.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Config.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

message(STATUS "${PROJECT_NAME} configured.")