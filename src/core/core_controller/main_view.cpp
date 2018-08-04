#include <QApplication>
#include <QSettings>
#include <QStatusBar>
#include <core_client_socket.h>
#include "main_view.h"

MainViewController::MainViewController(Config &config, Plugins &plugins, CoreClientSocket &socket)
    : QMainWindow{}
    , _socket{ socket }
    , _coreMenu{ socket, *this }
    , _splitter{ this }
    , _configView{ config, plugins, socket, *this }
    , _slaveParamsView{ config, plugins, socket, *this }
{
    setWindowIcon(QIcon{ QStringLiteral(":/res/icon.ico") });
    setWindowTitle(tr("RCluster Core Controller"));

    _splitter.addWidget(&_configView);
    _splitter.addWidget(&_slaveParamsView);
    _splitter.setEnabled(false);

    setCentralWidget(&_splitter);

    connect(qApp, &QApplication::aboutToQuit, this, &MainViewController::storeSettings);
    connect(&socket, &CoreClientSocket::connected, this, &MainViewController::onCoreConnected);
    connect(&socket, &CoreClientSocket::disconnected, this, &MainViewController::onCoreDisconnected);
    connect(&_configView, &ConfigView::selected, &_slaveParamsView, &SlaveParamsView::select);

    resize(800, 600);
    restoreSettings();
}

void MainViewController::storeSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("main_view"));
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.setValue(QStringLiteral("state"), saveState());
    settings.setValue(QStringLiteral("splitter_state"), _splitter.saveState());
    settings.setValue(QStringLiteral("splitter_geometry"), _splitter.saveGeometry());
    settings.endGroup();
}

void MainViewController::restoreSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("main_view"));
    restoreGeometry(settings.value(QStringLiteral("geometry")).toByteArray());
    restoreState(settings.value(QStringLiteral("state")).toByteArray());
    _splitter.restoreState(settings.value(QStringLiteral("splitter_state")).toByteArray());
    _splitter.restoreGeometry(settings.value(QStringLiteral("splitter_geometry")).toByteArray());
    settings.endGroup();
}

void MainViewController::onCoreConnected()
{
    _splitter.setEnabled(true);
}

void MainViewController::onCoreDisconnected()
{
    _splitter.setEnabled(false);
}
