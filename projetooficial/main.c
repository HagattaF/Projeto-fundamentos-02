#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "resource.h"
#include "tab.h"
#include "comboboxseries.h"
#include "base.h"
#include "treeview.h"
#include "historico.h"

#define WM_MY_CUSTOM_MESSAGE (WM_USER + 1)

int auxiliar = 0;

//janela parte criativa maratonar
BOOL CALLBACK maratonar(HWND hwnd,UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){
        case WM_INITDIALOG:{ // iniciar janela
            SetWindowText(hwnd, "Series para Maratonar");
            serieMaisepisodios(hwnd);
        }
        break;
        return TRUE;
        case WM_COMMAND:{
        }
        break;
        return TRUE;
        case WM_CLOSE:{//fechar janela
            EndDialog(hwnd,0);
        }
        break;


    }
    return FALSE;
}

//janela parte criativa
BOOL CALLBACK generosmais(HWND hwnd,UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){
        case WM_INITDIALOG:{//iniciar janela
            SetWindowText(hwnd, "Generos Mais Assistidos");
            generos_mais_assistidos(hwnd);
        }
        break;
        return TRUE;
        case WM_COMMAND:{
        }
        break;
        return TRUE;
        case WM_CLOSE:{//fechar janela
            EndDialog(hwnd,0);
        }
        break;


    }
    return FALSE;
}

//janela para assistir
BOOL CALLBACK editarhistorico(HWND hwnd,UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){
        case WM_INITDIALOG:{//iniciar janela

        }
        break;
        return TRUE;
        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case ASSISTIR_1:{//assistir 1 episodio
                     for (int contador = 0; contador < tamanhoHistorico;contador++){
                        if (strcmp(nomeselecionado,historico[contador].titulo) == 0){
                            cod = contador;
                        }
                    }
                    for (int contador = 0; contador < tamanhoDados;contador++){
                        if (strcmp(nomeselecionado,serie[contador].titulo) == 0){
                            maxtemp = serie[contador].quantidadeTemporadas;
                            maxepisodio = serie[contador].quantidadeEpTemporada[historico[cod].ultimatemporada - 1];
                        }
                    }
                    historico[cod].ultimoepisodio++;
                    if (historico[cod].ultimoepisodio > maxepisodio){
                        historico[cod].ultimoepisodio = 0;
                        historico[cod].ultimatemporada++;
                        if (historico[cod].ultimatemporada > maxtemp){
                            historico[cod].assistindo = 0;
                                printf("\nFUNCIONA\n");
                        }
                    }
                    printf("1 - %d\n",historico[cod].ultimoepisodio);
                }
                SendMessage(listbox_assistindo,LB_RESETCONTENT,0,0);
                preencherListboxAssistindo(hwnd,lParam);
                PostMessage(hwnd,WM_CLOSE,0,0);
                break;

                case CONFIRMARATUAL_HISTORICO:{ // assistir personalizado

                    for (int contador = 0; contador < tamanhoHistorico;contador++){
                        if (strcmp(nomeselecionado,historico[contador].titulo) == 0){
                            cod = contador;
                        }
                    }
                    for (int contador = 0; contador < tamanhoDados;contador++){
                        if (strcmp(nomeselecionado,serie[contador].titulo) == 0){
                            maxtemp = serie[contador].quantidadeTemporadas;
                            maxepisodio = serie[contador].quantidadeEpTemporada[historico[cod].ultimatemporada - 1];
                        }
                    }
                    char extrair[50];
                    GetDlgItemText(hwnd,TEMPORADAATUAL_EDITAR,extrair,10);
                    if (atoi(extrair) > maxtemp){
                        MessageBox(hwnd,"Valor nao permitido","Erro",MB_OK);
                        PostMessage(hwnd,WM_CLOSE,0,0);
                    }else{
                        historico[cod].ultimatemporada = atoi(extrair);
                    }
                    GetDlgItemText(hwnd,EPISODIOATUAL_EDITAR,extrair,10);
                    if(atoi(extrair) > maxepisodio){
                        MessageBox(hwnd,"Valor nao permitido","Erro",MB_OK);
                        PostMessage(hwnd,WM_CLOSE,0,0);
                    }else{
                        historico[cod].ultimoepisodio = atoi(extrair);
                    }
                    if (historico[cod].ultimatemporada == maxtemp && historico[cod].ultimoepisodio){
                        historico[cod].assistindo = 0;
                    }
                    MessageBox(hwnd,"Episodios foram assistidos","Adicionado",MB_OK);
                    SendMessage(listbox_assistindo,LB_RESETCONTENT,0,0);
                    preencherListboxAssistindo(hwnd,lParam);
                    PostMessage(hwnd,WM_CLOSE,0,0);
                }
                break;

        }
        break;
        return TRUE;
        case WM_CLOSE:{
            EndDialog(hwnd,0);
        }
        break;
        return TRUE;
    }
    return TRUE;
    }
    return FALSE;
}

