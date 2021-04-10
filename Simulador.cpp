#include <iostream>
#include <string>
#include <sstream>
#include "CamadaFisica.hpp"

using namespace std;

/*
    Simulação implementada em C++11 da Camada Física de comunicação utilizando
    os protocolos de modulação Binária, Manchester e Bipolar.
    O simulador é composto por uma aplicação transmissora e receptora e meio de
    transmissão. As aplicações possuem uma camada de aplicação e uma camada
    física que codificam e decodificam a mensagem, respectivamente.
    O fluxo de processamento funciona de forma que cada função chama a que será executada em seguida, na seguinte ordem:
        AplicacaoTransmissora() -> CamadaDeAplicacaoTransmissora() ->
        -> CamadaFisicaTransmissora() -> CamadaFisicaTransmissoraCodificacaoX()
        -> MeioDeComunicacao() -> CamadaFisicaReceptora() ->
        -> CamadaFisicaTransmissoraDecodificacaoX() ->
        -> CamadaDeAplicacaoReceptora() -> AplicacaoReceptora()
    Os detalhes do passo a passo de entradas e saídas está detalhado nos LOGs
    durante a execução do simulador.

    Entrada:
        string de texto de tamanho máximo de 1024 caracteres e o tipo de
        codificação escolhido (1: Binária, 2: Manchester, 3: Bipolar), ambos
        inseridos pelo usuário na GUI.
    Saída:
        print do string de texto exatamente igual ao de entrada.

    Exemplo (no terminal):
        g++ -std=c++11  *.cpp -o Simulador
        ./Simulador
*/
int main() {
    int logsFlag = 0;

    cout << "Deseja visualizar os LOGS do simulador?\n";
    cout << "\t1 - Sim\n";
    cout << "\t0 - Não\n";

    cout << "Resposta: ";
    cin >> logsFlag;

    cout << "\nINÍCIO DA SIMULAÇÃO" << endl;
    AplicacaoTransmissora(logsFlag);
}
