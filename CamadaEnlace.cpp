#include <iostream>
#include <cmath>

#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
#include "CamadaAplicacao.hpp"
#include "FuncoesAuxiliares.hpp"

using namespace std;

int tipoEnquadramento = 0;
int tipoControleDeErro = 0;

void CamadaEnlaceDadosTransmissora(vector<bitset<PACKET_SIZE>> sequenciaPacotes) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros;

    for (size_t i = 0; i < sequenciaPacotes.size(); i++){
        bitset<FRAME_SIZE> quadro;
        quadro = sequenciaPacotes[i].to_ulong();

        quadro = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

        quadro = CamadaEnlaceDadosTransmissoraControleDeErro(quadro);

        sequenciaQuadros.push_back(quadro);
    }

    if (LOG_FLAG) {
        cout << "\nLOGS - ENCODE Camada de Enlace:\n";
        cout << "\tPacotes:\n";
        PrintaVetorBitset(sequenciaPacotes);
        cout << "\tQuadros (com controle de erro):\n";
        PrintaVetorBitset(sequenciaQuadros);
    }

    CamadaFisicaTransmissora(sequenciaQuadros);
}

bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraEnquadramento(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> quadroEnquadrado;

    if (tipoEnquadramento == 0) {
        cout << "\nOpções de tipo de enquadramento na camada de enlace da Aplicação Transmissora:\n";
        cout << "\t1 - Contagem de caracteres\n";
        cout << "\t2 - Inserção de bytes\n";

        cout << "Escolha um tipo de enquadramento: ";
        cin >> tipoEnquadramento;
    }

    switch (tipoEnquadramento) {
        case 1:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 2:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
        default:
            cout << "Erro na Camada de Enlace: tipo de codificação não suportado. Encerrando programa." << endl;
    }

    return quadroEnquadrado;
}

bitset<FRAME_SIZE>  CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> quadroEnquadrado;
    int tamanhoQuadro = ContaTamanhoQuadro(quadro);

    quadroEnquadrado |= quadro;
    quadroEnquadrado <<= 8;
    quadroEnquadrado |= tamanhoQuadro;

    return quadroEnquadrado;
}

vector<int> indiceSegundoMarcador;

bitset<FRAME_SIZE>  CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> quadroEnquadrado;
    int tamanhoQuadro = ContaTamanhoQuadro(quadro);
    indiceSegundoMarcador.push_back(tamanhoQuadro+1);

    quadroEnquadrado |= 0b00011011; // ESC
    quadroEnquadrado <<= tamanhoQuadro*8;
    quadroEnquadrado |= quadro;
    quadroEnquadrado <<= 8;
    quadroEnquadrado |= 0b00011011; // ESC

    return quadroEnquadrado;
}

bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErro(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> quadroControle;

    if (tipoControleDeErro == 0) {
        cout << "\nOpções de tipo de controle de erro na camada de enlace da Aplicação Transmissora:\n";
        cout << "\t1 - Bit de paridade par\n";
        cout << "\t2 - Polinomio CRC-32 (IEEE 802)\n";

        cout << "Escolha um tipo de enquadramento: ";
        cin >> tipoControleDeErro;
    }

    switch (tipoControleDeErro) {
        case 1:
            quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidadePar(quadro);
            break;
        case 2:
            quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroControleDeErroCRC(quadro);
            break;
        default:
            cout << "Erro na Camada de Enlace: tipo de codificação não suportado. Encerrando programa." << endl;
    }

    return quadroControle;
}

bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidadePar(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> quadroControle(0);
    int numBytes = ContaTamanhoQuadro(quadro);
    int indiceByteFinal = (tipoEnquadramento == 1) ? numBytes : numBytes-1 ;
    vector<bitset<FRAME_SIZE>> payload;

    // salvando o byte de header (pode ser o contador ou o marcador)
    bitset<FRAME_SIZE> headerByte = quadro.to_ulong() & 0xFF;

    // calcula e adiciona bit de paridade para cada byte do payload do quadro
    for (size_t i = 1; i < indiceByteFinal; i++) {
        quadro >>= 8;
        bitset<FRAME_SIZE> byte = quadro.to_ulong() & 0xFF;
        int paridadePar = byte.count()%2;
        byte <<= 1;
        byte |= paridadePar;
        payload.push_back(byte);
    }

    // caso seja do tipo marcador, insere no que será o final do quadro
    if (tipoEnquadramento == 2){
        quadroControle |= headerByte;
    }

    // caso seja do tipo marcador, insere no que será o final do quadro
    int tamanhoPayload = payload.size();
    for (size_t i = 0; i < tamanhoPayload; i++){
        quadroControle <<= 9;
        quadroControle |= payload.back();
        payload.pop_back();
    }
    cout << "\nDEBUG:\t" << quadroControle << "\n";

    // insere o marcador ou contador no começo do quadro
    quadroControle <<= 8;
    quadroControle |= headerByte;
    return quadroControle;
}

bitset<FRAME_SIZE> CamadaEnlaceDadosTransmissoraControleDeErroControleDeErroCRC(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> polinomioCRC = 0x04C11DB7;
    bitset<FRAME_SIZE> quadroControle(0);
    int indiceBit;
    // cout << "\nQUADRO:\t" << quadro << " " << quadro.to_ulong();

    bitset<FRAME_SIZE> headerByte = quadro.to_ulong() & 0xFF;
    quadro >>= 8;

    // caso o header seja enquadrado por inserção de bits, remove o do final para extrair o payload
    if (tipoEnquadramento == 2) {
        int numBitQuadros = ContaTamanhoQuadro(quadro)*8;
        for (size_t i = numBitQuadros-8; i < numBitQuadros; i++) quadro.reset(i);
    }

    bitset<FRAME_SIZE> quadroOriginal = quadro;
    // cout << "\nQUADRO:\t" << quadro << " " << quadro.to_ulong();

    // verificando qual o indice do bit mais significante para garantir que polinomio divisor termina com bit 1
    int tamanhoPolinomio = ContaTamanhoBits(polinomioCRC);
    // cout << "\nPOLI:\t" << polinomioCRC << " " << polinomioCRC.to_ulong();

    // divisão de dois bitsets. Como tamanho é fixo, a cada iteração precisamos fazer a operação de shift no polinomio e depois o XOR. Neste cálculo o quociente é ignorado pois só o resto da divisão é relevante.
    while ((indiceBit = ContaTamanhoBits(quadro)) >= tamanhoPolinomio) {
        quadro ^= polinomioCRC << (indiceBit - tamanhoPolinomio);
    }

    // o resto é o próprio quadro depois de todos os shifts necessários pra divisão. Esse resto é somado ao quadro
    // cout << "\nRESTO1:\t" << quadro << " " << quadro.to_ulong();
    // cout << "\nRESTO2:\t" << quadroOriginal.to_ulong() % polinomioCRC.to_ulong();
    quadroOriginal = quadroOriginal.to_ulong() + quadro.to_ulong() ;
    // cout << endl;

    if (tipoEnquadramento == 2){
        quadroControle |= headerByte;
        quadroControle <<= ContaTamanhoQuadro(quadroOriginal)*8;
    }

    quadroControle |= quadroOriginal;
    quadroControle <<= 8;
    quadroControle |= headerByte;

    // cout << "\nCRC:\t" << quadroControle << " " << quadroControle.to_ulong();

    return quadroControle;
}

