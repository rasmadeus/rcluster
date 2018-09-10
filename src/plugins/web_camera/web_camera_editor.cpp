#include <QFormLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <globals.h>
#include <config.h>
#include <core_bus.h>
#include <message.h>
#include "web_camera_editor.h"

WebCameraEditor::WebCameraEditor(QWidget &parent)
    : DefaultBaseEditor{ parent }
    , _cameras{ this }
{
    _cameras.addItem(tr("No data"));
    _cameras.setEnabled(false);

    _router.handle(QStringLiteral("CAMERAS"), std::bind(&WebCameraEditor::onCameras, this, std::placeholders::_1));

    auto mainLayout = new QFormLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);
    mainLayout->addRow(tr("Cameras:"), &_cameras);
}

void WebCameraEditor::init()
{
    connect(_corebus, &Corebus::ready, this, &WebCameraEditor::onMessage);

    auto computer = _config->parent(_id, QStringLiteral("COMPUTER"));
    _corebus->send(QStringLiteral("GET_CAMERAS"), computer.toString());
}

QVariantHash WebCameraEditor::params() const
{
    return {
        { QStringLiteral("device_desc"), _cameras.currentData() },
    };
}

void WebCameraEditor::setParams(QVariantHash const &params)
{
    Q_UNUSED(params)
}

void WebCameraEditor::onMessage(Message const &message)
{
    _router.route(message);
}

void WebCameraEditor::onCameras(Message const &message)
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

QStringList WebCameraEditor::errors() const
{
    QStringList errors;
    auto const computerId = _config->parent(_id, QStringLiteral("COMPUTER"));
    for(auto const &id : _config->descendants(computerId, QStringLiteral("WEB_CAMERA")))
    {
        auto const slave = _config->slave(id);
        auto const deviceDesc = slave.param(QStringLiteral("device_desc"));
        if (!deviceDesc.isValid())
            continue;

        if (deviceDesc == _cameras.currentData())
        {
            errors << tr("Camera \"%1\" has been already selected.").arg(deviceDesc.toString());
            break;
        }
    }
    return errors;
}
