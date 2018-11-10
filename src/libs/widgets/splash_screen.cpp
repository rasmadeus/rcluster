#include <QVBoxLayout>
#include <QTime>
#include <globals.h>
#include "splash_screen.h"

SplashScreen::SplashScreen(QWidget &surface)
    : QWidget{ &surface, Qt::SplashScreen }
    , _surface{ surface }
{
    setFixedSize(250, 250);

    _scrollArea.setWidget(&_label);
    _scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _scrollArea.setWidgetResizable(true);
    _scrollArea.setFrameShape(QFrame::NoFrame);

    _label.setWordWrap(true);
    _label.setAlignment(Qt::AlignLeft | Qt::AlignTop);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(rcluster::layoutGap());
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_scrollArea);

    surface.installEventFilter(this);
}

SplashScreen::~SplashScreen()
{
    stopShow();
}

bool SplashScreen::eventFilter(QObject *watched, QEvent *ev)
{
    if (watched == &_surface && (ev->type() == QEvent::Move || ev->type() == QEvent::Resize))
        updateGeometry();
    return false;
}

void SplashScreen::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == _stopShowTimerId)
    {
        stopShow();
        hide();
        _messages.clear();
    }
}

void SplashScreen::showMessage(QString const &message, QColor const &color)
{
    stopShow();

    _messages.push_front(QStringLiteral("<b>[%1]</b> %2").arg(QTime::currentTime().toString(QStringLiteral("hh:mm:ss.zzz"))).arg(message));
    _label.setText(QStringLiteral("<font color=\"%1\">%2</font>").arg(color.name()).arg(_messages.join(QStringLiteral("<hr />"))));

    updateGeometry();
    startShow();
}

void SplashScreen::updateGeometry()
{
    auto const rect = _surface.geometry();
    move(rect.right() - width(), rect.bottom() - height());
}

void SplashScreen::startShow()
{
    Q_ASSERT(_stopShowTimerId == -1);
   show();
   _stopShowTimerId = startTimer(15000);
}

void SplashScreen::stopShow()
{
    if (_stopShowTimerId != -1)
    {
        killTimer(_stopShowTimerId);
        _stopShowTimerId = -1;
    }

    _label.clear();
}
