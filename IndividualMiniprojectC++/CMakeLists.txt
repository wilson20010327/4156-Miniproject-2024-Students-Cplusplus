cmake_minimum_required(VERSION 3.15)

project(IndividualMiniproject)

set(INCLUDE_PATHS ~/boost_1_86_0 ~/Crow-1.2.0/include)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add coverage flag
set(CMAKE_BINARY_DIR ~/4156-Miniproject-2024-Students-Cplusplus/IndividualMiniprojectC++/build/CMakeFiles/IndividualMiniprojectTests.dir/src)
set(CMAKE_CXX_FLAGS "-O0 -coverage")
find_program(LCOV lcov REQUIRED)
find_program(GENHTML genhtml REQUIRED)
add_custom_target(coverage
# gather data
COMMAND ${LCOV} --directory . --capture --output-file coverage.info
# generate report
COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
# Main project executable
add_executable(IndividualMiniproject 
    src/main.cpp 
    src/Course.cpp 
    src/Department.cpp 
    src/MyFileDatabase.cpp 
    src/RouteController.cpp
    src/MyApp.cpp
    src/Globals.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    URL https://github.com/google/googletest/archive/ff233bdd4cac0a0bf6e5cd45bda3406814cb2796.zip 
)

FetchContent_MakeAvailable(googletest)

# Include directories for main executable
target_include_directories(IndividualMiniproject PUBLIC 
    ${INCLUDE_PATHS} 
    include
    ~/asio-1.30.2/include
)

target_link_libraries(IndividualMiniproject PRIVATE 
    gtest 
    gtest_main
)

enable_testing()

# Test executable
add_executable(IndividualMiniprojectTests
  test/CourseUnitTests.cpp
  test/DepartmentUnitTests.cpp
  test/MyFileDataBaseUnitTests.cpp
  test/MyAppUnitTests.cpp
  src/Course.cpp
  src/Department.cpp
  src/MyFileDatabase.cpp
  src/MyApp.cpp
)

target_include_directories(IndividualMiniprojectTests PRIVATE 
    ${INCLUDE_PATHS} 
    include
    ~/asio-1.30.2/include
)

target_link_libraries(IndividualMiniprojectTests PRIVATE 
    gtest 
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(IndividualMiniprojectTests)

# Find the cpplint program
find_program(CPPLINT cpplint)

if (CPPLINT)
    # List of source files to be checked by cpplint
    set(SOURCE_FILES
        src/main.cpp 
        src/Course.cpp 
        src/Department.cpp 
        src/MyFileDatabase.cpp 
        src/RouteController.cpp
        src/MyApp.cpp
        src/Globals.cpp
        test/CourseUnitTests.cpp
        test/DepartmentUnitTests.cpp
        test/MyFileDataBaseUnitTests.cpp
        test/MyAppUnitTests.cpp
    )

    # Custom target to run cpplint
    add_custom_target(
        cpplint
        COMMAND ${CPPLINT} --filter=-whitespace,-build/include_what_you_use ${SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running cpplint for Google C++ Style Guide compliance"
    )
else()
    message(WARNING "cpplint not found! Skipping style checks.")
endif()
