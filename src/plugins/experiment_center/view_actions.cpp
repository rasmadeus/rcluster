#include "data_view.h"
#include "view_actions.h"

ViewActions::ViewActions(DataView &dataView, QObject &parent)
    : Actions{ parent }
    , _dataView{ dataView }
{
    connect(
        &append(QStringLiteral("add"), tr("Append new tab"), false),
        &QAction::triggered,
        &_dataView,
        &DataView::appendTab
    );
}
