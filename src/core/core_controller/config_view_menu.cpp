#include <QMenu>
#include <config.h>
#include <core_bus.h>
#include <plugins.h>
#include "config_view_menu.h"

ConfigViewMenu::ConfigViewMenu(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent)
    : QObject{ &parent }
    , _parent{ parent }
    , _config{ config }
    , _plugins{ plugins }
    , _corebus{ corebus }
{
}

void ConfigViewMenu::watch(QMenu &menu, const QUuid &id)
{
    auto slave = _config.slave(id);

    if (!id.isNull())
    {
        menu.addAction(tr("Remove"), std::bind(&ConfigViewMenu::removeSlave, this, id));
        menu.addSeparator();
        menu.addAction(tr("Rename"), std::bind(&ConfigViewMenu::renameSlave, this, id));
        menu.addAction(tr("Enable"), std::bind(&ConfigViewMenu::enableSlave, this, id))->setEnabled(slave.disabled());
        menu.addAction(tr("Disable"), std::bind(&ConfigViewMenu::disableSlave, this, id))->setEnabled(slave.enabled());
        menu.addSeparator();
    }

    auto appendMenu = menu.addMenu(tr("Create"));
    for(auto const &plugin : _plugins.children(slave.type()))
    {
        auto const callBack = std::bind(&ConfigViewMenu::appendSlave, this, id, plugin->type());
        appendMenu->addAction(plugin->pixmap(), plugin->defaultName(), callBack);
    }
    appendMenu->setDisabled(appendMenu->actions().isEmpty());
}

void ConfigViewMenu::appendSlave(QUuid const &parent, QString const &type)
{
    auto const plugin = _plugins.plugin(type);
    auto const name = NameDialog::getName(plugin->defaultName(), _parent);
    if (name.isEmpty())
        return;

    Slave slave;
    slave.setParent(parent);
    slave.setId(QUuid::createUuid());
    slave.setType(type);
    slave.setName(name);
    slave.update(plugin->defaultParams());

    _corebus.send(QStringLiteral("APPEND"), QStringLiteral("core"), {
        { QStringLiteral("slave"), slave.toJson() },
    });
}

void ConfigViewMenu::removeSlave(QUuid const &id)
{
    _corebus.send(QStringLiteral("REMOVE"), QStringLiteral("core"), {
        { QStringLiteral("slave"), id }
    });
}

void ConfigViewMenu::renameSlave(QUuid const &id)
{
    auto const name = NameDialog::getName(_config.slave(id).name(), _parent);
    if (!name.isEmpty())
    {
        _corebus.send(QStringLiteral("RENAME"), QStringLiteral("core"), {
            { QStringLiteral("slave"), id }, { QStringLiteral("name"), name },
        });
    }
}

void ConfigViewMenu::enableSlave(QUuid const &id)
{
    _corebus.send(QStringLiteral("ENABLE"), QStringLiteral("core"), {
        { QStringLiteral("slave"), id },
    });
}

void ConfigViewMenu::disableSlave(QUuid const &id)
{
    _corebus.send(QStringLiteral("DISABLE"), QStringLiteral("core"), {
        { QStringLiteral("slave"), id },
    });
}
