#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <config.h>
#include <corebus.h>
#include <message.h>
#include <simplecrypt.h>
#include "lab_rest_api_controller.h"

namespace
{
    auto paramsFrom(Message const &message)
    {
        QVector<QPair<QString, QString>> params;
        for(auto const value : message.param(QStringLiteral("params")).toJsonArray())
        {
            auto const json = value.toObject();
            params.push_back({ json.value(QStringLiteral("key")).toString(), json.value(QStringLiteral("value")).toString() });
        }
        return params;
    }
}

LabRestApiController::LabRestApiController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithoutActivity{ config, plugin, corebus }
{
    _router.handle(QStringLiteral("GET"), std::bind(&LabRestApiController::onGet, this, std::placeholders::_1));
    connect(&_accessPoint, &LabAccessPoint::ready, this, &LabRestApiController::onReady);
    connect(&_accessPoint, &LabAccessPoint::error, this, &LabRestApiController::onError);
}

void LabRestApiController::onSetup(Slave const &slave)
{
    auto const host = slave.param(QStringLiteral("host")).toString();
    auto const username = slave.param(QStringLiteral("username")).toString();
    auto const password = slave.param(QStringLiteral("password")).toString();

    _accessPoint.setHost(host);
    _accessPoint.login(username, SimpleCrypt{}.decryptToString(password));
}

void LabRestApiController::onError(QString const &path, QString const &client, int operation, QString const &what)
{
    if (client == QStringLiteral("self"))
        return;

    _corebus.send(QStringLiteral("ERROR"), client, {
        { QStringLiteral("path"), path },
        { QStringLiteral("operation"), operation },
        { QStringLiteral("what"), what },
    });
}

void LabRestApiController::onReady(QString const &path, QString const &client, int operation, QJsonObject const &json)
{
    if (client == QStringLiteral("self"))
        return;

    _corebus.send(QStringLiteral("REPLY"), client, {
        { QStringLiteral("path"), path },
        { QStringLiteral("operation"), operation },
        { QStringLiteral("json"), json },
    });
}

void LabRestApiController::onGet(Message const &message)
{
    _accessPoint.get(
        message.param(QStringLiteral("path")).toString(),
        message.from(),
       ::paramsFrom(message)
    );
}
