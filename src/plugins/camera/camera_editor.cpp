#include <QFormLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <globals.h>
#include <config.h>
#include <core_bus.h>
#include <message.h>
#include "camera_editor.h"
#include "video_source_type.h"

CameraEditor::CameraEditor(QWidget &parent)
    : DefaultBaseEditor{ parent }
    , _cameras{ this }
{
    _cameras.addItem(tr("No data"));
    _cameras.setEnabled(false);

    _router.handle(QStringLiteral("CAMERAS"), std::bind(&CameraEditor::onCameras, this, std::placeholders::_1));

    auto mainLayout = new QFormLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);
    mainLayout->addRow(tr("Cameras:"), &_cameras);
}

void CameraEditor::init()
{
    connect(_corebus, &Corebus::ready, this, &CameraEditor::onMessage);

    auto computer = _config->parent(_id, QStringLiteral("COMPUTER"));
    _corebus->send(QStringLiteral("GET_CAMERAS"), computer.toString());
}

QVariantHash CameraEditor::params() const
{
    return {
        { QStringLiteral("device_desc"), _cameras.currentData() },
    };
}

void CameraEditor::setParams(QVariantHash const &params)
{
    Q_UNUSED(params)
}

void CameraEditor::onMessage(Message const &message)
{
    _router.route(message);
}

void CameraEditor::onCameras(Message const &message)
{
    _cameras.clear();
    _cameras.addItem(tr("Don't use"));

    for(auto value : message.param(QStringLiteral("cameras")).toJsonArray())
    {
        auto const object = value.toObject();
        auto const desc = object.value(QStringLiteral("desc"));
        _cameras.addItem(desc.toString(), desc);
    }

    _cameras.setEnabled(_cameras.count() > 1);

    auto deviceDesc = _config->slave(_id).param(QStringLiteral("device_desc"));
    _cameras.setCurrentIndex(std::max(0, _cameras.findData(deviceDesc)));
}

QStringList CameraEditor::errors() const
{
    QStringList errors;
    for(auto const &id : _config->siblings(_id))
    {
        auto const slave = _config->slave(id);
        auto const deviceDesc = slave.param(QStringLiteral("device_desc"));
        if (!deviceDesc.isValid())
            continue;

        if (deviceDesc == _cameras.currentData())
        {
            errors << tr("Camera \"%1\" has been already selected at \"%2\".").arg(deviceDesc.toString()).arg(slave.name());
            break;
        }
    }
    return errors;
}
