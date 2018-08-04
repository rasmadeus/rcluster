#include <QApplication>
#include <QLayout>
#include <QSettings>
#include <core_client_socket.h>
#include <message.h>
#include "main_view.h"

MainView::MainView(Config const &config, Plugin const &plugin, CoreClientSocket &socket)
    : MainViewController{ config, plugin, socket }
    , _log{ this }
{
    setWindowTitle(tr("Message Viewer"));
    _log.setReadOnly(true);
    setCentralWidget(&_log);
    resize(800, 600);
}

void MainView::onMessage(Message const &message)
{
    ++_count;
    if (_count > 1000)
    {
        _log.clear();
        _count = 0;
    }

    _log.appendPlainText(message.toString());
}
