#-------------------------------------------------------------------------------
# Poropy CMake Configuration
#-------------------------------------------------------------------------------

#------------------------------------------------------------------------------#
# PROJECT
#------------------------------------------------------------------------------#

project(poropy-core)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(POROPY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(Python_ADDITONAL_VERSIONS 3.4)
find_package( PythonInterp 3 REQUIRED )
find_package( PythonLibs 3 REQUIRED )

#------------------------------------------------------------------------------#
# CMAKE MODULES
#------------------------------------------------------------------------------#

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/tools/CMake")

#------------------------------------------------------------------------------#
# USER OPTIONS
#------------------------------------------------------------------------------#

# Set the default build type (debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build, options are: Debug Release." FORCE)
endif()

#------------------------------------------------------------------------------#
# EXTERNAL LIBRARIES
#------------------------------------------------------------------------------#

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${PROJECT_BINARY_DIR}/config)
set(CMAKE_SWIG_FLAGS "-v")

#------------------------------------------------------------------------------#
# CONFIGURATION
#------------------------------------------------------------------------------#

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include(GetTheDate)
get_the_date(POROPY_COMPILED_D POROPY_COMPILED_M POROPY_COMPILED_Y)

set(POROPY_WC_REVISION_HASH "unknown")
find_package(Git)
if(GIT_FOUND)
  GIT_WC_INFO(${CMAKE_CURRENT_SOURCE_DIR} "poropy-core")
endif()

# Write config file, install it, and include that directory for all source
set(POROPY_CONFIG_IN  "${CMAKE_CURRENT_SOURCE_DIR}/poropy_config.h.in")
set(POROPY_CONFIG_OUT "${PROJECT_BINARY_DIR}/config/poropy_config.h")
configure_file(${POROPY_CONFIG_IN} ${POROPY_CONFIG_OUT})
include_directories("${PROJECT_BINARY_DIR}/config")

#------------------------------------------------------------------------------#
# TESTING
#------------------------------------------------------------------------------#

option(USE_TESTING "Build testing" ON)
if (POROPY_ENABLE_TEST)
    enable_testing()
    include(CTest)
endif()

#------------------------------------------------------------------------------#
# SOURCE
#------------------------------------------------------------------------------#

include_directories(src)
add_subdirectory(src)

#------------------------------------------------------------------------------#
# INSTALL
#------------------------------------------------------------------------------#

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR} CACHE STRING
      "Installation prefix; default is build directory."
      FORCE)
endif()

#------------------------------------------------------------------------------#
# OUTPUT
#------------------------------------------------------------------------------#

message(" ")
message("---------------------------------------------------------------")
message("              SUMMARY OF CMAKE CONFIGURATION")
message("---------------------------------------------------------------")
message("++++ System:      ${CMAKE_SYSTEM} ${CMAKE_SYSTEM_PROCESSOR}")
message("++++ CXX:         ${CMAKE_CXX_COMPILER}")
message("++++ Build type:  ${CMAKE_BUILD_TYPE}")
message("++++ Install:     ${CMAKE_INSTALL_PREFIX}")
message("++++ Git SHA1:    ${POROPY_WC_REVISION}")
message(" ")
message("---------------------------------------------------------------")
message("                      BUILD OPTIONS")
message("---------------------------------------------------------------")
if(POROPY_ENABLE_DBC)
  message("++++++ DBC:     enabled")
else()
  message("++++++ DBC:     disabled")
endif()
if(POROPY_ENABLE_TEST)
  message("++++++ Testing: enabled")
else()
  message("++++++ Testing: disabled")
endif()
message("---------------------------------------------------------------")

