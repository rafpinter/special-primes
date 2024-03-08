// Nom, Matricule
// Nom, Matricule

#include "PrimeSequenceCalculator.h"
#include <vector>
#include <unordered_set>
// #include <math.h>
//#include <algorithm>
#include <iostream>
#include <string>

// ce fichier contient les definitions des methodes de la classe PrimeSequenceCalculator
// this file contains the definitions of the methods of the PrimeSequenceCalculator class

PrimeSequenceCalculator::PrimeSequenceCalculator()
{
}

void printVector(const std::vector<int>& vec) {
    // debugging
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
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

std::vector<int> PrimeSequenceCalculator::FindPrimesBetween(int min, int max){
    // Find all prime number between min and max
    std::vector<int> prime_numbers;
    for (int ref_number = min; ref_number < max; ref_number++) {
        if (IsPrime(ref_number)) {
            prime_numbers.push_back(ref_number);
        }
    }
    return prime_numbers;
}


std::vector<int> PrimeSequenceCalculator::FindSublistOfPrimes(std::vector<int> & prime_numbers){
    // Finds a sublist of primes with the same digits

    int first_prime = prime_numbers[0];
    std::string string_first_prime = std::to_string(first_prime);
    prime_numbers.erase(prime_numbers.begin());
    std::vector<int> matched_primes;

    matched_primes.push_back(first_prime);
    // ref https://stackoverflow.com/questions/17006808/find-all-permutations-of-a-string-in-c
    do
    {
        int num = std::stoi(string_first_prime);
        if (CheckIfNumberInList(num, prime_numbers)) {
            matched_primes.push_back(num);
            prime_numbers.erase(std::remove(prime_numbers.begin(), prime_numbers.end(), num),
                                prime_numbers.end());
        }
    } while ( std::next_permutation(string_first_prime.begin(), string_first_prime.end()) );

    return matched_primes;
}

std::vector<std::vector<int>> PrimeSequenceCalculator::FindValidSequences(std::vector<int> & primes_same_digits) {

    std::vector<std::vector<int>> sol;

    while (primes_same_digits.size() > 2) {
        int ref_min = primes_same_digits[0];

        primes_same_digits.erase(primes_same_digits.begin());
        for (int j = 0; j < primes_same_digits.size(); j++){
            int k = primes_same_digits[j] - ref_min;

            std::vector<int> tmp_sol;
            tmp_sol.push_back(ref_min);
            tmp_sol.push_back(primes_same_digits[j]);

            int i = 2;
            int next = ref_min + i * k;
            while (CheckIfNumberInList(next, primes_same_digits)) {
                tmp_sol.push_back(next);
                i++;
                next = ref_min + i * k;
            }

            if (tmp_sol.size() > 2) {
                ProcessAndAddToSolution(tmp_sol, sol);
            }
        }
    }

    return sol;
}



bool PrimeSequenceCalculator::CheckIfNumberInList(int N, std::vector<int> list) {
    // Binary search for finding number in a sorted vector
    return std::binary_search(list.begin(), list.end(), N);
}

void PrimeSequenceCalculator::AddValidSeqsToFinalSolution(
        std::vector<std::vector<int>> tmp_solution,
        std::vector<std::vector<int>> & final_solution) {
    // Adds triplets to final solution
    final_solution.insert(final_solution.end(), tmp_solution.begin(), tmp_solution.end());
}

std::vector<std::vector<int>> PrimeSequenceCalculator::ProcessAndAddToSolution(
        std::vector<int> tmp_solution,
        std::vector<std::vector<int>> & solution
        ){
    // Process list of vector in triplets
    if (tmp_solution.size() >= 3) {
        for (size_t i = 0; i <= tmp_solution.size() - 3; ++i) {
            std::vector<int> triplet = {tmp_solution[i], tmp_solution[i + 1], tmp_solution[i + 2]};
            solution.push_back(triplet);
        }
    }
    return solution;
}


std::vector<std::vector<int>> PrimeSequenceCalculator::CalculatePrimeSequences(const int N)
{
    std::vector<std::vector<int>> solution;
    std::vector<std::vector<int>> valid_sequences;
    std::vector<int> primes_list;
    std::vector<int> primes_same_digits;
    int end;

    int k = 100;
    while (k < N) {
        if (10 * k > N) {
            end = N;
        }
        else {
            end = 10 * k;
        }
        primes_list = FindPrimesBetween(k, end);
        while (primes_list.size() > 2) {
            primes_same_digits = FindSublistOfPrimes(primes_list);
            valid_sequences = FindValidSequences(primes_same_digits);
            if (!valid_sequences.empty()) {
                AddValidSeqsToFinalSolution(valid_sequences, solution);
            }
        }
        k = 10 * k;
    }
    std::sort(solution.begin(), solution.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a.front() < b.front();
    });
    return solution;
}