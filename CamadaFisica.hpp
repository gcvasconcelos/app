#include <vector>
#include <bitset>

#include "Constantes.hpp"

void CamadaFisicaTransmissora(std::vector<std::bitset<FRAME_SIZE>> sequenciaQuadros);

void CamadaFisicaTransmissoraCodificacaoBinaria(std::bitset<FRAME_SIZE> quadro, std::vector<int> &fluxoBrutoDeBits);
void CamadaFisicaTransmissoraCodificacaoManchester(std::bitset<FRAME_SIZE> quadro, std::vector<int> &fluxoBrutoDeBits);
void CamadaFisicaTransmissoraCodificacaoBipolar(std::bitset<FRAME_SIZE> quadro, std::vector<int> &fluxoBrutoDeBits);

void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits);

void CamadaFisicaReceptora(std::vector<int> fluxoBrutoDeBits);

std::vector<int> CamadaFisicaTransmissoraDecodificacaoBinaria(std::vector<int> fluxoBrutoDeBits);
std::vector<int> CamadaFisicaTransmissoraDecodificacaoManchester(std::vector<int> fluxoBrutoDeBits);
std::vector<int> CamadaFisicaTransmissoraDecodificacaoBipolar(std::vector<int> fluxoBrutoDeBits);
