#include <windows.h>
#include <stdio.h>
/*essa biblioteca e responsavel por pelo recurso de tabs do projeto*/
HINSTANCE hInst;
HWND hTab;

HWND escolha;
HWND pesquisar_box;
HWND filtrar_box;
HWND filtrar_combobox;
HWND listbox_series;
HWND series_box;
HWND informacoes_box;
HWND nome_box;
HWND temporadas_box;
HWND totalepi_box;
HWND plataforma_box;
HWND classificacao_box;
HWND genero_box;
HWND duracao_box;
HWND nome;
HWND temporadas;
HWND totalepi;
HWND plataforma;
HWND classificacao;
HWND genero;
HWND duracao;
HWND exibirEpisodios;
HWND assistir_botao;
HWND pesquisar_botao;
HWND pesquisar;

HWND assistindo_box;
HWND episodioatual_box;
HWND temporadaatual_box;
HWND episodioatual_text;
HWND temporadaatual_text;
HWND assistir1ep;
HWND finalizar_botao;
HWND listbox_assistindo;

HWND historico_box;
HWND pesquisarhistorico_box;
HWND historico_text;
HWND assistindo_historico_box;
HWND listbox_historico;
HWND removerhistorico_botao;
HWND pesquisarhistorico_botao;
HWND pesquisarhistorico;


TCITEM tie;

void adicionarTab(HWND hwnd){ // funcao p/ adicionar tab ( uso da biblioteca windowns.h)
    hTab = GetDlgItem(hwnd,TAB);
    tie.mask = TCIF_TEXT;
    tie.pszText = "Assistindo";
    TabCtrl_InsertItem(hTab,0,&tie);

    tie.pszText = "Séries";
    TabCtrl_InsertItem(hTab,1,&tie);

    tie.pszText = "Historico";
    TabCtrl_InsertItem(hTab,2,&tie);


    return;
}
void tabSeries(HWND hwnd){// funcao p/  tab series ( uso da biblioteca windowns.h)
    escolha = GetDlgItem(hwnd,LISTBOX_SERIES);
    pesquisar_box = GetDlgItem(hwnd, PESQUISAR_BOX);
    filtrar_box = GetDlgItem(hwnd, FILTRAR_BOX);
    filtrar_combobox = GetDlgItem(hwnd, FILTRAR_COMBOBOX);
    listbox_series = GetDlgItem(hwnd, LISTBOX_SERIES);
    series_box = GetDlgItem(hwnd, SERIES_BOX);
    informacoes_box = GetDlgItem(hwnd, INFORMACOES_BOX);
    nome_box = GetDlgItem(hwnd, NOME_BOX);
    temporadas_box = GetDlgItem(hwnd, TEMPORADAS_BOX);
    totalepi_box = GetDlgItem(hwnd, TOTALEPI_BOX);
    plataforma_box = GetDlgItem(hwnd, PLATAFORMA_BOX);
    classificacao_box = GetDlgItem(hwnd, CLASSIFICACAO_BOX);
    genero_box = GetDlgItem(hwnd, GENERO_BOX);
    duracao_box = GetDlgItem(hwnd, DURACAO_BOX);
    nome = GetDlgItem(hwnd, NOME);
    temporadas = GetDlgItem(hwnd, TEMPORADAS);
    totalepi = GetDlgItem(hwnd, TOTALEPI);
    plataforma = GetDlgItem(hwnd, PLATAFORMA);
    classificacao = GetDlgItem(hwnd, CLASSIFICACAO);
    genero = GetDlgItem(hwnd, GENERO);
    duracao = GetDlgItem(hwnd, DURACAO);
    exibirEpisodios = GetDlgItem(hwnd,EPISODIOS_TREEVIEW);
    assistir_botao = GetDlgItem(hwnd,ASSISTIR_BOTAO);
    pesquisar_botao = GetDlgItem(hwnd,PESQUISAR_BOTAO);
    pesquisar = GetDlgItem(hwnd,PESQUISAR);
    return;
}
void tabSeriesOcultar(HWND hwnd){/q// funcao p/ ocultar as tabs nao usadas naquele momento pelo usuario ( uso da biblioteca windowns.h)
    ShowWindow(pesquisar_box,0);
    ShowWindow(filtrar_box,0);
    ShowWindow(filtrar_combobox,0);
    ShowWindow(listbox_series,0);
    ShowWindow(series_box,0);
    ShowWindow(informacoes_box,0);
    ShowWindow(nome_box, 0);
    ShowWindow(temporadas_box, 0);
    ShowWindow(totalepi_box, 0);
    ShowWindow(plataforma_box, 0);
    ShowWindow(classificacao_box, 0);
    ShowWindow(genero_box, 0);
    ShowWindow(duracao_box, 0);
    ShowWindow(nome, 0);
    ShowWindow(temporadas, 0);
    ShowWindow(totalepi, 0);
    ShowWindow(plataforma, 0);
    ShowWindow(classificacao, 0);
    ShowWindow(genero, 0);
    ShowWindow(duracao, 0);
    ShowWindow(exibirEpisodios, 0);
    ShowWindow(assistir_botao, 0);
    ShowWindow(pesquisar_botao, 0);
    ShowWindow(pesquisar, 0);
    return;
}

