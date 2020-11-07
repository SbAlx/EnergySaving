#include "DataHierarhy.h"

void DataHierarhy::Set(const HWND& hwndParent, const HINSTANCE& hInst)
{
    RECT rcClient;
    GetClientRect(hwndParent,&rcClient);
    this->hwndTreeview = CreateWindowEx(0,
                                        WC_TREEVIEW,
                                        TEXT("Tree View"),
                                        Style,
                                        0,
                                        0,
                                        rcClient.right,
                                        rcClient.bottom,
                                        hwndParent,
                                        NULL,
                                        hInst,
                                        NULL);

    /* Создание списка изображений */
    himl = ImageList_Create(16,16,ILC_COLOR32,22,0);

    /* Получение описателя битового образа */
    hbmp = LoadBitmap(hInst, tagNameImageRes.c_str());

    /* Формирование индексов изображений */
    //BMP.reserve(CountBitmapImage);
    BMP.insert(BMP.begin(),CountBitmapImage,0);
    BMP[0]=ImageList_Add(himl, hbmp, (HBITMAP)NULL);
    std::iota(BMP.begin()+1,BMP.end(),1);//генерирование последовательности

    //Ассоциация списка изображений с элементом управления tree view
    TreeView_SetImageList(hwndTreeview, himl, TVSIL_NORMAL);

    //TreeViewInertItem(ItemNameListBox[0], TVI_ROOT,BMP[0],BMP[0]);
    DeployStruct();

    #ifdef DEBUG
    printf("BMP:\n");
    for(int i=0;i<BMP.size();i++)
    {
        printf("%d\n",BMP[i]);
    }
    #endif // DEBUG

    //Очистка
    DeleteObject(hbmp);
}

void DataHierarhy::DeployStruct()
{
    /* Заполнение ListBox */
    HTREEITEM hRoot;
    hRoot = TreeViewInertItem(  ItemNameListBox[Node::COMPANY],
                                TVI_ROOT,
                                BMP[Node::COMPANY],
                                BMP[Node::COMPANY],
                                Node::COMPANY);

    HTREEITEM htiBranch = TreeViewInertItem(  ItemNameListBox[Node::BRANCH],
                        hRoot,
                        BMP[Node::BRANCH],
                        BMP[Node::BRANCH],
                        Node::BRANCH);

    TreeViewInertItem(  ItemNameListBox[Node::CLASSOBJ],
                        htiBranch,
                        BMP[Node::CLASSOBJ],
                        BMP[Node::CLASSOBJ],
                        Node::CLASSOBJ);

    TreeViewInertItem(  ItemNameListBox[Node::LOCALDEPT],
                        htiBranch,
                        BMP[Node::LOCALDEPT],
                        BMP[Node::LOCALDEPT],
                        Node::LOCALDEPT);

    TreeViewInertItem(  ItemNameListBox[Node::DEPART],
                        hRoot,
                        BMP[Node::DEPART],
                        BMP[Node::DEPART],
                        Node::DEPART);

    HTREEITEM htiDocs = TreeViewInertItem(  ItemNameListBox[Node::DOCS],
                        hRoot,
                        BMP[Node::DOCS],
                        BMP[Node::DOCS],
                        Node::DOCS);

    TreeViewInertItem(  ItemNameListBox[Node::ORDERS],
                        htiDocs,
                        BMP[Node::ORDERS],
                        BMP[Node::ORDERS],
                        Node::ORDERS);

    TreeViewInertItem(  ItemNameListBox[Node::GUIDLINES],
                        htiDocs,
                        BMP[Node::GUIDLINES],
                        BMP[Node::GUIDLINES],
                        Node::GUIDLINES);

    TreeViewInertItem(  ItemNameListBox[Node::EU],
                        hRoot,
                        BMP[Node::EU],
                        BMP[Node::EU],
                        Node::EU);

    TreeViewInertItem(  ItemNameListBox[Node::INITPAR],
                        hRoot,
                        BMP[Node::INITPAR],
                        BMP[Node::INITPAR],
                        Node::INITPAR);

    TreeViewInertItem(  ItemNameListBox[Node::CALCPAR],
                        hRoot,
                        BMP[Node::CALCPAR],
                        BMP[Node::CALCPAR],
                        Node::CALCPAR);

    TreeViewInertItem(  ItemNameListBox[Node::FORMULA],
                        hRoot,
                        BMP[Node::FORMULA],
                        BMP[Node::FORMULA],
                        Node::FORMULA);

    TreeViewInertItem(  ItemNameListBox[Node::TYPERES],
                        hRoot,
                        BMP[Node::TYPERES],
                        BMP[Node::TYPERES],
                        Node::TYPERES);

    TreeViewInertItem(  ItemNameListBox[Node::EVENTS],
                        hRoot,
                        BMP[Node::EVENTS],
                        BMP[Node::EVENTS],
                        Node::EVENTS);


}

HTREEITEM DataHierarhy::TreeViewInertItem(std::string text, const HTREEITEM& hParent, int image, int selimage, const Node& lparam)
{
    HIMAGELIST himl;  // handle to image list
    HBITMAP hbmp;     // handle to bitmap
    TVITEM tvi;
    TVINSERTSTRUCT tvins;
    HTREEITEM hti;

    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST;

    tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
    // Set the text of the item.
    tvi.pszText = const_cast<char*>(text.c_str());
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]);
    tvi.lParam = static_cast<LPARAM>(lparam);
    // Assume the item is not a parent item, so give it a
    // document image.
    tvi.iImage = image;
    tvi.iSelectedImage = selimage;
    tvins.item = tvi;
    tvins.hInsertAfter = TVI_LAST;
    tvins.hParent = hParent;

    hPrev = (HTREEITEM)SendMessage(hwndTreeview, TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);

    if (hPrev == NULL)
        return NULL;

    return hPrev;
}

const HWND& DataHierarhy::GetHWND()
{
    return this->hwndTreeview;
}

void GetParentX(const HWND& hwnd,HTREEITEM hti)
{
    HTREEITEM h = TreeView_GetParent(hwnd,hti);
    if(h)
    {
        MessageBox(hwnd,"!hti","1",NULL);
        char szBuffer[25] = "";
        TVITEMEX tvitem = {0};
        tvitem.hItem = h;
        tvitem.mask = TVIF_TEXT|TVIF_PARAM;
        tvitem.pszText = szBuffer;
        tvitem.cchTextMax = 25;
        TreeView_GetItem(hwnd, &tvitem);
        std::string str = "lParam = ";
        str+=std::to_string(tvitem.lParam);
        printf("lparam = %d",tvitem.lParam);
        //MessageBox(hwnd, str.c_str(), "", 0);
        //GetParentX(Hierarhy.GetHWND(),tvitem.hItem);
    }
}
