#include <iostream>
#include <cmath>

#include "CamadaAplicacao.hpp"
#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
#include "FuncoesAuxiliares.hpp"

using namespace std;

/*
    Simula a Aplicação Transmissora de uma mensagem em texto e de tamanho
    limitado. A função da início ao processo de transmissão.

    Entrada:
        recebe no terminal uma string de até 1024 caracteres.
    Saída:
        chama a função da Camada de Aplicação Transmissora.

    Exemplo:
        << "qualquer mensagem"
 */
void AplicacaoTransmissora() {
    string mensagem;

    cout << "\nDigite uma mensagem: ";
    // cin.ignore();
    getline(cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

/*
    Simula a Camada de Aplicação da Aplicação Transmissora. A função processa a
    mensagem e a transforma em quadros (bits dos caracteres da mensagem), de
    tamanho fixo, para serem enviados a camada física. Funciona como uma
    interface entre o usuário e a camada física.

    Entrada:
        string da mensagem.
    Saída:
        quadro (bitset) correspondente a mensagem e chama a função da Camada
        Física Transmissora.

    Exemplo:
        CamadaDeAplicacaoTransmissora("mensagem");
        >> 0110110101100101011011100111001101100001011001110110010101101101
 */
void CamadaDeAplicacaoTransmissora(string mensagem) {
    vector<bitset<PACKET_SIZE>> sequenciaPacotes;
    int flag = 1, indicePacote = 0;
    int tamanho = mensagem.size();
    int numPacotes = ceil(tamanho/8.0);

    for (size_t i = 0; i < numPacotes; i++) {
        bitset<PACKET_SIZE> pacote;

        for (; indicePacote < tamanho; indicePacote++) {
            if (indicePacote % 8 == 0 && indicePacote >= 8) {
                if (flag) {
                    flag = 0;
                    break;
                } else {
                    flag = 1;
                }
            }
            pacote <<= 8;
            pacote |= mensagem[(tamanho-1)-indicePacote];
        }
        sequenciaPacotes.push_back(pacote);
    }

    if (LOG_FLAG) {
        cout << "\nLOGS - ENCODE Camada de Aplicação\n";
        cout << "\tMensagem: " << mensagem << "\n";
        cout << "\tPacotes:\n" ;
        PrintaVetorBitset(sequenciaPacotes);
    }

    CamadaEnlaceDadosTransmissora(sequenciaPacotes);
}

/*
    Simula a Camada de Aplicação da Aplicação Receptora. A função processa o
    quadro e o converte na mensagem em texto recebida.

    Entrada:
        quadro (bitset).
    Saída:
        string da mensagem e chama a função da Aplicacao Receptora.

    Exemplo:
        CamadaDeAplicacaoReceptora(01100001);
        >> "a"
 */
void CamadaDeAplicacaoReceptora(vector<bitset<FRAME_SIZE>> sequenciaQuadros) {
    int numQuadros = sequenciaQuadros.size();
    vector<bitset<PACKET_SIZE>> sequenciaPacotes;

    if (LOG_FLAG) {
        cout << "\nLOGS - DECODE Camada de Aplicação\n";
        cout << "\tQuadros:\n" ;
        PrintaVetorBitset(sequenciaQuadros);
    }

    for (size_t i = 0; i < numQuadros; i++) {
        bitset<PACKET_SIZE> pacote;

        pacote = sequenciaQuadros[i].to_ulong();

        sequenciaPacotes.push_back(pacote);
    }

    if (LOG_FLAG) {
        cout << "\tPacotes:\n" ;
        PrintaVetorBitset(sequenciaPacotes);
    }

    AplicacaoReceptora(sequenciaPacotes);
}

/*
    Simula a Aplicação Receptora de uma mensagem.

    Entrada:
        string da mensagem.
    Saída:
        printa a mensagem recebida e encerra a simulação.

    Exemplo:
        AplicacaoReceptora("mensagem");
        >> Mensagem recebida: mensagem
 */
void AplicacaoReceptora(vector<bitset<PACKET_SIZE>> sequenciaPacotes) {
    string mensagem = "";
    int numPacotes = sequenciaPacotes.size();
    int indiceByte = 0, flagByte = 1;

    for (size_t i = 0; i < numPacotes; i++) {
        bitset<PACKET_SIZE> pacote = sequenciaPacotes[(numPacotes-1)-i];

        int tamanhoPacote = ContaTamanhoPacote(pacote);

        for (; indiceByte < PACKET_SIZE*8; indiceByte++) {
            if (indiceByte % 8 == 0 && indiceByte >= 8) {
                if (flagByte) {
                    flagByte = 0;
                    break;
                } else {
                    flagByte = 1;
                }
            }
            char ch = pacote.to_ulong() & 0xFF;
            pacote >>= 8;

            mensagem = mensagem + ch;
        }
    }

    cout << "\nMensagem recebida:\n\t\t" << mensagem << endl;
}
