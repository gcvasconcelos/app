#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include "CamadaAplicacao.hpp"
#include "CamadaFisica.hpp"
#include "FuncoesAuxiliares.hpp"

using namespace std;

//  Variável global para receber codificação selecionada pelo usuário e ser
//  usada na decodificação
int tipoCodificacao = 0;

/*
    Simula a Camada Física da Aplicação Transmissora. A função processa o
    quadro e seleciona a codificação com base na escolha do usuário que
    resultará em um fluxo bruto de bits. Na sequência este será enviado para
    o meio de transmissão.
    O tipo vetor de inteiros foi escolhido para o retono pois a estrutura de
    dados do bitset não aceita todos os valores possíveis de saída
    (especificamente o valor -1 de tensão da codificação bipolar).

    Entrada:
        quadro (bitset).
    Saída:
        fluxo bruto de bits (vector<int>) e chama o simulador do meio de
        transmissão.

    Exemplo:
        CamadaFisicaTransmissora(01100001);
        << 1
        >> 0 1 1 0 0 0 0 1
 */
// void CamadaFisicaTransmissora(bitset<8*FRAME_SIZE> quadro, int size) {
//     vector<int> fluxoBrutoDeBits(size*8);

//     cout << "\nOpções de codificação na camada física da Aplicação Transmissora:\n";
//     cout << "\t1 - Codificação binária (NRZ unipolar)\n";
//     cout << "\t2 - Codificação Manchester\n";
//     cout << "\t3 - Codificação Bipolar\n";

//     cout << "Escolha um tipo de codificação: ";
//     cin >> tipoCodificacao;

//     if (LOG_FLAG) {
//         cout << "\nLOGS - ENCODE Camada Física:\n";
//         cout << "\tQuadro:\t\t" << quadro << "\n";
//     }
//     switch (tipoCodificacao) {
//         case 1:
//             fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro, size);
//             break;
//         case 2:
//             fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro, size);
//             break;
//         case 3:
//             fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro, size);
//             break;
//         default:
//             cout << "Erro. Encerrando programa." << endl;
//             return;
//     }
//     if (LOG_FLAG) {
//         cout << "\tFluxo de bits:  ";
//         PrintaVetor(fluxoBrutoDeBits);
//     }
//     MeioDeComunicacao(fluxoBrutoDeBits);
// }

// /*
//     Simula o protocolo de codificação binária NRZ (Non Return Zero) na Camada
//     Física da Aplicação Transmissora. Cada bit 1 equivale ao valor 1 de tensão
//     e cada bit 0 equivale ao valor 0 de tensão.

//     Entrada:
//         quadro (bitset).
//     Saída:
//         fluxo bruto de bits (vector<int>).

//     Exemplo:
//         CamadaFisicaTransmissoraCodificacaoBinaria(01100001);
//         >> 0 1 1 0 0 0 0 1
//  */
// vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(bitset<8*MAX_SIZE> quadro, int size) {
//     int bits = size*8;
//     vector<int> fluxoBrutoDeBits(bits, 0);

//     for (size_t i = 0; i < bits; i++) {
//         if (quadro[i]) fluxoBrutoDeBits[(bits-1)-i] = 1;
//     }

//     return fluxoBrutoDeBits;
// }

// /*
//     Simula o protocolo de codificação Manchester na Camada Física da Aplicação
//     Transmissora. Existe um clock (começa do 0 e alterna entre 1 e 0 pelo tamanho do quadro). Cada bit que for diferente do clock vale 1 e cada bit
//     igual vale 0 (XOR).

//     Entrada:
//         quadro (bitset).
//     Saída:
//         fluxo bruto de bits (vector<int>).

//     Exemplo:
//         CamadaFisicaTransmissoraCodificacaoManchester(01100001);
//         >> 0 0 1 1 0 1 0 0
//  */
// vector<int> CamadaFisicaTransmissoraCodificacaoManchester(bitset<8*MAX_SIZE> quadro, int size) {
//     int bits = size*8;
//     vector<int> fluxoBrutoDeBits(bits, 0);
//     bitset<8*MAX_SIZE> clock;

