find_package (GTest REQUIRED)
enable_testing()

include_directories (${algorithms2_SOURCE_DIR}/lib/include
                     ${GTEST_INCLUDE_DIRS}
                     )
					 
add_executable (pqtest priorityqueue_test.cpp)
target_link_libraries (pqtest
                       algolib
                       GTest::GTest
                       )
add_test (NAME PQTest COMMAND pqtest)
