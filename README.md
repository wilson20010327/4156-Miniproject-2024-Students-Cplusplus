# Welcome Students of 4156
Please follow the assignment specifications on Courseworks when completing this project.
* [BugsList](./fix_bug.md)
## Coverage 
### Setup 
* Download [lcov](https://github.com/linux-test-project/lcov) 
* Add codes in CMakeList.txt
``` cmake
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
```
### command
```
cd IndividualMiniprojectC++/build
cmake ..
make && make test && make coverage
open CMakeFiles/IndividualMiniprojectTests.dir/src/coverage/index.html
```
