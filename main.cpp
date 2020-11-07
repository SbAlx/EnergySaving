#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <commctrl.h>

#include "DataHierarhy.h"



class Confighierarhy
{
public:
    BOOL Init(HWND& hwndParent, HINSTANCE g_hInst);

private:
    HWND hwndTreeview;
    HTREEITEM TreeViewInsertItem(char* itemtext, const HTREEITEM& hParent, int image = 0, int selimage = 0);
};

BOOL Confighierarhy::Init(HWND& hwndParent, HINSTANCE hInst)
{
   RECT rcClient;

   InitCommonControls();
   GetClientRect(hwndParent,&rcClient);
   this->hwndTreeview = CreateWindowEx(0,
                                       WC_TREEVIEW,
                                       TEXT("Tree View"),
                                       WS_VISIBLE|WS_CHILD|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
                                       0,
                                       0,
                                       rcClient.right,
                                       rcClient.bottom,
                                       hwndParent,
                                       NULL,
                                       hInst,
                                       NULL);

}

HTREEITEM Confighierarhy::TreeViewInsertItem(char* itemtext, const HTREEITEM& hParent, int image, int selimage)
{
    HTREEITEM hPrevHTI;
    TVITEM tvi;
    TVINSERTSTRUCT tvins;

    //Set mask of settings item
    tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

    // Set the text of the item.
    tvi.pszText = itemtext;
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]);

    // Assume the item is not a parent item, so give it a
    // document image.
    //tvi.iImage = image;
    //tvi.iSelectedImage = selimage;

    tvins.item = tvi;
    tvins.hInsertAfter = TVI_LAST;
    tvins.hParent = hParent;

    hPrevHTI = (HTREEITEM)SendMessage(this->hwndTreeview, TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);

    if (hPrevHTI == NULL)
        return NULL;

    return hPrevHTI;
}

/*ID's images treeview item*/
enum enIMAGE {ENTRPRS,
              RQSTS,
              BRNCH,
              EMPL,
              TPE_OBJ,
              CEX,
              CEXSYSTEM,
              OBJCTS,
              OBJECTSSTM,
              RND_EMPT,
              RND_FILL,
              FLDDEPTS,
              DEPTS,
              DOCS,
              ORDR,
              GDLNS,
              EUS,
              PARAMS,
              CALCPARAMS,
              FORMULS,
              TPSRESRS,
              EVNTS} g_idImages;


int Bmp[25];
HWND CreateATreeView(HWND hwndParent);
HWND CreateATreeView2(HWND hwndParent);
HTREEITEM TreeViewInertItem(char* text, const HTREEITEM& hParent, int image, int selimage);


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
std::string szAppName = _T("Настройка данных");

HINSTANCE g_hInst;
 HWND hwndChild;
