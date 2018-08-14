#include <QFormLayout>
#include <globals.h>
#include <config.h>
#include <core_bus.h>
#include <message.h>
#include "web_camera_editor.h"

WebCameraEditor::WebCameraEditor(QWidget &parent)
    : DefaultBaseEditor{ parent }
    , _cameras{ this }
{
    _router.handle(QStringLiteral("CAMERAS"), std::bind(&WebCameraEditor::onCameras, this, std::placeholders::_1));

    auto mainLayout = new QFormLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addRow(tr("Cameras:"), &_cameras);
}

void WebCameraEditor::init()
{
    connect(_corebus, &Corebus::ready, this, &WebCameraEditor::onMessage);
}

QVariantHash WebCameraEditor::params() const
{
    return {
        { QStringLiteral("name"), _cameras.currentData() },
    };
}

void WebCameraEditor::setParams(QVariantHash const &params)
{
    Q_UNUSED(params)
    auto const id = _config->parent(_id, QStringLiteral("COMPUTER"));
    _corebus->send(QStringLiteral("GET_CAMERAS"), id.toString());
}

void WebCameraEditor::onMessage(Message const &message)
{
    _router.route(message);
}

void WebCameraEditor::onCameras(Message const &message)
{
    _cameras.clear();
    _cameras.addItem(tr("Don't use"), QString{});

    for(auto const value : message.param(QStringLiteral("cameras")).toJsonArray())
    {
        auto const camera = value.toObject();
        _cameras.addItem(camera.value(QStringLiteral("desc")).toString(), camera.value(QStringLiteral("name")).toString());
    }

    auto const name = _config->slave(_id).param(QStringLiteral("name"));
    _cameras.setCurrentIndex(std::max(0, _cameras.findData(name)));
}
