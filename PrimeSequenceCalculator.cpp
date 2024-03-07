// Nom, Matricule
// Nom, Matricule

#include "PrimeSequenceCalculator.h"
#include <vector>
#include <unordered_set>
// #include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
// ce fichier contient les definitions des methodes de la classe PrimeSequenceCalculator
// this file contains the definitions of the methods of the PrimeSequenceCalculator class

PrimeSequenceCalculator::PrimeSequenceCalculator()
{
}

void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}


std::vector<int> PrimeSequenceCalculator::GeneratePrimesUpToN(int N)
{
    // a completer
    // TODO
    int prime_number = 2;
    int ref_number = 2;
    std::vector<int> prime_numbers;

    // Loop to find the next prime.
    // Counts the number of primes already found.
    while (prime_number < N)
    {
        if(IsPrime(ref_number))
        {
            prime_number = ref_number;
            prime_numbers.push_back(prime_number);
        }
        ref_number++;
    }
    // Found prime
    printVector(prime_numbers);
    return prime_numbers;
}

bool PrimeSequenceCalculator::IsPrime(int number) {
    // Inspiration from https://www.linkedin.com/pulse/nth-prime-number-ebubechukwu-oguaju-dike-/
    if (number <= 1)
        return false;
    if (number <= 3)
        return true;
    if (number % 2 == 0 || number % 3 == 0)
        return false;
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0)
            return false;
    }
    return true;
}

std::vector<int> PrimeSequenceCalculator::FindNumbersWithSameDigits(int N, std::vector<int> prime_numbers){
    // TODO Finds numbers that are permutations of the digits in the number N
    // Makes a copy para não alterar o mesmo lugar na memória
    std::vector<int> permutations;
    std::string refString = std::to_string(N);
    std::sort(refString.begin(), refString.end());

    for(int num : prime_numbers) {
        std::string numString = std::to_string(num);
        std::sort(numString.begin(), numString.end());
        if (numString == refString) {
            permutations.push_back(num);
        }
    }
    return permutations;
}

bool PrimeSequenceCalculator::CheckIfNumberInList(int N, std::vector<int> list) {
    return std::binary_search(list.begin(), list.end(), N);
}

std::vector<std::vector<int>> PrimeSequenceCalculator::AddTmpSolutionToFinalSolution(std::vector<int> tmp_solution, std::vector<std::vector<int>> final_solution) {
    if (tmp_solution.size() >= 3) {
        for (size_t i = 0; i <= tmp_solution.size() - 3; ++i) {
            std::vector<int> sub_vector(tmp_solution.begin() + i, tmp_solution.begin() + i + 3);
            final_solution.push_back(sub_vector);
        }
    }
    return final_solution;
}

std::vector<std::vector<int>> PrimeSequenceCalculator::CalculatePrimeSequences(const int N)
{
    // TODO
    // À compléter / To be completed
    // n <- números primos até N
    std::vector<int> prime_numbers;
    prime_numbers = GeneratePrimesUpToN(N);
    size_t length = prime_numbers.size();

    std::vector<std::vector<int>> all_valid_solutions;

    std::cout << "Hello, world!" << std::endl;

    for (int i = 0; i < length; i++) {
        int ni = prime_numbers[i];

        // filtra números com os mesmos dígitos
        std::vector<int> filtered_prime_numbers = FindNumbersWithSameDigits(ni, prime_numbers);
        if (filtered_prime_numbers.size() < 3){
            // TODO: passa a vez
            continue;
        }

        std::vector<int> tmp_solution;
        for (int j = i; j < length; j++) {
            int ref = filtered_prime_numbers[j] - ni;
            int x = 1;
            int n_temp = ni + ref * x;
            while (n_temp < N) {
                bool n_temp_found_in_prime_numbers = CheckIfNumberInList(n_temp, prime_numbers);
                if (n_temp_found_in_prime_numbers) {
                    tmp_solution.push_back(n_temp);
                } else {
                    // TODO break the cycle
                    break;
                }
                x++;
                n_temp = ni + ref * x;
            }
            if (tmp_solution.size() < 3) {
                // pass
            } else {
                AddTmpSolutionToFinalSolution(tmp_solution, all_valid_solutions);
            }

        }
    }
    return all_valid_solutions;
}