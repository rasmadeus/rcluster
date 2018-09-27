#ifndef LAB_ACCESS_POINT_H
#define LAB_ACCESS_POINT_H

#include "access_point.h"

class LabAccessPoint : public AccessPoint
{
public:
    explicit LabAccessPoint(QObject *parent = nullptr);

public:
    void login(QString const &username, QString const &password);
    void logout();

private:
    void onReady(QString const &path, QString const &client, int operation, QJsonObject const &json);
};

#endif // LAB_ACCESS_POINT_H
