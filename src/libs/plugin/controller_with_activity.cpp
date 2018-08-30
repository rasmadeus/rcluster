#include <QApplication>
#include <QLayout>
#include <QSettings>
#include <core_bus.h>
#include <globals.h>
#include <message.h>
#include "controller_with_activity.h"
#include "plugin.h"

ControllerWithActivity::ControllerWithActivity()
    : QMainWindow{ nullptr, Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint }
    , SlaveController{}
{
    setContentsMargins(rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap(), rcluster::layoutGap());
    connect(qApp, &QApplication::aboutToQuit, this, static_cast<void(ControllerWithActivity::*)()>(&ControllerWithActivity::storeSettings));
}

void ControllerWithActivity::onInit()
{
    setWindowIcon(_plugin->pixmap({ 32, 32}));
    restoreSettings();
    show();
}

void ControllerWithActivity::storeSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("main_view"));
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.setValue(QStringLiteral("state"), saveState());
    storeSettings(settings);
    settings.endGroup();
}

void ControllerWithActivity::restoreSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("main_view"));
    restoreGeometry(settings.value(QStringLiteral("geometry")).toByteArray());
    restoreState(settings.value(QStringLiteral("state")).toByteArray());
    restoreSettings(settings);
    settings.endGroup();
}
