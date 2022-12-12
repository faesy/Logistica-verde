
#include <iostream>
#include "Construtor.h"
#include "Maquina.h"
#include "Processo.h"

using namespace std;

Construtor::Construtor(CriadorInstancias *a)
{
    this->instancia = a;
    Solucao *b = new Solucao();
    this->solucao = b;
    Lista *c = new Lista();
    this->lista = c;
    Adiciona_Basico();
    Calcular_media_Consumo_por_tempo();
    Calcular_media_trabalho_por_tempo();
    Calcular_Custo_Minuto();

    int sequenciaProcessos[this->instancia->get_n()];
    for (int i = 0; i < this->instancia->get_n(); i++)
    {
        sequenciaProcessos[i] = i;
    }
    for (int i = 0; i < this->instancia->get_n() * 5; i++)
    {
        embaralhar(sequenciaProcessos, this->instancia->get_n());
    }

    for (int i = 0; i < this->instancia->get_n(); i++)
    {
        AdicionaPontos(sequenciaProcessos[i]);
        //RemovePontos(sequenciaProcessos[i]);

        int sorteado = this->lista->Sorteia_na_Lista();
        // cout<<"adicionando processo "<<sequenciaProcessos[i]<<" Na Maquina: "<<sorteado<<endl;
        this->Adiciona_Processo_Na_Maquina(sequenciaProcessos[i], sorteado);
        this->lista->Zera_Lista();
    }
    int makespam = 0;
    for (MaquinaSol *a = this->solucao->primeira_maquina; a != NULL; a = a->prox_maquinaSol)
    {
        if (a->min_Atual > makespam)
        {
            makespam = a->min_Atual;
        }
    }

    this->solucao->makespam = makespam;

    // Imprime();
}

void Construtor::Imprime()
{
    int custo = 0;
    for (MaquinaSol *a = this->solucao->primeira_maquina; a != NULL; a = a->prox_maquinaSol)
    {
        cout << "Maquina " << a->id << " :";
        for (ProcessoSol *b = a->primeiro_processoSol; b != NULL; b = b->prox_processoSol)
        {
            cout << b->id << " -> ";
            custo = custo + this->instancia->buscaProcesso(b->id)->custos_energia[a->id];
        }
        cout << "Tempo final: " << a->min_Atual << endl;
    }
    cout << "Makespam: " << solucao->makespam << endl;
    cout << "Custo Energetico: " << solucao->custoEnergia << endl;
    cout << "Custo Monetario: " << solucao->custoMonetario << endl;
}

