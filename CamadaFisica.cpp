#include <iostream>
#include <cmath>

#include "CamadaAplicacao.hpp"
#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
#include "FuncoesAuxiliares.hpp"

using namespace std;

//  Variável global para receber codificação selecionada pelo usuário e ser
//  usada na decodificação
int tipoCodificacao = 0;
int numQuadros = 0;

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
void CamadaFisicaTransmissora(vector<bitset<FRAME_SIZE>> sequenciaQuadros) {
    vector<int> sinalEletrico;
    numQuadros = sequenciaQuadros.size();

    cout << "\nOpções de codificação na camada física da Aplicação Transmissora:\n";
    cout << "\t1 - Codificação binária (NRZ unipolar)\n";
    cout << "\t2 - Codificação Manchester\n";
    cout << "\t3 - Codificação Bipolar\n";

    cout << "Escolha um tipo de codificação: ";
    cin >> tipoCodificacao;

    if (LOG_FLAG) {
        cout << "\nLOGS - ENCODE Camada Física:\n";
        cout << "\tQuadros:\n" ;
        PrintaVetorBitset(sequenciaQuadros);
    }
    for (size_t i = 0; i < numQuadros; i++) {
        bitset<FRAME_SIZE> quadro;
        quadro = sequenciaQuadros[i];

        switch (tipoCodificacao) {
            case 1:
                CamadaFisicaTransmissoraCodificacaoBinaria(quadro, sinalEletrico);
                break;
            case 2:
                CamadaFisicaTransmissoraCodificacaoManchester(quadro, sinalEletrico);
                break;
            case 3:
                CamadaFisicaTransmissoraCodificacaoBipolar(quadro, sinalEletrico);
                break;
            default:
                cout << "Erro na Camada Física: tipo de codificação não suportado. Encerrando programa." << endl;
                return;
        }
    }

    if (LOG_FLAG) {
        cout << "\tSinal Elétrico:\n\t\t";
        PrintaVetor(sinalEletrico);
    }

    MeioDeComunicacao(sinalEletrico);
}

/*
    Simula o protocolo de codificação binária NRZ (Non Return Zero) na Camada
    Física da Aplicação Transmissora. Cada bit 1 equivale ao valor 1 de tensão
    e cada bit 0 equivale ao valor 0 de tensão.

    Entrada:
        quadro (bitset).
    Saída:
        fluxo bruto de bits (vector<int>).

    Exemplo:
        CamadaFisicaTransmissoraCodificacaoBinaria(01100001);
        >> 0 1 1 0 0 0 0 1
 */
void CamadaFisicaTransmissoraCodificacaoBinaria(bitset<FRAME_SIZE> quadro, vector<int> &fluxoBrutoDeBits) {
    // int numBits = ContaTamanhoQuadro(quadro)*8;
    int numBits = FRAME_SIZE;

    for (size_t i = 0; i < numBits; i++) {
        int bit = (quadro[i]) ? 1 : 0;
        fluxoBrutoDeBits.push_back(bit);
    }
    return;
}

/*
    Simula o protocolo de codificação Manchester na Camada Física da Aplicação
    Transmissora. Existe um clock (começa do 0 e alterna entre 1 e 0 pelo tamanho do quadro). Cada bit que for diferente do clock vale 1 e cada bit
    igual vale 0 (XOR).

    Entrada:
        quadro (bitset).
    Saída:
        fluxo bruto de bits (vector<int>).

    Exemplo:
        CamadaFisicaTransmissoraCodificacaoManchester(01100001);
        >> 0 0 1 1 0 1 0 0
 */
void CamadaFisicaTransmissoraCodificacaoManchester(bitset<FRAME_SIZE> quadro, vector<int> &fluxoBrutoDeBits) {
    // int numBits = ContaTamanhoQuadro(quadro)*8;
    int numBits = FRAME_SIZE;
    bitset<FRAME_SIZE> clock;

    for (size_t i = 0; i < numBits; i++) {
        if (i % 2 == 0) clock.set(i);
    }
    if (LOG_FLAG) {
        cout << "\tClock:\n\t\t" << clock << "\n";
    }

    quadro ^= clock; // XOR

    for (size_t i = 0; i < numBits; i++) {
        int bit = (quadro[i]) ? 1 : 0;
        fluxoBrutoDeBits.push_back(bit);
    }
}

/*
    Simula o protocolo de codificação bipolar na Camada Física da Aplicação
    Transmissora. Cada bit 1 o tensão alternadamente vale 1 e -1 e cada bit 0
    equivale 0 de tensão.

    Entrada:
        quadro (bitset).
    Saída:
        fluxo bruto de bits (vector<int>).

    Exemplo:
        CamadaFisicaTransmissoraCodificacaoBipolar(01100001);
        >> 0 -1 1 0 0 0 0 -1
 */
void CamadaFisicaTransmissoraCodificacaoBipolar(bitset<FRAME_SIZE> quadro, vector<int> &fluxoBrutoDeBits) {
    // int numBits = ContaTamanhoQuadro(quadro)*8;
    int numBits = FRAME_SIZE;
    int valor = -1;

    for (size_t i = 0; i < numBits; i++) {
        if (quadro[i]) {
            valor = -valor;
            fluxoBrutoDeBits.push_back(valor);
        } else {
            fluxoBrutoDeBits.push_back(0);
        }
    }
}

/*
    Simula o meio de transmissão e o próprio processo de transmissão entre a
    Aplicação Transmissora e a Aplicação Receptora.

    Entrada:
        fluxo bruto de bits (vector<int>).
    Saída:
        fluxo bruto de bits (vector<int>) e chama a função da Camada
        Física Receptora.

    Exemplo:
        MeioDeComunicacao(0 1 1 0 0 0 0 1);
        >> 0 1 1 0 0 0 0 1
 */
