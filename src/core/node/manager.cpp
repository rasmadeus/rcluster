#include <QApplication>
#include <QTimer>
#include <globals.h>
#include <plugins.h>
#include "args.h"
#include "manager.h"

Manager::Manager(Args const &args, QObject *parent)
    : QObject{ parent }
    , _args{ args }
    , _plugin{ Plugins::load(args.type) }
    , _configWatcher{ _config }
    , _corebus{ args.id }
    , _controller{ _plugin->controller(_config, *_plugin, _corebus) }
{
    Q_ASSERT(_controller != nullptr);

    QApplication::setOrganizationName(rcluster::organizationName());
    QApplication::setApplicationName(_plugin->type().toLower());

    qApp->setWindowIcon(_plugin->pixmap({ 32, 32 }));

    connect(&_config, &Config::reseted, this, &Manager::onReseted);
    connect(&_config, &Config::updated, this, &Manager::onUpdated);
    connect(&_corebus, &Corebus::ready, this, &Manager::onReady);

    QTimer::singleShot(0, this, &Manager::restoreSettings);
}

void Manager::start()
{
    _corebus.connectToHost(_args.host, _args.port);
}

void Manager::restoreSettings()
{
    _controller->restoreSettings();
}

void Manager::onReseted()
{
    _controller->onSetup(_config.node(_args.id));
}

void Manager::onUpdated(QUuid const &id)
{
    if (id == _args.id)
        onReseted();
}

void Manager::onReady(Message const &message)
{
    if (!_configWatcher.route(message))
        _controller->onMessage(message);
}