void CamadaEnlaceDadosReceptora(vector<int> fluxoBrutoDeBits) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros;
    vector<bitset<FRAME_SIZE>> sequenciaQuadrosDesenquadrados;


    if (LOG_FLAG) {
        cout << "\nLOGS - DECODE Camada de Enlace:\n";
        cout << "\tFluxo bruto de bits:\n\t\t";
        PrintaVetor(fluxoBrutoDeBits);
    }

    sequenciaQuadros = CamadaEnlaceDadosReceptoraEnquadramento(fluxoBrutoDeBits);

    for (size_t i = 0; i < sequenciaQuadros.size(); i++) {
        bitset<FRAME_SIZE> quadro;

        quadro = CamadaEnlaceDadosReceptoraControleDeErro(sequenciaQuadros[i]);

        sequenciaQuadrosDesenquadrados.push_back(quadro);
    }

    if (LOG_FLAG) {
        cout << "\tQuadros desenquadrados:\n";
        PrintaVetorBitset(sequenciaQuadrosDesenquadrados);
    }

    // CamadaDeAplicacaoReceptora(sequenciaQuadrosDesenquadrados);
}

vector<bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> fluxoBrutoDeBits) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros(0);

    switch (tipoEnquadramento) {
        case 1:
            sequenciaQuadros = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(fluxoBrutoDeBits);
            break;
        case 2:
            sequenciaQuadros = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(fluxoBrutoDeBits);
            break;
        default:
            cout << "Erro na Camada de Enlace. Encerrando programa." << endl;
    }

    return sequenciaQuadros;
}

vector<bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> fluxoBrutoDeBits) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros;
    // int numBytes = PACKET_SIZE/8 + 1; // 4 bytes de conteudo + 1 do cabeçalho
    // int numQuadros = ceil((fluxoBrutoDeBits.size()/8)/ ((float) numBytes));
    int numQuadros = ceil(fluxoBrutoDeBits.size()/ ((float) FRAME_SIZE));

    for (size_t i = 0; i < numQuadros; i++) {
        bitset<FRAME_SIZE> quadro(0);
        bitset<8> tamanhoQuadro(0);

        // busca tamamnho do quadro no primeiro byte enviado
        for (size_t j = 0; j < 8; j++) {
            if (fluxoBrutoDeBits.back()) tamanhoQuadro.set(j);
            fluxoBrutoDeBits.pop_back();
        }
        // checa se é necessário considerar o bit de paridade
        int tamanhoByte = (tipoControleDeErro == 1) ? 9 : 8;
        int numBits = tamanhoQuadro.to_ulong()*tamanhoByte;
        // preenche o quadro com as informações dos próximos bytes enviados
        for (size_t j = 0; j < numBits; j++) {
            if (fluxoBrutoDeBits.back()) quadro.set(j);
            fluxoBrutoDeBits.pop_back();
        }
        int numZeros = FRAME_SIZE - (numBits+8);
        for (size_t j = 0; j < numZeros; j++) fluxoBrutoDeBits.pop_back();

        sequenciaQuadros.push_back(quadro);
    }

    return sequenciaQuadros;
}

