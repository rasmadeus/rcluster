#include <QFormLayout>
#include <QVBoxLayout>
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
    _typeComboBox.addItem(tr("Fake camera"), QVariant::fromValue(VideoSourceType::Fake));
    _typeComboBox.addItem(tr("Web camera"), QVariant::fromValue(VideoSourceType::WebCamera));

    _paramsWidgets.addWidget(&_fakeCameraEditor);
    _paramsWidgets.addWidget(&_webCameraEditor);

    auto commonLayout = new QFormLayout{};
    commonLayout->setMargin(0);
    commonLayout->setSpacing(rcluster::layoutGap());
    commonLayout->addRow(tr("Video source:"), &_typeComboBox);
    commonLayout->addRow(tr("Rtsp server port:"), &_portSpinBox);
    commonLayout->addRow(tr("Rtsp url:"), &_rtspServerLabel);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addLayout(commonLayout);
    mainLayout->addWidget(&_paramsWidgets);

    connect(&_typeComboBox, static_cast<void(DataComboBox::*)(int)>(&DataComboBox::currentIndexChanged), this, &CameraEditor::onTypeChanged);
    connect(&_portSpinBox, static_cast<void(PortSpinBox::*)(int)>(&PortSpinBox::valueChanged), this, &CameraEditor::buildRtspUrl);

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
        case VideoSourceType::Fake: _paramsWidgets.setCurrentWidget(&_fakeCameraEditor); break;
        case VideoSourceType::WebCamera: _paramsWidgets.setCurrentWidget(&_webCameraEditor); break;
    }
}

void CameraEditor::buildRtspUrl()
{
    auto const computerId = _config.parent(_id, QStringLiteral("COMPUTER"));
    auto const computerIp = _config.slave(computerId).param(QStringLiteral("ip")).toString();
    auto const mountPath = _id.toString();
    _rtspServerLabel.setText(QStringLiteral("rtsp://%1:%2/%3").arg(computerIp).arg(_portSpinBox.value()).arg(mountPath));
}