//janela auxiliar para alterar episodios
BOOL CALLBACK NovoDialogo4(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg){
        case WM_INITDIALOG:{//iniciar janela
            auxiliar = 0;
            SetWindowText(hwnd, "Alterar Episodios");
            HWND auxiliar_label_alterar = GetDlgItem(hwnd,AUXILIAR_LABEL_ALTERAR);
            serie[selecionadop].quantidadeEpTemporada = (int*)malloc(serie[selecionadop].quantidadeTemporadas * sizeof(int));
            if (serie[selecionadop].quantidadeTemporadas == NULL){
                MessageBox(hwnd,"Não Inseriu a quantidade de temporadas!","Erro",MB_OK);
                PostMessage(hwnd,WM_CLOSE,0,0);
            }else{
                HWND auxiliar_label = GetDlgItem(hwnd,AUXILIAR_LABEL);
                for (int contador = 0; contador < serie[selecionadop].quantidadeTemporadas;contador++){
                    sprintf(nometemporadas[contador],"%d",contador + 1);
                    strcat(nometemporadas[contador],"° Temporada");
                }
                SendMessage(auxiliar_label_alterar,WM_SETTEXT,0,(LPARAM)nometemporadas[0]);
            }
            break;

        }
        return TRUE;

         case WM_COMMAND:{//comandos
            switch (LOWORD(wParam)){
                case IDOK_ALTERAR:{ 
                    HWND auxiliar_label_alterar = GetDlgItem(hwnd,AUXILIAR_LABEL_ALTERAR);
                    SendMessage(auxiliar_label_alterar,WM_SETTEXT,0,(LPARAM)nometemporadas[auxiliar + 1]);
                    HWND episodios_inserir_alterar = GetDlgItem(hwnd,EPISODIOS_INSERIR_ALTERAR);
                    char inserir_episodios[250];
                    GetDlgItemText(hwnd,EPISODIOS_INSERIR_ALTERAR,inserir_episodios,10);
                    serie[selecionadoAlterar].quantidadeEpTemporada[auxiliar] = atoi(inserir_episodios);
                    serie[selecionadoAlterar].episodiosSomados += serie[selecionadoAlterar].quantidadeEpTemporada[auxiliar];
                    if ((auxiliar + 1) == serie[selecionadoAlterar].quantidadeTemporadas){
                          PostMessage(hwnd,WM_CLOSE,0,0);
                    }
                    SetWindowText(episodios_inserir_alterar," ");
                    auxiliar++;
                    }

                }
                break;
            break;
        }
        return TRUE;
        case WM_CLOSE:{//fechar janela
            EndDialog(hwnd,0);
        }
        return TRUE;
    }
    return FALSE;
}

//janela auxiliar para inserir episodios
BOOL CALLBACK NovoDialogo3(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg){
        case WM_INITDIALOG://iniciar janela 
            auxiliar = 0;
            SetWindowText(hwnd, "Inserir Episodios");
            serie = (Serie*) realloc(serie, (tamanhoDados + 1)*sizeof(Serie));
            serie[tamanhoDados].quantidadeEpTemporada = (int*)malloc(serie[tamanhoDados].quantidadeTemporadas * sizeof(int));
            if (serie[tamanhoDados].quantidadeTemporadas == NULL){
                MessageBox(hwnd,"Não Inseriu a quantidade de temporadas!","Erro",MB_OK);
                PostMessage(hwnd,WM_CLOSE,0,0);
            }else{
                HWND auxiliar_label = GetDlgItem(hwnd,AUXILIAR_LABEL);
                for (int contador = 0; contador < serie[tamanhoDados].quantidadeTemporadas;contador++){
                    sprintf(nometemporadas[contador],"%d",contador + 1);
                    strcat(nometemporadas[contador],"° Temporada");
                }
                SendMessage(auxiliar_label,WM_SETTEXT,0,(LPARAM)nometemporadas[0]);
            }
            break;

        return TRUE;

        case WM_COMMAND:{
            switch (LOWORD(wParam)){
                case IDOK:{ // inserir episodio
                    HWND hwndDest = FindWindow(NULL, "Inserir Série");
                    HWND inserir_botao = GetDlgItem(hwnd,INSERIR_BOTAO);
                    HWND auxiliar_label = GetDlgItem(hwnd,AUXILIAR_LABEL);
                    SendMessage(auxiliar_label,WM_SETTEXT,0,(LPARAM)nometemporadas[auxiliar + 1]);
                    
                    HWND episodios_inserir = GetDlgItem(hwnd,EPISODIOS_INSERIR);
                    char inserir_episodios[250];
                    GetDlgItemText(hwnd,EPISODIOS_INSERIR,inserir_episodios,10);
                    serie[tamanhoDados].quantidadeEpTemporada[auxiliar] = atoi(inserir_episodios);
                    
                    serie[tamanhoDados].episodiosSomados += serie[tamanhoDados].quantidadeEpTemporada[auxiliar];
                    if ((auxiliar + 1) == serie[tamanhoDados].quantidadeTemporadas){

                          PostMessage(hwnd,WM_CLOSE,0,0);
                          SendMessage(hwndDest,WM_MY_CUSTOM_MESSAGE,0,0);
                    }
                    SetWindowText(episodios_inserir,"");
                    auxiliar++;
                    }

                }
                break;
            break;
        }

        return TRUE;
        case WM_CLOSE:{//fechar janela
            EndDialog(hwnd,0);
        }
        return TRUE;

    }
    return FALSE;
}

