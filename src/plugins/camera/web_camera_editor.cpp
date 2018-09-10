#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFormLayout>
#include <config.h>
#include <editor_data.h>
#include <globals.h>
#include <message.h>
#include "web_camera_editor.h"

WebCameraEditor::WebCameraEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
{
    _camerasComboBox.addItem(tr("No data"));
    _camerasComboBox.setEnabled(false);

    auto mainLayout = new QFormLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addRow(tr("Cameras:"), &_camerasComboBox);
}

QVariantHash WebCameraEditor::params() const
{
    return {
        { QStringLiteral("device_desc"), _camerasComboBox.currentData() },
    };
}

void WebCameraEditor::setParams(QVariantHash const &params)
{
    _camerasComboBox.setIndex(params.value(QStringLiteral("device_desc")));
}

QStringList WebCameraEditor::errors() const
{
    QStringList errors;
    auto const dublicateId = _data.config.findLocalParam(_data.id, QStringLiteral("device_desc"), _camerasComboBox.currentData());
    if (!dublicateId.isNull())
        errors << tr("Camera \"%1\" has been already selected at %2.").arg(dublicateId.toString()).arg(_data.config.slave(dublicateId).name());
    return errors;
}

void WebCameraEditor::fill(Message const &message)
{
    _camerasComboBox.clear();
    _camerasComboBox.addItem(tr("Don't use"));

    for(auto value : message.param(QStringLiteral("cameras")).toJsonArray())
    {
        auto const object = value.toObject();
        auto const desc = object.value(QStringLiteral("desc"));
        _camerasComboBox.addItem(desc.toString(), desc);
    }

    _camerasComboBox.setEnabled(_camerasComboBox.count() > 1);

    auto deviceDesc = _data.config.slave(_data.id).param(QStringLiteral("device_desc"));
    _camerasComboBox.setIndex(deviceDesc);
}
