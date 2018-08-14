#include <QApplication>
#include <QMenuBar>
#include <QSettings>
#include <QStatusBar>
#include <core_bus.h>
#include "main_view.h"

MainViewController::MainViewController(Config &config, Plugins &plugins, Corebus &corebus)
    : QMainWindow{}
    , _corebus{ corebus }
    , _coreActions{ corebus, *this }
    , _splitter{ this }
    , _configView{ config, plugins, corebus, *this }
    , _slaveParamsView{ config, plugins, corebus, *this }
{
    setWindowIcon(QIcon{ QStringLiteral(":/res/icon.ico") });
    setWindowTitle(tr("RCluster Core Controller"));

    auto coreMenu = menuBar()->addMenu(tr("Core actions"));
    coreMenu->setObjectName(QStringLiteral("core_actions_menu"));
   _coreActions.install(*coreMenu);

    auto coreToolBar = addToolBar(tr("Core actions"));
    coreToolBar->setObjectName(QStringLiteral("core_actions_tool_bar"));
    _coreActions.install(*coreToolBar);

    auto viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(coreToolBar->toggleViewAction());

    _splitter.addWidget(&_configView);
    _splitter.addWidget(&_slaveParamsView);
    _splitter.setEnabled(false);

    setCentralWidget(&_splitter);

    connect(qApp, &QApplication::aboutToQuit, this, &MainViewController::storeSettings);
    connect(&corebus, &Corebus::connected, this, &MainViewController::onCoreConnected);
    connect(&corebus, &Corebus::disconnected, this, &MainViewController::onCoreDisconnected);
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
