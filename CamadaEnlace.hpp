#include <bitset>

const int MAX_SIZE = 512;

void CamadaEnlaceDadosTransmissora(std::bitset<8*MAX_SIZE> quadro, int size);

std::bitset<8*MAX_SIZE+64> CamadaEnlaceDadosTransmissoraEnquadramento(std::bitset<8*MAX_SIZE> quadro, int size);

std::bitset<8*MAX_SIZE+64> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::bitset<8*MAX_SIZE> quadro, int size);
std::bitset<8*MAX_SIZE+64> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::bitset<8*MAX_SIZE> quadro);

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramento(std::bitset<8*MAX_SIZE+64> quadroEnquadrado);

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::bitset<8*MAX_SIZE+64> quadroEnquadrado);
std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::bitset<8*MAX_SIZE+64> quadroEnquadrado);

void CamadaEnlaceDadosReceptora(std::bitset<8*MAX_SIZE> quadroEnquadrado);
