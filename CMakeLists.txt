cmake_minimum_required(VERSION 3.14)
project(Doodles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

#add_executable(Doodles main.cpp)
add_executable(Check_Digits Check_Strings_For_Digits.c)
add_executable(Test_String stringconcat_test.c)
add_executable(Word_Count Word_Count.c)
add_executable(javascript javascript.cpp)
add_executable(Homework02_06 Homework02_06.cc)
add_executable(Newt Newt.cpp)
add_executable(Caesar_Cypher Caesar_Cypher.cc)
add_executable(Tic_Tak_Toe Tic_Tak_Toe.cc)
add_executable(My_Vector Test_MyVector.cc My_Vector.cc)
add_executable(OS_Homework02 Homework2.c)
add_executable(OS_Homework03 Homework3.cc)
add_executable(Integer_to_English Integer_to_English.cc)


add_executable(TagReader tagreader.cpp)
target_include_directories(TagReader PUBLIC /usr/include/taglib)
target_link_libraries(TagReader tag)

target_link_libraries(OS_Homework02 pthread)
target_link_libraries(OS_Homework03 pthread)
target_link_libraries(Newt newt)