#include <iostream>
#include <cmath>

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
            cout << "Erro na Camada de Enlace: tipo de codificação não suportado. Encerrando programa." << endl;
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

void CamadaEnlaceDadosReceptora(vector<int> fluxoBrutoDeBits) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros;

    CamadaEnlaceDadosReceptoraEnquadramento(fluxoBrutoDeBits, sequenciaQuadros);

    CamadaDeAplicacaoReceptora(sequenciaQuadros);
}

void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> fluxoBrutoDeBits, vector<bitset<FRAME_SIZE>> &sequenciaQuadros) {
    if (LOG_FLAG) {
        cout << "\nLOGS - DECODE Camada de Enlace:\n";
        cout << "\tFluxo de bits:\n\t\t";
        PrintaVetor(fluxoBrutoDeBits);
    }
    switch (tipoEnquadramento) {
        case 1:
            sequenciaQuadros = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(fluxoBrutoDeBits);
            break;
        case 2:
            sequenciaQuadros = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(fluxoBrutoDeBits);
            break;
        default:
            cout << "Erro na Camada de Enlace. Encerrando programa." << endl;
            return;
    }

    if (LOG_FLAG) {
        cout << "\tQuadros Desenquadrados:\n" ;
        PrintaVetorBitset(sequenciaQuadros);
    }
}

vector<bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> fluxoBrutoDeBits) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros;
    int numQuadros = ceil((fluxoBrutoDeBits.size()/8)/9.0);

    for (size_t i = 0; i < numQuadros; i++) {
        bitset<FRAME_SIZE> quadro(0);
        bitset<8> tamanhoQuadro(0);

        // busca tamamnho do quadro no primeiro byte enviado
        for (size_t j = 0; j < 8; j++) {
            if (fluxoBrutoDeBits.back()) tamanhoQuadro.set(j);
            fluxoBrutoDeBits.pop_back();
        }

        // preenche o quadro com as informações dos próximos bytes enviados
        for (size_t j = 0; j < tamanhoQuadro.to_ulong()*8; j++) {
            if (fluxoBrutoDeBits.back()) quadro.set(j);
            fluxoBrutoDeBits.pop_back();
        }

        // quadro <<= 8;
        // quadro |= tamanhoQuadro.to_ulong();

        sequenciaQuadros.push_back(quadro);
    }

    return sequenciaQuadros;
}

vector<bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> fluxoBrutoDeBits) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros;
    float tamanhoQuadro = 10.0;
    int numQuadros = ceil((fluxoBrutoDeBits.size()/8)/tamanhoQuadro);

    for (size_t i = 0; i < numQuadros; i++) {
        bitset<FRAME_SIZE> quadro(0);
        bitset<8> byte(0);
        int indiceQuadro = 0;
        int flagQuadro = 0, flagByte = 1;

        do {
            byte.reset();

            // busca primeiro byte, que deve ser o marcador "\0"
            for (size_t j = 0; j < 8; j++) {
                if (fluxoBrutoDeBits.back()) byte.set(j);
                fluxoBrutoDeBits.pop_back();
            }

            // checa se o byte atual é primeiro ou último marcador "\0" para controlar a repetição
            if (byte.to_ulong() == 0b00011011) {
                flagQuadro = (flagQuadro) ? 0 : 1;
            } else {
                // preenche o byte no quadro
                for (size_t j = 0; indiceQuadro < tamanhoQuadro*8; indiceQuadro++, j++) {
                    if (indiceQuadro % 8 == 0 && indiceQuadro >= 8) {
                        if (flagByte) {
                            flagByte = 0;
                            break;
                        } else {
                            flagByte = 1;
                        }
                    }
                    quadro[indiceQuadro] = byte[j];
                }
            }

        } while (flagQuadro);

        sequenciaQuadros.push_back(quadro);
    }

    return sequenciaQuadros;
}
