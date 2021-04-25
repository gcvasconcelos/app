#include <iostream>
#include <cmath>
#include "CamadaFisica.hpp"
#include "CamadaAplicacao.hpp"

using namespace std;

int flagLogs = 0;

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
void AplicacaoTransmissora(int flag) {
    string mensagem;

    flagLogs = flag;

    cout << "\nDigite uma mensagem: ";
    cin.ignore();
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
    bitset<8*MAX_SIZE> quadro;
    int size = mensagem.size();

    for (size_t i = 0; i < size; i++) {
        quadro <<= 8;
        quadro |= mensagem[i];
    }

    if (flagLogs) {
        cout << "\nLOGS - ENCODE Camada de Aplicação\n";
        cout << "\tMensagem: " << mensagem << "\n";
        cout << "\tQuadro: " << quadro << endl;
    }

    CamadaFisicaTransmissora(quadro, size);
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
void CamadaDeAplicacaoReceptora(bitset<8*MAX_SIZE> quadro, int size) {
    string mensagem = "";
    bitset<8*MAX_SIZE> ulong_kernel;
    int num_ulongs = ceil(size/64.0);
    int byte_idx = 0;
    int flag = 1;

    if (flagLogs) {
        cout << "\nLOGS - DECODE Camada de Aplicação\n";
        cout << "\tQuadro: " << quadro << "\n";
    }

    for (size_t i = 0; i < 64; i++) ulong_kernel.set(i);

    // o tamanho máximo do quadro para a conversão para caracteres é um ulong
    // (64bits). Portanto se divide o quadro em vários ulongs.
    for (size_t i = 0; i < num_ulongs; i++) {
        bitset<8*MAX_SIZE> quadro_ulong;
        quadro_ulong = quadro & ulong_kernel;

        for (;byte_idx < size/8;byte_idx++) {
            // checa se está no fim do ulong para sair do loop e garante que
            // na volta, não caia no mesmo condicional
            if (byte_idx % 8 == 0 && byte_idx >= 8) {
                if (flag) {
                    flag = 0;
                    break;
                } else {
                    flag = 1;
                }
            }
            char ch = quadro_ulong.to_ulong() & 0xFF;

            mensagem = ch + mensagem;
            quadro_ulong >>= 8;
        }
        // passa para proximo ulong do quadro
        quadro >>= 64;
    }

    if (flagLogs) {
        cout << "\tMensagem: " << mensagem << endl;
    }

    AplicacaoReceptora(mensagem);
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
void AplicacaoReceptora(string mensagem) {
    cout << "\nMensagem recebida: " << mensagem << endl;
}
