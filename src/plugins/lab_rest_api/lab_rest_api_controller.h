#ifndef LAB_REST_API_CONTROLLER_H
#define LAB_REST_API_CONTROLLER_H

#include <controller_without_activity.h>
#include "lab_access_point.h"

class LabRestApiController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit LabRestApiController(Config const &config, Plugin const &plugin, Corebus &corebus);

public:
    void onSetup(Slave const &slave) override;

private:
    void onError(QString const &path, QString const &client, int operation, QString const &what);
    void onReady(QString const &path, QString const &client, int operation, QJsonObject const &json);

    void onGet(Message const &message);

private:
    LabAccessPoint _accessPoint;
};

#endif // LAB_REST_API_CONTROLLER_H
