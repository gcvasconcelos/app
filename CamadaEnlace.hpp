#include <vector>
#include <bitset>
#include "Constantes.hpp"

void CamadaEnlaceDadosTransmissora(std::vector<std::bitset<PACKET_SIZE>> sequenciaPacotes);

std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramento(std::bitset<FRAME_SIZE> quadro);

std::bitset<FRAME_SIZE>CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::bitset<FRAME_SIZE> quadro);
std::bitset<FRAME_SIZE>CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::bitset<FRAME_SIZE> quadro);

std::bitset<FRAME_SIZE>  CamadaEnlaceDadosTransmissoraControleDeErro(std::bitset<FRAME_SIZE> quadro);

std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidadePar(std::bitset<FRAME_SIZE> quadro);
std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErroControleDeErroCRC(std::bitset<FRAME_SIZE> quadro);

void CamadaEnlaceDadosReceptora(std::vector<int> fluxoBrutoDeBits);

void CamadaEnlaceDadosReceptoraEnquadramento(std::vector<int> fluxoBrutoDeBits, std::vector<std::bitset<FRAME_SIZE>> &sequenciaQuadros);

std::vector<std::bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> fluxoBrutoDeBits);
std::vector<std::bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> fluxoBrutoDeBits);
