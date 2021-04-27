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

void PrintaVetorBitset(vector<bitset<PACKET_SIZE>> vetor) {
    for (int i = 0; i < vetor.size(); i++) {
        cout << "\t\t" << vetor[i] << "\n";
    }
}

void PrintaVetorBitset(vector<bitset<FRAME_SIZE>> vetor) {
    for (int i = 0; i < vetor.size(); i++) {
        cout << "\t\t" << vetor[i] << "\n";
    }
}

int ContaTamanhoQuadro(std::bitset<FRAME_SIZE> quadro) {
    int tamanho = 0;
    bitset<FRAME_SIZE> ulong_kernel;

    for (size_t i = 0; i < PACKET_SIZE; i++) ulong_kernel.set(i);

    for (size_t i = 0; i < FRAME_SIZE/PACKET_SIZE; i++) {
        bitset<FRAME_SIZE> quadro_ulong;
        quadro_ulong = quadro & ulong_kernel;

        for (size_t j = 0; j < PACKET_SIZE/8; j++) {
            std::bitset<FRAME_SIZE> ch;
            ch = quadro_ulong.to_ulong() & 0xFF;
            quadro_ulong >>= 8;

            if (ch != '\0') {
                tamanho++;
            }
        }
        quadro >>= PACKET_SIZE;
    }

    return tamanho;
}
