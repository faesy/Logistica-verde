
using namespace std;

#include <iostream>
#include "Construtivo.h"

float importanciaf0=0;
float importanciaf1=1;
float importanciaf2=1;

float parametro_de_analise=0.5;

Solucao* Construtivo::criaSol(Instancia *instancia)
{
    Solucao *solucao = new Solucao();
    solucao->pos=0;
    ListaCandidatos *lista = new ListaCandidatos();
    Adiciona_Basico(solucao,instancia);

    int sequenciaProcessos[instancia->get_n()];
    for (int i = 0; i < instancia->get_n(); i++)
    {
        sequenciaProcessos[i] = i;
    }
    for (int i = 0; i < instancia->get_n() * 5; i++)
    {
        embaralhar(sequenciaProcessos, instancia->get_n());
    }


    for (int i = 0; i < instancia->get_n(); i++)
    {
        AdicionaPontos(sequenciaProcessos[i],solucao,instancia,lista);
        RemovePontos(sequenciaProcessos[i],solucao,instancia,lista);
        int sorteado = lista->Sorteia_na_Lista();
        Adiciona_Processo_Na_Maquina(sequenciaProcessos[i], sorteado,solucao,instancia);
        lista->Zera_Lista();
    }
    int makespam = 0;
    for (MaquinaSol *a = solucao->primeira_maquina; a != NULL; a = a->prox_maquinaSol)
    {
        if (a->min_Atual > makespam)
        {
            makespam = a->min_Atual;
        }
    }

    solucao->makespam = makespam;

    
    for(MaquinaSol *a = solucao->primeira_maquina; a != NULL; a = a->prox_maquinaSol){
        for(ProcessoSol *b = a->primeiro_processoSol; b != NULL; b=b->prox_processoSol){
            solucao->jobs[b->id]=a->id;
        }
    }

    //cout<<"Makespam: "<<solucao->makespam<<endl;
    return solucao;
    // Imprime();
}

void Construtivo::Imprime(Solucao* solucao,Instancia* instancia)
{
    int custo = 0;
    for (MaquinaSol *a = solucao->primeira_maquina; a != NULL; a = a->prox_maquinaSol)
    {
        cout << "Maquina " << a->id << " : ";
        for (ProcessoSol *b = a->primeiro_processoSol; b != NULL; b = b->prox_processoSol)
        {
            cout << b->id << " -> ";
            custo = custo + instancia->buscaProcesso(b->id)->custos_energia[a->id];
        }
        cout << "Tempo final: " << a->min_Atual << " || Custo Energetico: "<<a->CE<<endl;
    }
    cout << "Makespam: " << solucao->makespam << endl;
    cout << "Custo Energetico: " << solucao->custoEnergia << endl;
}

