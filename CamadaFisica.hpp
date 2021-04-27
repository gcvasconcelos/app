#include <vector>
#include <bitset>

#include "Constantes.hpp"

void CamadaFisicaTransmissora(std::vector<std::bitset<FRAME_SIZE>> sequenciaQuadros);

void CamadaFisicaTransmissoraCodificacaoBinaria(std::bitset<FRAME_SIZE> quadro, std::vector<int> &fluxoBrutoDeBits);
void CamadaFisicaTransmissoraCodificacaoManchester(std::bitset<FRAME_SIZE> quadro, std::vector<int> &fluxoBrutoDeBits);
void CamadaFisicaTransmissoraCodificacaoBipolar(std::bitset<FRAME_SIZE> quadro, std::vector<int> &fluxoBrutoDeBits);

void MeioDeComunicacao(std::vector<int> sinalEletricoOrigem);

void CamadaFisicaReceptora(std::vector<int> sinalEletrico);

std::vector<int> CamadaFisicaTransmissoraDecodificacaoBinaria(std::vector<int> sinalEletrico);
std::vector<int> CamadaFisicaTransmissoraDecodificacaoManchester(std::vector<int> sinalEletrico);
std::vector<int> CamadaFisicaTransmissoraDecodificacaoBipolar(std::vector<int> sinalEletrico);
