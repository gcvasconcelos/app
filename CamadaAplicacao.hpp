#include <string>
#include <bitset>
#include <vector>

#include "Constantes.hpp"

void AplicacaoTransmissora();

void CamadaDeAplicacaoTransmissora(std::string mensagem);

void AplicacaoReceptora(std::vector<std::bitset<PACKET_SIZE>> sequenciaPacotes);

void CamadaDeAplicacaoReceptora(std::vector<std::bitset<FRAME_SIZE>> sequenciaQuadros);