void Construtivo::RemovePontos(int id_Processo,Solucao* solucao,Instancia* instancia,ListaCandidatos *lista)
{
    Processo *processo;
    for (Processo *it = instancia->get_primeiro_Processo(); it != NULL; it = it->get_prox_Processo())
    {
        if (it->get_id() == id_Processo)
        {
            processo = it;
            break;
        }
    }
    int tamanhoVetor = instancia->get_m() *parametro_de_analise;
    int maquinas_mais_devagar[tamanhoVetor];
    int maquinas_mais_devagar2[tamanhoVetor];
    bool maquinas_mais_devagar_bool[instancia->get_m()];
    int maquinas_com_maior_makespam[tamanhoVetor];
    int maquinas_com_maior_makespam2[tamanhoVetor];
    bool maquinas_com_maior_makespam_bool[instancia->get_m()];
    int maquinas_com_maior_consumo[tamanhoVetor];
    int maquinas_com_maior_consumo2[tamanhoVetor];
    bool maquinas_com_maior_consumo_bool[instancia->get_m()];

    for (int j = 0; j < tamanhoVetor; j++)
    {
        maquinas_mais_devagar[j] = 99999999;
        maquinas_com_maior_makespam[j] = 0;
        maquinas_com_maior_consumo[j] = 0;
    }

    for (int j = 0; j < instancia->get_m(); j++)
    {
        maquinas_mais_devagar_bool[j] = false;
        maquinas_com_maior_makespam_bool[j] = false;
        maquinas_com_maior_consumo_bool[j] = false;
    }

    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (Maquina *i = instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
        {
            if (maquinas_mais_devagar_bool[contador] == false)
            {
                if (maquinas_mais_devagar[r] > processo->tempos_processamento[i->get_id()])
                {
                    maquinas_mais_devagar[r] = processo->tempos_processamento[i->get_id()];
                    maquinas_mais_devagar2[r] = i->get_id();

                    index_melhor_resultado = contador;
                }
            }
            contador++;
        }
        maquinas_mais_devagar_bool[index_melhor_resultado] = true;
    }

    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (Maquina *i = instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
        {
            if (maquinas_com_maior_consumo_bool[contador] == false)
            {
                if (maquinas_com_maior_consumo[r] < processo->custos_energia[i->get_id()])
                {
                    maquinas_com_maior_consumo[r] = processo->custos_energia[i->get_id()];
                    maquinas_com_maior_consumo2[r] = i->get_id();
                    index_melhor_resultado = contador;
                }
            }
            contador++;
        }
        maquinas_com_maior_consumo_bool[index_melhor_resultado] = true;
    }

    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (MaquinaSol *i = solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
        {
            if (maquinas_com_maior_makespam_bool[contador] == false)
            {
                if (maquinas_com_maior_makespam[r] < i->min_Atual)
                {
                    maquinas_com_maior_makespam[r] = i->min_Atual;
                    maquinas_com_maior_makespam2[r] = i->id;
                    index_melhor_resultado = contador;
                }
            }
            contador++;
        }
        maquinas_com_maior_makespam_bool[index_melhor_resultado] = true;
    }

    for (int j = 0; j < tamanhoVetor; j++)
    {
        lista->Remove_na_Lista(maquinas_mais_devagar2[j], (((instancia->get_m()) - j)* parametro_de_analise) * (importanciaf0));
        lista->Remove_na_Lista(maquinas_com_maior_makespam2[j], (((instancia->get_m())* parametro_de_analise) - j) * (importanciaf1) );

        lista->Remove_na_Lista(maquinas_com_maior_consumo2[j], (((instancia->get_m())* parametro_de_analise) - j) * (importanciaf2) );
    }

    if(lista->primeiro_elemento==NULL){
        lista->Adicionar_na_Lista(rand()%instancia->get_m(),1);
    }
}

void Construtivo::AdicionaPontos(int id_Processo,Solucao* solucao,Instancia* instancia,ListaCandidatos* lista)
{
    Processo *processo;
    for (Processo *it = instancia->get_primeiro_Processo(); it != NULL; it = it->get_prox_Processo())
    {
        if (it->get_id() == id_Processo)
        {
            processo = it;
            break;
        }
    }
    int tamanhoVetor = instancia->get_m() * parametro_de_analise;
    int maquinas_mais_rapidas[tamanhoVetor];
    int maquinas_mais_rapidas2[tamanhoVetor];
    bool maquinas_mais_rapidas_bool[instancia->get_m()];
    int maquinas_com_menos_makespam[tamanhoVetor];
    int maquinas_com_menos_makespam2[tamanhoVetor];
    bool maquinas_com_menos_makespam_bool[instancia->get_m()];
    int maquinas_com_menos_consumo[tamanhoVetor];
    int maquinas_com_menos_consumo2[tamanhoVetor];
    bool maquinas_com_menos_consumo_bool[instancia->get_m()];
    for (int j = 0; j < tamanhoVetor; j++)
    {
        maquinas_mais_rapidas[j] = 0;
        maquinas_com_menos_makespam[j] = 99999999;
        maquinas_com_menos_consumo[j] = 99999999;
    }
    for (int j = 0; j < instancia->get_m(); j++)
    {
        maquinas_mais_rapidas_bool[j] = false;
        maquinas_com_menos_makespam_bool[j] = false;
        maquinas_com_menos_consumo_bool[j] = false;
    }
    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (Maquina *i = instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
        {
            if (maquinas_mais_rapidas_bool[contador] == false)
            {
                if (maquinas_mais_rapidas[r] < processo->tempos_processamento[i->get_id()])
                {
                    maquinas_mais_rapidas[r] = processo->tempos_processamento[i->get_id()];
                    maquinas_mais_rapidas2[r] = i->get_id();
                    index_melhor_resultado = contador;
                }
            }
            contador++;
        }
        maquinas_mais_rapidas_bool[index_melhor_resultado] = true;
    }

    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (Maquina *i = instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
        {
            if (maquinas_com_menos_consumo_bool[contador] == false)
            {
                if (maquinas_com_menos_consumo[r] > processo->custos_energia[i->get_id()])
                {
                    maquinas_com_menos_consumo[r] = processo->custos_energia[i->get_id()];
                    maquinas_com_menos_consumo2[r] = i->get_id();
                    index_melhor_resultado = contador;
                }
            }
            contador++;
        }
        maquinas_com_menos_consumo_bool[index_melhor_resultado] = true;
    }
    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (MaquinaSol *i = solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
        {
            if (maquinas_com_menos_makespam_bool[contador] == false)
            {
                if (maquinas_com_menos_makespam[r] > i->min_Atual)
                {
                    maquinas_com_menos_makespam[r] = i->min_Atual;
                    maquinas_com_menos_makespam2[r] = i->id;
                    index_melhor_resultado = contador;
                }
            }
            contador++;
        }
        maquinas_com_menos_makespam_bool[index_melhor_resultado] = true;
    }
    for (int j = 0; j < tamanhoVetor; j++)
    {
        lista->Adicionar_na_Lista(maquinas_mais_rapidas2[j], (((instancia->get_m())* parametro_de_analise) - j) * (importanciaf0));
        lista->Adicionar_na_Lista(maquinas_com_menos_makespam2[j], (((instancia->get_m())* parametro_de_analise) - j) * (importanciaf1) );

        lista->Adicionar_na_Lista(maquinas_com_menos_consumo2[j], (((instancia->get_m())* parametro_de_analise) - j) * (importanciaf2) );
    }
}

