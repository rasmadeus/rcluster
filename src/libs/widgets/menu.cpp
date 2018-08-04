#include <QMenuBar>
#include "menu.h"

Menu::Menu(QString const &name, QWidget &parent)
    : QObject{ &parent }
    , _menu{ name, &parent }
{
}

void Menu::install(QMenuBar &bar)
{
    bar.addMenu(&_menu);
}
