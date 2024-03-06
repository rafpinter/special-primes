// CE FICHIER NE SERT QU'A APPELER ET TESTER VOTRE CODE. 
// VOUS NE DEVRIEZ PAS AVOIR BESOIN DE LE MODIFIER, SAUF POUR 
// AJOUTER VOUS-MÊME D'AUTRES TESTS SI VOUS LE VOULEZ.
// NE PAS REMETTRE SUR STUDIUM. REMETTEZ SEULEMENT PrimeSequenceCalculator.cpp/.h

// THIS FILE IS ONLY USED TO CALL AND TEST YOUR CODE.
// YOU SHOULD NOT HAVE TO MODIFY IT, EXCEPT FOR ADDING 
// NEW CUSTOM TESTS IF YOU WISH TO DO SO.
// DO NOT SUBMIT ON STUDIUM. ONLY SUBMIT PrimeSequenceCalculator.cpp/.h


#include <iostream> // pour l'affichage dans la console // for display in console
#include "PrimeSequenceCalculator.h" // pour la classe principale de l'exercice // for the main class of the exercise
#include <vector> // pour utiliser les vecteurs de la librairie standard // to use vectors from the standard library
#include <cstdlib> // pour convertir le input en int // to convert input to int

// commandes / command (PowerShell) :
//  g++ -o prime_numbers_sequences.exe .\prime_numbers_sequences.cpp .\PrimeSequenceCalculator.cpp
// .\prime_numbers_sequences.exe 20000

// for VS Code, make sure to compile all the files of the project
// you might want to change "${file}", by "${fileDirname}\\**.cpp" in the tasks.json of .vscode -> taks -> args
// pour VS Code, veillez à compiler tous les fichiers du projet
// vous souhaiterez peut-être remplacer "${file}", par "${fileDirname}\\**.cpp" dans le fichier task.json de .vscode -> taks -> args

// Calculateur de sequences de nombres premiers / Prime Numbers Sequence Calculator
// 1487 4817 8147
// 2969 6299 9629
// 11483 14813 18143
// 12713 13217 13721

bool TestPrimeCalculator();

int main(int argc, char *argv[])
{
    std::cout << "Calculateur de sequences de nombres premiers / Prime Numbers Sequence Calculator" << std::endl;

    int N = 1000;
    if (argc >= 2){
        N = atoi(argv[1]);
        if (N == 0){
            std::cout << "Erreur d'entree / input error" << std::endl;
            N = 10000;
        }
        
    }

    PrimeSequenceCalculator Calculator = PrimeSequenceCalculator();
    std::vector<std::vector<int>> PrimeSequences = Calculator.CalculatePrimeSequences(N);

    for (const auto sequence : PrimeSequences){
        for (const auto number : sequence){
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }

    // tests
    if (TestPrimeCalculator()){
        std::cout << "Tests reussis / Tests passed !" << std::endl;
    } else {
        std::cout << "Tests echoues / Failed tests :(" << std::endl;
    }

}

bool TestPrimeCalculator(){
    std::vector<std::vector<int>> ExpectedReturns;
    PrimeSequenceCalculator Calculator = PrimeSequenceCalculator();
    ExpectedReturns.push_back({1487,4817,8147});
    ExpectedReturns.push_back({2969,6299,9629});
    ExpectedReturns.push_back({11483,14813,18143});
    ExpectedReturns.push_back({12713,13217,13721});

    std::vector<std::vector<int>> ReceivedReturns = Calculator.CalculatePrimeSequences(20000);

    if (ReceivedReturns.size() != ExpectedReturns.size())
        return false;

    for (int idx = 0; idx < ExpectedReturns.size(); idx++){
        if (ReceivedReturns[idx] != ExpectedReturns[idx])
            return false;
    }

    return true;
}

/*
Note : prends 10 secondes pour trouver les sequences inferieures a N = 100000, et l'algo n'est pas le plus optimal
*/