void MeioDeComunicacao(vector<int> sinalEletricoOrigem) {
    int periodo = sinalEletricoOrigem.size();
    vector<int> sinalEletricoDestino(periodo);
    int porcentagemDeErros = 1;
    int numErros = 0;
    int bitNegativo = (tipoCodificacao == 3) ? -1 : 0;


    if (LOG_FLAG) {
        cout << "\nLOGS - Meio de Comunicação:\n";
        cout << "\tSinal elétrico enviado:\n\t\t";
        PrintaVetor(sinalEletricoOrigem);
    }

    for (size_t i = 0; i < periodo; i++) {
        if (rand()%100 > porcentagemDeErros) {
            sinalEletricoDestino[i] = sinalEletricoOrigem[i];
        } else {
            numErros++;
            sinalEletricoDestino[i] = (sinalEletricoOrigem[i] == 1) ? bitNegativo : 1;
        }
    }
    cout << "\tNúmero de erros na transmissão: " << numErros << "\n";

    if (LOG_FLAG) {
        cout << "\tSinal elétrico recebido:\n\t\t";
        PrintaVetor(sinalEletricoDestino);
    }

    CamadaFisicaReceptora(sinalEletricoDestino);
}

/*
    Simula a Camada Física da Aplicação Receptora. A função processa o
    fluxo bruto de bits e seleciona a decodificação com base na escolha do usuário que resultará em um quadro. Na sequência este será enviado para
    a Camada de Aplicação.

    Entrada:
        fluxo bruto de bits (vector<int>).
    Saída:
        quadro (bitset) e chama a função da Camada de Aplicação Receptora.

    Exemplo:
        CamadaFisicaReceptora(0 1 1 0 0 0 0 1);
        se tipoCodificacao==1 >> 01100001
 */
void CamadaFisicaReceptora(vector<int> sinalEletrico) {
    vector<int> fluxoBrutoDeBits;

    if (LOG_FLAG) {
        cout << "\nLOGS - DECODE Camada Física:\n";
        cout << "\tSinal elétrico:\n\t\t";
        PrintaVetor(sinalEletrico);
    }

    switch (tipoCodificacao) {
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoBinaria(sinalEletrico);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoManchester(sinalEletrico);
            break;
        case 3:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraDecodificacaoBipolar(sinalEletrico);
            break;
    }

    if (LOG_FLAG) {
        cout << "\tFluxo de bits:\n\t\t";
        PrintaVetor(fluxoBrutoDeBits);
    }
    CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}


/*
    Simula o protocolo de decodificação binária NRZ (Non Return Zero) na Camada
    Física da Aplicação Receptora. Cada tensão igual 1 equivale a um bit 1 e tensão igual a 0 vale um bit 0.

    Entrada:
        fluxo bruto de bits (vector<int>).
    Saída:
        quadro (bitset).

    Exemplo:
        CamadaFisicaTransmissoraDecodificacaoBinaria(0 1 1 0 0 0 0 1);
        >> 01100001
 */
vector<int> CamadaFisicaTransmissoraDecodificacaoBinaria(vector<int> sinalEletrico) {
    int numBits = sinalEletrico.size();
    vector<int> fluxoBrutoDeBits;

    for (size_t i = 0; i < numBits; i++) {
        fluxoBrutoDeBits.push_back(sinalEletrico.back());
        sinalEletrico.pop_back();
    }

    return fluxoBrutoDeBits;
}

/*
    Simula o protocolo de decodificação Manchester na Camada Física da Aplicação
    Receptora. Existe um clock (começa do 0 e alterna entre 1 e 0 pelo tamanho
    da mensagem). Cada valor de tensão que for diferente do clock vale um bit 1 e sdo contrário vale um bit 0 (XOR).

    Entrada:
        fluxo bruto de bits (vector<int>).
    Saída:
        quadro (bitset).

    Exemplo:
        CamadaFisicaTransmissoraDecodificacaoManchester(0 0 1 1 0 1 0 0);
        >> 01100001
 */
vector<int> CamadaFisicaTransmissoraDecodificacaoManchester(vector<int> sinalEletrico) {
    int numBits = sinalEletrico.size();
    vector<int> fluxoBrutoDeBits;
    vector<int> clock;

    for (size_t i = 0; i < numBits; i++) {
        int bit = (i % 2 == 0) ? 1 : 0;
        clock.push_back(bit);
    }
    if (LOG_FLAG) {
        cout << "\tClock:\n\t\t";
        PrintaVetor(clock);
    }

    for (size_t i = 0; i < numBits; i++) {
        int bit = (sinalEletrico[(numBits-1)-i] != clock[(numBits-1)-i]) ? 1: 0;
        fluxoBrutoDeBits.push_back(bit);
    }

    return fluxoBrutoDeBits;
}

/*
    Simula o protocolo de decodificação bipolar na Camada Física da Aplicação
    Receptora. Os valores de tensão -1 e 1 equivale a um bit 1 e o valor 0
    equivale ao bit 0.

    Entrada:
        fluxo bruto de bits (vector<int>).
    Saída:
        quadro (bitset).

    Exemplo:
        CamadaFisicaTransmissoraDecodificacaoManchester(0 -1 1 0 0 0 0 -1);
        >> 01100001
 */
vector<int> CamadaFisicaTransmissoraDecodificacaoBipolar(vector<int> sinalEletrico) {
    int numBits = sinalEletrico.size();
    vector<int> fluxoBrutoDeBits;

    for (size_t i = 0; i < numBits; i++) {
        fluxoBrutoDeBits.push_back(abs(sinalEletrico.back()));
        sinalEletrico.pop_back();
    }

    return fluxoBrutoDeBits;
}
