// Nom, Matricule
// Nom, Matricule

#include <vector>
#include <unordered_set>
// ce fichier contient les declarations des methodes de la classe PrimeSequenceCalculator
// peut être modifié si vous voulez ajouter d'autres méthodes à la classe
// this file contains the declarations of the methods of the PrimeSequenceCalculator class
// can be modified if you wish to add other methods to the class

class PrimeSequenceCalculator{
    public :
        PrimeSequenceCalculator();
        bool IsPrime(int N);
        std::vector<int> CalculateNthPrime(int N);
        std::vector<int> FindNumbersWithSameDigits(int N, std::vector<int> prime_numbers);
        bool CheckIfNumberInList(int N, std::unordered_set<int> list);
        std::vector<std::vector<int>> CalculatePrimeSequences(const int N);

    std::vector<std::vector<int>>
    AddTmpSequenceToFinalSolution(std::vector<int> tmp_solution, std::vector<std::vector<int>> final_solution);
};