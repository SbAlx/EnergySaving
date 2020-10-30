#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string>

//Users controls
#include "menu.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
std::string szAppName = _T("Настройка данных");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

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
    wincl.lpszMenuName = _T("GenericMenu");                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Настройка данных"),       /* Title Text */
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
    static int iColorID[5] = { WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH,DKGRAY_BRUSH, BLACK_BRUSH };
    static int iSelection = IDM_WHITE;
    HMENU hMenu;

    switch (message)                  /* handle the messages */
    {
    case WM_COMMAND:
        hMenu = GetMenu(hwnd);
        switch(LOWORD(wParam))
        {
            case IDM_NEW :
            case IDM_OPEN :
            case IDM_SAVE :
            case IDM_SAVEAS :
                MessageBeep(0);
                return 0;
            case IDM_EXIT :
                SendMessage(hwnd, WM_CLOSE, 0, 0L);
                return 0;
            case IDM_UNDO :
            case IDM_CUT :
            case IDM_COPY :
            case IDM_PASTE :
            case IDM_DEL :
                MessageBeep(0);
                return 0;
            case IDM_WHITE : // Note: Logic below
            case IDM_LTGRAY : // assumes that IDM_WHITE
            case IDM_GRAY : // through IDM_BLACK are
            case IDM_DKGRAY : // consecutive numbers in
            case IDM_BLACK : // the order shown here.
                CheckMenuItem(hMenu, iSelection, MF_UNCHECKED);
                iSelection = LOWORD(wParam);
                CheckMenuItem(hMenu, iSelection, MF_CHECKED);
                SetClassLong(hwnd, GCL_HBRBACKGROUND,(LONG) GetStockObject(iColorID[LOWORD(wParam) - IDM_WHITE]));
                InvalidateRect(hwnd, NULL, TRUE);
                return 0;
            case IDM_START :
                if(SetTimer(hwnd, 1, 1000, NULL))
                {
                    EnableMenuItem(hMenu, IDM_START, MF_GRAYED);
                    EnableMenuItem(hMenu, IDM_STOP, MF_ENABLED);
                }
                return 0;
            case IDM_STOP :
                KillTimer(hwnd, 1);
                EnableMenuItem(hMenu, IDM_START, MF_ENABLED);
                EnableMenuItem(hMenu, IDM_STOP, MF_GRAYED);
                return 0;
            case IDM_HELP :
                MessageBox(hwnd, "Help not yet implemented!",szAppName.c_str(), MB_ICONEXCLAMATION | MB_OK);
                return 0;
            case IDM_ABOUT :
                MessageBox(hwnd, "Menu Demonstration Program.",szAppName.c_str(), MB_ICONINFORMATION | MB_OK);
                return 0;
        }
        break;
        case WM_TIMER :
            MessageBeep(0);
            return 0;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
}