//janela inserir serie
BOOL CALLBACK NovoDialogo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg){
        case WM_INITDIALOG: // iniciar janela
            SetWindowText(hwnd, "Inserir Série");
            AdicionarGeneroComboBoxInserir(hwnd,lParam);
            HWND inserir_botao = GetDlgItem(hwnd,INSERIR_BOTAO);
            ShowWindow(inserir_botao,0);
            break;

        return TRUE;
                            
        case WM_MY_CUSTOM_MESSAGE:{ // comando personalizado para aparecer o botao inserir
            HWND inserir_botao = GetDlgItem(hwnd,INSERIR_BOTAO);
            ShowWindow(inserir_botao,5);
            break;
        }
        return TRUE;

        case WM_COMMAND:{
            switch (LOWORD(wParam)){
                case CONFIRMAR_BOTAO:{ // comando confirmar_botao
                    HWND temporadas_inserir = GetDlgItem(hwnd,TEMPORADAS_INSERIR);
                    char digitarTemporadas[20];
                    serie = (Serie*) realloc(serie, (tamanhoDados + 1)*sizeof(Serie));
                    serie[tamanhoDados].quantidadeEpTemporada = (int*)malloc(serie[tamanhoDados].quantidadeTemporadas * sizeof(int));
                    GetDlgItemText(hwnd,TEMPORADAS_INSERIR,digitarTemporadas,32);
                    serie[tamanhoDados].quantidadeTemporadas = atoi(digitarTemporadas);
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG3),NULL,(DLGPROC)NovoDialogo3);
                }

                break;

                case INSERIR_BOTAO:{// inserir serie
                    char extrair[50];
                    HWND genero_inserir = GetDlgItem(hwnd,GENERO_INSERIR);
                    HWND inserir_botao = GetDlgItem(hwnd,INSERIR_BOTAO);
                    serie[tamanhoDados].codigo = tamanhoDados + 1;
                    GetDlgItemText(hwnd,NOME_INSERIR,serie[tamanhoDados].titulo,50);
                    GetDlgItemText(hwnd,CLASSIFICACAO_INSERIR,extrair,50);
                    serie[tamanhoDados].classificacao = atoi(extrair);
                    GetDlgItemText(hwnd,PLATAFORMA_INSERIR,serie[tamanhoDados].plataforma,50);
                    GetDlgItemText(hwnd,DURACAO_INSERIR,extrair,50);
                    serie[tamanhoDados].duracaoMediaEp = atoi(extrair);
                    int genero = SendMessage(genero_inserir, CB_GETCURSEL, 0, 1);
                    generosSelecionar(genero);
                    //MessageBox(hwnd,"Serie Inserida com Sucesso","Sucesso",MB_OK);
                    tamanhoDados++;
                    serie = (Serie*)realloc(serie,tamanhoDados * sizeof(Serie));
                    printf("\n%d\n",tamanhoDados);
                    printf("%d\n",serie[tamanhoDados - 1].classificacao);
                    printf("%s\n",serie[tamanhoDados - 1].genero);
                    printf("%d\n",serie[tamanhoDados - 1].codigo);
                    printf("%s\n",serie[tamanhoDados - 1].plataforma);
                    printf("%s\n",serie[tamanhoDados - 1].titulo);
                    printf("%d\n",serie[tamanhoDados - 1].episodiosSomados);
                    //printf("%d\n",serie[tamanhoDados].);
                    MessageBox(hwnd,"Serie Inserida com Sucesso","Sucesso",MB_OK);
                    PostMessage(hwnd,WM_CLOSE,0,0);
                }
                break;

                case MB_OK:{ // nao precisa mais ta ae
                    //PostMessage(hwnd,WM_CLOSE,0,0);
                }
                break;

            }

        }
        return TRUE;

        case WM_CLOSE:{//fechar janela

            EndDialog(hwnd,0);

        }
        return TRUE;

    }
    return FALSE;
}