void Construtor::RemovePontos(int id_Processo)
{
    Processo *processo;
    for (Processo *it = this->instancia->get_primeiro_Processo(); it != NULL; it = it->get_prox_Processo())
    {
        if (it->get_id() == id_Processo)
        {
            processo = it;
            break;
        }
    }
    cout<<"rem instancia->get_m() "<<instancia->get_m()<<endl;
    int tamanhoVetor = instancia->get_m() /* parametro_de_analise*/;
    int maquinas_mais_devagar[tamanhoVetor];
    int maquinas_mais_devagar2[tamanhoVetor];
    bool maquinas_mais_devagar_bool[instancia->get_m()];
    int maquinas_com_maior_makespam[tamanhoVetor];
    int maquinas_com_maior_makespam2[tamanhoVetor];
    bool maquinas_com_maior_makespam_bool[instancia->get_m()];
    int maquinas_com_maior_consumo[tamanhoVetor];
    int maquinas_com_maior_consumo2[tamanhoVetor];
    bool maquinas_com_maior_consumo_bool[instancia->get_m()];
    int maquinas_com_maior_gasto[tamanhoVetor];
    int maquinas_com_maior_gasto2[tamanhoVetor];
    bool maquinas_com_maior_gasto_bool[instancia->get_m()];

    for (int j = 0; j < tamanhoVetor; j++)
    {
        maquinas_mais_devagar[j] = 99999999;
        maquinas_com_maior_makespam[j] = 0;
        maquinas_com_maior_consumo[j] = 0;
        maquinas_com_maior_gasto[j] = 0;
    }

    for (int j = 0; j < instancia->get_m(); j++)
    {
        maquinas_mais_devagar_bool[j] = false;
        maquinas_com_maior_makespam_bool[j] = false;
        maquinas_com_maior_consumo_bool[j] = false;
        maquinas_com_maior_gasto_bool[j] = false;
    }

    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (Maquina *i = this->instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
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
        for (Maquina *i = this->instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
        {
            if (maquinas_com_maior_gasto_bool[contador] == false)
            {
                if (maquinas_com_maior_gasto[r] < processo->custos_energia[i->get_id()] * this->instancia->intervalos[(this->solucao->procura_maquina(i->get_id())->min_Atual) % 1440])
                {
                    maquinas_com_maior_gasto[r] = processo->custos_energia[i->get_id()] * this->instancia->intervalos[(this->solucao->procura_maquina(i->get_id())->min_Atual) % 1440];
                    maquinas_com_maior_gasto2[r] = i->get_id();
                    index_melhor_resultado = contador;
                }
            }
            contador++;
        }
        maquinas_com_maior_gasto_bool[index_melhor_resultado] = true;
    }

    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (Maquina *i = this->instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
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
        for (MaquinaSol *i = this->solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
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
        // cout<<endl;
        // this->lista->Imprime();
        // cout<<"Removendo "<<(this->instancia->get_m()-j)/2<<" copias da maquina "<<maquinas_mais_devagar2[j]<<" da lista"<<endl;
        //this->lista->Remove_na_Lista(maquinas_mais_devagar2[j], ((this->instancia->get_m()) - j) * (importanciaf1*0.25));
        // this->lista->Imprime();
        this->lista->Remove_na_Lista(maquinas_com_maior_makespam2[j], ((this->instancia->get_m()) - j) * (importanciaf1));
        this->lista->Remove_na_Lista(maquinas_com_maior_consumo2[j], ((this->instancia->get_m()) - j) * importanciaf2);
        this->lista->Remove_na_Lista(maquinas_com_maior_gasto2[j], ((this->instancia->get_m()) - j) * importanciaf3);
    }

    if(this->lista->primeiro_elemento==NULL){
        this->lista->Adicionar_na_Lista(rand()%this->instancia->get_m(),1);
    }
}

void Construtor::AdicionaPontos(int id_Processo)
{
    Processo *processo;
    for (Processo *it = this->instancia->get_primeiro_Processo(); it != NULL; it = it->get_prox_Processo())
    {
        if (it->get_id() == id_Processo)
        {
            processo = it;
            break;
        }
    }
    int tamanhoVetor = instancia->get_m() /** parametro_de_analise*/;
    int maquinas_mais_rapidas[tamanhoVetor];
    int maquinas_mais_rapidas2[tamanhoVetor];
    bool maquinas_mais_rapidas_bool[instancia->get_m()];
    int maquinas_com_menos_makespam[tamanhoVetor];
    int maquinas_com_menos_makespam2[tamanhoVetor];
    bool maquinas_com_menos_makespam_bool[instancia->get_m()];
    int maquinas_com_menos_consumo[tamanhoVetor];
    int maquinas_com_menos_consumo2[tamanhoVetor];
    bool maquinas_com_menos_consumo_bool[instancia->get_m()];
    int maquinas_com_menos_gasto[tamanhoVetor];
    int maquinas_com_menos_gasto2[tamanhoVetor];
    bool maquinas_com_menos_gasto_bool[instancia->get_m()];

    for (int j = 0; j < tamanhoVetor; j++)
    {
        maquinas_mais_rapidas[j] = 0;
        maquinas_com_menos_makespam[j] = 99999999;
        maquinas_com_menos_consumo[j] = 99999999;
        maquinas_com_menos_gasto[j] = 99999999;
    }

    for (int j = 0; j < instancia->get_m(); j++)
    {
        maquinas_mais_rapidas_bool[j] = false;
        maquinas_com_menos_makespam_bool[j] = false;
        maquinas_com_menos_consumo_bool[j] = false;
        maquinas_com_menos_gasto_bool[j] = false;
    }

    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (Maquina *i = this->instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
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
        for (Maquina *i = this->instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
        {

            if (maquinas_com_menos_gasto_bool[contador] == false)
            {

                if (maquinas_com_menos_gasto[r] > processo->custos_energia[i->get_id()] * this->instancia->intervalos[(this->solucao->procura_maquina(i->get_id())->min_Atual) % 1440])
                {

                    maquinas_com_menos_gasto[r] = processo->custos_energia[i->get_id()] * this->instancia->intervalos[(this->solucao->procura_maquina(i->get_id())->min_Atual) % 1440];
                    maquinas_com_menos_gasto2[r] = i->get_id();

                    index_melhor_resultado = contador;
                }
            }
            contador++;
        }

        maquinas_com_menos_gasto_bool[index_melhor_resultado] = true;
    }

    for (int r = 0; r < tamanhoVetor; r++)
    {
        int contador = 0;
        int index_melhor_resultado = -1;
        for (Maquina *i = this->instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
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
        for (MaquinaSol *i = this->solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
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
        //this->lista->Adicionar_na_Lista(maquinas_mais_rapidas2[j], ((this->instancia->get_m()) - j) * (importanciaf1*0.25));
        this->lista->Adicionar_na_Lista(maquinas_com_menos_makespam2[j], ((this->instancia->get_m()) - j) * (importanciaf1));
        this->lista->Adicionar_na_Lista(maquinas_com_menos_consumo2[j], ((this->instancia->get_m()) - j) * importanciaf2);
        this->lista->Adicionar_na_Lista(maquinas_com_menos_gasto2[j], ((this->instancia->get_m()) - j) * importanciaf3);
    }
}

void Construtor::embaralhar(int *vet, int vetSize)
{
    for (int i = 0; i < vetSize; i++)
    {
        int r = rand() % vetSize;

        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}

void Construtor::Adiciona_Basico()
{

    int j = 0;
    for (Maquina *i = this->instancia->get_primeira_maquina(); i != NULL; i = i->get_prox_Maquina())
    {

        if (j == 0)
        {
            MaquinaSol *maquinaSol = new MaquinaSol();
            maquinaSol->min_Atual = this->instancia->calcInicioDia();
            maquinaSol->id = i->get_id();
            maquinaSol->primeiro_processoSol = NULL;
            maquinaSol->ultimo_processoSol = NULL;
            maquinaSol->ant_maquinaSol = NULL;
            maquinaSol->prox_maquinaSol = NULL;
            this->solucao->primeira_maquina = maquinaSol;
            this->solucao->ultima_maquina = maquinaSol;
        }
        else
        {
            MaquinaSol *maquinaSol = new MaquinaSol();
            maquinaSol->min_Atual = this->instancia->calcInicioDia();
            maquinaSol->id = j;
            maquinaSol->primeiro_processoSol = NULL;
            maquinaSol->ultimo_processoSol = NULL;

            this->solucao->ultima_maquina->prox_maquinaSol = maquinaSol; // proxima maquina da maquina anterior passa a ser essa maquina
            maquinaSol->ant_maquinaSol = this->solucao->ultima_maquina;  // maquina anterior passa a ser a ultima maquina adicionada
            maquinaSol->prox_maquinaSol = NULL;

            this->solucao->ultima_maquina = maquinaSol;
        }

        j++;
    }
}

void Construtor::Adiciona_Processo_Na_Maquina(int id_processo, int id_maquina)
{

    for (MaquinaSol *i = this->solucao->primeira_maquina; i != NULL; i = i->prox_maquinaSol)
    {
        if (i->id == id_maquina)
        {

            for (Processo *k = this->instancia->get_primeiro_Processo(); k != NULL; k = k->get_prox_Processo())
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
                        float customedioEnergia = 0;
                        for (int f = 0; f < k->tempos_processamento[i->id]; f++)
                        {
                            customedioEnergia = customedioEnergia + instancia->intervalos[(i->min_Atual + f) % 1440];
                        }
                        customedioEnergia = customedioEnergia / (float)k->tempos_processamento[i->id];
                        solucao->custoMonetario = solucao->custoMonetario + k->custos_energia[i->id] * customedioEnergia;

                        i->min_Atual = (i->min_Atual + k->tempos_processamento[i->id]);
                    }
                    else
                    {
                        processo->prox_processoSol = NULL;
                        processo->ant_processoSol = i->ultimo_processoSol;
                        i->ultimo_processoSol->prox_processoSol = processo;

                        i->ultimo_processoSol = processo;

                        solucao->custoEnergia = solucao->custoEnergia + k->custos_energia[i->id];
                        float customedioEnergia = 0;
                        for (int f = 0; f < k->tempos_processamento[i->id]; f++)
                        {
                            customedioEnergia = customedioEnergia + instancia->intervalos[(i->min_Atual + f) % 1440];
                        }
                        customedioEnergia = customedioEnergia / (float)k->tempos_processamento[i->id];
                        solucao->custoMonetario = solucao->custoMonetario + k->custos_energia[i->id] * customedioEnergia;

                        i->min_Atual = (i->min_Atual + k->tempos_processamento[i->id]);
                    }
                }
            }

            break;
        }
    }
}

void Construtor::Calcular_media_Consumo_por_tempo()
{

    float soma1 = 0;

    for (Processo *processo = this->instancia->get_primeiro_Processo(); processo != NULL; processo = processo->get_prox_Processo())
    { // para todos processos

        for (int i = 0; i < this->instancia->get_m(); i++)
        { // em todas as maquinas
            soma1 = soma1 + (processo->custos_energia[i] / processo->tempos_processamento[i]);
        }

        this->media_Consumo_por_tempo = soma1 / this->instancia->get_n();
    }
}

void Construtor::Calcular_media_trabalho_por_tempo()
{
    float soma1 = 0;

    for (Processo *processo = this->instancia->get_primeiro_Processo(); processo != NULL; processo = processo->get_prox_Processo())
    { // para todos processos

        for (int i = 0; i < this->instancia->get_m(); i++)
        { // em todas as maquinas
            soma1 = soma1 + (processo->get_qt() / processo->tempos_processamento[i]);
        }

        this->media_trabalho_por_tempo = soma1 / this->instancia->get_n();
    }
}

void Construtor::Calcular_Custo_Minuto()
{
    float soma1 = 0;
    int k;

    this->instancia->calcInicioDia();

    for (int i = this->instancia->calcInicioDia(); i < (this->instancia->get_b() + this->instancia->calcInicioDia()); i++)
    { // para todos processos

        k = i % 1440;
        soma1 = soma1 + this->instancia->intervalos[k];
    }

    this->media_Custo_Minuto = soma1 / this->instancia->get_b();
}