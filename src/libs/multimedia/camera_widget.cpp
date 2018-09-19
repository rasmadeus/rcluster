#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include "camera_widget.h"

CameraWidget::CameraWidget(QString const &url, QWidget &parent)
    : QWidget{ &parent }
    , _url{ url }
{
    connect(&_observer, &GstPipelineObserver::error, this, &CameraWidget::onError);
    connect(&_observer, &GstPipelineObserver::stateChanged, this, &CameraWidget::onStateChanged);
    _client = std::make_unique<RtspClient>(url, winId(), _observer);
}

void CameraWidget::setUrl(QString const &url)
{
    _url = url;

    if (_client != nullptr)
    {
        _client.reset();
        _client = std::make_unique<RtspClient>(url, winId(), _observer);
    }
}

void CameraWidget::paintEvent(QPaintEvent *ev)
{
    QPainter painter{ this };
    painter.fillRect(ev->rect(), Qt::black);

    if (_state != GST_STATE_PLAYING)
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
        _client = std::make_unique<RtspClient>(_url, winId(), _observer);
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
