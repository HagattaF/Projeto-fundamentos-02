#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

typedef struct{
    int codigo;
    char titulo[50];
    char genero[50];
    int classificacao;
    char plataforma[50];
    int quantidadeTemporadas;
    int* quantidadeEpTemporada;
    int duracaoMediaEp;
    int episodiosSomados;
}Serie;

typedef struct{
    char classificao[50];
    char quantidadeTemporadas[50];
    char quantidadeEpTemporada[400][50];
    char duracaoMediaEp[50];
    char episodiosSomados[50];
}SerieString;

HWND listbox_maratonar;

char nomeselecionado[50];
char nomeselecionado2[50];

char textcombobox[50];

int selecionado;
int selecionadop;
int selecionadop2;
int selecionadoAlterar;

char treeviewTp[400][50];
char pesquisartext[50];
char encontrado[50];

Serie* serie = NULL;
SerieString seriestring;

int maxepisodio;
int maxtemp;
int cod = 0;

int tamanhoDados;
int num = 1;

int existeDado = 1;

char nometemporadas[50][50];


bool carrega_CSV() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    serie = (Serie*)malloc(1*sizeof(Serie));
    FILE* arquivo = fopen("streaming_db.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo nao encontrado. Os dados serao iniciados do zero.\n");
        return false;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Extrair os dados separados por vírgula
        char* token = strtok(linha, ",");
        if (token == NULL) {
            printf("Erro ao processar linha do arquivo codigo.\n");
            continue;
        }
        serie[tamanhoDados].codigo = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha do arquivo titulo.\n");
            continue;
        }
        strcpy(serie[tamanhoDados].titulo, token);
        token = strtok(NULL, ",");
        if (token == NULL){
            printf("Erro ao processar linha do arquivo genero.\n");
            continue;
        }
        strcpy(serie[tamanhoDados].genero, token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha do arquivo classificacao.\n");
            continue;
        }
        serie[tamanhoDados].classificacao = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha do arquivo plataforma.\n");
            continue;
        }
        strcpy(serie[tamanhoDados].plataforma, token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha do arquivo duracao media.\n");
            continue;
        }
        serie[tamanhoDados].duracaoMediaEp = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha do arquivo quantidade temporada.\n");
            continue;
        }
        serie[tamanhoDados].quantidadeTemporadas = atoi(token);

        // Extrair os dados de quantidade de episódios separados por espaço
        token = strtok(NULL, " ");

        serie[tamanhoDados].quantidadeEpTemporada = (int*)malloc(serie[tamanhoDados].quantidadeTemporadas * sizeof(int));

        for (int h = 0; h < serie[tamanhoDados].quantidadeTemporadas; h++) {
            if (token == NULL) {
                printf("Erro ao processar linha do arquivo episodios.\n");
                continue;
            } else {
                serie[tamanhoDados].quantidadeEpTemporada[h] = atoi(token);
                token = strtok(NULL, " ");
            }
        }
        serie = (Serie*)realloc(serie,(num + 1) * sizeof(Serie));
        tamanhoDados++;
        num++;
    }

    for (int i = 0; i < tamanhoDados; i++) {
        for (int j = 0; j < serie[i].quantidadeTemporadas; j++) {
            serie[i].episodiosSomados += serie[i].quantidadeEpTemporada[j];
        }
    }

    fclose(arquivo);
    return true;
}

bool carregarDados(){
    FILE* arquivo_series = fopen("series.bin","rb");
    if (arquivo_series == NULL) {
        printf("Arquivo de series nao encontrado. Os dados serao iniciados do zero.\n");
        existeDado = 0;
        return false;
    }
    fread(&tamanhoDados,sizeof(int),1,arquivo_series);


    serie = (Serie*)malloc((tamanhoDados + 1)* sizeof(Serie));

    for (int contador = 0; contador < tamanhoDados;contador++){
        fread(&serie[contador],sizeof(Serie),1,arquivo_series);
        serie[contador].quantidadeEpTemporada = (int*)malloc(serie[contador].quantidadeTemporadas * sizeof(int));
        for (int i = 0; i < serie[contador].quantidadeTemporadas;i++){
            fread(&serie[contador].quantidadeEpTemporada[i],sizeof(int),1,arquivo_series);
        }
    }
    fclose(arquivo_series);
    return;
}

