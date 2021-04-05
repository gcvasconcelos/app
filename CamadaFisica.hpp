#include <string>
#include <bitset>
#include <vector>

void AplicacaoTransmissora(void);

void CamadaDeAplicacaoTransmissora(std::string mensagem);

const int MAX_SIZE = 8;

std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(std::bitset<8*MAX_SIZE> quadro, int size);
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester(std::bitset<8*MAX_SIZE> quadro, int size);
std::vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(std::bitset<8*MAX_SIZE> quadro, int size);

void CamadaFisicaTransmissora(std::bitset<8*MAX_SIZE> quadro, int size);

void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits);

std::bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoBinaria(std::vector<int> fluxoBrutoDeBits);
std::bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoManchester(std::vector<int> fluxoBrutoDeBits);
std::bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoBipolar(std::vector<int> fluxoBrutoDeBits);

void CamadaFisicaReceptora(std::vector<int> fluxoBrutoDeBits);

void CamadaDeAplicacaoReceptora(std::bitset<8*MAX_SIZE> quadro, int size);

void AplicacaoReceptora(std::string mensagem);
