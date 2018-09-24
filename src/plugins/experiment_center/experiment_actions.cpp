#include <QMessageBox>
#include "experiment_actions.h"
#include "experiment_center.h"

ExperimentActions::ExperimentActions(ExperimentCenter &experimentCenter, QWidget &parent)
    : Actions{ parent }
    , _parent{ parent }
    , _experimentCenter{ experimentCenter }
{
    connect(
        &append(QStringLiteral("start"), tr("Start"), false),
        &QAction::triggered,
        &_experimentCenter,
        &ExperimentCenter::start
    );

    connect(
        &append(QStringLiteral("stop"), tr("Stop"), false),
        &QAction::triggered,
        this,
        &ExperimentActions::stopExperiment
    );
}

void ExperimentActions::stopExperiment()
{
    auto const key = QMessageBox::question(&_parent, tr("Stop the experiment"), tr("Do you want to stop this experiment?"));
    if (key == QMessageBox::Yes)
        _experimentCenter.stop();
}
