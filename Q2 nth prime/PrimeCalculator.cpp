// Rafaela Souza Pinter, 20266933

#include "PrimeCalculator.h"
#include <vector>
#include <math.h>
#include <iostream> // pour l'affichage dans la console // for display in console

// ce fichier contient les definitions des methodes de la classe PrimeCalculator
// this file contains the definitions of the methods of the PrimeCalculator class

PrimeCalculator::PrimeCalculator()
{

}

std::vector<int> PrimeCalculator::CalculateNthPrime(int N)
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
        ref_number++;
        if(IsPrime(ref_number))
        {
            prime_number = ref_number;
            prime_numbers.push_back(prime_number);
        }
    }
    // Found prime
    return prime_numbers;
}

bool PrimeCalculator::IsPrime(int number) {
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