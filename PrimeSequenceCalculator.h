// Nom, Matricule
// Nom, Matricule

#include <vector>
// ce fichier contient les declarations des methodes de la classe PrimeSequenceCalculator
// peut être modifié si vous voulez ajouter d'autres méthodes à la classe
// this file contains the declarations of the methods of the PrimeSequenceCalculator class
// can be modified if you wish to add other methods to the class

class PrimeSequenceCalculator{
    public :
        PrimeSequenceCalculator();

//    std::vector<int> GeneratePrimesUpToN(int N);
    bool IsPrime(int number);
    std::vector<int> FindPrimesBetween(int min, int max);
    std::vector<int> FindSublistOfPrimes(std::vector<int> & prime_numbers);
    std::vector<std::vector<int>> FindValidSequences(std::vector<int> & primes_same_digits);
    bool CheckIfNumberInList(int N, std::vector<int> list);
    void AddValidSeqsToFinalSolution(std::vector<std::vector<int>> tmp_solution, std::vector<std::vector<int>> & final_solution);
    std::vector<std::vector<int>> ProcessAndAddToSolution(std::vector<int> tmp_solution, std::vector<std::vector<int>> & solution);
    std::vector<std::vector<int>> CalculatePrimeSequences(const int N);
};