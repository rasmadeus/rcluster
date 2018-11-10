#ifndef ACTIONS_H
#define ACTIONS_H

#include <memory>
#include <vector>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include "widgets_global.h"

class QToolBar;

class WIDGETS_SHARED_EXPORT Actions : public QObject
{
    Q_OBJECT

public:
    explicit Actions(QObject &parent);

public:
    QAction &append(QString const &icon, QString const &name, bool afterSeparator = false, QSize const &iconSize = { 32, 32 });
    void install(QMenu &menu) { install<QMenu>(menu); }
    void install(QToolBar &tool) { install<QToolBar>(tool); }

private:
    template<class T>
    void install(T &t)
    {
        for(auto &action : _actions)
        {
            t.addAction(action.first.get());
            if (action.second)
                t.addSeparator();
        }
    }

private:
    std::vector<std::pair<std::unique_ptr<QAction>, bool>> _actions;
};

#endif // ACTIONS_H