HWND g_hwndTreeview;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */

    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    g_hInst = hThisInstance;

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    wincl.lpszClassName = _T("CHILD_WINDOW");
    wincl.lpfnWndProc = ChildWindowProcedure;      /* This function is called by windows */

     /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           szAppName.c_str(),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           0,       /* Windows decides the position */
           0,       /* where the window ends up on the screen */
           GetSystemMetrics(SM_CXSCREEN),                 /* The programs width */
           GetSystemMetrics(SM_CYSCREEN),                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    InitCommonControls();

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rcClient;  // dimensions of client area
    HWND hwndTV;    // handle to tree-view control

    HIMAGELIST himl;  // handle to image list
    HBITMAP hbmp;     // handle to bitmap
    char* s[2];

    TVITEM tvi;
    TVINSERTSTRUCT tvins;
    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST;
    HTREEITEM hPrev2, hPrev3, hPrev4, hPrev5, hPrev6, hPrev7, hPrev8, hPrev9, hPrev10;
    HTREEITEM hPrevRootItem = NULL;
    HTREEITEM hPrevLev2Item = NULL;
    HTREEITEM hti;



    // Ensure that the common control DLL is loaded.
    InitCommonControls();

    static DataHierarhy& Hierarhy = DataHierarhy::instance();
    static HWND hwndClient;
    CLIENTCREATESTRUCT clientcreate;
    MDICREATESTRUCT mdicreate;
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        //clientcreate.hWindowMenu = hMenuInitWindow;
        clientcreate.idFirstChild = 100;
        hwndClient = CreateWindow("MDICLIENT",
                                  NULL,
                                  WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
                                  0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
                                  hwnd,
                                  (HMENU) 1,
                                  g_hInst,
                                  (LPSTR) &clientcreate);

        mdicreate.szClass = _T("CHILD_WINDOW");
        mdicreate.szTitle = "Hello";
        mdicreate.hOwner = g_hInst;
        mdicreate.x = CW_USEDEFAULT;
        mdicreate.y = CW_USEDEFAULT;
        mdicreate.cx = CW_USEDEFAULT;
        mdicreate.cy = CW_USEDEFAULT;
        mdicreate.style = 0;
        mdicreate.lParam = 0;
        hwndChild =(HWND) SendMessage(  hwndClient,
                                        WM_MDICREATE,
                                        0,
                                        (LPARAM)(LPMDICREATESTRUCT) &mdicreate);
        Hierarhy.Set(hwndChild, g_hInst);

        /*
        GetClientRect(hwndChild, &rcClient);
        //GetClientRect(hwnd,&rcClient);
        g_hwndTreeview =  CreateWindowEx(0,
                            WC_TREEVIEW,
                            TEXT("Tree View"),
                            WS_VISIBLE|WS_CHILD|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
                            0,
                            0,
                            rcClient.right,
                            rcClient.bottom,
                            hwndChild,
                            NULL,
                            g_hInst,
                            NULL);
        Create image list
        if((himl=ImageList_Create(16,16,ILC_COLOR32,22,0))==NULL)
            MessageBox(hwnd,"ImageList_Create(64,16,FALSE,4,0)=NULL","Caption",0);
dje
        // Add the open file, closed file, and document bitmaps.
        if((hbmp = LoadBitmap(g_hInst, "IDB_PROPRES"))==NULL)
            MessageBox(hwnd,"hbmp==NULL","Caption",0);

        Bmp[0]=9;

        Bmp[0] = ImageList_Add(himl, hbmp, (HBITMAP)NULL);
        Bmp[1] = Bmp[0]+1;
        Bmp[2] = Bmp[1]+1;
        Bmp[3] = Bmp[2]+1;
        Bmp[4] = Bmp[3]+1;
        Bmp[5] = Bmp[4]+1;
        Bmp[6] = Bmp[5]+1;
        Bmp[7] = Bmp[6]+1;
        Bmp[8] = Bmp[7]+1;
        Bmp[9] = Bmp[8]+1;
        Bmp[10] = Bmp[9]+1;
        Bmp[11] = Bmp[10]+1;
        Bmp[12] = Bmp[11]+1;
        Bmp[13] = Bmp[12]+1;
        Bmp[14] = Bmp[13]+1;
        Bmp[15] = Bmp[14]+1;
        Bmp[16] = Bmp[15]+1;
        Bmp[17] = Bmp[16]+1;
        Bmp[18] = Bmp[17]+1;
        Bmp[19] = Bmp[18]+1;
        Bmp[20] = Bmp[19]+1;
        Bmp[21] = Bmp[20]+1;
        DeleteObject(hbmp);
        char buf[16];
        sprintf(buf,"%d",Bmp[0]);

        //MessageBox(hwnd,buf,"Заголовок",0);

        // Associate the image list with the tree-view control.
        TreeView_SetImageList(g_hwndTreeview, himl, TVSIL_NORMAL);

        hPrev = TreeViewInertItem("Предприятие", TVI_ROOT,enIMAGE::ENTRPRS,Bmp[0]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие","Заголовок",0);

        hPrev2 = TreeViewInertItem("Реквизиты", hPrev,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev2 = TreeViewInertItem("Филиал", hPrev,enIMAGE::BRNCH,Bmp[2]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Филиалы","Заголовок",0);

        hPrev3 = TreeViewInertItem("Реквизиты", hPrev2,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка","Заголовок",0);

        hPrev3 = TreeViewInertItem("Типы объектов", hPrev2,enIMAGE::TPE_OBJ,Bmp[4]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка","Заголовок",0);

        hPrev4 = TreeViewInertItem("Компрессорные цеха", hPrev3,enIMAGE::CEX,Bmp[5]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка","Заголовок",0);

        hPrev4 = TreeViewInertItem("Линейная часть МГ", hPrev3,enIMAGE::CEX,Bmp[5]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка","Заголовок",0);

        hPrev4 = TreeViewInertItem("ГРС", hPrev3,enIMAGE::CEX,Bmp[5]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка","Заголовок",0);

        hPrev5 = TreeViewInertItem("КС-6", hPrev4,enIMAGE::CEXSYSTEM,Bmp[6]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка","Заголовок",0);

        hPrev6 = TreeViewInertItem("Реквизиты", hPrev5,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev6 = TreeViewInertItem("Объекты", hPrev5,enIMAGE::OBJCTS,Bmp[7]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev7 = TreeViewInertItem("АВО газа", hPrev6,enIMAGE::OBJECTSSTM,Bmp[8]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev8 = TreeViewInertItem("Реквизиты", hPrev7,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev8 = TreeViewInertItem("Объемы", hPrev7,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev9 = TreeViewInertItem("10 электродвигателей АВО газа", hPrev8,enIMAGE::RND_FILL,Bmp[10]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev10 = TreeViewInertItem("Реквизиты", hPrev9,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);



        hPrev3 = TreeViewInertItem("Производственные службы", hPrev2,enIMAGE::FLDDEPTS,Bmp[11]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Филиалы","Заголовок",0);

        hPrev4 = TreeViewInertItem("СЭВС", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Отделы","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Ответственные за энергосбережение", hPrev4,enIMAGE::EMPL,Bmp[3]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev6 = TreeViewInertItem("Сибиряков А.А. - Инженер-программист 2 кат.", hPrev5,enIMAGE::RND_FILL,Bmp[10]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev7 = TreeViewInertItem("Реквизиты", hPrev6,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("ДС", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Отделы","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev6 = TreeViewInertItem("Ответственные за энергосбережение", hPrev4,enIMAGE::EMPL,Bmp[3]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev7 = TreeViewInertItem("Сибиряков А.А. - Инженер-программист 2 кат.", hPrev6,enIMAGE::RND_FILL,Bmp[10]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev8 = TreeViewInertItem("Реквизиты", hPrev7,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);



        hPrev2 = TreeViewInertItem("Производственные отделы", hPrev,enIMAGE::DEPTS,Bmp[12]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Отделы","Заголовок",0);

        hPrev4 = TreeViewInertItem("ОГЭ", hPrev2,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Отделы","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Отделы","Заголовок",0);

        hPrev5 = TreeViewInertItem("Ответственные за энергосбережение", hPrev4,enIMAGE::EMPL,Bmp[3]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev6 = TreeViewInertItem("Сибиряков А.А. - Инженер-программист 2 кат.", hPrev5,enIMAGE::RND_FILL,Bmp[10]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev7 = TreeViewInertItem("Реквизиты", hPrev6,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("ПО МГ", hPrev2,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Отделы","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Отделы","Заголовок",0);

        hPrev5 = TreeViewInertItem("Ответственные за энергосбережение", hPrev4,enIMAGE::EMPL,Bmp[3]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev6 = TreeViewInertItem("Сибиряков А.А. - Инженер-программист 2 кат.", hPrev5,enIMAGE::RND_FILL,Bmp[10]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev7 = TreeViewInertItem("Реквизиты", hPrev6,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev2 = TreeViewInertItem("Документы", hPrev,enIMAGE::DOCS,Bmp[13]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev3 = TreeViewInertItem("Приказы о назначении ответственных лиц", hPrev2,enIMAGE::ORDR,Bmp[14]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Приказ №1", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Приказ №2", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

         hPrev3 = TreeViewInertItem("Методические указания", hPrev2,enIMAGE::GDLNS,Bmp[15]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Методические указания №1", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Методические указания №2", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev3 = TreeViewInertItem("Единицы измерения", hPrev,enIMAGE::EUS,Bmp[16]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Единица измерения №1", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Единица измерения №2", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);


        hPrev3 = TreeViewInertItem("Исходные параметры", hPrev,enIMAGE::PARAMS,Bmp[17]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Исходный параметр №1", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Исходный параметр №2", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev3 = TreeViewInertItem("Вычисляемые параметры", hPrev,enIMAGE::CALCPARAMS,Bmp[18]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Вычисляемый параметр №1", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Вычисляемый параметр №2", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev3 = TreeViewInertItem("Формулы", hPrev,enIMAGE::FORMULS,Bmp[19]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Вычисляемый параметр №1", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Вычисляемый параметр №2", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev3 = TreeViewInertItem("Типы ресурсов", hPrev,enIMAGE::TPSRESRS,Bmp[20]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Тип ресурса №1", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Тип ресурса №2", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev3 = TreeViewInertItem("Мероприятия", hPrev,enIMAGE::EVNTS,Bmp[21]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Мероприятие №1", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev4 = TreeViewInertItem("Мероприятие №2", hPrev3,enIMAGE::RND_EMPT,Bmp[9]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);

        hPrev5 = TreeViewInertItem("Реквизиты", hPrev4,enIMAGE::RQSTS,Bmp[1]);
        if(hPrev==NULL) MessageBox(hwnd,"Ошибка Предприятие - реквизиты","Заголовок",0);
        */

        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


