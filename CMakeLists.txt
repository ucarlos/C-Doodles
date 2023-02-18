
cmake_minimum_required(VERSION 3.14)
project(Doodles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Bitlevel Programs
add_executable(Float_to_IEEv1 src/Bitlevel-Programs/Float_to_IEEE_Representation.c)
target_link_libraries(Float_to_IEEv1 m)
add_executable(Problem2_60 src/Bitlevel-Programs/Problem2_60.c)
add_executable(Problem2_74 src/Bitlevel-Programs/Problem2_74.c)

# STL Implementations
add_executable(My_Vector src/STL-Implementations/Test_MyVector.cc)
add_executable(List src/STL-Implementations/List.cc)

# C++ Games
#add_executable(Connect_Four Connect_Four.cc)
add_executable(Tic_Tak_Toe src/Games/TicTacToe.cc)
add_executable(Snake src/Games/Snake.cc)

# Standalone Programs
add_executable(Integer_to_English src/Standalone/Integer_to_English.cc)
add_executable(Check_Digits src/Standalone/Check_Strings_For_Digits.c)
add_executable(Mark_Example src/Standalone/Mark_Example.cc)
add_executable(Caesar_Cypher src/Standalone/Caesar_Cypher.cc)

# Requires Linking: Commented out for Windows
#add_executable(Newt Newt.cpp)
#target_link_libraries(Newt newt)

# Test Programs
add_executable(Word_Count src/Test-Programs/Word_Count.c)
add_executable(TestDeepCopy src/Test-Programs/TestCopying.cc)
add_executable(TestFunction src/Test-Programs/TestFunction.c)
add_executable(TestEnum src/Test-Programs/Enum.cc)
add_executable(Itoa src/Test-Programs/Itoa.cc)
add_executable(Encoding_Test src/Test-Programs/Encoding_Test.cc)

# Algorithms
add_executable(Bubble_Sort src/Algorithms/Bubble_Sort.cc)
add_executable(Disjoint src/Algorithms/Disjoint.cc)

# Regex Programs
add_executable(Japanese_Regex_Test src/Regex/Japanese_Regex_Test.cc)
add_executable(GetAllRegexMatches src/Regex/GetAllRegexMatches.cc)
add_executable(Databases main.cpp)

