#include <QPair>
#include "lab_access_point.h"

LabAccessPoint::LabAccessPoint(QObject *parent)
    : AccessPoint{ parent }
{
    connect(this, &LabAccessPoint::ready, this, &LabAccessPoint::onReady);
}

void LabAccessPoint::login(QString const &username, QString const &password)
{
    get(QStringLiteral("login"), QStringLiteral("self"), {
        { QStringLiteral("username"), username },
        { QStringLiteral("password"), password },
    });
}

void LabAccessPoint::logout()
{
    get(QStringLiteral("logout"), QStringLiteral("self"));
}

void LabAccessPoint::onReady(QString const &path, QString const &client, int operation, QJsonObject const &json)
{
    if (client != QStringLiteral("self"))
        return;

    if (operation == QNetworkAccessManager::GetOperation)
    {
        if (path == QStringLiteral("/core/api/login/"))
            setToken(json.value(QStringLiteral("token")).toString());
        else if (path == QStringLiteral("logout"))
            setToken({});
    }
}
