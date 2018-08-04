#include "controller.h"
#include "ntp_client_plugin.h"
#include "ntp_client_editor.h"

QVariantHash NtpClientPlugin::defaultParams() const
{
    return {
        { QStringLiteral("host"), QStringLiteral("pool.ntp.org") },
        { QStringLiteral("port"), 123 },
        { QStringLiteral("sync_time_sec"), 1800 },
    };
}

Editor *NtpClientPlugin::editor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent) const
{
    return new NtpClientEditor{ config, plugins, socket, id, parent };
}

std::unique_ptr<SlaveController> NtpClientPlugin::controller(Config const &config, Plugin const &plugin, CoreClientSocket &socket) const
{
    return std::unique_ptr<SlaveController>(new Controller{ config, plugin, socket });
}
