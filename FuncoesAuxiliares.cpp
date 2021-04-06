#include <iostream>
#include <vector>
#include "FuncoesAuxiliares.hpp"

using namespace std;

/*
    Printa no terminal o conteúdo de um vetor de inteiros.

    Entrada:
        vetor (vector<int>).
    Saída:
        print no terminal

    Exemplo:
        PrintaVetor([01100001]);
        >> "01100001"
 */
void PrintaVetor(vector<int> vetor) {
    for (int i = 0; i < vetor.size(); i++) {
        if (i % 8 == 0 && i != 0) cout << " ";
        cout << vetor[i];
    }
    cout << endl;
}
