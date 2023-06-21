#include <windows.h>

HWND combobox_series;
HWND genero_inserir;
// combo box (generos)
void AdicionarGeneroComboBoxSeries(HWND hwnd,LPARAM lParam){
    combobox_series = GetDlgItem(hwnd,FILTRAR_COMBOBOX);
    SendMessage(combobox_series,CB_ADDSTRING,0,(LPARAM)"Todos");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Ação");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Animação");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Aventura");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Biografia");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Comédia");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Comédia Romântica");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Crime");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Documentário");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Drama");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Esporte");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Família");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Fantasia");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Faroeste");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Ficção");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Ficção Científica");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Guerra");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"História");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Horror");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Humor Ácido");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Infantil");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Mistério");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Musical");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Policial");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Reality Show");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Romance");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Sci-Fi");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Suspense");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Terror");
    SendMessage(combobox_series, CB_ADDSTRING, 0, (LPARAM)"Thriller");
    return;
}
void AdicionarGeneroComboBoxInserir(HWND hwnd,LPARAM lParam){
    genero_inserir = GetDlgItem(hwnd,GENERO_INSERIR);
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Ação");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Animação");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Aventura");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Biografia");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Comédia");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Comédia Romântica");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Crime");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Documentário");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Drama");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Esporte");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Família");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Fantasia");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Faroeste");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Ficção");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Ficção Científica");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Guerra");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"História");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Horror");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Humor Ácido");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Infantil");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Mistério");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Musical");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Policial");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Reality Show");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Romance");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Sci-Fi");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Suspense");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Terror");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Thriller");
    SendMessage(genero_inserir, CB_ADDSTRING, 0, (LPARAM)"Western");
}

void AdicionarGeneroComboBoxAlterar(HWND hwnd,LPARAM lParam){
    HWND genero_alterar = GetDlgItem(hwnd,GENERO_ALTERAR);
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Ação");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Animação");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Aventura");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Biografia");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Comédia");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Comédia Romântica");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Crime");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Documentário");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Drama");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Esporte");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Família");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Fantasia");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Faroeste");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Ficção");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Ficção Científica");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Guerra");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"História");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Horror");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Humor Ácido");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Infantil");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Mistério");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Musical");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Policial");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Reality Show");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Romance");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Sci-Fi");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Suspense");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Terror");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Thriller");
    SendMessage(genero_alterar, CB_ADDSTRING, 0, (LPARAM)"Western");
}


