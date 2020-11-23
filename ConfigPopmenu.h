#ifndef CONFIGPOPMENU_H_INCLUDED
#define CONFIGPOPMENU_H_INCLUDED

#define IDM_CONFIG_PROP 1

class ConfigPopMenu
{
public:
    //ќбеспечение единственного экземпл€ра класса дл€ списка данных
    static ConfigPopMenu& instance()
    {
        static ConfigPopMenu dh;
        return dh;
    }
private:
    //ќбеспечение единственного экземпл€ра класса дл€ списка данных
    ConfigPopMenu() {};
    ConfigPopMenu(ConfigPopMenu const&);
    ConfigPopMenu& operator=(ConfigPopMenu const&);


};

#endif // CONFIGPOPMENU_H_INCLUDED
