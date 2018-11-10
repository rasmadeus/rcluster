#include <QHBoxLayout>
#include <globals.h>
#include "empty_node_editor.h"

EmptyNodeEditor::EmptyNodeEditor(QWidget &parent)
    : QWidget{ &parent }
    , _info{ tr("No settings for current selection"), this }
{
    _info.setAlignment(Qt::AlignCenter);
    _info.setWordWrap(true);

    auto mainLayout = new QHBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_info);
}
