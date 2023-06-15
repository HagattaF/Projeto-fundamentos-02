#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h" // Incluindo o arquivo de cabeçalho do histórico
#include <stdbool.h> // para usar o bool

typedef struct{
int codigo;
char Titulo[50];
char Genero[50];
int classificacao;
char plataforma[50];
int quantidadeTemporadas;
int* quantidadeEpTemporada;
float duracaoMediaEp; 


}Serie;
// Função para salvar os dados em um arquivo binário
bool salvar_dados(Serie* series, int numSeries, Historico* historicos, int numHistoricos) {
    FILE* arquivo_series = fopen("series.bin", "wb");
    if (arquivo_series == NULL) {
        printf("Erro ao abrir o arquivo de series.\n");
        return false;
    }

    fwrite(&numSeries, sizeof(int), 1, arquivo_series); // Grava o número de séries

    for (int i = 0; i < numSeries; i++) {
        fwrite(&series[i], sizeof(Serie), 1, arquivo_series); // Grava cada série
    }

    fclose(arquivo_series);
    printf("Dados das series salvos com sucesso.\n");

    FILE* arquivo_historicos = fopen("historicos.bin", "wb");
    if (arquivo_historicos == NULL) {
        printf("Erro ao abrir o arquivo de históricos.\n");
        return false;
    }

    fwrite(&numHistoricos, sizeof(int), 1, arquivo_historicos); // Grava o número de históricos

    for (int i = 0; i < numHistoricos; i++) {
        fwrite(&historicos[i], sizeof(Historico), 1, arquivo_historicos); // Grava cada histórico
    }

    fclose(arquivo_historicos);
    printf("Dados dos historicos salvos com sucesso.\n");

    return true;
}

// Função para carregar os dados de um arquivo binário
bool carregar_dados(Serie** series, int* numSeries, Historico** historicos, int* numHistoricos) {
    FILE* arquivo_series = fopen("series.bin", "rb");
    if (arquivo_series == NULL) {
        printf("Arquivo de series nao encontrado. Os dados serao iniciados do zero.\n");
        return false;
    }

    fread(numSeries, sizeof(int), 1, arquivo_series); // Lê o número de séries

    *series = (Serie*)malloc((*numSeries) * sizeof(Serie)); // Aloca memória para as séries

    for (int i = 0; i < *numSeries; i++) {
        fread(&(*series)[i], sizeof(Serie), 1, arquivo_series); // Lê cada série
    }

    fclose(arquivo_series);
    printf("Dados das series carregados do arquivo com sucesso.\n");

    FILE* arquivo_historicos = fopen("historicos.bin", "rb");
    if (arquivo_historicos == NULL) {
        printf("Arquivo de historicos nao encontrado. Os dados serao iniciados do zero.\n");
        return false;
   }}
// carregando aquivo csv
bool carrega_CSV(Serie** series, int* numSeries) {
    FILE* arquivo = fopen("streaming_db.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado. Os dados serão iniciados do zero.\n");
        return false;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Serie serie;

        char* token = strtok(linha, ",");
        if (token == NULL) {
            printf("Erro ao processar linha do arquivo.\n");
            continue;
        }
        serie.codigo = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha do arquivo.\n");
            continue;
        }
        strcpy(serie.Titulo, token);

        // Continuar a extração dos demais campos...

        // Adicionar a série ao vetor de séries
        (*series) = (Serie*)realloc((*series), (*numSeries + 1) * sizeof(Serie));
        (*series)[*numSeries] = serie;
        (*numSeries)++;
    }

    fclose(arquivo);
    printf("Dados carregados do arquivo com sucesso.\n");
    return true;
}

void lestring(char string[], int tamanho){
    setbuf(stdin, NULL);
    fgets(string, tamanho, stdin);
    string[strcspn(string, "\n")]='\0';
    } //letring


