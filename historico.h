#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct {
    int codigoSerie;
    int ultimaTemporadaAssistida;
    int ultimoEpisodioAssistido;
} Historico;

void InserirHistorico(Historico** historicos, int* numHistoricos) {
    int codigoSerie, ultimaTemporada, ultimoEpisodio;

    printf("Inserindo historico:\n");
    printf("Insira o codigo da serie: ");
    scanf("%d", &codigoSerie);
    printf("Insira a ultima temporada assistida: ");
    scanf("%d", &ultimaTemporada);
    printf("Insira o ultimo episodio assistido: ");
    scanf("%d", &ultimoEpisodio);

    *historicos = realloc(*historicos, (*numHistoricos + 1) * sizeof(Historico));
    Historico* novoHistorico = &((*historicos)[*numHistoricos]);

    novoHistorico->codigoSerie = codigoSerie;
    novoHistorico->ultimaTemporadaAssistida = ultimaTemporada;
    novoHistorico->ultimoEpisodioAssistido = ultimoEpisodio;

    (*numHistoricos)++;
}

void ListarHistoricos(Historico* historicos, int numHistoricos) {
    printf("Listando historicos:\n");
    for (int i = 0; i < numHistoricos; i++) {
        Historico* historico = &historicos[i];
        printf("Serie: Codigo %d - Ultima Temporada Assistida: %d - Ultimo Episodio Assistido: %d\n",
            historico->codigoSerie, historico->ultimaTemporadaAssistida, historico->ultimoEpisodioAssistido);
    }
}

int PesquisarHistorico(Historico* historicos, int numHistoricos, int codigoSerie) {
    for (int i = 0; i < numHistoricos; i++) {
        if (historicos[i].codigoSerie == codigoSerie) {
            return i; // Retorna o indice do historico encontrado
        }
    }
    return -1; // Retorna -1 se nao encontrar o historico
}

void AlterarHistorico(Historico* historicos, int numHistoricos) {
    int codigoSerie, ultimaTemporada, ultimoEpisodio;

    printf("Alterando historico:\n");
    printf("Insira o codigo da serie a ser alterada: ");
    scanf("%d", &codigoSerie);

    int indice = PesquisarHistorico(historicos, numHistoricos, codigoSerie);
    if (indice != -1) {
        printf("Insira a nova ultima temporada assistida: ");
        scanf("%d", &ultimaTemporada);
        printf("Insira o novo ultimo episodio assistido: ");
        scanf("%d", &ultimoEpisodio);

        historicos[indice].ultimaTemporadaAssistida = ultimaTemporada;
        historicos[indice].ultimoEpisodioAssistido = ultimoEpisodio;
        printf("Historico alterado com sucesso.\n");
    } else {
        printf("Historico nao encontrado.\n");
    }
}

void ExcluirHistorico(Historico** historicos, int* numHistoricos) {
    int codigoSerie;

    printf("Excluindo historico:\n");
    printf("Insira o codigo da serie a ser excluida: ");
    scanf("%d", &codigoSerie);

    int indice = PesquisarHistorico(*historicos, *numHistoricos, codigoSerie);
    if (indice != -1) {
        // Deslocar os historicos a partir do indice para sobrescrever o historico a ser excluido
        for (int i = indice; i < *numHistoricos - 1; i++) {
            (*historicos)[i] = (*historicos)[i + 1];
        }

        *historicos = realloc(*historicos, (*numHistoricos - 1) * sizeof(Historico));
        (*numHistoricos)--;
        printf("Historico excluido com sucesso.\n");
    } else {
        printf("Historico nao encontrado.\n");
    }
}


#endif