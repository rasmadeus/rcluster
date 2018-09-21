#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include "camera_widget.h"

CameraWidget::CameraWidget(QWidget &parent)
    : QWidget{ &parent }
    , _client{ winId() }
{
    connect(&_client, &RtspClient::stateChanged, this, &CameraWidget::onStateChanged);
    connect(&_client, &RtspClient::error, this, &CameraWidget::onError);
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

    auto const caption = _state == DeviceState::On ? tr("On") : tr("Off");

    auto font = QFont{};
    font.setPixelSize(std::min(ev->rect().width(), ev->rect().height()) / 10);
    font.setBold(true);

    auto captionRect = QFontMetrics{ font }.boundingRect(caption);
    captionRect.moveCenter(ev->rect().center());

    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(captionRect, caption);

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
        _state = DeviceState::Unknown;
        _client.stop();
        _reconnectTimerId = startTimer(std::chrono::seconds(5));
        repaint();
    }
}
