#ifndef EXPERIMENT_ACTIONS_H
#define EXPERIMENT_ACTIONS_H

#include <actions.h>

class ExperimentCenter;

class ExperimentActions : public Actions
{
    Q_OBJECT

public:
    explicit ExperimentActions(ExperimentCenter &experimentCenter, QWidget &parent);

private:
    void stopExperiment();

private:
    QWidget &_parent;
    ExperimentCenter &_experimentCenter;
};
#endif // EXPERIMENT_ACTIONS_H
