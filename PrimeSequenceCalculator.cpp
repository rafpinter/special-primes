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
    // a completer
    // TODO
//    std::cout << "Achando primos..." << std::endl;
    std::vector<int> prime_numbers;

    // Loop to find the next prime.
    // Counts the number of primes already found.
    for (int ref_number = min; ref_number < max; ref_number++) {
        if (IsPrime(ref_number)) {
            prime_numbers.push_back(ref_number);
        }
    }
    // Found prime
//    printVector(prime_numbers);
    return prime_numbers;
}


std::vector<int> PrimeSequenceCalculator::FindSublistOfPrimes(std::vector<int> & prime_numbers){
    // TODO
    // preciso pegar o primeiro número da primes_numbers (removendo-o da lista) e
    // achar todas as permutações que são primos também nessa lista.
    // toda vez que acessar um número da lista, remover inplace da prime_numbers
    // Exemplo: prime_numbers: [113, 131, 311, 997]
    // Retorna: [113, 131, 311]
    // prime_numbers: [997]
    // Step 1: Extract the first prime number.
//    std::cout << "Achando subset de primos..." << std::endl;
    int first_prime = prime_numbers[0];
    std::string string_first_prime = std::to_string(first_prime);

    // Remove the first prime number from the original list.
    prime_numbers.erase(prime_numbers.begin());

    // Step 2: Generate all unique permutations of the first prime number.
    std::sort(string_first_prime.begin(), string_first_prime.end());
    std::unordered_set<int> prime_permutations;

    do {
        int perm = std::stoi(string_first_prime);
        prime_permutations.insert(perm);
    } while (std::next_permutation(string_first_prime.begin(), string_first_prime.end()));

    std::vector<int> matching_primes;
    auto it = prime_numbers.begin();

    while (it != prime_numbers.end()) {
        if (prime_permutations.find(*it) != prime_permutations.end()) {
            matching_primes.push_back(*it);
            it = prime_numbers.erase(it); // This also advances the iterator.
        } else {
            ++it;
        }
    }

    // Including the first prime number in the result if it's a permutation of itself.
    if (prime_permutations.find(first_prime) != prime_permutations.end()) {
        matching_primes.insert(matching_primes.begin(), first_prime);
    }
//    printVector(matching_primes);
    return matching_primes;
//    printVector(matching_primes);
}

std::vector<std::vector<int>> PrimeSequenceCalculator::FindValidSequences(
        std::vector<int> & primes_same_digits) {
    //
//    std::cout << "Achando sequencia válida de primos..." << std::endl;
    std::vector<std::vector<int>> sol;

//    printVector(primes_same_digits);

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
    return std::binary_search(list.begin(), list.end(), N);
}

void PrimeSequenceCalculator::AddValidSeqsToFinalSolution(
        std::vector<std::vector<int>> tmp_solution,
        std::vector<std::vector<int>> & final_solution) {
    // tmp_solution = [[e, f, g], [f, g, h]]
    // solution = [[a, b, c], [b, c, d]]
    // modifies solution (inplace) to:
    //      [[a, b, c], [b, c, d], [e, f, g], [f, g, h]]
//    std::cout << "Adicionando valid seqs na solução..." << std::endl;
    final_solution.insert(final_solution.end(), tmp_solution.begin(), tmp_solution.end());
}

std::vector<std::vector<int>> PrimeSequenceCalculator::ProcessAndAddToSolution(
        std::vector<int> tmp_solution,
        std::vector<std::vector<int>> & solution
        ){
    // tmp_solution = [a, b, c, d]
    // solution = [[]] or [[...]]
    // returns
    //      solution = [[a, b, c], [b, c, d]]
    // Check if tmp_solution has at least 3 elements to form a triplet
//    std::cout << "Processando e adicionando na solução..." << std::endl;
    if (tmp_solution.size() >= 3) {
        for (size_t i = 0; i <= tmp_solution.size() - 3; ++i) {
            // Extract the triplet [i, i+1, i+2]
            std::vector<int> triplet = {tmp_solution[i], tmp_solution[i + 1], tmp_solution[i + 2]};
            // Add the triplet to the solution vector
            solution.push_back(triplet);
        }
    }
    // Return the updated solution for consistency, even though it's modified in place
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
    std::cout << "Iniciando..." << std::endl;
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