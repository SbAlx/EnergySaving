#ifndef DATAHIERARHY_H_INCLUDED
#define DATAHIERARHY_H_INCLUDED

#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <numeric>
#include <stdio.h>
#include <string>

#define DEBUG

struct tagStructItems
{

};

//��������� ������ ����� ���� ���� (SingleTon)
class DataHierarhy
{
public:
    //����������� ������������� ���������� ������ ��� ������ ������
    static DataHierarhy& instance()
    {
        static DataHierarhy dh;
        return dh;
    }
    void Set(const HWND&, const HINSTANCE&);
    const HWND& GetHWND();
private:
    HWND hwndTreeview;//��������� ����
    HIMAGELIST himl;//����� ��� ������ �����������
    HBITMAP hbmp;//����������� (�������)
    DWORD Style = WS_VISIBLE|WS_CHILD|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT;//����� ��� listbox
    int CountBitmapImage = 25;
    std::string tagNameImageRes = "IDB_PROPRES";
    std::vector<int> BMP;
    enum Node //�������������� ��������� ������
    {   COMPANY,
        BRANCH,
        DEPART,
        DOCS,
        EU,
        INITPAR,
        CALCPAR,
        FORMULA,
        TYPERES,
        EVENTS,
        CLASSOBJ,
        LOCALDEPT,
        ORDERS,
        GUIDLINES};
    //��������� ������ ��� �������� ������������ ������ � ListBox
    std::vector<std::string> ItemNameListBox {  "�����������",
                                                "������",
                                                "���������������� ������",
                                                "���������",
                                                "������� ���������",
                                                "�������� ���������",
                                                "����������� ���������",
                                                "�������",
                                                "���� ��������",
                                                "�����������",
                                                "����� ��������",
                                                "���������������� ������",
                                                "������� � ���������� ������������� ���",
                                                "������������ ��������"};
private:
    //����������� ������������� ���������� ������ ��� ������ ������
    DataHierarhy() {};
    DataHierarhy(DataHierarhy const&);
    DataHierarhy& operator=(DataHierarhy const&);

    /* ����� ��� ����������  */
    HTREEITEM TreeViewInertItem(std::string text, const HTREEITEM& hParent, int image, int selimage, const Node& lParam);

    /* ������������� ��������� */
    void DeployStruct();
};

void GetParentX(const HWND& hwnd,HTREEITEM hti);

#endif // DATAHIERARHY_H_INCLUDED
