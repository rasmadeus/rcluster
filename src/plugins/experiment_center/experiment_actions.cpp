#include "experiment_actions.h"
#include "experiment_center.h"

ExperimentActions::ExperimentActions(ExperimentCenter &experimentCenter, QObject &parent)
    : Actions{ parent }
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
        &_experimentCenter,
        &ExperimentCenter::stop
    );
}
