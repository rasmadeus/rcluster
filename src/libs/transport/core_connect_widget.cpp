#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSettings>
#include <globals.h>
#include "core_bus.h"
#include "core_connect_widget.h"

CoreConnectWidget::CoreConnectWidget(Corebus &corebus, QWidget *parent)
    : QDialog{ parent }
    , _corebus{ corebus }
{
    setWindowTitle(tr("Connect to core"));

    _statusLabel = new QLabel{ this };

    _statusLabel = new QLabel{ this };
    _hostLineEdit = new QLineEdit{ this };

    _portSpinBox = new QSpinBox{ this };
    _portSpinBox->setRange(1, 65535);

    _connectButton = new QPushButton{ tr("Connect"), this };

    _disconnectButton = new QPushButton{ tr("Disconnect"), this };
    _disconnectButton->setEnabled(false);

    auto buttonsLayout = new QHBoxLayout{};
    buttonsLayout->setMargin(0);
    buttonsLayout->setSpacing(rcluster::layoutGap());
    buttonsLayout->addWidget(_connectButton);
    buttonsLayout->addWidget(_disconnectButton);

    auto editsLayout = new QFormLayout{};
    editsLayout->setMargin(0);
    editsLayout->setSpacing(rcluster::layoutGap());
    editsLayout->addRow(tr("Status:"), _statusLabel);
    editsLayout->addRow(tr("Host:"), _hostLineEdit);
    editsLayout->addRow(tr("Port:"), _portSpinBox);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(rcluster::layoutGap());
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addLayout(editsLayout);
    mainLayout->addLayout(buttonsLayout);

    connect(_connectButton, &QPushButton::clicked, this, &CoreConnectWidget::connectToHost);
    connect(_disconnectButton, &QPushButton::clicked, this, &CoreConnectWidget::disconnectFromHost);
    connect(&_corebus, &Corebus::connected, this, &CoreConnectWidget::onCorebusConnected);
    connect(&_corebus, &Corebus::disconnected, this, &CoreConnectWidget::onCorebusDisconnected);

    resize(250, 120);

    restoreSettings();
    connectToHost();
}

void CoreConnectWidget::connectToHost()
{
    _corebus.connectToHost(_hostLineEdit->text(), static_cast<quint16>(_portSpinBox->value()));
}

void CoreConnectWidget::disconnectFromHost()
{
    _corebus.disconnectFromHost();
}

void CoreConnectWidget::storeSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("socket_connect_widget"));
    settings.setValue(QStringLiteral("host"), _hostLineEdit->text());
    settings.setValue(QStringLiteral("port"), _portSpinBox->value());
    settings.endGroup();
}

void CoreConnectWidget::restoreSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("socket_connect_widget"));
    _hostLineEdit->setText(settings.value(QStringLiteral("host"), QStringLiteral("127.0.0.1")).toString());
    _portSpinBox->setValue(settings.value(QStringLiteral("port"), rcluster::corePort()).toInt());
    settings.endGroup();
}

void CoreConnectWidget::onCorebusConnected()
{
    _statusLabel->setText(tr("connected."));
    _connectButton->setEnabled(false);
    _disconnectButton->setEnabled(true);
    storeSettings();
}

void CoreConnectWidget::onCorebusDisconnected()
{
    _statusLabel->setText(tr("disconnected."));
    _connectButton->setEnabled(true);
    _disconnectButton->setEnabled(false);
}
