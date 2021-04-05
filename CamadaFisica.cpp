#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include "CamadaFisica.hpp"
#include "FuncoesAuxiliares.hpp"


using namespace std;

int tipoCodificacao = 0;

void AplicacaoTransmissora(void) {
    string mensagem;
    cout << "Digite uma mensagem: ";
    cin >> mensagem;
    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem) {
    std::bitset<8*MAX_SIZE> quadro;
    int size = mensagem.size();

    for (size_t i = 0; i < size; i++) {
        quadro <<= 8;
        quadro |= mensagem[i];
    }
    // quadro <<= (MAX_SIZE - size) * 8;
    cout << "\nLOGS - ENCODE Camada de Aplicação\n";
    cout << "\tMensagem: " << mensagem << "\n";
    cout << "\tQuadro: " << quadro << endl;


    CamadaFisicaTransmissora(quadro, size);
}

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(std::bitset<8*MAX_SIZE> quadro, int size) {
    int bits = size*8;
    vector<int> fluxoBrutoDeBits(bits, 0);

    for (size_t i = 0; i < bits; i++) {
        if (quadro[i]) fluxoBrutoDeBits[(bits-1)-i] = 1;
    }

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(std::bitset<8*MAX_SIZE> quadro, int size) {
    int bits = size*8;
    vector<int> fluxoBrutoDeBits(bits, 0);
    std::bitset<8*MAX_SIZE> clock;

    for (size_t i = 0; i < bits; i++) {
        if (i % 2 == 0) clock.set(i);
    }
    cout << "\tClock:\t\t" << clock << "\n";

    quadro ^= clock;

    for (size_t i = 0; i < bits; i++) {
        if (quadro[i]) fluxoBrutoDeBits[(bits-1)-i] = 1;
    }

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(std::bitset<8*MAX_SIZE> quadro, int size) {
    int bits = size*8;
    vector<int> fluxoBrutoDeBits(bits, 0);
    int valor = 1;

    for (size_t i = 0; i < bits; i++) {
        if (quadro[i]) {
            valor = -valor;
            fluxoBrutoDeBits[(bits-1)-i] = valor;
        } else {
            fluxoBrutoDeBits[(bits-1)-i] = 0;
        }
    }

    return fluxoBrutoDeBits;
}

void CamadaFisicaTransmissora(std::bitset<8*MAX_SIZE> quadro, int size) {
    vector<int> fluxoBrutoDeBits(size*8);

    cout << "\nOpções de codificação na camada física:\n";
    cout << "\t1 - Codificação binária (NRZ unipolar)\n";
    cout << "\t2 - Codificação Manchester\n";
    cout << "\t3 - Codificação Bipolar\n";

    cout << "Escolha um tipo de codificação: ";
    cin >> tipoCodificacao;

    cout << "\nLOGS - ENCODE Camada Física:\n";
    cout << "\tQuadro:\t\t" << quadro << "\n";

    switch (tipoCodificacao) {
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro, size);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro, size);
            break;
        case 3:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro, size);
            break;
        default:
            cout << "Erro. Encerrando programa." << endl;
            return;
    }
    cout << "\tFluxo de bits: ";
    PrintaVetor(fluxoBrutoDeBits);
    MeioDeComunicacao(fluxoBrutoDeBits);
}

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits) {
    int bits = fluxoBrutoDeBits.size();
    vector<int> fluxoBrutoDeBits_origem(bits)
        , fluxoBrutoDeBits_destino(bits);

    fluxoBrutoDeBits_origem = fluxoBrutoDeBits;

    for (size_t i = 0; i < bits; i++) {
        fluxoBrutoDeBits_destino[i] = fluxoBrutoDeBits_origem[i];
    }

    cout << "\nLOGS - Meio de Comunicação:\n";
    cout << "\tFluxo de bits enviados:\t\t";
    PrintaVetor(fluxoBrutoDeBits_origem);
    cout << "\tFluxo de bits recebidos:\t";
    PrintaVetor(fluxoBrutoDeBits_destino);

    CamadaFisicaReceptora(fluxoBrutoDeBits_destino);
}

std::bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoBinaria(std::vector<int> fluxoBrutoDeBits) {
    int bits = fluxoBrutoDeBits.size();
    std::bitset<8*MAX_SIZE> quadro;

    for (size_t i = 0; i < bits; i++) {
        if (fluxoBrutoDeBits[i] == 1) {
            quadro.set((bits-1)-i);
        } else {
            quadro.reset((bits-1)-i);
        }
    }

    return quadro;
}

std::bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoManchester(std::vector<int> fluxoBrutoDeBits) {
    int bits = fluxoBrutoDeBits.size();
    std::bitset<8*MAX_SIZE> clock;
    std::bitset<8*MAX_SIZE> quadro;

    for (size_t i = 0; i < bits; i++) {
        if (i % 2 == 0) clock.set(i);
    }

    for (size_t i = 0; i < bits; i++) {
        if (fluxoBrutoDeBits[i] == 1) {
            quadro.set((bits-1)-i);
        } else {
            quadro.reset((bits-1)-i);
        }
    }

    cout << "\tFluxo de bits:\t" << quadro << "\n";
    cout << "\tClock:\t\t" << clock << "\n";

    quadro ^= clock;

    return quadro;
}

std::bitset<8*MAX_SIZE> CamadaFisicaTransmissoraDecodificacaoBipolar(std::vector<int> fluxoBrutoDeBits) {
    int bits = fluxoBrutoDeBits.size();
    std::bitset<8*MAX_SIZE> quadro;

    for (size_t i = 0; i < bits; i++) {
        if (abs(fluxoBrutoDeBits[i]) == 1) {
            quadro.set((bits-1)-i);
        } else {
            quadro.reset((bits-1)-i);
        }
    }

    return quadro;
}

void CamadaFisicaReceptora(std::vector<int> fluxoBrutoDeBits) {
    int bits = fluxoBrutoDeBits.size();
    std::bitset<8*MAX_SIZE> quadro;

    cout << "\nLOGS - DECODE Camada Física:\n";
    cout << "\tFluxo de bits:\t";
    PrintaVetor(fluxoBrutoDeBits);

    switch (tipoCodificacao) {
        case 1:
            quadro = CamadaFisicaTransmissoraDecodificacaoBinaria(fluxoBrutoDeBits);
            break;
        case 2:
            quadro = CamadaFisicaTransmissoraDecodificacaoManchester(fluxoBrutoDeBits);
            break;
        case 3:
            quadro = CamadaFisicaTransmissoraDecodificacaoBipolar(fluxoBrutoDeBits);
            break;
    }

    cout << "\tQuadro: \t" << quadro << endl;
    CamadaDeAplicacaoReceptora(quadro, bits);
}

void CamadaDeAplicacaoReceptora(std::bitset<8*MAX_SIZE> quadro, int size) {
    string mensagem = "";
    char ch;

    for (size_t i = 0; i < size/8; i++) {
        ch = quadro.to_ulong() & 0xFF;
        mensagem = ch + mensagem;
        quadro >>= 8;
    }

    cout << "\nLOGS - DECODE Camada de Aplicação\n";
    cout << "\tQuadro: " << quadro << "\n";
    cout << "\tMensagem: " << mensagem << endl;

    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(string mensagem) {
    cout << "\nMensagem recebida: " << mensagem << endl;
}
