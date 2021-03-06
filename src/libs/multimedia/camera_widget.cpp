#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include "camera_widget.h"

CameraWidget::CameraWidget(QWidget &parent)
    : QWidget{ &parent }
    , _client{ winId() }
{
    connect(&_client, &RtspRenderer::error, this, &CameraWidget::onError);
}

void CameraWidget::setUrl(QString const &url)
{
    _url = url;
    _client.start({ { QStringLiteral("location"), url }, });
}

void CameraWidget::paintEvent(QPaintEvent *ev)
{
    QPainter painter{ this };
    painter.fillRect(ev->rect(), Qt::black);
}

void CameraWidget::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == _reconnectTimerId)
    {
        _client.start({ { QStringLiteral("location"), _url }, });
        killTimer(_reconnectTimerId);
        _reconnectTimerId = -1;
    }
}

void CameraWidget::onError()
{
    if (_reconnectTimerId == -1)
    {
        _client.stop();
        _reconnectTimerId = startTimer(5000);
        repaint();
    }
}
