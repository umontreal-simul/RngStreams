project(RngStreams LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5)

option(RngStreams_BUILD_SHARED_LIBS "Compile RngStreams as a shared library" ON)
if(RngStreams_BUILD_SHARED_LIBS)
  add_library(${PROJECT_NAME}
    SHARED
      src/RngStream.cpp
      src/RngStream.h
  )
  message(STATUS "Configuring ${PROJECT_NAME} shared library")
else()
  add_library(${PROJECT_NAME}
    STATIC
      src/RngStream.cpp
      src/RngStream.h
  )
  message(STATUS "Configuring ${PROJECT_NAME} static library")
endif()
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
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

if (${PROJECT_NAME}_BUILD_TESTS)
  add_subdirectory(tests/doctest)
  # find_package(doctest REQUIRED)
  enable_testing()
  add_subdirectory(tests/)
endif()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG>
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG>
)

install(FILES RngStream.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Config.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

message(STATUS "${PROJECT_NAME} configured.")
