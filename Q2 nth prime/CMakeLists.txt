cmake_minimum_required(VERSION 3.27)
project(Q2_nth_prime)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Q2_nth_prime
        nth_prime.cpp
        PrimeCalculator.cpp
        PrimeCalculator.h
        nth_prime_origina.cpp)