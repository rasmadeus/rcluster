#include <QFormLayout>
#include <globals.h>
#include "lab_rest_api_editor.h"

LabRestApiEditor::LabRestApiEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
{
    auto mainLayout = new QFormLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addRow(tr("Host:"), &_host);
    mainLayout->addRow(tr("Username:"), &_username);
    mainLayout->addRow(tr("Password:"), &_password);
}

QVariantHash LabRestApiEditor::params() const
{
    return {
        { QStringLiteral("host"), _host.text() },
        { QStringLiteral("username"), _username.text() },
        { QStringLiteral("password"), _password.password() },
    };
}

void LabRestApiEditor::setParams(QVariantHash const &params)
{
    _host.setText(params.value(QStringLiteral("host")).toString());
    _username.setText(params.value(QStringLiteral("username")).toString());
    _password.setPassword(params.value(QStringLiteral("password")).toString());
}

QStringList LabRestApiEditor::errors() const
{
    QStringList errors;
    if (_host.text().isEmpty())
        errors << tr("Fill the host field, please.");
    if (_username.text().isEmpty())
        errors << tr("Fill the login field, please.");
    if (_password.text().isEmpty())
        errors << tr("Fill the password field, please.");
    return errors;
}
