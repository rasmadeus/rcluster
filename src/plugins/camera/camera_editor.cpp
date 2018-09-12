#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <globals.h>
#include <config.h>
#include <core_bus.h>
#include <video_source_type.h>
#include "camera_editor.h"

CameraEditor::CameraEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
    , _fakeCameraEditor{ data, _paramsWidgets }
    , _webCameraEditor{ data, _paramsWidgets }
{
    _typeComboBox.addItem(tr("Fake camera"), QVariant::fromValue(VideoSourceType::FakeCamera));
    _typeComboBox.addItem(tr("Web camera"), QVariant::fromValue(VideoSourceType::WebCamera));

    _paramsWidgets.addWidget(&_fakeCameraEditor);
    _paramsWidgets.addWidget(&_webCameraEditor);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    auto controlsLayout = new QGridLayout{};
    controlsLayout->setMargin(0);
    controlsLayout->setSpacing(rcluster::layoutGap());
    controlsLayout->addWidget(new QLabel{ tr("Video source:"), this }, 0, 0);
    controlsLayout->addWidget(&_typeComboBox, 0, 1);
    controlsLayout->addWidget(new QLabel{ tr("Rtsp server port:"), this }, 1, 0);
    controlsLayout->addWidget(&_portSpinBox, 1, 1);
    controlsLayout->addWidget(&_paramsWidgets, 2, 0, 2, 0);
    controlsLayout->setColumnStretch(0, 1);
    controlsLayout->setColumnStretch(1, 3);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addSpacerItem(new QSpacerItem{ 0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding });

    connect(&_typeComboBox, static_cast<void(DataComboBox::*)(int)>(&DataComboBox::currentIndexChanged), this, &CameraEditor::onTypeChanged);

    _router.handle(QStringLiteral("CAMERAS"), std::bind(&WebCameraEditor::fill, &_webCameraEditor, std::placeholders::_1));
    connect(&_corebus, &Corebus::ready, this, &CameraEditor::onMessage);

    auto computer = _config.parent(_id, QStringLiteral("COMPUTER"));
    _corebus.send(QStringLiteral("GET_CAMERAS"), computer.toString());
}

QVariantHash CameraEditor::params() const
{
    auto params = static_cast<Editor*>(_paramsWidgets.currentWidget())->params();
    params[QStringLiteral("type")] = _typeComboBox.currentData().toInt();
    params[QStringLiteral("port")] = _portSpinBox.value();
    return params;
}

void CameraEditor::setParams(QVariantHash const &params)
{
    _typeComboBox.setIndex(params.value(QStringLiteral("type")));
    static_cast<Editor*>(_paramsWidgets.currentWidget())->setParams(params);
    _portSpinBox.setValue(params.value(QStringLiteral("port")).toInt());
}

QStringList CameraEditor::errors() const
{
    auto errors = static_cast<Editor*>(_paramsWidgets.currentWidget())->errors();
    auto id = _config.findLocalParam(_id, QStringLiteral("port"), _portSpinBox.value());
    if (!id.isNull())
        errors << tr("Port %1 is already in use.").arg(_portSpinBox.value());
    return errors;
}

void CameraEditor::onMessage(Message const &message)
{
    _router.route(message);
}

void CameraEditor::onTypeChanged()
{
    auto const type = _typeComboBox.currentData().value<VideoSourceType>();
    switch(type)
    {
        case VideoSourceType::FakeCamera: _paramsWidgets.setCurrentWidget(&_fakeCameraEditor); break;
        case VideoSourceType::WebCamera: _paramsWidgets.setCurrentWidget(&_webCameraEditor); break;
    }
}
