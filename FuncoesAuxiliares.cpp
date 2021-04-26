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

void PrintaVetorBitset(vector<bitset<PACKET_SIZE> > vetor) {
    for (int i = 0; i < vetor.size(); i++) {
        cout << "\t\t" << vetor[i] << "\n";
    }
    cout << endl;
}

void PrintaVetorBitset(vector<bitset<FRAME_SIZE> > vetor) {
    for (int i = 0; i < vetor.size(); i++) {
        cout << "\t\t" << vetor[i] << "\n";
    }
    cout << endl;
}

int TamanhoBitset(std::bitset<FRAME_SIZE> bits) {
    int tamanho = 0;

    for (size_t i = 0; i < PACKET_SIZE/8; i++) {
        std::bitset<FRAME_SIZE> ch;
        ch = bits.to_ulong() & 0xFF;
        bits >>= 8;

        if (ch != '\0') {
            tamanho++;
        }
    }
    return tamanho;
}
