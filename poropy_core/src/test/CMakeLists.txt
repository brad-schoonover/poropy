#------------------------------------------------------------------------------#
# Poropy unit tests
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------------#
# Create test executables
#------------------------------------------------------------------------------#

ADD_EXECUTABLE(test_Testing test_Testing.cc)
TARGET_LINK_LIBRARIES(test_Testing poropy_core)

ADD_EXECUTABLE(test_MathUtilities test_MathUtilities.cc)
TARGET_LINK_LIBRARIES(test_MathUtilities poropy_core)

ADD_EXECUTABLE(test_ParamDB test_ParamDB.cc)
TARGET_LINK_LIBRARIES(test_ParamDB poropy_core)

ADD_EXECUTABLE(test_Core test_Core.cc)
TARGET_LINK_LIBRARIES(test_Core poropy_core)

ADD_EXECUTABLE(test_FlareSolver test_FlareSolver.cc)
TARGET_LINK_LIBRARIES(test_FlareSolver poropy_core)


#------------------------------------------------------------------------------#
# Define tests
#------------------------------------------------------------------------------#

ADD_TEST(test_Testing_pass test_Testing 0)
ADD_TEST(test_Testing_fail test_Testing 1)

ADD_TEST(test_MathUtilities_0 test_MathUtilities 0)
ADD_TEST(test_MathUtilities_1 test_MathUtilities 1)
ADD_TEST(test_MathUtilities_2 test_MathUtilities 2)

ADD_TEST(test_ParamDB_0 test_ParamDB 0) 

ADD_TEST(test_Core_0 test_Core 0) 

ADD_TEST(test_FlareSolver_0 test_Core 0) 