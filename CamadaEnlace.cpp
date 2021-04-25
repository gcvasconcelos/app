#include <iostream>
#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"

int tipoEnquadramento = 0;
int flagLogs = 0;

const int FRAME = 8*MAX_SIZE+64;

void CamadaEnlaceDadosTransmissora(std::bitset<8*MAX_SIZE> quadro, int size) {
    bitset<8*MAX_SIZE> quadroEnquadrado;

    quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro, size);

    CamadaFisicaTransmissora(quadroEnquadrado);
}

std::bitset<FRAME> CamadaEnlaceDadosTransmissoraEnquadramento(std::bitset<8*MAX_SIZE> quadro, int size) {
    bitset<FRAME> quadroEnquadrado;

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

std::bitset<FRAME> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::bitset<8*MAX_SIZE> quadro, int size) {
    std::bitset<FRAME> quadroEnquadrado;


    // TODO
}

std::bitset<FRAME> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::bitset<8*MAX_SIZE> quadro, int size) {
    // TODO
}

void CamadaEnlaceDadosReceptora(std::bitset<FRAME> quadroEnquadrado) {
    bitset<8*MAX_SIZE> quadro;

    quadro = CamadaEnlaceDadosReceptoraEnquadramento(quadroEnquadrado);

    CamadaDeAplicacaoReceptora(quadro);
}

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramento(std::bitset<FRAME> quadroEnquadrado) {
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

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::bitset<FRAME> quadroEnquadrado) {
    // TODO
}

std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::bitset<FRAME> quadroEnquadrado) {
    // TODO
}
