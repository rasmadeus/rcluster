#include <QVBoxLayout>
#include <globals.h>
#include "data_view.h"

DataView::DataView(QWidget *parent)
    : QWidget{ parent }
{
    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_tabs);
}