void tabSeriesExibir(HWND hwnd){ // funcao p/ exibir tab series ( uso da biblioteca windowns.h)
    ShowWindow(pesquisar_box,5);
    ShowWindow(filtrar_box,5);
    ShowWindow(filtrar_combobox,5);
    ShowWindow(listbox_series,5);
    ShowWindow(series_box,5);
    ShowWindow(informacoes_box,5);
    ShowWindow(nome_box, 5);
    ShowWindow(temporadas_box, 5);
    ShowWindow(totalepi_box, 5);
    ShowWindow(plataforma_box, 5);
    ShowWindow(classificacao_box, 5);
    ShowWindow(genero_box, 5);
    ShowWindow(duracao_box, 5);
    ShowWindow(nome, 5);
    ShowWindow(temporadas, 5);
    ShowWindow(totalepi, 5);
    ShowWindow(plataforma, 5);
    ShowWindow(classificacao, 5);
    ShowWindow(genero, 5);
    ShowWindow(duracao, 5);
    ShowWindow(exibirEpisodios, 5);
    ShowWindow(assistir_botao, 5);
    ShowWindow(pesquisar_botao, 5);
    ShowWindow(pesquisar, 5);
    return;
}
void tabAssistindo(HWND hwnd){ // funcao p/  tab assistindo ( uso da biblioteca windowns.h)
    assistindo_box = GetDlgItem(hwnd,ASSISTINDO_BOX);
    episodioatual_box = GetDlgItem(hwnd,EPISODIOATUAL_BOX);
    temporadaatual_box = GetDlgItem(hwnd,TEMPORADAATUAL_BOX);
    episodioatual_text = GetDlgItem(hwnd,EPISODIOATUAL_TEXT);
    temporadaatual_text = GetDlgItem(hwnd,TEMPORADAATUAL_TEXT);
    assistir1ep = GetDlgItem(hwnd,ASSISTIR1EP);
    finalizar_botao = GetDlgItem(hwnd,FINALIZAR_BOTAO);
    listbox_assistindo = GetDlgItem(hwnd,LISTBOX_ASSISTINDO);
    return;
}

void tabAssistindoExibir(HWND hwnd){ // funcao p/ exibir tab assistindo ( uso da biblioteca windowns.h)
    ShowWindow(assistindo_box,5);
    ShowWindow(episodioatual_box,5);
    ShowWindow(temporadaatual_box,5);
    ShowWindow(episodioatual_text,5);
    ShowWindow(temporadaatual_text,5);
    ShowWindow(assistir1ep,5);
    ShowWindow(finalizar_botao,5);
    ShowWindow(listbox_assistindo,5);
    return;
}
void tabAssistindoOcultar(HWND hwnd){// funcao p/ ocultar tab assistindo ( uso da biblioteca windowns.h)
    ShowWindow(assistindo_box,0);
    ShowWindow(episodioatual_box,0);
    ShowWindow(temporadaatual_box,0);
    ShowWindow(episodioatual_text,0);
    ShowWindow(temporadaatual_text,0);
    ShowWindow(assistir1ep,0);
    ShowWindow(finalizar_botao,0);
    ShowWindow(listbox_assistindo,0);
    return;
}
void tabHistorico(HWND hwnd){// funcao p/  tab historico ( uso da biblioteca windowns.h)
    historico_box = GetDlgItem(hwnd,HISTORICO_BOX);
    pesquisarhistorico_box = GetDlgItem(hwnd,PESQUISARHISTORICO_BOX);
    historico_text = GetDlgItem(hwnd,HISTORICO_TEXT);
    assistindo_historico_box = GetDlgItem(hwnd,ASSISTINDO_HISTORICO_BOX);
    listbox_historico = GetDlgItem(hwnd,LISTBOX_HISTORICO);
    removerhistorico_botao = GetDlgItem(hwnd,REMOVERHISTORICO_BOTAO);
    pesquisarhistorico_botao = GetDlgItem(hwnd,PESQUISARHISTORICO_BOTAO);
    pesquisarhistorico = GetDlgItem(hwnd,PESQUISARHISTORICO);
    return;
}
void tabHistoricoExibir(HWND hwnd){// funcao p/ exibir tab historico ( uso da biblioteca windowns.h)
    ShowWindow(historico_box,5);
    ShowWindow(pesquisarhistorico_box,5);
    ShowWindow(historico_text,5);
    ShowWindow(assistindo_historico_box,5);
    ShowWindow(listbox_historico,5);
    ShowWindow(removerhistorico_botao,5);
    ShowWindow(pesquisarhistorico_botao,5);
    ShowWindow(pesquisarhistorico,5);
    return;
}
void tabHistoricoOcultar(HWND hwnd){ // funcao p/ ocultar tab historico ( uso da biblioteca windowns.h)
    ShowWindow(historico_box,0);
    ShowWindow(pesquisarhistorico_box,0);
    ShowWindow(historico_text,0);
    ShowWindow(assistindo_historico_box,0);
    ShowWindow(listbox_historico,0);
    ShowWindow(removerhistorico_botao,0);
    ShowWindow(pesquisarhistorico_botao,0);
    ShowWindow(pesquisarhistorico,0);
   return;
}
