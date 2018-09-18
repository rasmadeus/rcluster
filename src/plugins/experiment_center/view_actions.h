#ifndef VIEW_ACTIONS_H
#define VIEW_ACTIONS_H

#include <actions.h>

class DataView;

class ViewActions : public Actions
{
    Q_OBJECT

public:
    explicit ViewActions(DataView &dataView, QObject &parent);

private:
    DataView &_dataView;
};

#endif // VIEW_ACTIONS_H