LRESULT CALLBACK ChildWindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static DataHierarhy& Hierarhy = DataHierarhy::instance();
    switch (message)                  /* handle the messages */
    {
    case WM_NOTIFY:
        {
            LPNMTREEVIEW pnmtv = (LPNMTREEVIEW) lParam;
            if (pnmtv -> hdr.code == TVN_SELCHANGED)
            {
                char szBuffer[25] = "";
                TVITEMEX tvitem = {0};
                tvitem.hItem = TreeView_GetSelection(Hierarhy.GetHWND());
                tvitem.mask = TVIF_TEXT;
                tvitem.pszText = szBuffer;
                tvitem.cchTextMax = 25;
                TreeView_GetItem(Hierarhy.GetHWND(), &tvitem);
                //MessageBox(hwnd, szBuffer, "", 0);
                //GetParentX(Hierarhy.GetHWND(),tvitem.hItem);
            }
        }
        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

HTREEITEM TreeViewInertItem(char* text, const HTREEITEM& hParent, int image, int selimage)
{
    HIMAGELIST himl;  // handle to image list
    HBITMAP hbmp;     // handle to bitmap
    TVITEM tvi;
    TVINSERTSTRUCT tvins;
    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST;
    HTREEITEM hti;

     tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

    // Set the text of the item.
    tvi.pszText = text;
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]);

    // Assume the item is not a parent item, so give it a
    // document image.
    tvi.iImage = image;
    tvi.iSelectedImage = selimage;
    tvins.item = tvi;
    tvins.hInsertAfter = TVI_LAST;
    tvins.hParent = hParent;

    hPrev = (HTREEITEM)SendMessage(g_hwndTreeview, TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);

    if (hPrev == NULL)
        return NULL;

    return hPrev;
}
