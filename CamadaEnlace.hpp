#include <vector>
#include <bitset>
#include "Constantes.hpp"

void CamadaEnlaceDadosTransmissora(std::vector<std::bitset<PACKET_SIZE>> sequenciaPacotes);

std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramento(std::bitset<FRAME_SIZE> quadro);

std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::bitset<FRAME_SIZE> quadro);
std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::bitset<FRAME_SIZE> quadro);

std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErro(std::bitset<FRAME_SIZE> quadroEnquadrado);

std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidadePar(std::bitset<FRAME_SIZE> quadroEnquadrado);
std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErroControleDeErroCRC(std::bitset<FRAME_SIZE> quadroEnquadrado);
std::bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErroControleDeErroCodigoDeHamming(std::bitset<FRAME_SIZE> quadroEnquadrado);

void CamadaEnlaceDadosReceptora(std::vector<int> fluxoBrutoDeBits);

std::vector<std::bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramento(std::vector<int> fluxoBrutoDeBits);

std::vector<std::bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> fluxoBrutoDeBits);
std::vector<std::bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> fluxoBrutoDeBits);

std::bitset<FRAME_SIZE> CamadaEnlaceDadosReceptoraControleDeErro(std::bitset<FRAME_SIZE> quadro);

std::bitset<FRAME_SIZE> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(std::bitset<FRAME_SIZE> quadro);
std::bitset<FRAME_SIZE> CamadaEnlaceDadosReceptoraControleDeErroControleDeErroCRC(std::bitset<FRAME_SIZE> quadro);
std::bitset<FRAME_SIZE> CamadaEnlaceDadosReceptoraControleDeErroControleDeErroCodigoDeHamming(std::bitset<FRAME_SIZE> quadro);
