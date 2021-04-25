#include <bitset>
#include "Constantes.hpp"

void CamadaEnlaceDadosTransmissora(std::bitset<8*MAX_SIZE> quadro, int size);

std::bitset<8*FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramento(std::bitset<8*MAX_SIZE> quadro, int size);

std::bitset<8*FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::bitset<8*MAX_SIZE> quadro, int size);
std::bitset<8*FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::bitset<8*MAX_SIZE> quadro);

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramento(std::bitset<8*FRAME_SIZE> quadroEnquadrado);

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::bitset<8*FRAME_SIZE> quadroEnquadrado);
std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::bitset<8*FRAME_SIZE> quadroEnquadrado);

void CamadaEnlaceDadosReceptora(std::bitset<8*MAX_SIZE> quadroEnquadrado, int size);
