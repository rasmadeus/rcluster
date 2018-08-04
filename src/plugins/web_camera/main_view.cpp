#include "main_view.h"

MainView::MainView(Config const &config, Plugin const &plugin, CoreClientSocket &socket)
    : MainViewController{ config, plugin, socket }
{
    setWindowTitle(tr("Web Camera"));
}

void MainView::onMessage(Message const &message)
{
    Q_UNUSED(message)
}
