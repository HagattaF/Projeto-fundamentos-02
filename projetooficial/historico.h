#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct{
    int codigo;
    int assistindo;
    char titulo[50];
    int ultimatemporada;
    int ultimoepisodio;
}Historico;

typedef struct{
    char ultimatemporada[50];
    char ultimoepisodio[50];
}HistoricoString;

HistoricoString historicostring;
Historico* historico;

int tamanhoHistorico = 0;
int contar = 1;

int existeHistorico = 1;

bool carregarhistorico(){
    FILE* arquivo_historico = fopen("historicos.bin","rb");
    if (arquivo_historico == NULL) {
        printf("Arquivo de historico nao encontrado. Os dados serao iniciados do zero.\n");
        existeHistorico = 0;
        return false;
    }
    fread(&tamanhoHistorico,sizeof(int),1,arquivo_historico);

    historico = (Historico*)malloc(tamanhoHistorico * sizeof(Historico));

    for (int contador = 0; contador < tamanhoHistorico;contador++){
        fread(&historico[contador],sizeof(Historico),1,arquivo_historico);
        printf("%s\n",historico[contador].titulo);
    }
    fclose(arquivo_historico);
    printf("Dados Carregados:\n");
    return true;
}

bool salvarhistorico(){
    FILE* arquivo_historicos = fopen("historicos.bin", "wb");
    if (arquivo_historicos == NULL) {
        printf("Erro ao abrir o arquivo de históricos.\n");
        return false;
    }

    fwrite(&tamanhoHistorico, sizeof(int), 1, arquivo_historicos); // Grava o número de históricos
    printf("%d - ?",tamanhoHistorico);

    for (int i = 0; i < tamanhoHistorico; i++) {
        fwrite(&historico[i], sizeof(Historico), 1, arquivo_historicos); // Grava cada histórico
    }

    fclose(arquivo_historicos);

    return true;
}

void inserirHistorico(){
    historico = (Historico*)realloc(historico,(tamanhoHistorico + 2) * sizeof(Historico));
    //printf("Contar %d\n ",contar);
    historico[tamanhoHistorico].codigo = serie[selecionadop].codigo;
    historico[tamanhoHistorico].assistindo = 1;
    historico[tamanhoHistorico].ultimatemporada = 1;
    historico[tamanhoHistorico].ultimoepisodio = 1;
    strcpy(historico[tamanhoHistorico].titulo,nomeselecionado);
    printf ("%s\n",historico[tamanhoHistorico].titulo);
    tamanhoHistorico++;
    contar++;
    //printf("tamanho : %d\n",tamanhoHistorico);
    return;
}

void preencherListboxAssistindo(HWND hwnd, LPARAM lParam){
    //HWND listbox_assistindo = GetDlgItem(hwnd,LISTBOX_ASSISTINDO);
    for (int contador = 0; contador < tamanhoHistorico;contador++){
        if (historico[contador].assistindo == 1){
            SendMessage(listbox_assistindo, LB_ADDSTRING, 0, (LPARAM)historico[contador].titulo);
            printf("%s\n",historico[contador].titulo);
            printf("bora caraio");
        }
    }
    return;
}

void preencherListboxHistorico(HWND hwnd,LPARAM lParam){
    for (int contador = 0; contador < tamanhoHistorico;contador++){
        SendMessage(listbox_historico, LB_ADDSTRING, 0, (LPARAM)historico[contador].titulo);
    }
    return;
}

void converterStringHistorico(){
    sprintf(historicostring.ultimatemporada,"%d",historico[selecionado].ultimatemporada);
    strcat(historicostring.ultimatemporada,"° Temporada");
    sprintf(historicostring.ultimoepisodio,"%d",historico[selecionado].ultimoepisodio);
    strcat(historicostring.ultimoepisodio," Episodio");
    return;
}