//     for (size_t i = 0; i < bits; i++) {
//         if (i % 2 == 0) clock.set(i);
//     }
//     if (LOG_FLAG) {
//         cout << "\tClock:\t\t" << clock << "\n";
//     }
//     quadro ^= clock; // XOR

//     for (size_t i = 0; i < bits; i++) {
//         if (quadro[i]) fluxoBrutoDeBits[(bits-1)-i] = 1;
//     }

//     return fluxoBrutoDeBits;
// }

// /*
//     Simula o protocolo de codificação bipolar na Camada Física da Aplicação
//     Transmissora. Cada bit 1 o tensão alternadamente vale 1 e -1 e cada bit 0
//     equivale 0 de tensão.

//     Entrada:
//         quadro (bitset).
//     Saída:
//         fluxo bruto de bits (vector<int>).

//     Exemplo:
//         CamadaFisicaTransmissoraCodificacaoBipolar(01100001);
//         >> 0 -1 1 0 0 0 0 -1
//  */
// vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(bitset<8*MAX_SIZE> quadro, int size) {
//     int bits = size*8;
//     vector<int> fluxoBrutoDeBits(bits, 0);
//     int valor = 1;

//     for (size_t i = 0; i < bits; i++) {
//         if (quadro[i]) {
//             valor = -valor;
//             fluxoBrutoDeBits[(bits-1)-i] = valor;
//         } else {
//             fluxoBrutoDeBits[(bits-1)-i] = 0;
//         }
//     }

//     return fluxoBrutoDeBits;
// }

// /*
//     Simula o meio de transmissão e o próprio processo de transmissão entre a
//     Aplicação Transmissora e a Aplicação Receptora.

//     Entrada:
//         fluxo bruto de bits (vector<int>).
//     Saída:
//         fluxo bruto de bits (vector<int>) e chama a função da Camada
//         Física Receptora.

//     Exemplo:
//         MeioDeComunicacao(0 1 1 0 0 0 0 1);
//         >> 0 1 1 0 0 0 0 1
//  */
// void MeioDeComunicacao(vector<int> fluxoBrutoDeBits) {
//     int bits = fluxoBrutoDeBits.size();
//     vector<int> fluxoBrutoDeBits_origem(bits)
//         , fluxoBrutoDeBits_destino(bits);

//     fluxoBrutoDeBits_origem = fluxoBrutoDeBits;

//     for (size_t i = 0; i < bits; i++) {
//         fluxoBrutoDeBits_destino[i] = fluxoBrutoDeBits_origem[i];
//     }

//     if (LOG_FLAG) {
//         cout << "\nLOGS - Meio de Comunicação:\n";
//         cout << "\tFluxo de bits enviados:\t\t";
//         PrintaVetor(fluxoBrutoDeBits_origem);
//         cout << "\tFluxo de bits recebidos:\t";
//         PrintaVetor(fluxoBrutoDeBits_destino);
//     }

//     CamadaFisicaReceptora(fluxoBrutoDeBits_destino);
// }

// /*
//     Simula a Camada Física da Aplicação Receptora. A função processa o
//     fluxo bruto de bits e seleciona a decodificação com base na escolha do usuário que resultará em um quadro. Na sequência este será enviado para
//     a Camada de Aplicação.

//     Entrada:
//         fluxo bruto de bits (vector<int>).
//     Saída:
//         quadro (bitset) e chama a função da Camada de Aplicação Receptora.

//     Exemplo:
//         CamadaFisicaReceptora(0 1 1 0 0 0 0 1);
//         se tipoCodificacao==1 >> 01100001
//  */
// void CamadaFisicaReceptora(std::vector<int> fluxoBrutoDeBits) {
//     int bits = fluxoBrutoDeBits.size();
//     bitset<8*MAX_SIZE> quadro;

