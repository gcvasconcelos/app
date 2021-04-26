#include <vector>
#include <bitset>
#include "Constantes.hpp"

void PrintaVetor(std::vector<int> vetor);

void PrintaVetorBitset(std::vector<std::bitset<PACKET_SIZE> > vetor);
void PrintaVetorBitset(std::vector<std::bitset<FRAME_SIZE> > vetor);

int TamanhoBitset(std::bitset<FRAME_SIZE> bits);
