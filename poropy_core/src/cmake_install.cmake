# Install script for directory: /home/brad/workspace/seniorProjoct/poropy/poropy_core/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/python/poropy_core/poropy_core.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/python/poropy_core" TYPE FILE FILES "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/poropy_core.py")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/python/poropy_core/_poropy_core.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/python/poropy_core" TYPE FILE FILES "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/_poropy_core.so")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/FixedDataModel.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/Core.i.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/BaseThermalModel.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/GenException.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/ParamDB.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/BaseSolver.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/Assembly.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/Definitions.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/DBC.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/TestDriver.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/Core.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/FlareSolver.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/SoftEquivalence.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/BaseDataModel.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/State.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/SimpleDataModel.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/Logger.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/MathUtilities.hh"
    "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/ParamDB.i.hh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libporopy_core.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libporopy_core.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libporopy_core.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/libporopy_core.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libporopy_core.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libporopy_core.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libporopy_core.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/xporopy" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/xporopy")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/xporopy"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/brad/workspace/seniorProjoct/poropy/poropy_core/src/xporopy")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/xporopy" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/xporopy")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/xporopy")
    endif()
  endif()
endif()

