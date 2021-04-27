#include <vector>
#include <bitset>
#include "Constantes.hpp"

void PrintaVetor(std::vector<int> vetor);

void PrintaVetorBitset(std::vector<std::bitset<PACKET_SIZE>> vetor);

void PrintaVetorBitset(std::vector<std::bitset<FRAME_SIZE>> vetor);

int ContaTamanhoPacote(std::bitset<PACKET_SIZE> pacote);

int ContaTamanhoQuadro(std::bitset<FRAME_SIZE> quadro);
