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

Editor *NtpClientPlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new NtpClientEditor{ data, parent };
}

std::unique_ptr<NodeController> NtpClientPlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    return std::make_unique<Controller>(config, plugin, corebus);
}