//janela de excluir series
BOOL CALLBACK NovoDialogo1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg){
        case WM_INITDIALOG: // iniciar janela
            SetWindowText(hwnd, "Excluir Série");
            mostrarListbox(hwnd,lParam);
            break;

        return TRUE;

        case WM_COMMAND:{
            switch (LOWORD(wParam)){
                case LISTBOX_EXCLUIR:{ // controle listbox
                    if (HIWORD(wParam) == LBN_SELCHANGE){
                        HWND listbox_excluir = GetDlgItem(hwnd,LISTBOX_EXCLUIR);
                        int selecionadoExcluir = SendMessage(listbox_excluir,LB_GETCURSEL,0,0);
                        
                        SendMessage(listbox_excluir, LB_GETTEXT, selecionadoExcluir, (LPARAM)nomeselecionado);
                        

                    }
                    break;
                }
                case BOTAO_EXCLUIR:{ // botao para excluir 
                    for (int contador = 0; contador < tamanhoDados; contador++){
                        if (strcmp(nomeselecionado,serie[contador].titulo) == 0){
                    
                            int indice = contador;
                            for (int contador2 = indice; contador2 < tamanhoDados -1; contador2++){
                                serie[contador2] = serie[contador2 + 1];
                                serie[contador2].codigo -= 1;
                            }
                            tamanhoDados--;
                            serie = (Serie*)realloc(serie,(tamanhoDados) * sizeof(Serie));
                            MessageBox(hwnd,"Serie Excluida com Sucesso","Sucesso",MB_OK);
                            PostMessage(hwnd,WM_CLOSE,0,0);
                        }
                    }
                }
                break;
                case BOTAO_PESQUISAR_EXCLUIR:{//botao que pesquisa na listbox
                    HWND listbox_excluir = GetDlgItem(hwnd,LISTBOX_EXCLUIR);
                    GetDlgItemText(hwnd,LABEL_EXCLUIR,pesquisartext,32);
                    Pesquisar(serie);
                    if (strcmp(encontrado,pesquisartext) == 0){
                        SendMessage(listbox_excluir,LB_RESETCONTENT,0,0);
                        SendMessage(listbox_excluir, LB_ADDSTRING, 0, (LPARAM)encontrado);
                    }else{
                        MessageBox(hwnd,"Não está na lista!","Erro",MB_OK);
                    }
                }
                break;
            }
            break;
        }

        return TRUE;
        case WM_CLOSE:{//fechar janela
            EndDialog(hwnd,0);
        }
        return TRUE;

    }
    return FALSE;
}

