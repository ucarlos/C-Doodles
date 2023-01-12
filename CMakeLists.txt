cmake_minimum_required(VERSION 3.14)
project(Doodles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Bitlevel Programs
add_executable(Float_to_IEEv1 Float_to_IEEE_Representation.c)
target_link_libraries(Float_to_IEEv1 m)
add_executable(Problem2_60 Problem2_60.c)
add_executable(Problem2_74 Problem2_74.c)

# STL Implementations
add_executable(My_Vector Test_MyVector.cc)
add_executable(List List.cc)

# C++ Games
#add_executable(Connect_Four Connect_Four.cc)
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
add_executable(Word_Count Word_Count.c)
add_executable(TestDeepCopy TestCopying.cc)
add_executable(TestFunction TestFunction.c)
add_executable(TestEnum Enum.cc)
add_executable(Itoa Itoa.cc)
add_executable(Encoding_Test Encoding_Test.cc)

# TCP Server/Client Test
#add_executable(TCP_Server TCP_Server.cc)
#add_executable(TCP_Client TCP_Client.cc)
#target_link_libraries(TCP_Client boost_system)
#target_link_libraries(TCP_Server boost_system)


# Algorithms
add_executable(Bubble_Sort Bubble_Sort.cc)
add_executable(Disjoint Disjoint.cc)