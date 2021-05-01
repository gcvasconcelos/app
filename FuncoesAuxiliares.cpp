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

    for (size_t j = 0; j < FRAME_SIZE/8; j++) {
        std::bitset<FRAME_SIZE> ch;
        ch = quadro.to_ulong() & 0xFF;
        quadro >>= 8;

        if (ch != '\0') {
            tamanho++;
        }
    }

    return tamanho;
}

int ContaTamanhoPacote(std::bitset<PACKET_SIZE> pacote) {
    int tamanho = 0;

    for (size_t j = 0; j < PACKET_SIZE/8; j++) {
        std::bitset<FRAME_SIZE> ch;
        ch = pacote.to_ulong() & 0xFF;
        pacote >>= 8;

        if (ch != '\0') {
            tamanho++;
        }
    }

    return tamanho;
}

int ContaTamanhoBits(std::bitset<FRAME_SIZE> quadro) {
    int tamanho = 0;

    for (tamanho = FRAME_SIZE-1; tamanho >= 0; tamanho--) {\
        if (quadro.test(tamanho)) break;
    }

    return tamanho;
}
