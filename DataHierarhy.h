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

//Экземпляр класса может быть один (SingleTon)
class DataHierarhy
{
public:
    //Обеспечение единственного экземпляра класса для списка данных
    static DataHierarhy& instance()
    {
        static DataHierarhy dh;
        return dh;
    }
    void Set(const HWND&, const HINSTANCE&);
    const HWND& GetHWND();
private:
    HWND hwndTreeview;//описатель окна
    HIMAGELIST himl;//хэндл для списка изображений
    HBITMAP hbmp;//изображение (ресурсы)
    DWORD Style = WS_VISIBLE|WS_CHILD|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT;//Стиль для listbox
    int CountBitmapImage = 25;
    std::string tagNameImageRes = "IDB_PROPRES";
    std::vector<int> BMP;
    enum Node
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
    //Временный массив для хранения наименований итемов в ListBox
    std::vector<std::string> ItemNameListBox {  "Предприятие",
                                                "Филиал",
                                                "Производственные отделы",
                                                "Документы",
                                                "Единицы измерения",
                                                "Исходные параметры",
                                                "Вычисляемые параметры",
                                                "Формулы",
                                                "Типы ресурсов",
                                                "Мероприятия",
                                                "Класс объектов",
                                                "Производственные службы",
                                                "Приказы о назначении ответственных лиц",
                                                "Методические указания",

                                                "Компрессорные цеха",
                                                "Линейная часть МГ",
                                                "ГРС",
                                                "КС-6",
                                                "Объекты",
                                                "АВО газа",
                                                "Объемы",
                                                "10 электродвигателей АВО газа",

                                                "СЭВС",
                                                "Ответственные за энергосбережение",
                                                "Сибиряков А.А. - Инженер-программист 2 кат.",
                                                "ДС",
                                                "Ответственные за энергосбережение",
                                                "Сибиряков А.А. - Инженер-программист 2 кат.",
                                                "ОГЭ",
                                                "Ответственные за энергосбережение",
                                                "Сибиряков А.А. - Инженер-программист 2 кат.",
                                                "ПО МГ",
                                                "Ответственные за энергосбережение",
                                                "Сибиряков А.А. - Инженер-программист 2 кат.",


                                                "Приказ №1",
                                                "Приказ №2",

                                                "Методические указания №1",
                                                "Методические указания №2",

                                                "Единица измерения №1",
                                                "Единица измерения №2",

                                                "Исходный параметр №1",
                                                "Исходный параметр №2",

                                                "Вычисляемый параметр №1",
                                                "Вычисляемый параметр №2",

                                                "Вычисляемый параметр №1",
                                                "Вычисляемый параметр №2",

                                                "Тип ресурса №1",
                                                "Тип ресурса №2",

                                                "Мероприятие №1",
                                                "Мероприятие №2"};
private:
    //Обеспечение единственного экземпляра класса для списка данных
    DataHierarhy() {};
    DataHierarhy(DataHierarhy const&);
    DataHierarhy& operator=(DataHierarhy const&);

    /* Метод для добавления  */
    HTREEITEM TreeViewInertItem(std::string text, const HTREEITEM& hParent, int image, int selimage, const Node& lParam);

    /* Развертывание структуры */
    void DeployStruct();
};

void GetParentX(const HWND& hwnd,HTREEITEM hti);

#endif // DATAHIERARHY_H_INCLUDED
