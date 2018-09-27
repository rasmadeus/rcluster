#include <QApplication>
#include <QLayout>
#include <QSettings>
#include <corebus.h>
#include <globals.h>
#include <message.h>
#include "controller_with_activity.h"
#include "plugin.h"

ControllerWithActivity::ControllerWithActivity(Config const &config, Plugin const &plugin, Corebus &corebus)
    : QMainWindow{ nullptr, Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint }
    , SlaveController{ config, plugin, corebus }
{
    setObjectName(QStringLiteral("controller_with_activity"));
    connect(qApp, &QApplication::aboutToQuit, this, &ControllerWithActivity::storeControllerSettings);

    setWindowIcon(_plugin.pixmap({ 32, 32 }));
    show();
}

void ControllerWithActivity::storeControllerSettings() const
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
