#include "main_view.h"

MainView::MainView()
    : MainViewController{}
{
    setWindowTitle(tr("Web Camera"));
}

void MainView::onMessage(Message const &message)
{
    Q_UNUSED(message)
}
