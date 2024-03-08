cmake_minimum_required(VERSION 3.27)
project(Q2_Nombres_Premiers_En_Sequence)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Q2_Nombres_Premiers_En_Sequence
        prime_numbers_sequences.cpp
        PrimeSequenceCalculator.cpp
        PrimeSequenceCalculator.h
        test/test.h
        test/test.h
        test/test.h
        test/test.cpp)