//função para inserir 
void Inserir(Serie* series,  int ultimovet) {
   Serie* serie = &series[ultimovet];
    printf("Insira o titulo da Serie: ");
    lestring(serie->Titulo, 50);

    printf("Insira o Genero da Serie: ");
    lestring(serie->Genero, 50);

    printf("Insira a classificacao do filme: ");
    scanf("%i", &serie->classificacao);
    setbuf(stdin, NULL);

    printf("Insira a plataforma da Serie: ");
    lestring(serie->plataforma, 50);

    printf("Quantidade de temporadas: ");
    scanf("%d", &serie->quantidadeTemporadas);
     setbuf(stdin, NULL);

    serie->quantidadeEpTemporada = (int*)(malloc(serie->quantidadeTemporadas * sizeof(int)));

    for (int h = 0; h < serie->quantidadeTemporadas; h++) {
        printf("Episodios da temporada [%d]: ", h);
        scanf("%d", &serie->quantidadeEpTemporada[h]);
    }

    printf("Insira a duracao media dos episodios: ");
    scanf("%f", &serie->duracaoMediaEp);
    setbuf(stdin,NULL);
}

//função listar
void listarSeries(Serie* series, int numSeries) {
    if (numSeries == 0) {
        printf("Não há séries cadastradas.\n");
        return;
    }

    printf("Séries cadastradas:\n");
    for (int i = 0; i < numSeries; i++) {
        Serie* serie = &series[i];
        printf("Codigo: %d\n", serie->codigo);
        printf("Titulo: %s\n", serie->Titulo);
        printf("Genero: %s\n", serie->Genero);
        printf("Classificacao: %d\n", serie->classificacao);
        printf("Plataforma: %s\n", serie->plataforma);
        printf("Quantidade de temporadas: %d\n", serie->quantidadeTemporadas);
        printf("Quantidade de episodios por temporada:\n");

        for (int h = 0; h < serie->quantidadeTemporadas; h++) {
            printf("Temporada: %d Episodios: %d\n", h + 1, serie->quantidadeEpTemporada[h]);
        }

        printf("Duracao media dos episodios: %1.2f\n", serie->duracaoMediaEp);
        printf("-----------------------------\n");

        setbuf(stdin,NULL);
    }
}//imprimir


//void Pesquisar(){
    

void buscar_series(Serie S[], int j) {
    setbuf(stdin,NULL);
    char buscas[50];
    printf("Digite o nome da serie: ");
    fgets(buscas, 50, stdin);
    buscas[strcspn(buscas, "\n")] = '\0';
    for(int i = 0; i < j; i++) {
        if(strcmp(S[i].Titulo, buscas) == 0) {
            printf("serie : %s\n", S[i].Titulo);
            
            
        }
    }
}// buscar_series
void buscar_series_cod(Serie S[], int j ) {
    int cod;
    printf("Insira o codigo da serie desejada: ");
    scanf("%d", &cod);
     for (int i = 0; i < j; i++){
        if(S[i].codigo == cod) {
            printf("serie : %s\n", S[i].Titulo);
           
        }
     }
    }//buscar_series_cod

//  alterar serie 
void alterar_serie(Serie S[], int j) {
    int cod;
    printf("Insira o código da série a ser alterada: ");
    scanf("%d", &cod);

    for (int i = 0; i < j; i++) {
        if (S[i].codigo == cod) {
            printf("Serie encontrada. Insira os novos dados:\n");

            printf("Insira o titulo da Serie:\n");
            lestring(S[i].Titulo, 50);

            printf("Insira o Genero da Serie: \n");
            lestring(S[i].Genero, 50);

            printf("Insira a classificacao da Serie: \n");
            scanf("%i", &S[i].classificacao);

            printf("Insira a plataforma da Serie:\n");
            lestring(S[i].plataforma, 50);

            printf("Quantidade de temporadas: ");
            scanf("%d", &S[i].quantidadeTemporadas);

            S[i].quantidadeEpTemporada = (int*)(realloc(S[i].quantidadeEpTemporada, S[i].quantidadeTemporadas * sizeof(int)));

            for (int h = 0; h < S[i].quantidadeTemporadas; h++) {
                printf("Episodios da temporada [%d]: ", h);
                scanf("%d", &S[i].quantidadeEpTemporada[h]);
            }

            printf("Insira a duracao media dos episodios: \n");
            scanf("%f", &S[i].duracaoMediaEp);

            printf("Serie alterada com sucesso.\n");
            return;
        }
    }

    printf("Serie não encontrada\n");
}    
// exclui serie 
void excluir_serie(Serie S[], int* j) {
    int cod;
    printf("Insira o codigo da serie a ser excluida: ");
    scanf("%d", &cod);

    for (int i = 0; i < *j; i++) {
        if (S[i].codigo == cod) { 
            for (int k = i; k < (*j - 1); k++) {
                S[k] = S[k + 1];
            }

            (*j)--;
            S = (Serie*)(realloc(S, (*j) * sizeof(Serie)));

            printf("Serie excluida com sucesso.\n");
            return;
        }
    }// for
}// excluir_serie