bool salvar_dados(){
    FILE* arquivo_series = fopen("series.bin", "wb");
    if (arquivo_series == NULL) {
        printf("Erro ao abrir o arquivo de series.\n");
        return false;
    }

    fwrite(&tamanhoDados, sizeof(int), 1, arquivo_series); // Grava o número de séries

    for (int i = 0; i < tamanhoDados; i++) {
        fwrite(&serie[i], sizeof(Serie), 1, arquivo_series); // Grava cada série
        for (int contador = 0; contador < serie[i].quantidadeTemporadas; contador++){
            fwrite(&serie[i].quantidadeEpTemporada[contador],sizeof(int),1,arquivo_series);
        }
    }

    fclose(arquivo_series);

    return true;
}

void treeviewPreparar(){
    limpartreeview();
     for (int contador = 0; contador < serie[selecionadop].quantidadeTemporadas;contador++){
                //printf("serie selecionado %d\n",serie[selecionadop].quantidadeTemporadas);
                sprintf(treeviewTp[contador],"%d",contador + 1);
                if (strcmp(treeviewTp[contador],"\0") != 0){
                    strcat(treeviewTp[contador],"° Temporada");
                    printf("%s\n",treeviewTp[contador]);
                }
            }
    return;
}

void converterString(){
    //seriestring.quantidadeEpTemporada[50] = (char*) malloc (1*sizeof(seriestring.quantidadeEpTemporada));
    for (int contador = 0; contador < tamanhoDados; contador++){
        if (strcasecmp(nomeselecionado,serie[contador].titulo) == 0){
            sprintf(seriestring.classificao,"%d",serie[contador].classificacao);
            sprintf(seriestring.quantidadeTemporadas,"%d",serie[contador].quantidadeTemporadas);
            strcat(seriestring.quantidadeTemporadas," Temporadas");
            //seriestring.quantidadeEpTemporada[50] = (char*) malloc (serie[contador].quantidadeTemporadas*sizeof(char));
            //printf("%d\n",serie[contador].quantidadeTemporadas * sizeof(seriestring.quantidadeEpTemporada));
            for (int i = 0; i < serie[contador].quantidadeTemporadas; i++){
                sprintf(seriestring.quantidadeEpTemporada[i],"%d",serie[contador].quantidadeEpTemporada[i]);
                strcat(seriestring.quantidadeEpTemporada[i]," Episodios");
            }

            sprintf(seriestring.duracaoMediaEp,"%d",serie[contador].duracaoMediaEp);
            setbuf(stdin,NULL);
            sprintf(seriestring.episodiosSomados,"%d",serie[contador].episodiosSomados);
            strcat(seriestring.episodiosSomados," Episodios");
        }
    }
    return;

}

void limpartreeview(){
    for (int contador = 0; contador < tamanhoDados; contador++){
        treeviewTp[contador][50] = "\0";
        seriestring.quantidadeEpTemporada[contador][50] = "\0";
    }
    return;
}

void mostrarListbox(HWND hwnd, LPARAM lParam) {
    HWND escolha = GetDlgItem(hwnd,LISTBOX_SERIES);
    HWND listbox_excluir  = GetDlgItem(hwnd,LISTBOX_EXCLUIR);
    HWND listbox_alterar  = GetDlgItem(hwnd,LISTBOX_ALTERAR);
    for (int contador = 0; contador < tamanhoDados; contador++) {
        SendMessage(escolha, LB_ADDSTRING, 0, (LPARAM)serie[contador].titulo);
        SendMessage(listbox_excluir, LB_ADDSTRING, 0, (LPARAM)serie[contador].titulo);
        SendMessage(listbox_alterar, LB_ADDSTRING, 0, (LPARAM)serie[contador].titulo);
    }
    return;
}
void filtrarGenero(int selecionar_genero){
    generos(selecionar_genero);
    SendMessage(listbox_series,LB_RESETCONTENT,0,0);
    for (int contador = 0; contador < tamanhoDados; contador++){
        if (strcmp(serie[contador].genero, textcombobox) == 0){
             SendMessage(escolha, LB_ADDSTRING, 0, (LPARAM)serie[contador].titulo);
        }
    }

    return;
}
void Pesquisar(){
    SendMessage(listbox_series,LB_RESETCONTENT,0,0);
    for (int contador = 0; contador < tamanhoDados;contador++){
        if (stricmp(serie[contador].titulo,pesquisartext) == 0){
            strcpy(encontrado,serie[contador].titulo);
        }
    }

}

