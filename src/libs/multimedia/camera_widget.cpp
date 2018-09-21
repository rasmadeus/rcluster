#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include "camera_widget.h"

CameraWidget::CameraWidget(QWidget &parent)
    : QWidget{ &parent }
{
}

void CameraWidget::setUrl(QString const &url)
{
    _url = url;

    if (_client != nullptr)
        _client.reset();

    _client = std::make_unique<RtspClient>(winId());
    connect(_client.get(), &RtspClient::stateChanged, this, &CameraWidget::onStateChanged);
    connect(_client.get(), &RtspClient::error, this, &CameraWidget::onError);
    _client->start({ { QStringLiteral("location"), url }, });
}

void CameraWidget::paintEvent(QPaintEvent *ev)
{
    QPainter painter{ this };
    painter.fillRect(ev->rect(), Qt::black);

    if (_state != DeviceState::On)
    {
        static auto const caption = tr("Connecting...");

        auto captionRect = QFontMetrics{ {} }.boundingRect(caption);
        captionRect.moveCenter(ev->rect().center());

        painter.setPen(Qt::white);
        painter.drawText(captionRect, caption);
    }
}

void CameraWidget::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == _reconnectTimerId)
    {
        Q_ASSERT(_client == nullptr);
        _client = std::make_unique<RtspClient>(winId());
        connect(_client.get(), &RtspClient::stateChanged, this, &CameraWidget::onStateChanged);
        connect(_client.get(), &RtspClient::error, this, &CameraWidget::onError);
        _client->start({ { QStringLiteral("location"), _url }, });
        killTimer(_reconnectTimerId);
        _reconnectTimerId = -1;
    }
}

void CameraWidget::onError()
{
    if (_reconnectTimerId == -1)
    {
        Q_ASSERT(_client != nullptr);
        _client.reset();
        _reconnectTimerId = startTimer(std::chrono::seconds(5));
        repaint();
    }
}
