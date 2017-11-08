#------------------------------------------------------------------------------#
# src/CMakeLists.txt
#------------------------------------------------------------------------------#

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#------------------------------------------------------------------------------#
# SOURCE
#------------------------------------------------------------------------------#

set(SRC
    Assembly.cc
    Core.cc
    GenException.cc
    BaseSolver.cc
    FlareSolver.cc
    ParamDB.cc
    BaseDataModel.cc
    SimpleDataModel.cc
    FixedDataModel.cc
    BaseThermalModel.cc
)

#------------------------------------------------------------------------------#
# SHARED LIBRARY
#------------------------------------------------------------------------------#

add_library(poropy_core
            SHARED
            ${SRC} 
)

#------------------------------------------------------------------------------#
# EXECUTABLE
#------------------------------------------------------------------------------#

add_executable(xporopy
               poropy.cc
               ${SRC} 
)

#------------------------------------------------------------------------------#
# TESTING
#------------------------------------------------------------------------------#

if(POROPY_ENABLE_TEST)
  include_directories(${SRC_DIR}/test)
  add_subdirectory(${SRC_DIR}/test)
endif()

#------------------------------------------------------------------------------#
# INSTALLATION
#------------------------------------------------------------------------------#

INSTALL_TARGETS(/bin xporopy)
INSTALL_FILES(/include .hh)
INSTALL_TARGETS(/lib poropy_core)

#-------------------------------------#
# PYTHON BINDINGS
#-------------------------------------#

set_source_files_properties(poropy.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(poropy_core python poropy.i)
SWIG_LINK_LIBRARIES(poropy_core
                    ${PYTHON_LIBRARIES} 
                    poropy_core)

# Install the module and library
install(FILES ${CMAKE_BINARY_DIR}/src/poropy_core.py
        DESTINATION ${CMAKE_INSTALL_PREFIX}/python/poropy_core)
install(FILES ${CMAKE_BINARY_DIR}/src/_poropy_core.so
        DESTINATION ${CMAKE_INSTALL_PREFIX}/python/poropy_core)
