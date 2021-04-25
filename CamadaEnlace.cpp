#include <iostream>
#include <bitset>

#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
#include "CamadaAplicacao.hpp"

using namespace std;


int tipoEnquadramento = 0;
int flagLogs = 0;

void CamadaEnlaceDadosTransmissora(std::bitset<8*MAX_SIZE> quadro, int size) {
    bitset<8*FRAME_SIZE> quadroEnquadrado;

    quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro, size);

    CamadaFisicaTransmissora(quadroEnquadrado, size);
}

std::bitset<8*FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramento(std::bitset<8*MAX_SIZE> quadro, int size) {
    bitset<8*FRAME_SIZE> quadroEnquadrado;

    cout << "\nOpções de tipo de enquadramento na camada de enlace da Aplicação Transmissora:\n";
    cout << "\t1 - Contagem de caracteres\n";
    cout << "\t2 - Inserção de bytes\n";

    cout << "Escolha um tipo de enquadramento: ";
    cin >> tipoEnquadramento;

    if (flagLogs) {
        cout << "\nLOGS - ENCODE Camada de Enlace:\n";
        cout << "\tQuadro:\t\t" << quadro << "\n";
    }
    switch (tipoEnquadramento) {
        case 1:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro, size);
            break;
        case 2:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro, size);
            break;
        default:
            cout << "Erro na Camada de Enlace. Encerrando programa." << endl;
            return;
    }

    if (flagLogs) {
        cout << "\tQuadro Enquadrado:\t" << quadroEnquadrado << endl;
    }

    return quadroEnquadrado;
}

std::bitset<8*FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::bitset<8*MAX_SIZE> quadro, int size) {
    std::bitset<8*FRAME_SIZE> quadroEnquadrado;


    // TODO
}

std::bitset<8*FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::bitset<8*MAX_SIZE> quadro, int size) {
    // TODO
}

void CamadaEnlaceDadosReceptora(std::bitset<8*FRAME_SIZE> quadroEnquadrado, int size) {
    bitset<8*MAX_SIZE> quadro;

    quadro = CamadaEnlaceDadosReceptoraEnquadramento(quadroEnquadrado);

    CamadaDeAplicacaoReceptora(quadro, size);
}

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramento(std::bitset<8*FRAME_SIZE> quadroEnquadrado) {
    bitset<8*MAX_SIZE> quadro;

    if (flagLogs) {
        cout << "\nLOGS - DECODE Camada de Enlace:\n";
        cout << "\tQuadro Enquadrado:\t" << quadroEnquadrado << "\n";
    }
    switch (tipoEnquadramento) {
        case 1:
            quadro = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadroEnquadrado);
            break;
        case 2:
            quadro = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadroEnquadrado);
            break;
        default:
            cout << "Erro na Camada de Enlace. Encerrando programa." << endl;
            return;
    }

    if (flagLogs) {
        cout << "\tQuadro:\t\t" << quadro << endl;
    }

    return quadro;
}

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::bitset<8*FRAME_SIZE> quadroEnquadrado) {
    // TODO
}

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::bitset<8*FRAME_SIZE> quadroEnquadrado) {
    // TODO
}
