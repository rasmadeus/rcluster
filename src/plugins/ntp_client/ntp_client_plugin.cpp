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

Editor *NtpClientPlugin::editor(QWidget &parent) const
{
    return new NtpClientEditor{ parent };
}

std::unique_ptr<SlaveController> NtpClientPlugin::controller() const
{
    return std::make_unique<Controller>();
}
