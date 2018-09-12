#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QGridLayout>
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

    auto mainLayout = new QGridLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(new QLabel{ tr("Cameras:"), this }, 0, 0);
    mainLayout->addWidget(&_camerasComboBox, 0, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 3);
}

QVariantHash WebCameraEditor::params() const
{
    return {
        { QStringLiteral("params"), QVariantHash{ { QStringLiteral("device_index"), _camerasComboBox.currentData() }, } }
    };
}

void WebCameraEditor::setParams(QVariantHash const &params)
{
    _camerasComboBox.setIndex(params.value(QStringLiteral("device_desc")));
}

QStringList WebCameraEditor::errors() const
{
    QStringList errors;
    auto const dublicateId = _config.findLocalParam(_id, QStringLiteral("device_desc"), _camerasComboBox.currentData());
    if (!dublicateId.isNull())
        errors << tr("Camera \"%1\" has been already selected at %2.").arg(dublicateId.toString()).arg(_config.slave(dublicateId).name());
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
        auto const index = object.value(QStringLiteral("device_index"));
        _camerasComboBox.addItem(desc.toString(), index);
    }

    _camerasComboBox.setEnabled(_camerasComboBox.count() > 1);

    auto deviceIndex = _config.slave(_id).param(QStringLiteral("device_index"));
    _camerasComboBox.setIndex(deviceIndex);
}
