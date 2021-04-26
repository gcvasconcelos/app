#include <vector>
#include <bitset>
#include "Constantes.hpp"

void CamadaEnlaceDadosTransmissora(std::vector<std::bitset<PACKET_SIZE> > sequenciaPacotes);

std::vector<std::bitset<FRAME_SIZE> > CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<std::bitset<FRAME_SIZE> > sequenciaQuadros);

std::vector<std::bitset<FRAME_SIZE> >CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<std::bitset<FRAME_SIZE> > sequenciaQuadros);
std::vector<std::bitset<FRAME_SIZE> >CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<std::bitset<FRAME_SIZE> > sequenciaQuadros);

// std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramento(std::bitset<8*FRAME_SIZE> quadroEnquadrado);

// std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::bitset<8*FRAME_SIZE> quadroEnquadrado);
// std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::bitset<8*FRAME_SIZE> quadroEnquadrado);

// void CamadaEnlaceDadosReceptora(std::bitset<8*MAX_SIZE> quadroEnquadrado, int size);
