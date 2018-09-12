#include <QVBoxLayout>
#include <globals.h>
#include "experiment_center_editor.h"

ExperimentCenterEditor::ExperimentCenterEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
{
    _respondentView.setSelectionMode(QAbstractItemView::SingleSelection);
    _respondentView.setSelectionBehavior(QAbstractItemView::SelectRows);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);
    mainLayout->addWidget(&_respondentView);
}