void PesquisarHistorico(){
    SendMessage(listbox_historico,LB_RESETCONTENT,0,0);
    for (int contador = 0; contador < tamanhoDados;contador++){
        if (stricmp(serie[contador].titulo,pesquisartext) == 0){
            strcpy(encontrado,serie[contador].titulo);
        }
    }

}
void generos(int selecionar_genero) {
    switch (selecionar_genero) {
        case 1:
            strcpy(textcombobox, "Acao");
            break;
        case 2:
            strcpy(textcombobox, "Animacao");
            break;
        case 3:
            strcpy(textcombobox, "Aventura");
            break;
        case 4:
            strcpy(textcombobox, "Biografia");
            break;
        case 5:
            strcpy(textcombobox, "Comedia");
            break;
        case 6:
            strcpy(textcombobox, "Comedia Romantica");
            break;
        case 7:
            strcpy(textcombobox, "Crime");
            break;
        case 8:
            strcpy(textcombobox, "Documentario");
            break;
        case 9:
            strcpy(textcombobox, "Drama");
            break;
        case 10:
            strcpy(textcombobox, "Esporte");
            break;
        case 11:
            strcpy(textcombobox, "Familia");
            break;
        case 12:
            strcpy(textcombobox, "Fantasia");
            break;
        case 13:
            strcpy(textcombobox, "Faroeste");
            break;
        case 14:
            strcpy(textcombobox, "Ficcao");
            break;
        case 15:
            strcpy(textcombobox, "Ficcao Cientifica");
            break;
        case 16:
            strcpy(textcombobox, "Guerra");
            break;
        case 17:
            strcpy(textcombobox, "Historia");
            break;
        case 18:
            strcpy(textcombobox, "Horror");
            break;
        case 19:
            strcpy(textcombobox, "Humor Acido");
            break;
        case 20:
            strcpy(textcombobox, "Infantil");
            break;
        case 21:
            strcpy(textcombobox, "Misterio");
            break;
        case 22:
            strcpy(textcombobox, "Musical");
            break;
        case 23:
            strcpy(textcombobox, "Policial");
            break;
        case 24:
            strcpy(textcombobox, "Reality Show");
            break;
        case 25:
            strcpy(textcombobox, "Romance");
            break;
        case 26:
            strcpy(textcombobox, "Sci-Fi");
            break;
        case 27:
            strcpy(textcombobox, "Suspense");
            break;
        case 28:
            strcpy(textcombobox, "Terror");
            break;
        case 29:
            strcpy(textcombobox, "Thriller");
            break;
        case 30:
            strcpy(textcombobox, "Western");
            break;
        default:
            strcpy(textcombobox, "");
            break;
    }
}
void generosSelecionar(int genero) {
    switch (genero) {
        case 0:
            strcpy(serie[tamanhoDados].genero, "Acao");
            break;
        case 1:
            strcpy(serie[tamanhoDados].genero, "Animacao");
            break;
        case 2:
            strcpy(serie[tamanhoDados].genero, "Aventura");
            break;
        case 3:
            strcpy(serie[tamanhoDados].genero, "Biografia");
            break;
        case 4:
            strcpy(serie[tamanhoDados].genero, "Comedia");
            break;
        case 5:
            strcpy(serie[tamanhoDados].genero, "Comedia Romantica");
            break;
        case 6:
            strcpy(serie[tamanhoDados].genero, "Crime");
            break;
        case 7:
            strcpy(serie[tamanhoDados].genero, "Documentario");
            break;
        case 8:
            strcpy(serie[tamanhoDados].genero, "Drama");
            break;
        case 9:
            strcpy(serie[tamanhoDados].genero, "Esporte");
            break;
        case 10:
            strcpy(serie[tamanhoDados].genero, "Familia");
            break;
        case 11:
            strcpy(serie[tamanhoDados].genero, "Fantasia");
            break;
        case 12:
            strcpy(serie[tamanhoDados].genero, "Faroeste");
            break;
        case 13:
            strcpy(serie[tamanhoDados].genero, "Ficcao");
            break;
        case 14:
            strcpy(serie[tamanhoDados].genero, "Ficcao Cientifica");
            break;
        case 15:
            strcpy(serie[tamanhoDados].genero, "Guerra");
            break;
        case 16:
            strcpy(serie[tamanhoDados].genero, "Historia");
            break;
        case 17:
            strcpy(serie[tamanhoDados].genero, "Horror");
            break;
        case 18:
            strcpy(serie[tamanhoDados].genero, "Humor Acido");
            break;
        case 19:
            strcpy(serie[tamanhoDados].genero, "Infantil");
            break;
        case 20:
            strcpy(serie[tamanhoDados].genero, "Misterio");
            break;
        case 21:
            strcpy(serie[tamanhoDados].genero, "Musical");
            break;
        case 22:
            strcpy(serie[tamanhoDados].genero, "Policial");
            break;
        case 23:
            strcpy(serie[tamanhoDados].genero, "Reality Show");
            break;
        case 24:
            strcpy(serie[tamanhoDados].genero, "Romance");
            break;
        case 25:
            strcpy(serie[tamanhoDados].genero, "Sci-Fi");
            break;
        case 26:
            strcpy(serie[tamanhoDados].genero, "Suspense");
            break;
        case 27:
            strcpy(serie[tamanhoDados].genero, "Terror");
            break;
        case 28:
            strcpy(serie[tamanhoDados].genero, "Thriller");
            break;
        case 29:
            strcpy(serie[tamanhoDados].genero, "Western");
            break;
        default:
            strcpy(serie[tamanhoDados].genero, "");
            break;
    }
}
void generosAlterar(int genero) {
    switch (genero) {
        case 0:
            strcpy(serie[selecionadop].genero, "Acao");
            break;
        case 1:
            strcpy(serie[selecionadop].genero, "Animacao");
            break;
        case 2:
            strcpy(serie[selecionadop].genero, "Aventura");
            break;
        case 3:
            strcpy(serie[selecionadop].genero, "Biografia");
            break;
        case 4:
            strcpy(serie[selecionadop].genero, "Comedia");
            break;
        case 5:
            strcpy(serie[selecionadop].genero, "Comedia Romantica");
            break;
        case 6:
            strcpy(serie[selecionadop].genero, "Crime");
            break;
        case 7:
            strcpy(serie[selecionadop].genero, "Documentario");
            break;
        case 8:
            strcpy(serie[selecionadop].genero, "Drama");
            break;
        case 9:
            strcpy(serie[selecionadop].genero, "Esporte");
            break;
        case 10:
            strcpy(serie[selecionadop].genero, "Familia");
            break;
        case 11:
            strcpy(serie[selecionadop].genero, "Fantasia");
            break;
        case 12:
            strcpy(serie[selecionadop].genero, "Faroeste");
            break;
        case 13:
            strcpy(serie[selecionadop].genero, "Ficcao");
            break;
        case 14:
            strcpy(serie[selecionadop].genero, "Ficcao Cientifica");
            break;
        case 15:
            strcpy(serie[selecionadop].genero, "Guerra");
            break;
        case 16:
            strcpy(serie[selecionadop].genero, "Historia");
            break;
        case 17:
            strcpy(serie[selecionadop].genero, "Horror");
            break;
        case 18:
            strcpy(serie[selecionadop].genero, "Humor Acido");
            break;
        case 19:
            strcpy(serie[selecionadop].genero, "Infantil");
            break;
        case 20:
            strcpy(serie[selecionadop].genero, "Misterio");
            break;
        case 21:
            strcpy(serie[selecionadop].genero, "Musical");
            break;
        case 22:
            strcpy(serie[selecionadop].genero, "Policial");
            break;
        case 23:
            strcpy(serie[selecionadop].genero, "Reality Show");
            break;
        case 24:
            strcpy(serie[selecionadop].genero, "Romance");
            break;
        case 25:
            strcpy(serie[selecionadop].genero, "Sci-Fi");
            break;
        case 26:
            strcpy(serie[selecionadop].genero, "Suspense");
            break;
        case 27:
            strcpy(serie[selecionadop].genero, "Terror");
            break;
        case 28:
            strcpy(serie[selecionadop].genero, "Thriller");
            break;
        case 29:
            strcpy(serie[selecionadop].genero, "Western");
            break;
        default:
            strcpy(serie[selecionadop].genero, "");
            break;
    }
}

