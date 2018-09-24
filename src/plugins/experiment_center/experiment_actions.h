#ifndef EXPERIMENT_ACTIONS_H
#define EXPERIMENT_ACTIONS_H

#include <actions.h>

class ExperimentCenter;

class ExperimentActions : public Actions
{
    Q_OBJECT

public:
    explicit ExperimentActions(ExperimentCenter &experimentCenter, QObject &parent);

private:
    ExperimentCenter &_experimentCenter;
};
#endif // EXPERIMENT_ACTIONS_H
