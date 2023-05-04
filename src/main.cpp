/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Construtor.h"
#include "CriadorInstancias.h"
#include <chrono>
#include <thread>
#include <time.h>
#include <stdlib.h>
#include "ListaSol.h"
#include "BL.h"

using namespace std;

int main(int argc, char const *argv[])
{

    // string nomeArquivo;
    // cout << "Digite o nome do arquivo" << endl;
    // cin >> nomeArquivo;
    cout<<"a"<<endl;
    //ofstream output_file;

    //output_file.open("teste2.txt", ios::out | ios::trunc);

    int cod_instancia = 0;
    // cout << "Digite o codigo da Instancia: ";
    // cin >> instancia;
    // 1670879965
    // 1670879893
    // 1670879957
    cod_instancia = 1670879895;
    srand(cod_instancia);


    CriadorInstancias *instancia = new CriadorInstancias();

    ListaSol *sol = new ListaSol(instancia);

    sol->ConstruirSolucoes(100);

    srand(time(NULL));

    //BL *bl = new BL(a);
   // ConjuntoPopulacional *populacao = new ConjuntoPopulacional(numeroDeSolucoesTotais);
    //for (int i = 0; i < numeroDeSolucoesTotais; i++)
    //{

        //Construtor *b = new Construtor(instancia);
        //b->solucao->id = i;

        // b->Imprime();
        // bl->AdicionaProcesso(b->solucao->primeira_maquina,a->buscaProcesso(b->solucao->primeira_maquina->primeiro_processoSol->id),1);
        // b->Imprime();

        //bl->AtualizaCustos(b->solucao);
        // b->Imprime();

        // b->Imprime();
        // bl->AtualizaCustos(b->solucao);
        // cout<<b->solucao->makespam<<endl;
        //populacao->preencheListasPorRequisito(b->solucao);
    //}


    return 0;
}