void serieMaisepisodios(HWND hwnd) {
    HWND listbox_maratonar = GetDlgItem(hwnd,LISTBOX_MARATONAR);
    int max_episodios[5] = {0}; // Vetor com os 5 maiores números de episódios
    char* series_mais_episodios[5] = {NULL}; // Vetor com os títulos das 5 séries com mais episódios

    for (int i = 0; i < tamanhoDados; i++) {
        int menor_episodio = max_episodios[0];
        int posicao_menor_episodio = 0;

        // Verifica se a série atual tem mais episódios do que alguma das séries já encontradas
        for (int j = 0; j < 5; j++) {
            if (serie[i].quantidadeTemporadas > max_episodios[j]) {
                menor_episodio = max_episodios[j];
                posicao_menor_episodio = j;
                break;
            }
        }

        // Se a série atual tem mais episódios do que alguma das séries já encontradas, atualiza o vetor de títulos
        if (serie[i].quantidadeTemporadas > menor_episodio) {
            for (int j = 4; j > posicao_menor_episodio; j--) {
                max_episodios[j] = max_episodios[j - 1];
                series_mais_episodios[j] = series_mais_episodios[j - 1];
            }
            max_episodios[posicao_menor_episodio] = serie[i].quantidadeTemporadas;
            series_mais_episodios[posicao_menor_episodio] = serie[i].titulo;
        }
    }

    printf("As 5 series com mais episodios sao:\n");
    for (int i = 0; i < 5; i++) {
        SendMessage(listbox_maratonar, LB_ADDSTRING, 0, (LPARAM)series_mais_episodios[i]);
    }
}

