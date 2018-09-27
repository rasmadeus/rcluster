#include <QApplication>
#include <QJsonDocument>
#include <QHttpMultiPart>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QUrlQuery>
#include "access_point.h"

namespace
{
    QUrlQuery makeQuery(QVector<QPair<QString, QString>> const &params)
    {
        QUrlQuery query;
        for(auto const &param : params)
            query.addQueryItem(param.first, param.second);
        return query;
    }
}

AccessPoint::AccessPoint(QObject *parent)
    : QObject{ parent }
{
}

void AccessPoint::get(QString const &path, QString const &client, QVector<QPair<QString, QString>> const &params)
{
    auto const url = this->url(path, params);
    qDebug() << "GET request:" << url.toString() << "; client:" << client;

    auto reply = _accessManager.get(authRequest(url));
    reply->setProperty("client", client);
    connect(reply, &QNetworkReply::finished, this, &AccessPoint::onReplyFinished);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &AccessPoint::onReplyError);
    connect(reply, &QNetworkReply::sslErrors, this, &AccessPoint::onReplyError);
}

void AccessPoint::put(QString const &path, QString const &client, QHttpMultiPart *multiPart)
{
    auto const url = this->url(path);
    qDebug() << "PUT request:" << url.toString() << "; client:" << client;

    auto reply = _accessManager.put(csrfRequest(url), multiPart);
    reply->setProperty("client", client);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::finished, this, &AccessPoint::onReplyFinished);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &AccessPoint::onReplyError);
    connect(reply, &QNetworkReply::sslErrors, this, &AccessPoint::onReplyError);
}

void AccessPoint::post(QString const &path, QString const &client, QHttpMultiPart *multiPart)
{
    auto const url = this->url(path);
    qDebug() << "POST request:" << url.toString() << "; client:" << client;

    auto reply = _accessManager.post(csrfRequest(url), multiPart);
    reply->setProperty("client", client);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::finished, this, &AccessPoint::onReplyFinished);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &AccessPoint::onReplyError);
    connect(reply, &QNetworkReply::sslErrors, this, &AccessPoint::onReplyError);
}

void AccessPoint::deleteResource(QString const &path, QString const &client)
{
    auto const url = this->url(path);
    qDebug() << "DELETE request:" << url.toString() << "; client:" << client;

    auto reply = _accessManager.deleteResource(csrfRequest(url));
    reply->setProperty("client", client);

    connect(reply, &QNetworkReply::finished, this, &AccessPoint::onReplyFinished);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &AccessPoint::onReplyError);
    connect(reply, &QNetworkReply::sslErrors, this, &AccessPoint::onReplyError);
}

QNetworkRequest AccessPoint::authRequest(QUrl const &url) const
{
    QNetworkRequest request{ url };
    request.setRawHeader("User-Agent", QStringLiteral("%1/%2 (rcluster)").arg(qApp->applicationName()).arg(qApp->applicationVersion()).toUtf8());
    request.setRawHeader("Authorization", _token.toUtf8());
    return request;
}

QNetworkRequest AccessPoint::csrfRequest(QUrl const &url) const
{
    auto request = authRequest(url);
    request.setRawHeader("X-CSRFToken", csrf());
    return request;
}

QUrl AccessPoint::url(QString const &path, QVector<QPair<QString, QString>> const &params) const
{
    auto url = QUrl::fromUserInput(QStringLiteral("%1/%2/").arg(_host, path));
    url.setQuery(::makeQuery(params));
    return url;
}

QByteArray AccessPoint::csrf() const
{
    auto const cookies = _accessManager.cookieJar()->cookiesForUrl(url(QStringLiteral("/")));
    auto const it = std::find_if(cookies.cbegin(), cookies.cend(), [](auto const &cookie){ return cookie.name() == QStringLiteral("csrftoken"); });
    return it == cookies.cend() ? QByteArray{} : it->value();
}

void AccessPoint::onReplyFinished()
{
    auto reply = qobject_cast<QNetworkReply*>(sender());
    Q_ASSERT(reply != nullptr);

    auto const client = reply->property("client").toString();

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Reply" << reply->url().toString() << "for" << client << "finished with error:" << reply->errorString();
        return;
    }

    qDebug() << "Reply" << reply->url().toString() << "for" << client << "finished with no error.";
    emit ready(reply->url().path(), client, reply->operation(), QJsonDocument::fromJson(reply->readAll()).object());

    reply->deleteLater();
}

void AccessPoint::onReplyError()
{
    auto reply = qobject_cast<QNetworkReply*>(sender());
    Q_ASSERT(reply != nullptr);

    auto const client = reply->property("client").toString();

    qDebug() << "Reply" << reply->url().toString() << "for" << client << "finished with error:" << reply->errorString();
    emit error(reply->url().path(), client, reply->operation(), reply->errorString());

    reply->deleteLater();
}
