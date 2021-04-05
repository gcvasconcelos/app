#include <iostream>
#include <vector>
#include "FuncoesAuxiliares.hpp"

using namespace std;

void PrintaVetor(vector<int> vetor) {
    for (int i = 0; i < vetor.size(); i++) {
        if (i % 8 == 0 && i != 0) cout << " ";
        cout << vetor[i];
    }
    cout << endl;
}