//janela alterar serie
BOOL CALLBACK NovoDialogo2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg){
        case WM_INITDIALOG: // iniciar janelas
            SetWindowText(hwnd, "Alterar Série");
            mostrarListbox(hwnd,lParam);
            HWND nome_alterar = GetDlgItem(hwnd,NOME_ALTERAR);
            HWND classificacao_alterar = GetDlgItem(hwnd,CLASSIFICACAO_ALTERAR);
            HWND plataforma_alterar = GetDlgItem(hwnd,PLATAFORMA_ALTERAR);
            HWND temporadas_alterar = GetDlgItem(hwnd,TEMPORADAS_ALTERAR);
            HWND duracao_alterar = GetDlgItem(hwnd,DURACAO_ALTERAR);
            AdicionarGeneroComboBoxAlterar(hwnd,lParam);
            break;

        return TRUE;

        case WM_COMMAND:{
            switch (LOWORD(wParam)){
                case LISTBOX_ALTERAR:{ // controle da listbox alterar
                    if (HIWORD(wParam) == LBN_SELCHANGE){
                        HWND nome_alterar = GetDlgItem(hwnd,NOME_ALTERAR);
                        HWND classificacao_alterar = GetDlgItem(hwnd,CLASSIFICACAO_ALTERAR);
                        HWND plataforma_alterar = GetDlgItem(hwnd,PLATAFORMA_ALTERAR);
                        HWND temporadas_alterar = GetDlgItem(hwnd,TEMPORADAS_ALTERAR);
                        HWND duracao_alterar = GetDlgItem(hwnd,DURACAO_ALTERAR);
                        HWND listbox_alterar = GetDlgItem(hwnd,LISTBOX_ALTERAR);
                        HWND genero_alterar = GetDlgItem(hwnd,GENERO_ALTERAR);
                        selecionadoAlterar = SendMessage(listbox_alterar,LB_GETCURSEL,0,0);
                        SendMessage(listbox_alterar, LB_GETTEXT, selecionadoAlterar,(LPARAM)nomeselecionado);
                        for (int contador = 0; contador < tamanhoDados;contador++){
                            if (strcmp(nomeselecionado,serie[contador].titulo) == 0){
                                converterString();
                                selecionadop = serie[contador].codigo - 1;
                                SendMessage(nome_alterar,WM_SETTEXT,0,(LPARAM)serie[contador].titulo);
                                SendMessage(plataforma_alterar,WM_SETTEXT,0,(LPARAM)serie[contador].plataforma);
                                SendMessage(classificacao_alterar,WM_SETTEXT,0,(LPARAM)seriestring.classificao);
                                sprintf(seriestring.quantidadeTemporadas,"%d",serie[contador].quantidadeTemporadas);
                                SendMessage(temporadas_alterar,WM_SETTEXT,0,(LPARAM)seriestring.quantidadeTemporadas);
                                SendMessage(duracao_alterar,WM_SETTEXT,0,(LPARAM)seriestring.duracaoMediaEp);
                                SendMessage(genero_alterar, CB_SETCURSEL, 0,(LPARAM)1);


                            }
                        }
                    }
                }
                break;//botao pesquisar da janela alterar
                case BOTAO_PESUISAR_ALTERAR:{
                    HWND listbox_alterar = GetDlgItem(hwnd,LISTBOX_ALTERAR);
                    GetDlgItemText(hwnd,LABEL_PESQUISAR,pesquisartext,32);
                    Pesquisar(serie);
                    if (strcmp(encontrado,pesquisartext) == 0){
                        SendMessage(listbox_alterar,LB_RESETCONTENT,0,0);
                        SendMessage(listbox_alterar, LB_ADDSTRING, 0, (LPARAM)encontrado);
                    }else{
                        MessageBox(hwnd,"Não está na lista!","Erro",MB_OK);
                    }

                }
                break;

                case CONFIRMAR_ALTERAR:{ //botao para confirmar a quantidade de temporadas
                    HWND temporadas_alterar = GetDlgItem(hwnd,TEMPORADAS_ALTERAR);
                    printf("FUNCIONA DESGRAcA\n");
                    char digitarTemporadas[20];
                    serie[selecionadoAlterar].quantidadeEpTemporada = (int*)malloc(serie[selecionadoAlterar].quantidadeTemporadas * sizeof(int));
                    GetDlgItemText(hwnd,TEMPORADAS_ALTERAR,digitarTemporadas,32);
                    serie[selecionadoAlterar].quantidadeTemporadas = atoi(digitarTemporadas);
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG5),NULL,(DLGPROC)NovoDialogo4);
                }
                break;
                case BOTAO_ALTERAR:{ // botao alterar
                    char extrair[50];
                    printf("\n%d\n",selecionadop);
                    HWND genero_alterar = GetDlgItem(hwnd,GENERO_ALTERAR);
                    HWND botao_alterar = GetDlgItem(hwnd,BOTAO_ALTERAR);
                    GetDlgItemText(hwnd,NOME_ALTERAR,serie[selecionadop].titulo,50);
                    GetDlgItemText(hwnd,CLASSIFICACAO_ALTERAR,extrair,50);
                    serie[selecionadop].classificacao = atoi(extrair);
                    GetDlgItemText(hwnd,PLATAFORMA_ALTERAR,serie[selecionadop].plataforma,50);
                    GetDlgItemText(hwnd,DURACAO_ALTERAR,extrair,50);
                    serie[selecionadop].duracaoMediaEp = atoi(extrair);
                    int genero = SendMessage(genero_alterar, CB_GETCURSEL, 0, 1);

                    generosAlterar(genero);
                    printf("%d\n",serie[selecionadop].classificacao);
                    printf("%s\n",serie[selecionadop].genero);
                    printf("%d\n",serie[selecionadop].codigo);
                    printf("%s\n",serie[selecionadop].plataforma);
                    printf("%s\n",serie[selecionadop].titulo);
                    printf("%d\n",serie[selecionadop].episodiosSomados);
                    MessageBox(hwnd,"Serie Alterada com Sucesso","Sucesso",MB_OK);
                    PostMessage(hwnd,WM_CLOSE,0,0);
                }
            }
            break;
        }
        return TRUE;
        case WM_CLOSE:{ // fechar janela
            EndDialog(hwnd,0);
        }
        return TRUE;

    }
    return FALSE;
}


