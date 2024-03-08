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
    // inspiration from https://stackoverflow.com/questions/10750057/how-do-i-print-out-the-contents-of-a-vector
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) { // just adding some commas between the numbers
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
    // loop to test all numbers
    for (int ref_number = min; ref_number < max; ref_number++) {
        if (IsPrime(ref_number)) {
            // if it's prime, add to the list
            prime_numbers.push_back(ref_number);
        }
    }
    return prime_numbers;
}


std::vector<int> PrimeSequenceCalculator::FindSublistOfPrimes(std::vector<int> & prime_numbers){
    // Finds a sublist of primes with the same digits

    // Takes the first number as a reference
    // Remove from prime_numbers
    int first_prime = prime_numbers[0];
    std::string string_first_prime = std::to_string(first_prime);
    prime_numbers.erase(prime_numbers.begin());
    // add to matched_primes
    std::vector<int> matched_primes;
    matched_primes.push_back(first_prime);

    // ref https://stackoverflow.com/questions/17006808/find-all-permutations-of-a-string-in-c
    do
    {
        int num = std::stoi(string_first_prime);
        // if permutation is in the list, add to matched_primes and remove from prime_numbers
        if (CheckIfNumberInList(num, prime_numbers)) {
            matched_primes.push_back(num);
            prime_numbers.erase(std::remove(prime_numbers.begin(), prime_numbers.end(), num),
                                prime_numbers.end());
        }
    } while ( std::next_permutation(string_first_prime.begin(), string_first_prime.end()) );

    return matched_primes;
}

std::vector<std::vector<int>> PrimeSequenceCalculator::FindValidSequences(std::vector<int> & primes_same_digits) {
    // Calculates if there is a valid sequence in the primes with same digits

    std::vector<std::vector<int>> sol;
    // while there's still hope to find a sequence at least of 3
    while (primes_same_digits.size() > 2) {
        // get the ref and remove from list
        int ref_min = primes_same_digits[0];
        primes_same_digits.erase(primes_same_digits.begin());

        // main loop
        for (int j = 0; j < primes_same_digits.size(); j++){
            // diff between ref and next on the list
            int k = primes_same_digits[j] - ref_min;

            std::vector<int> tmp_sol;
            tmp_sol.push_back(ref_min);
            tmp_sol.push_back(primes_same_digits[j]);

            // Now try to find if there is arithmetic progression
            int i = 2;
            int next = ref_min + i * k;
            while (CheckIfNumberInList(next, primes_same_digits)) {
                tmp_sol.push_back(next);
                i++;
                next = ref_min + i * k;
            }
            // if so, and if list is long enough, add to the solution
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
    // variables
    std::vector<std::vector<int>> solution;
    std::vector<std::vector<int>> valid_sequences;
    std::vector<int> primes_list;
    std::vector<int> primes_same_digits;
    int end;
    // start at 100 because below this number it's impossible to have a sequence of 3 permutations
    // with the same digits
    int k = 100;

    // loop to compare only numbers with the same "number" of digits
    while (k < N) {
        // finding the upper bound of the primes list
        if (10 * k > N) {
            end = N;
        }
        else {
            end = 10 * k;
        }
        // Finding all primes in the range
        primes_list = FindPrimesBetween(k, end);
        // While we haven't processed all the list
        while (primes_list.size() > 2) {
            // Find a sublist of primes with the same digits
            primes_same_digits = FindSublistOfPrimes(primes_list);
            // Searches for valid sequences within that list
            valid_sequences = FindValidSequences(primes_same_digits);
            // If we found some, add to the solutions vector in the right format
            if (!valid_sequences.empty()) {
                AddValidSeqsToFinalSolution(valid_sequences, solution);
            }
        }
        k = 10 * k;
    }
    // Sorting by first number of every subvector
    std::sort(solution.begin(), solution.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a.front() < b.front();
    });
    return solution;
}