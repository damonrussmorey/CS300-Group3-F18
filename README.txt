This is a fun project!

Document links:
  Requirements
  https://docs.google.com/document/d/1VVRtT8Bagtg6XWmBbnYXdioFyLTKA0IeCZ0oR9lsJ7I/edit?usp=sharing
  Design:
  https://docs.google.com/document/d/15J1Y1fHEFWMtBEzHijU7zVx3vwKrxRT6RjqQ1FPyXp0/edit?usp=sharing
  Test:
  https://docs.google.com/document/d/1jSgFzduvDiMJ-ywP_bxDs4WD1aTDJ83w8HVdXMtB--A/edit?usp=sharing
  Presentation:
  https://docs.google.com/presentation/d/1uvMDj10YuBkS1RQgOFaU9Ruf5H_6td8T-bgskhWYn6U/edit?usp=sharing

 
======= How to run ChocAn Program Demo =======

***In main project directory***
make
cd bin
./Demo

***CRITICAL NOTE***
DO NOT DO
./bin/Demo

WILL ENCOUTER ERRORS WITH FILE WRITES

======= How to install Google Test =======
Instructions from https://www.srcmake.com/google-cpp-test-framework
***If any problems are encountered, view link, it includes a video tutorial***

Ultimately, what we are trying to do is install
google test to the user's lib folder. (/usr/lib)

We will also have to install cmake
For Linux, this can be done with the following terminal commands
from the user's home directory.

sudo apt-get install libgtest-dev
sudo apt-get install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib


Now google tests should be installed and useable.


For our ChocAn project, tests are compiled and run in the following way.
***from directory 'test'***
make
./executeTests
make clean     //Cleaning can be a good habit


======= Extra On Making and Setting up Google Test =======
To actually start makeing and running tests, create the following files in
the relevant project directory

vim some_prog.cpp //The project you want to test
vim some_prog_test.cpp //The test program where the google test framework
		       //will be used to write tests
vim CMakeLists.txt //used to setup Makefile and other stuff(only used when first seting up test,
		   //or when you've made new testprograms in new files you want to be run

For CMakeLists.txt the following will need to be copied in

***Text again from https://www.srcmake.com/google-cpp-test-framework ***

cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(executeTests ***some_prog_test***.cpp)
target_link_libraries(executeTests ${GTEST_LIBRARIES} pthread)

***End of text to copy***

Everytime the list of test programs to run (add_executable ...) is edited do the following
in the project folder to update the Makefile and other files for running tests.

cmake CMakeLists.txt

And that should be it...
