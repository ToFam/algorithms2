find_package (GTest REQUIRED)
enable_testing()

include_directories (${algorithms2_SOURCE_DIR}/lib/include
                     ${GTEST_INCLUDE_DIRS}
)

macro (addTest name)
    add_executable (${name} ${name}.cpp)
    target_link_libraries (${name} algolib GTest::GTest)
    add_test (NAME ${name} COMMAND ${name})
endmacro()

addTest (priorityqueue_test)
addTest (adressable_pq_test)