//     if (LOG_FLAG) {
//         cout << "\nLOGS - DECODE Camada Física:\n";
//         cout << "\tFluxo de bits:\t";
//         PrintaVetor(fluxoBrutoDeBits);
//     }
//     switch (tipoCodificacao) {
//         case 1:
//             quadro = CamadaFisicaTransmissoraDecodificacaoBinaria(fluxoBrutoDeBits);
//             break;
//         case 2:
//             quadro = CamadaFisicaTransmissoraDecodificacaoManchester(fluxoBrutoDeBits);
//             break;
//         case 3:
//             quadro = CamadaFisicaTransmissoraDecodificacaoBipolar(fluxoBrutoDeBits);
//             break;
//     }
//     if (LOG_FLAG) {
//         cout << "\tQuadro: \t" << quadro << endl;
//     }
//     CamadaDeAplicacaoReceptora(quadro, bits);
// }


// /*
//     Simula o protocolo de decodificação binária NRZ (Non Return Zero) na Camada
//     Física da Aplicação Receptora. Cada tensão igual 1 equivale a um bit 1 e tensão igual a 0 vale um bit 0.

//     Entrada:
//         fluxo bruto de bits (vector<int>).
//     Saída:
//         quadro (bitset).

//     Exemplo:
//         CamadaFisicaTransmissoraDecodificacaoBinaria(0 1 1 0 0 0 0 1);
//         >> 01100001
//  */
// bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoBinaria(std::vector<int> fluxoBrutoDeBits) {
//     int bits = fluxoBrutoDeBits.size();
//     bitset<8*MAX_SIZE> quadro;

//     for (size_t i = 0; i < bits; i++) {
//         if (fluxoBrutoDeBits[i] == 1) {
//             quadro.set((bits-1)-i);
//         } else {
//             quadro.reset((bits-1)-i);
//         }
//     }

//     return quadro;
// }

// /*
//     Simula o protocolo de decodificação Manchester na Camada Física da Aplicação
//     Receptora. Existe um clock (começa do 0 e alterna entre 1 e 0 pelo tamanho
//     da mensagem). Cada valor de tensão que for diferente do clock vale um bit 1 e sdo contrário vale um bit 0 (XOR).

//     Entrada:
//         fluxo bruto de bits (vector<int>).
//     Saída:
//         quadro (bitset).

//     Exemplo:
//         CamadaFisicaTransmissoraDecodificacaoManchester(0 0 1 1 0 1 0 0);
//         >> 01100001
//  */
// bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoManchester(std::vector<int> fluxoBrutoDeBits) {
//     int bits = fluxoBrutoDeBits.size();
//     bitset<8*MAX_SIZE> clock;
//     bitset<8*MAX_SIZE> quadro;

//     for (size_t i = 0; i < bits; i++) {
//         if (i % 2 == 0) clock.set(i);
//     }

//     for (size_t i = 0; i < bits; i++) {
//         if (fluxoBrutoDeBits[i] == 1) {
//             quadro.set((bits-1)-i);
//         } else {
//             quadro.reset((bits-1)-i);
//         }
//     }

//     if (LOG_FLAG) {
//         cout << "\tFluxo de bits:\t" << quadro << "\n";
//         cout << "\tClock:\t\t" << clock << "\n";
//     }

//     quadro ^= clock; // XOR

//     return quadro;
// }

// /*
//     Simula o protocolo de decodificação bipolar na Camada Física da Aplicação
//     Receptora. Os valores de tensão -1 e 1 equivale a um bit 1 e o valor 0
//     equivale ao bit 0.

//     Entrada:
//         fluxo bruto de bits (vector<int>).
//     Saída:
//         quadro (bitset).

//     Exemplo:
//         CamadaFisicaTransmissoraDecodificacaoManchester(0 -1 1 0 0 0 0 -1);
//         >> 01100001
//  */
// bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoBipolar(std::vector<int> fluxoBrutoDeBits) {
//     int bits = fluxoBrutoDeBits.size();
//     bitset<8*MAX_SIZE> quadro;

//     for (size_t i = 0; i < bits; i++) {
//         if (abs(fluxoBrutoDeBits[i]) == 1) {
//             quadro.set((bits-1)-i);
//         } else {
//             quadro.reset((bits-1)-i);
//         }
//     }

//     return quadro;
// }