vector<bitset<FRAME_SIZE>> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> fluxoBrutoDeBits) {
    vector<bitset<FRAME_SIZE>> sequenciaQuadros;
    int numBytes = PACKET_SIZE/8 + 2; // 4 bytes de conteudo + 2 do cabeçalho
    // int numQuadros = ceil((fluxoBrutoDeBits.size()/8)/(float)numBytes);
    int numQuadros = ceil(fluxoBrutoDeBits.size()/ ((float) FRAME_SIZE));
    int tamanhoByte = (tipoControleDeErro == 1) ? 9 : 8;


    for (size_t i = 0; i < numQuadros; i++) {
        bitset<FRAME_SIZE> quadro(0);
        // checa se é necessário considerar o bit de paridade
        bitset<9> byte(0);
        int indiceQuadro = 0;
        int flagQuadro = 0, flagByte = 1;
        int contador = 0;

        cout << "\nDEBUG:\t" << indiceSegundoMarcador[i];
        do {
            byte.reset();

            // busca primeiro byte, que deve ser o marcador "\0"
            int numBits = (contador > 0  && contador < indiceSegundoMarcador[i]) ? tamanhoByte : 8;
            for (size_t j = 0; j < numBits; j++) {
                if (fluxoBrutoDeBits.back()) byte.set(j);
                fluxoBrutoDeBits.pop_back();
            }
            contador++;

            // checa se o byte atual é primeiro ou último marcador "\0" para controlar a repetição
            if (byte.to_ulong() == 0b00011011) {
                flagQuadro = (flagQuadro) ? 0 : 1;
            } else {
                // preenche o byte no quadro
                for (size_t j = 0; indiceQuadro < numBytes*tamanhoByte; indiceQuadro++, j++) {
                    if (indiceQuadro % tamanhoByte == 0 && indiceQuadro >= tamanhoByte) {
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

        int numZeros = FRAME_SIZE - ((contador-2)*9+16);
        for (size_t j = 0; j < numZeros; j++) fluxoBrutoDeBits.pop_back();

        sequenciaQuadros.push_back(quadro);
    }

    return sequenciaQuadros;
}

bitset<FRAME_SIZE> CamadaEnlaceDadosReceptoraControleDeErro(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> quadroVerificado;

    switch (tipoControleDeErro) {
        case 1:
            quadroVerificado = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
            break;
        case 2:
            quadroVerificado = CamadaEnlaceDadosReceptoraControleDeErroControleDeErroCRC(quadro);
            break;
        default:
            cout << "Erro na Camada de Enlace: tipo de codificação não suportado. Encerrando programa." << endl;
    }

    return quadroVerificado;
}

bitset<FRAME_SIZE> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> quadroVerificado(0);
    vector<bitset<9>> payload;
    int flag = 1;

    do {
        bitset<9> byte(0);
        for (size_t i = 0; i < 9; i++) {
            if (quadro[i]) byte.set(i);
        }
        quadro >>= 9;

        // para quando chega no final do quadro
        if (byte.to_ulong() == 0){
            flag = 0;
        // checa se o bit é par e remove o bit de paridade
        } else if (byte.count() % 2 == 0) {
            byte >>= 1;
            cout << "\nDEBUG:\t" << byte;
            payload.push_back(byte);
        // para a análise quando detecta um erro e zero a saída
        } else {
            cout << "\n\tERRO: Erro detectado na transmissão do bit\n";
            quadroVerificado = 0;
            flag = 0;
        }

    } while (flag);

    int tamanhoPayload = payload.size();
    for (size_t i = 0; i < tamanhoPayload; i++){
        quadroVerificado <<= 8;
        quadroVerificado |= payload.back().to_ulong();
        payload.pop_back();
    }
    return quadroVerificado;
}

bitset<FRAME_SIZE> CamadaEnlaceDadosReceptoraControleDeErroControleDeErroCRC(bitset<FRAME_SIZE> quadro) {
    bitset<FRAME_SIZE> polinomioCRC = 0x04C11DB7;
    bitset<FRAME_SIZE> quadroVerificado(0);
    bitset<FRAME_SIZE> resultado(0);
    int indiceBit;

    // verificando qual o indice do bit mais significante para garantir que polinomio divisor termina com bit 1
    int tamanhoPolinomio = ContaTamanhoBits(polinomioCRC);

    // divisão de dois bitsets. Como tamanho é fixo, a cada iteração precisamos fazer a operação de shift no polinomio e depois o XOR. Neste cálculo o quociente é ignorado pois só o resto da divisão é relevante.
    while ((indiceBit = ContaTamanhoBits(quadro)) >= tamanhoPolinomio) {
        resultado.set(indiceBit - tamanhoPolinomio);
        quadro ^= polinomioCRC << (indiceBit - tamanhoPolinomio);
    }

    cout << "\nDEBUG:\t" << quadro << "\n";

    if (quadro.to_ulong() == 0) {
        cout << "\n\tERRO: Erro detectado na transmissão do bit\n";
    }

    return quadroVerificado;
}
