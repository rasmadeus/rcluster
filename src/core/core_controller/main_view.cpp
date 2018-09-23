#include <QApplication>
#include <QDesktopServices>
#include <QMenuBar>
#include <QSettings>
#include <QStatusBar>
#include <QUrl>
#include <globals.h>
#include <corebus.h>
#include "main_view.h"

ControllerWithActivity::ControllerWithActivity(Config &config, Plugins &plugins, Corebus &corebus)
    : QMainWindow{}
    , _corebus{ corebus }
    , _coreActions{ corebus, *this }
    , _splitter{ this }
    , _configView{ config, plugins, corebus, *this }
    , _slaveParamsView{ config, plugins, corebus, *this }
{
    setWindowIcon(QIcon{ QStringLiteral(":/res/icon.ico") });
    setWindowTitle(tr("RCluster Core Controller"));

    auto coreMenu = menuBar()->addMenu(tr("Core"));
    coreMenu->setObjectName(QStringLiteral("core_actions_menu"));
   _coreActions.install(*coreMenu);

    auto coreToolBar = addToolBar(tr("Core actions"));
    coreToolBar->setObjectName(QStringLiteral("core_actions_tool_bar"));
    _coreActions.install(*coreToolBar);

    auto viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->setObjectName(QStringLiteral("view_menu"));
    viewMenu->addAction(coreToolBar->toggleViewAction());

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->setObjectName(QStringLiteral("help_menu"));
    helpMenu->addAction(tr("Open the application folder"), []{ QDesktopServices::openUrl(QUrl::fromLocalFile(rcluster::writableLocation())); });

    _splitter.setContentsMargins(rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap());
    _splitter.addWidget(&_configView);
    _splitter.addWidget(&_slaveParamsView);
    _splitter.setEnabled(false);

    setCentralWidget(&_splitter);

    connect(qApp, &QApplication::aboutToQuit, this, &ControllerWithActivity::storeSettings);
    connect(&corebus, &Corebus::connected, this, &ControllerWithActivity::onCoreConnected);
    connect(&corebus, &Corebus::disconnected, this, &ControllerWithActivity::onCoreDisconnected);
    connect(&_configView, &ConfigView::selected, &_slaveParamsView, &SlaveParamsView::select);

    resize(800, 600);
    restoreSettings();
}

void ControllerWithActivity::storeSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("main_view"));
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.setValue(QStringLiteral("state"), saveState());
    settings.setValue(QStringLiteral("splitter_state"), _splitter.saveState());
    settings.setValue(QStringLiteral("splitter_geometry"), _splitter.saveGeometry());
    settings.endGroup();
}

void ControllerWithActivity::restoreSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("main_view"));
    restoreGeometry(settings.value(QStringLiteral("geometry")).toByteArray());
    restoreState(settings.value(QStringLiteral("state")).toByteArray());
    _splitter.restoreState(settings.value(QStringLiteral("splitter_state")).toByteArray());
    _splitter.restoreGeometry(settings.value(QStringLiteral("splitter_geometry")).toByteArray());
    settings.endGroup();
}

void ControllerWithActivity::onCoreConnected()
{
    _splitter.setEnabled(true);
}

void ControllerWithActivity::onCoreDisconnected()
{
    _splitter.setEnabled(false);
}
