#ifndef MENU_H
#define MENU_H

#include <QMenu>
#include "widgets_global.h"

class QMenuBar;

class WIDGETS_SHARED_EXPORT Menu : public QObject
{
    Q_OBJECT

public:
    explicit Menu(QString const &name, QWidget &parent);

public:
    void install(QMenuBar &bar);

protected:
    QMenu _menu;
};

#endif // MENU_H