int main() {
    Serie* series = NULL;
    int codigo = 0;
    int numSeries = 0;
    int ultimovet = numSeries;
    int cod_bus;
    if (!carrega_CSV(&series, &numSeries)) {
        printf("Falha ao carregar dados do arquivo CSV.\n");
        return 1;
    }
    Historico* historicos = NULL;
    int numHistoricos = 0;
    // Carregar os dados do arquivo binário
    if (!carregar_dados(&series, &numSeries, &historicos, &numHistoricos)) {
        // Se falhar ao carregar os dados, inicialize-os manualmente
        series = (Serie*)malloc(10 * sizeof(Serie)); // Exemplo: alocar memória para 10 séries
        numSeries = 0;
        historicos = (Historico*)malloc(10 * sizeof(Historico)); // Exemplo: alocar memória para 10 históricos
        numHistoricos = 0;
    }

    int opcao;

    do {
        printf("Menu\n");
        printf("1 - Inserir serie\n");
        printf("2 - Listar series\n");
        printf("3 - Pesquisar serie\n");
        printf("4 - Alterar serie\n");
        printf("5 - Excluir serie\n");
        printf("6 - Inserir historico\n");
        printf("7 - Listar historicos\n");
        printf("8 - Pesquisar historico\n");
        printf("9 - Alterar historico\n");
        printf("10 - Excluir historico\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                
                printf("Inserindo serie:\n");
                
                series = (Serie*)(realloc(series, (numSeries + 1) * sizeof(Serie)));
                Inserir(series, numSeries);
                series[numSeries].codigo = codigo;
                ultimovet++;
                numSeries++;
                codigo++;
                break;
            case 2:
               printf("Listando series:\n");
               carrega_CSV(&series, &numSeries);
                listarSeries(series, numSeries);
                break;
            case 3:
                printf("Insira 1- buscar por titulo \n 2-buscar por codigo:\n");
                scanf("%d", &cod_bus);
                if(cod_bus==1){
                buscar_series(series, numSeries);}
                if(cod_bus==2){
                printf("Pesquisando serie por codigo:\n");
                buscar_series_cod(series, numSeries);}
                break;
            case 4:
               printf("Alterando serie:\n");
                alterar_serie(series, numSeries);
                break;
            case 5:
                printf("Excluindo serie:\n");
                excluir_serie(series, &numSeries);
                break;;
            case 6:
                printf("Inserindo histórico:\n");
                InserirHistorico(&historicos, &numHistoricos); // Chamada da função de inserir histórico
                break;
            case 7:
                printf("Listando históricos:\n");
                ListarHistoricos(historicos, numHistoricos); // Chamada da função de listar históricos
                break;
            case 8:
                printf("Pesquisando histórico:\n");
                PesquisarHistorico(historicos, numHistoricos,codigo);
                break;
            case 9:
                printf("Alterando histórico:\n");
                AlterarHistorico(historicos, numHistoricos);
                break;
            case 10:
                printf("Excluindo historico:\n");
                ExcluirHistorico(&historicos, &numHistoricos);
                break;
            case 0:
                if (salvar_dados(series, numSeries, historicos, numHistoricos)) {
                    printf("Dados salvos. O programa sera encerrado.\n");
                } 
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    // Liberação de memória e outras operações de limpeza
    free(series);

    return 0;
    }