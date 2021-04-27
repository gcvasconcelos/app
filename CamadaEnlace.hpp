#include <vector>
#include <bitset>
#include "Constantes.hpp"

void CamadaEnlaceDadosTransmissora(std::vector<std::bitset<PACKET_SIZE>> sequenciaPacotes);

std::vector<std::bitset<FRAME_SIZE>> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<std::bitset<FRAME_SIZE>> sequenciaQuadros);

std::vector<std::bitset<FRAME_SIZE>>CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<std::bitset<FRAME_SIZE>> sequenciaQuadros);
std::vector<std::bitset<FRAME_SIZE>>CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<std::bitset<FRAME_SIZE>> sequenciaQuadros);

void CamadaEnlaceDadosReceptora(std::vector<int> fluxoBrutoDeBits);

void CamadaEnlaceDadosReceptoraEnquadramento(std::vector<int> fluxoBrutoDeBits, std::vector<std::bitset<FRAME_SIZE>> &sequenciaQuadros);

std::vector<std::bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> fluxoBrutoDeBits);
std::vector<std::bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> fluxoBrutoDeBits);
