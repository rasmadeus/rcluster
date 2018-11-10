#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <QLabel>
#include <QScrollArea>
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT SplashScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget &surface);
    ~SplashScreen() override;

public:
    void info(QString const &message) { showMessage(message, Qt::black); }
    void error(QString const &message) { showMessage(message, Qt::red); }

protected:
    bool eventFilter(QObject *watched, QEvent *ev) override;
    void timerEvent(QTimerEvent *ev) override;

private:
    void showMessage(QString const &message, QColor const &color);
    void updateGeometry();
    void startShow();
    void stopShow();

private:
    QStringList _messages;
    QWidget &_surface;
    int _stopShowTimerId{ -1 };
    QScrollArea _scrollArea;
    QLabel _label;
    bool _hover{ false };
};

#endif // SPLASH_SCREEN_H
