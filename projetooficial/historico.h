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
}Historico; // estrutura

typedef struct{
    char ultimatemporada[50];
    char ultimoepisodio[50];
}HistoricoString;// estrutura ep 

HistoricoString historicostring;
Historico* historico;

int tamanhoHistorico = 0;
int contar = 1;

int existeHistorico = 1;

bool carregarhistorico(){ // funcao responsavel por carregar os dados da parte historico no programa 
    FILE* arquivo_historico = fopen("historicos.bin","rb");// abre o arquivo
    if (arquivo_historico == NULL) {// exibe msg se o arquivo nao for encontrado
        printf("Arquivo de historico nao encontrado. Os dados serao iniciados do zero.\n");
        existeHistorico = 0;
        return false;
    }
    fread(&tamanhoHistorico,sizeof(int),1,arquivo_historico);// Lê o número do historico

    historico = (Historico*)malloc(tamanhoHistorico * sizeof(Historico));// Aloca memória para o historico

    for (int contador = 0; contador < tamanhoHistorico;contador++){
        fread(&historico[contador],sizeof(Historico),1,arquivo_historico);// Lê cada série
        printf("%s\n",historico[contador].titulo);
    }
    fclose(arquivo_historico);// fecha arquivo
    printf("Dados Carregados:\n");
    return true;
}

bool salvarhistorico(){  // funcao para salvar em binario 
    FILE* arquivo_historicos = fopen("historicos.bin", "wb"); // abre o arquivo
    if (arquivo_historicos == NULL) { // exibe msg se o arquivo nao for encontrado
        printf("Erro ao abrir o arquivo de históricos.\n");
        return false;
    }

    fwrite(&tamanhoHistorico, sizeof(int), 1, arquivo_historicos); // Grava o número de históricos
    

    for (int i = 0; i < tamanhoHistorico; i++) {
        fwrite(&historico[i], sizeof(Historico), 1, arquivo_historicos); // Grava cada histórico
    }

    fclose(arquivo_historicos); // fecha arquivo

    return true;
}

void inserirHistorico(){ //funcao para inserir 
    historico = (Historico*)realloc(historico,(tamanhoHistorico + 2) * sizeof(Historico)); // realoca espaço pra preencher um novo
    //printf("Contar %d\n ",contar);
    historico[tamanhoHistorico].codigo = serie[selecionadop].codigo;// preenchimento do historico
    historico[tamanhoHistorico].assistindo = 1;
    historico[tamanhoHistorico].ultimatemporada = 1;
    historico[tamanhoHistorico].ultimoepisodio = 1;
    strcpy(historico[tamanhoHistorico].titulo,nomeselecionado);
    printf ("%s\n",historico[tamanhoHistorico].titulo);
    tamanhoHistorico++;// adiciona 1 ao tamanho do vetor 
    contar++;// 
    
    return;
}

void preencherListboxAssistindo(HWND hwnd, LPARAM lParam){ // codigo para função grafica exibir o que foi assistido
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

void preencherListboxHistorico(HWND hwnd,LPARAM lParam){ // codigo para função grafica exibir o  historico
    for (int contador = 0; contador < tamanhoHistorico;contador++){
        SendMessage(listbox_historico, LB_ADDSTRING, 0, (LPARAM)historico[contador].titulo);
    }
    return;
}

void converterStringHistorico(){ // funcao para conversão de string
    sprintf(historicostring.ultimatemporada,"%d",historico[selecionado].ultimatemporada);
    strcat(historicostring.ultimatemporada,"° Temporada");
    sprintf(historicostring.ultimoepisodio,"%d",historico[selecionado].ultimoepisodio);
    strcat(historicostring.ultimoepisodio," Episodio");
    return;
}



