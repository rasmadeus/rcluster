#include <limits>
#include <QFormLayout>
#include <globals.h>
#include "ntp_client_editor.h"

NtpClientEditor::NtpClientEditor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent)
    : DefaultBaseEditor{ config, plugins, socket, id, parent }
{
    _port.setRange(1, 65535);
    _updateInterval.setRange(1, std::numeric_limits<int>::max());

    auto mainLayout = new QFormLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addRow(tr("NTP host:"), &_host);
    mainLayout->addRow(tr("NTP port:"), &_port);
    mainLayout->addRow(tr("Update interval, sec:"), &_updateInterval);
}

QVariantHash NtpClientEditor::params() const
{
    return {
        { QStringLiteral("host"), _host.text() },
        { QStringLiteral("port"), _port.value() },
        { QStringLiteral("sync_time_sec"), _updateInterval.value() },
    };
}

void NtpClientEditor::setParams(QVariantHash const &params)
{
    _host.setText(params.value(QStringLiteral("host")).toString());
    _port.setValue(params.value(QStringLiteral("port")).toInt());
    _updateInterval.setValue(params.value(QStringLiteral("sync_time_sec")).toInt());
}