void generos_mais_assistidos(HWND hwnd) {
    HWND listbox_generosmais = GetDlgItem(hwnd,LISTBOX_GENEROSMAIS);
    // Cria um vetor auxiliar para contagem de gêneros
    int* contagemGeneros = (int*)calloc(tamanhoDados, sizeof(int));

    // Percorre todas as séries e incrementa a contagem de cada gênero
    for (int i = 0; i < tamanhoDados; i++) {
        contagemGeneros[i] = 0;
        for (int j = 0; j < tamanhoDados; j++) {
            if (strcmp(serie[i].genero, serie[j].genero) == 0) {
                contagemGeneros[i]++;
            }
        }
    }

    // Encontra o gênero mais assistido (maior contagem)
    int maxContagem = 0;
    for (int i = 0; i < tamanhoDados; i++) {
        if (contagemGeneros[i] > maxContagem) {
            maxContagem = contagemGeneros[i];
        }
    }

    // Imprime os gêneros mais assistidos (com contagem igual à maior contagem)
    printf("Gêneros mais assistidos:\n");
    for (int i = 0; i < tamanhoDados; i++) {
        if (contagemGeneros[i] == maxContagem){
            SendMessage(listbox_generosmais, LB_ADDSTRING, 0, (LPARAM)serie[i].titulo);
        }
    }

    // Libera a memória alocada
    free(contagemGeneros);
}



