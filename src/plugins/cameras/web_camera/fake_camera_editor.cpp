#include <QFormLayout>
#include <globals.h>
#include <config.h>
#include <core_bus.h>
#include <message.h>
#include "fake_camera_editor.h"

FakeCameraEditor::FakeCameraEditor(QWidget &parent)
    : DefaultBaseEditor{ parent }
    , _cameras{ this }
{
    _router.handle(QStringLiteral("CAMERAS"), std::bind(&FakeCameraEditor::onCameras, this, std::placeholders::_1));

    auto mainLayout = new QFormLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addRow(tr("Cameras:"), &_cameras);
}

void FakeCameraEditor::init()
{
    connect(_corebus, &Corebus::ready, this, &FakeCameraEditor::onMessage);
}

QVariantHash FakeCameraEditor::params() const
{
    return {
        { QStringLiteral("name"), _cameras.currentData() },
    };
}

void FakeCameraEditor::setParams(QVariantHash const &params)
{
    Q_UNUSED(params)
    auto const id = _config->parent(_id, QStringLiteral("COMPUTER"));
    _corebus->send(QStringLiteral("GET_CAMERAS"), id.toString());
}

void FakeCameraEditor::onMessage(Message const &message)
{
    _router.route(message);
}

void FakeCameraEditor::onCameras(Message const &message)
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