void Construtivo::embaralhar(int *vet, int vetSize)
{
    for (int i = 0; i < vetSize; i++)
    {
        int r = rand() % vetSize;

        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}

void Construtivo::Adiciona_Basico(Solucao* solucao,Instancia* instancia)
{

    int j = 0;
    for (Maquina *i = instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
    {

        if (j == 0)
        {
            MaquinaSol *maquinaSol = new MaquinaSol();
            maquinaSol->min_Atual = 0;
            maquinaSol->CE=0;
            maquinaSol->id = i->get_id();
            maquinaSol->primeiro_processoSol = NULL;
            maquinaSol->ultimo_processoSol = NULL;
            maquinaSol->ant_maquinaSol = NULL;
            maquinaSol->prox_maquinaSol = NULL;
            solucao->primeira_maquina = maquinaSol;
            solucao->ultima_maquina = maquinaSol;
        }
        else
        {
            MaquinaSol *maquinaSol = new MaquinaSol();
            maquinaSol->min_Atual =0;
            maquinaSol->CE=0;
            maquinaSol->id = j;
            maquinaSol->primeiro_processoSol = NULL;
            maquinaSol->ultimo_processoSol = NULL;

            solucao->ultima_maquina->prox_maquinaSol = maquinaSol; // proxima maquina da maquina anterior passa a ser essa maquina
            maquinaSol->ant_maquinaSol = solucao->ultima_maquina;  // maquina anterior passa a ser a ultima maquina adicionada
            maquinaSol->prox_maquinaSol = NULL;

            solucao->ultima_maquina = maquinaSol;
        }

        j++;
    }
}

void Construtivo::Adiciona_Processo_Na_Maquina(int id_processo, int id_maquina,Solucao* solucao,Instancia* instancia)
{

    for (MaquinaSol *i = solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
    {
        if (i->id == id_maquina)
        {

            for (Processo *k = instancia->get_primeiro_Processo(); k != NULL; k = k->get_prox_Processo())
            {
                if (k->get_id() == id_processo)
                {
                    ProcessoSol *processo = new ProcessoSol();
                    processo->id = id_processo;
                    if (i->primeiro_processoSol == NULL)
                    {
                        i->primeiro_processoSol = processo;
                        i->ultimo_processoSol = processo;

                        processo->prox_processoSol = NULL;
                        processo->ant_processoSol = NULL;

                        solucao->custoEnergia = solucao->custoEnergia + k->custos_energia[i->id];
                        i->CE=i->CE + k->custos_energia[i->id];
                        i->min_Atual = (i->min_Atual + k->tempos_processamento[i->id]);
                    }
                    else
                    {
                        processo->prox_processoSol = NULL;
                        processo->ant_processoSol = i->ultimo_processoSol;
                        i->ultimo_processoSol->prox_processoSol = processo;

                        i->ultimo_processoSol = processo;

                        solucao->custoEnergia = solucao->custoEnergia + k->custos_energia[i->id];
                        i->CE=i->CE + k->custos_energia[i->id];
                        i->min_Atual = (i->min_Atual + k->tempos_processamento[i->id]);
                    }
                }
            }
            break;
        }
    }
}


