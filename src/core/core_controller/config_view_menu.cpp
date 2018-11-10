#include <QMenu>
#include <config.h>
#include <corebus.h>
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
    auto node = _config.node(id);

    if (!id.isNull())
    {
        menu.addAction(tr("Remove"), std::bind(&ConfigViewMenu::removeNode, this, id));
        menu.addSeparator();
        menu.addAction(tr("Rename"), std::bind(&ConfigViewMenu::renameNode, this, id));
        menu.addAction(tr("Enable"), std::bind(&ConfigViewMenu::enableNode, this, id))->setEnabled(node.disabled());
        menu.addAction(tr("Disable"), std::bind(&ConfigViewMenu::disableNode, this, id))->setEnabled(node.enabled());
        menu.addSeparator();
    }

    auto appendMenu = menu.addMenu(tr("Create"));
    for(auto const &plugin : _plugins.children(node.type()))
    {
        auto const callBack = std::bind(&ConfigViewMenu::appendNode, this, id, plugin->type());
        appendMenu->addAction(plugin->pixmap(), plugin->defaultName(), callBack);
    }
    appendMenu->setDisabled(appendMenu->actions().isEmpty());
}

void ConfigViewMenu::appendNode(QUuid const &parent, QString const &type)
{
    auto const plugin = _plugins.plugin(type);
    auto const name = NameDialog::getName(plugin->defaultName(), _parent);
    if (name.isEmpty())
        return;

    Node node;
    node.setParent(parent);
    node.setId(QUuid::createUuid());
    node.setType(type);
    node.setName(name);

    auto params = plugin->defaultParams();
    if (plugin->hasEditor())
        params[QStringLiteral("is_fake")] = true;
    node.setParams(std::move(params));

    _last = node.id();

    _corebus.send(QStringLiteral("APPEND"), QStringLiteral("core"), {
        { QStringLiteral("node"), node.toJson() },
    });
}

void ConfigViewMenu::removeNode(QUuid const &id)
{
    _corebus.send(QStringLiteral("REMOVE"), QStringLiteral("core"), {
        { QStringLiteral("node"), id }
    });
}

void ConfigViewMenu::renameNode(QUuid const &id)
{
    auto const name = NameDialog::getName(_config.node(id).name(), _parent);
    if (!name.isEmpty())
    {
        _corebus.send(QStringLiteral("RENAME"), QStringLiteral("core"), {
            { QStringLiteral("node"), id }, { QStringLiteral("name"), name },
        });
    }
}

void ConfigViewMenu::enableNode(QUuid const &id)
{
    _corebus.send(QStringLiteral("ENABLE"), QStringLiteral("core"), {
        { QStringLiteral("node"), id },
    });
}

void ConfigViewMenu::disableNode(QUuid const &id)
{
    _corebus.send(QStringLiteral("DISABLE"), QStringLiteral("core"), {
        { QStringLiteral("node"), id },
    });
}
