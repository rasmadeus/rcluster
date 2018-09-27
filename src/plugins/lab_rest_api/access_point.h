#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <QObject>
#include <QJsonObject>
#include <QNetworkAccessManager>

class AccessPoint : public QObject
{
    Q_OBJECT

public:
    explicit AccessPoint(QObject *parent = nullptr);

public:
    void setHost(QString const &host) { _host = host; }
    QString const &host() const { return _host; }

    void setToken(QString const &token) { _token = token; }
    QString const &token() const { return _token; }

public:
    void get(QString const &path, QString const &client, QVector<QPair<QString, QString>> const &params = {});
    void put(QString const &path, QString const &client, QHttpMultiPart *multiPart);
    void post(QString const &path, QString const &client, QHttpMultiPart *multiPart);
    void deleteResource(QString const &path, QString const &client);

signals:
    void error(QString const &path, QString const &client, int operation, QString const &what);
    void ready(QString const &path, QString const &client, int operation, QJsonObject const &json);

private:
    QNetworkRequest authRequest(QUrl const &url) const;
    QNetworkRequest csrfRequest(QUrl const &url) const;
    QUrl url(QString const &path, QVector<QPair<QString, QString>> const &params = {}) const;
    QByteArray csrf() const;

private:
    void onReplyFinished();
    void onReplyError();

protected:
    QNetworkAccessManager _accessManager;
    QString _host;
    QString _token;
};

#endif // ACCESS_POINT_H
