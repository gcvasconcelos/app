#include <iostream>

#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
#include "CamadaAplicacao.hpp"
#include "FuncoesAuxiliares.hpp"

using namespace std;

int tipoEnquadramento = 0;

void CamadaEnlaceDadosTransmissora(vector<bitset<PACKET_SIZE>> sequenciaPacotes) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros;

    for (size_t i = 0; i < sequenciaPacotes.size(); i++){
        bitset<FRAME_SIZE> quadro;
        quadro = sequenciaPacotes[i].to_ulong();
        sequenciaQuadros.push_back(quadro);
    }

    sequenciaQuadros = CamadaEnlaceDadosTransmissoraEnquadramento(sequenciaQuadros);

    // detecção de erros

    CamadaFisicaTransmissora(sequenciaQuadros);
}

vector<bitset<FRAME_SIZE>> CamadaEnlaceDadosTransmissoraEnquadramento(vector<bitset<FRAME_SIZE>> sequenciaQuadros) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadrosEnquadrados;

    cout << "\nOpções de tipo de enquadramento na camada de enlace da Aplicação Transmissora:\n";
    cout << "\t1 - Contagem de caracteres\n";
    cout << "\t2 - Inserção de bytes\n";

    cout << "Escolha um tipo de enquadramento: ";
    cin >> tipoEnquadramento;

    if (LOG_FLAG) {
        cout << "\nLOGS - ENCODE Camada de Enlace:\n";
        cout << "\tQuadros:\n" ;
        PrintaVetorBitset(sequenciaQuadros);
    }

    switch (tipoEnquadramento) {
        case 1:
            sequenciaQuadrosEnquadrados = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(sequenciaQuadros);
            break;
        case 2:
            sequenciaQuadrosEnquadrados = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(sequenciaQuadros);
            break;
        default:
            cout << "Erro na Camada de Enlace. Encerrando programa." << endl;
    }

    if (LOG_FLAG) {
        cout << "\tQuadros Enquadrados:\n" ;
        PrintaVetorBitset(sequenciaQuadrosEnquadrados);
    }

    return sequenciaQuadrosEnquadrados;
}

vector<bitset<FRAME_SIZE>>  CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<bitset<FRAME_SIZE>> sequenciaQuadros) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadrosEnquadrados;
    int numQuadros = sequenciaQuadros.size();

    for (size_t i = 0; i < numQuadros; i++) {
        bitset<FRAME_SIZE> quadroEnquadrado;
        int tamanhoQuadro = ContaTamanhoQuadro(sequenciaQuadros[i]);

        quadroEnquadrado |= sequenciaQuadros[i];
        quadroEnquadrado <<= 8;
        quadroEnquadrado |= tamanhoQuadro;

        sequenciaQuadrosEnquadrados.push_back(quadroEnquadrado);
    }
    return sequenciaQuadrosEnquadrados;
}

vector<bitset<FRAME_SIZE>>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<bitset<FRAME_SIZE>> sequenciaQuadros) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadrosEnquadrados;
    int numQuadros = sequenciaQuadros.size();

    for (size_t i = 0; i < numQuadros; i++) {
        bitset<FRAME_SIZE> quadroEnquadrado;
        int tamanhoQuadro = ContaTamanhoQuadro(sequenciaQuadros[i]);

        quadroEnquadrado |= 0b00011011; // ESC
        quadroEnquadrado <<= tamanhoQuadro*8;
        quadroEnquadrado |= sequenciaQuadros[i];
        quadroEnquadrado <<= 8;
        quadroEnquadrado |= 0b00011011; // ESC

        sequenciaQuadrosEnquadrados.push_back(quadroEnquadrado);
    }
    return sequenciaQuadrosEnquadrados;
}

// void CamadaEnlaceDadosReceptora(std::bitset<8*FRAME_SIZE> quadroEnquadrado, int size) {
//     bitset<8*MAX_SIZE> quadro;

//     quadro = CamadaEnlaceDadosReceptoraEnquadramento(quadroEnquadrado);

//     CamadaDeAplicacaoReceptora(quadro, size);
// }

// std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramento(std::bitset<8*FRAME_SIZE> quadroEnquadrado) {
//     bitset<8*MAX_SIZE> quadro;

//     if (LOG_FLAG) {
//         cout << "\nLOGS - DECODE Camada de Enlace:\n";
//         cout << "\tQuadro Enquadrado:\t" << quadroEnquadrado << "\n";
//     }
//     switch (tipoEnquadramento) {
//         case 1:
//             quadro = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadroEnquadrado);
//             break;
//         case 2:
//             quadro = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadroEnquadrado);
//             break;
//         default:
//             cout << "Erro na Camada de Enlace. Encerrando programa." << endl;
//             return;
//     }

//     if (LOG_FLAG) {
//         cout << "\tQuadro:\t\t" << quadro << endl;
//     }

//     return quadro;
// }

// std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::bitset<8*FRAME_SIZE> quadroEnquadrado) {
//     // TODO
// }

// std::bitset<8*MAX_SIZE> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::bitset<8*FRAME_SIZE> quadroEnquadrado) {
//     // TODO
// }