// janela principal
BOOL CALLBACK DlgMain(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg){
        case WM_INITDIALOG:// iniciar dialogo
        {
            carregarDados();//carregar dados .bin series
            carregarhistorico();//carregar historico .bin
            if(existeDado == 0){
                carrega_CSV();// se nao carregar nem o historico nem o bin carregar o .csv
            }
            if (existeDado == 0 && existeHistorico == 0){
                MessageBox(hwnd,"BEM VINDO","BEM VINDO!",MB_OK);
            }


            SetWindowText(hwnd, "Streaming Control System - Basico");//definir nome da janela
            preencherListboxAssistindo(hwnd,lParam);
            SendMessage(listbox_assistindo,LB_RESETCONTENT,0,0);
            tabSeries(hwnd);//organizar o tab
            mostrarListbox(hwnd,lParam);// mostrar lista das series

            HWND titulo = GetDlgItem(hwnd,TITULO); //variavel do texto do titulo
            tabSeriesOcultar(hwnd);//ocultar a aba series
            AdicionarGeneroComboBoxSeries(hwnd,lParam);//adicionar os generos da combobox

            adicionarTab(hwnd);// adicionar os tabs
            tabAssistindo(hwnd);// colocar variaveis no widgets
            tabHistorico(hwnd); //colocar variaveis nos widgets
            tabAssistindoExibir(hwnd);//exibir a aba assistindo
            tabHistoricoOcultar(hwnd);//ocultar a aba historico
            tabSeriesOcultar(hwnd);//ocultar a aba series
            preencherListboxHistorico(hwnd,lParam);//preencher a listbox do historico

            //definir variavel fonte
            HFONT fonte_titulo = CreateFont(20,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS
                                            ,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Century Gothic");

            //colocar fontes
            SendMessage(titulo,WM_SETFONT,(WPARAM)fonte_titulo,TRUE);
            SendMessage(listbox_series, WM_SETFONT, (WPARAM)fonte_titulo, TRUE);
            SendMessage(exibirEpisodios, WM_SETFONT, (WPARAM)fonte_titulo, TRUE);
            SendMessage(hTab, WM_SETFONT, (WPARAM)fonte_titulo, TRUE);
            break;
        }

        return TRUE;

        case WM_CLOSE: // ao fechar a janela principal
        {
            salvar_dados(); // salvar dados
            salvarhistorico();//salvar historico
            EndDialog(hwnd,0);//fechar janela
        }
        return TRUE;

        case WM_NOTIFY: // comando notificar

        switch (((LPNMHDR)lParam)->code){
            case TCN_SELCHANGE:
                int tab_selecionado = TabCtrl_GetCurSel(hTab); // ler qual aba do tab esta aberta

                    switch(tab_selecionado){
                    case -1:
                        SendMessage(listbox_assistindo,LB_RESETCONTENT,0,0);
                        preencherListboxAssistindo(hwnd,lParam);
                        SendMessage(combobox_series, CB_SETCURSEL, 0,(LPARAM)"Todos");
                        tabSeriesOcultar(hwnd);//ocultar tab series
                        tabAssistindoExibir(hwnd);//exibir tab assistindo
                        tabHistoricoOcultar(hwnd);//ocultar tab historico
                        SendMessage(combobox_series, CB_SETCURSEL, 0,(LPARAM)"Todos");
                        break;
                    case 0:
                        SendMessage(listbox_assistindo,LB_RESETCONTENT,0,0);
                        preencherListboxAssistindo(hwnd,lParam);
                        SendMessage(combobox_series, CB_SETCURSEL, 0,(LPARAM)"Todos");
                        tabSeriesOcultar(hwnd);//ocultar tab series
                        tabHistoricoOcultar(hwnd); //ocultar tab historico
                        tabAssistindoExibir(hwnd);//exibir tab assistindo
                        break;
                    case 1:
                        SendMessage(combobox_series, CB_SETCURSEL, 0,(LPARAM)"Todos");
                        tabSeriesExibir(hwnd);//exibir tab series
                        tabAssistindoOcultar(hwnd);//ocultar tab historico
                        tabHistoricoOcultar(hwnd);//ocultar tab historico
                        break;
                    case 2:
                        SendMessage(listbox_historico,LB_RESETCONTENT,0,0);
                        preencherListboxHistorico(hwnd,lParam);
                        tabAssistindoOcultar(hwnd);//ocultar tab assistindo
                        tabSeriesOcultar(hwnd);//ocultar tab series
                        tabHistoricoExibir(hwnd);//exibir tab historico
                    }

        }
        break;


        case WM_COMMAND:
            switch (LOWORD(wParam)){
                case LISTBOX_SERIES:{
                    if (HIWORD(wParam)==LBN_SELCHANGE){
                        HWND escolha = GetDlgItem(hwnd,LISTBOX_SERIES);
                        HWND episodios_treeview = GetDlgItem(hwnd,EPISODIOS_TREEVIEW);

                        TreeView_DeleteAllItems(episodios_treeview);
                        selecionado = SendMessage(escolha,LB_GETCURSEL,0,0);

                        SendMessage(escolha, LB_GETTEXT, selecionado, (LPARAM)nomeselecionado);

                        for (int contador = 0; contador < tamanhoDados;contador++){
                            if (strcmp(nomeselecionado,serie[contador].titulo) == 0){
                                selecionadop = serie[contador].codigo - 1;
                                selecionadop2 = serie[contador].codigo - 1;
                                //printf("%d\n",selecionadop);
                                TreeView_DeleteAllItems(episodios_treeview);
                                limpartreeview();//limpar treeview
                                treeviewPreparar();
                                converterString();
                                SendMessage(nome,WM_SETTEXT,0,(LPARAM)serie[contador].titulo);
                                SendMessage(genero,WM_SETTEXT,0,(LPARAM)serie[contador].genero);
                                SendMessage(plataforma,WM_SETTEXT,0,(LPARAM)serie[contador].plataforma);
                                SendMessage(classificacao,WM_SETTEXT,0,(LPARAM)seriestring.classificao);
                                SendMessage(temporadas,WM_SETTEXT,0,(LPARAM)seriestring.quantidadeTemporadas);
                                SendMessage(duracao,WM_SETTEXT,0,(LPARAM)seriestring.duracaoMediaEp);
                                SendMessage(totalepi,WM_SETTEXT,0,(LPARAM)seriestring.episodiosSomados);

                                treeview(hwnd);
                                limpartreeview();

                            }
                        }
                    }
                    break;
                }
                break;
                case FILTRAR_COMBOBOX:{

                    if (HIWORD(wParam)== LBN_SELCHANGE){
                        combobox_series = GetDlgItem(hwnd,FILTRAR_COMBOBOX);
                        int selecionar_genero = SendMessage(combobox_series, CB_GETCURSEL, 0, 1);
                        SendMessage(combobox_series, CB_GETLBTEXT, selecionar_genero, (LPARAM)textcombobox);
                        if (selecionar_genero == 0){
                            SendMessage(listbox_series,LB_RESETCONTENT,0,0);
                            limpartreeview();
                            mostrarListbox(hwnd,lParam);
                        }else{
                            filtrarGenero(selecionar_genero);
                        }
                    }


                }
                break;

                case MENU_SERIES_INSERIR:{
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(DIALOG_INSERIR),NULL,(DLGPROC)NovoDialogo);
                    //return 0;
                }
                break;

                case PESQUISAR_BOTAO:{
                    HWND pesquisar_botao = GetDlgItem(hwnd,PESQUISAR_BOTAO);
                    GetDlgItemText(hwnd,PESQUISAR,pesquisartext,32);
                    printf ("%s",pesquisartext);
                    Pesquisar(serie);
                    if (strcmp(encontrado,pesquisartext) == 0){
                        SendMessage(listbox_series,LB_RESETCONTENT,0,0);
                        SendMessage(escolha, LB_ADDSTRING, 0, (LPARAM)encontrado);
                    }else{
                        MessageBox(hwnd,"Não está na lista!","Erro",MB_OK);
                    }

                }
                break;
                case MENU_SERIES_EXCLUIR:{
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG2),NULL,(DLGPROC)NovoDialogo1);
                    //return 0;
                }
                break;
                case MENU_SERIES_ALTERAR:{
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG4),NULL,(DLGPROC)NovoDialogo2);
                    //return 0;
                }
                break;
                case ASSISTIR_BOTAO:{
                    inserirHistorico();
                    SendMessage(listbox_assistindo,LB_RESETCONTENT,0,0);
                    MessageBox(hwnd,"Serie Inserida na aba assistindo","Inserido",MB_OK);

                }
                break;
                case LISTBOX_ASSISTINDO:{
                    if (HIWORD(wParam)==LBN_SELCHANGE){
                        HWND listbox_assistindo = GetDlgItem(hwnd,LISTBOX_ASSISTINDO);
                        selecionado = SendMessage(listbox_assistindo,LB_GETCURSEL,0,0);
                        SendMessage(listbox_assistindo, LB_GETTEXT, selecionado, (LPARAM)nomeselecionado);
                        for(int contador = 0;contador < tamanhoHistorico;contador++){
                            if (strcmp(nomeselecionado,historico[contador].titulo) == 0){
                                converterStringHistorico();
                                SendMessage(temporadaatual_text,WM_SETTEXT,0,(LPARAM)historicostring.ultimatemporada);
                                SendMessage(episodioatual_text,WM_SETTEXT,0,(LPARAM)historicostring.ultimoepisodio);
                            }
                        }

                    }

                }
                break;
                case ASSISTIR1EP:{
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG6),NULL,(DLGPROC)editarhistorico);

                }
                break;
                case FINALIZAR_BOTAO:{
                    for (int contador = 0; contador < tamanhoHistorico;contador++){
                        if (strcmp(nomeselecionado,historico[contador].titulo) == 0){
                            cod = contador;
                        }
                    }
                    for (int contador = 0;contador < tamanhoDados; contador++){
                        if (strcmp(nomeselecionado,serie[contador].titulo) == 0){
                            maxtemp = serie[contador].quantidadeTemporadas;
                            maxepisodio = serie[contador].quantidadeEpTemporada[historico[cod].ultimatemporada - 1];
                        }
                    }
                    historico[cod].ultimoepisodio = maxepisodio;
                    historico[cod].ultimatemporada = maxtemp;
                    historico[cod].assistindo = 0;
                    MessageBox(hwnd,"Serie Finalizada","Finalizada",MB_OK);
                    SendMessage(listbox_assistindo,LB_RESETCONTENT,0,0);

                }
                break;
                case LISTBOX_HISTORICO:{
                    if (HIWORD(wParam)==LBN_SELCHANGE){
                        HWND listbox_historico = GetDlgItem(hwnd,LISTBOX_HISTORICO);
                        selecionado = SendMessage(LISTBOX_HISTORICO,LB_GETCURSEL,0,0);
                        SendMessage(listbox_historico, LB_GETTEXT, selecionado, (LPARAM)nomeselecionado);
                        for(int contador = 0;contador < tamanhoHistorico;contador++){
                            if (strcmp(nomeselecionado,historico[contador].titulo) == 0){
                                if (historico[contador].assistindo == 0){
                                        SendMessage(historico_text,WM_SETTEXT,0,(LPARAM)"Finalizado");
                                    }
                                    if (historico[contador].assistindo == 1){
                                        SendMessage(historico_text,WM_SETTEXT,0,(LPARAM)"Assistindo");
                                    }
                                }
                            }
                        }
                    }

                break;
                case EXPORTAR_CSV:{
                    FILE* arquivo = fopen("dados.csv", "w");
                    if (arquivo == NULL) {
                        printf("Erro ao abrir o arquivo para exportar os dados.\n");
                        return;
                    }
                    // Escreve o cabeçalho do arquivo CSV
                    fprintf(arquivo, "Código,Título,Gênero,Classificação,Plataforma,Quantidade de Temporadas,Duração Média do Episódio\n");

                    // Escreve os dados de cada série no arquivo CSV
                    for (int i = 0; i < tamanhoDados; i++) {
                        fprintf(arquivo, "%d,%s,%s,%d,%s,%d,%d,", serie[i].codigo,
                                serie[i].titulo, serie[i].genero, serie[i].classificacao,
                                serie[i].plataforma, serie[i].quantidadeTemporadas, serie[i].duracaoMediaEp);
                        for (int j = 0; j < serie[i].quantidadeTemporadas;j++){
                            fprintf(arquivo,"%d ",serie[i].quantidadeEpTemporada[j]);
                        }
                        fprintf(arquivo,"\n");
                        }


                        fclose(arquivo);
                        MessageBox(hwnd,"Dados Exportados com Sucesso","Sucesso",MB_OK);
                        printf("Dados exportados com sucesso para o arquivo 'dados.csv'.\n");
                }
                break;
                case MENU_MARATONAR:{
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG7),NULL,(DLGPROC)maratonar);
                }
                break;
                case MENU_GENEROS_ASSISTIDOS:{
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG8),NULL,(DLGPROC)generosmais);
                }
                break;
                case PESQUISARHISTORICO_BOTAO:{
                    HWND pesquisarhistorico_botao = GetDlgItem(hwnd,PESQUISARHISTORICO_BOTAO);
                    GetDlgItemText(hwnd,PESQUISARHISTORICO,pesquisartext,32);
                    PesquisarHistorico(serie);
                    if (strcmp(encontrado,pesquisartext) == 0){
                        SendMessage(listbox_historico,LB_RESETCONTENT,0,0);
                        SendMessage(listbox_historico, LB_ADDSTRING, 0, (LPARAM)encontrado);
                    }else{
                        MessageBox(hwnd,"Não está na lista!","Erro",MB_OK);
                    }
                }
                break;
                case REMOVERHISTORICO_BOTAO:{
                    for (int contador = 0; contador < tamanhoHistorico; contador++){
                        if (strcmp(nomeselecionado,historico[contador].titulo) == 0){
                            int indice = contador;
                            for (int contador2 = indice; contador2 < tamanhoHistorico -1; contador2++){
                                historico[contador2] = historico[contador2 + 1];
                            }
                            tamanhoHistorico--;
                            MessageBox(hwnd,"Serie Excluida do historico com Sucesso","Sucesso",MB_OK);
                            SendMessage(listbox_historico,LB_RESETCONTENT,0,0);
                            preencherListboxHistorico(hwnd,lParam);
                            historico = (Historico*)realloc(historico,(tamanhoHistorico) * sizeof(Historico));
                        }
                    }
                }
                break;
            return TRUE;
        }
        break;

        return TRUE;
        break;
    }
    return FALSE;
}


// como a base da biblioteca windows.h não pode ter int main() entao WinMain é o main da interface grafica
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,INT nShowCmd){
    hInst = hInstance;//definir instancia da janela
    setlocale(LC_ALL, "Portuguese"); // definir janela em português
    InitCommonControls();//definir controles
    DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),NULL,(DLGPROC)DlgMain);//chamar primeiro dialogo
    return 0;
}


