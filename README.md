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
## Static check 
### Setup
* Download cppcheck
```bash
sudo apt-get install cppcheck
```
### Static check file
```bash
cd IndividualMiniprojectC++/src
cppcheck *.cpp
```
output
```
Checking Course.cpp ...
1/7 files checked 10% done
Checking Department.cpp ...
2/7 files checked 22% done
Checking Globals.cpp ...
3/7 files checked 22% done
Checking MyApp.cpp ...
4/7 files checked 41% done
Checking MyFileDatabase.cpp ...
5/7 files checked 47% done
Checking RouteController.cpp ...
6/7 files checked 98% done
Checking main.cpp ...
7/7 files checked 100% done
```