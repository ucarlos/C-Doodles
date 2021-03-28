cmake_minimum_required(VERSION 3.14)
project(Doodles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Bitlevel Programs
add_executable(DisplayFloatingBits DisplayFloatingBits.c)
add_executable(Float_to_IEEv1 Float_to_IEEE_Representation.c)

# STL Implementations
add_executable(My_Vector Test_MyVector.cc My_Vector.cc)
add_executable(List List.cc)

# C++ Games
add_executable(Connect_Four Connect_Four.cc)
add_executable(Tic_Tak_Toe TicTacToe.cc)
add_executable(Snake Snake.cc)

# Standalone Programs
add_executable(Integer_to_English Integer_to_English.cc)
add_executable(Check_Digits Check_Strings_For_Digits.c)
add_executable(Mark_Example Mark_Example.cc)
add_executable(Caesar_Cypher Caesar_Cypher.cc)

# Requires Linking: Commented out for Windows
#add_executable(Newt Newt.cpp)
#target_link_libraries(Newt newt)

# Test Programs
add_executable(Test_String stringconcat_test.c)
add_executable(Word_Count Word_Count.c)
add_executable(Homework02_06 Homework02_06.cc)
add_executable(TestDeepCopy TestCopying.cc)
add_executable(TestFunction TestFunction.c)
add_executable(TestEnum Enum.cc)
add_executable(TestGrade grade.cc)

# Algorithms
add_executable(Bubble_Sort Bubble_Sort.cc)
add_executable(Disjoint Disjoint.cc)