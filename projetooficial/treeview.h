#include <string.h>
#include <windows.h>

HTREEITEM serieH;
HTREEITEM itemT[3];
HTREEITEM itemE[3];

void treeview(HWND hwnd){
    HWND episodios_treeview = GetDlgItem(hwnd,EPISODIOS_TREEVIEW);

    TV_INSERTSTRUCT insert;
    ZeroMemory(&insert,sizeof(TV_INSERTSTRUCT));

    TreeView_DeleteAllItems(episodios_treeview);

    insert.hParent = TVI_ROOT;

    insert.hInsertAfter = TVI_LAST;
    insert.item.mask = TVIF_TEXT;

    insert.item.pszText = nomeselecionado;
    serieH = TreeView_InsertItem(episodios_treeview,&insert);

    for (int contador = 0; contador < serie[selecionadop].quantidadeTemporadas; contador++){
        HTREEITEM hItem = TreeView_GetRoot(episodios_treeview);
        TreeView_SetItemState(episodios_treeview,hItem, TVIS_EXPANDED, TVIS_EXPANDED);

        insert.hParent = serieH;
        insert.hInsertAfter = TVI_LAST;
        insert.item.pszText = treeviewTp[contador];
        itemT[contador] = TreeView_InsertItem(episodios_treeview,&insert);


        insert.hParent = itemT[contador];
        insert.hInsertAfter = TVI_LAST;
        insert.item.pszText = seriestring.quantidadeEpTemporada[contador];
        printf("%s - teste\n",seriestring.quantidadeEpTemporada[contador]);
        itemE[contador] = TreeView_InsertItem(episodios_treeview,&insert);


    }
}
