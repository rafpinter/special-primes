// Nom, Matricule
// Nom, Matricule

#include "PrimeSequenceCalculator.h"
#include <vector>
#include <unordered_set>
// #include <math.h>
// #include <algorithm>
// #include <iostream>
// #include <string>
// ce fichier contient les definitions des methodes de la classe PrimeSequenceCalculator
// this file contains the definitions of the methods of the PrimeSequenceCalculator class

PrimeSequenceCalculator::PrimeSequenceCalculator()
{
}

std::unordered_set<int> PrimeSequenceCalculator::CalculateNthPrime(int N)
{
    int prime_number = 2;
    int ref_number = 2;
    std::unordered_set<int> prime_numbers;

    while (prime_numbers.size() < N)
    {
        ref_number++;
        if(IsPrime(ref_number))
        {
            prime_numbers.insert(ref_number);
            prime_number = ref_number;
        }
    }
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
}

bool PrimeSequenceCalculator::CheckIfNumberInList(int N, std::unordered_set<int> set){
    return set.find(N) != set.end();
}

std::vector<std::vector<int>> PrimeSequenceCalculator::AddTmpSequenceToFinalSolution(std::vector<int> tmp_solution, std::vector<std::vector<int>> final_solution) {
    // TODO process tmp_solution and add to final solution
    return final_solution
}

std::vector<std::vector<int>> PrimeSequenceCalculator::CalculatePrimeSequences(const int N)
{
    // TODO
    // À compléter / To be completed

    // n <- números primos até N
    std::unordered_set<int> prime_numbers = CalculateNthPrime(N);
//    size_t length = prime_numbers.size();

    std::vector<std::vector<int>> all_valid_solutions;

    for (auto& ni : prime_numbers) {

        // filtra números com os mesmos dígitos
        std::vector<int> filtered_prime_numbers = FindNumbersWithSameDigits(ni, prime_numbers);
        if (filtered_prime_numbers.size() < 3){
            // TODO: passa a vez
        }

        //
        std::vector<int> tmp_solution;
        for (auto& fj : filtered_prime_numbers) {
            int ref = fj - ni;
            int x = 1;
            int n_temp = ni + ref * x;
            while (n_temp < N) {
                bool n_temp_found_in_prime_numbers = CheckIfNumberInList(n_temp, prime_numbers);
                if (n_temp_found_in_prime_numbers) {
                    tmp_solution.push_back(n_temp);
                } else {
                    // TODO break the cycle
                }
                x++;
                n_temp = ni + ref * x;
            }
            if (tmp_solution.size() < 3) {
                // pass
            } else {
                AddTmpSequenceToFinalSolution(tmp_solution, all_valid_solutions);
            }

        }
    }
    return all_valid_solutions;
}
