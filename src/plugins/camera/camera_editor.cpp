#include <rtsp_server.h>
#include <QFormLayout>
#include <globals.h>
#include <config.h>
#include <core_bus.h>
#include <message.h>
#include "camera_editor.h"
#include "video_source_type.h"

CameraEditor::CameraEditor(QWidget &parent)
    : DefaultBaseEditor{ parent }
    , _typesComboBox{ this }
    , _portSpinBox{ this }
    , _urlLabel{ this }
{
    _typesComboBox.addItem(tr("Fake camera"), QVariant::fromValue(VideoSourceType::Fake));

    auto mainLayout = new QFormLayout{ this };
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->setMargin(0);

    mainLayout->addRow(tr("Camera type:"), &_typesComboBox);
    mainLayout->addRow(tr("Server port:"), &_portSpinBox);
    mainLayout->addRow(tr("Server url:"), &_urlLabel);
}

void CameraEditor::init()
{
    connect(&_portSpinBox, static_cast<void(PortSpinBox::*)(int)>(&PortSpinBox::valueChanged), this, &CameraEditor::updateUrlLabel);
}

QVariantHash CameraEditor::params() const
{
    return {
        { QStringLiteral("type"), _typesComboBox.currentData() },
        { QStringLiteral("host"), host() },
        { QStringLiteral("port"), port() },
        { QStringLiteral("mount_path"), mountPath() },
        { QStringLiteral("launch"), launch() },
    };
}

void CameraEditor::setParams(QVariantHash const &params)
{
    auto const type = params.value(QStringLiteral("type"));
    _typesComboBox.setCurrentIndex(std::max(0, _typesComboBox.findData(type)));

    auto const port = params.value(QStringLiteral("port"));
    _portSpinBox.setValue(params.value(QStringLiteral("port")).toInt());

    updateUrlLabel();
}

void CameraEditor::updateUrlLabel()
{
    _urlLabel.setText(RtspServer::url(host(), port(), mountPath()));
}

QString CameraEditor::host() const
{
    auto const computerId = _config->parent(_id, QStringLiteral("COMPUTER"));
    return _config->slave(computerId).param(QStringLiteral("ip")).toString();
}

QString CameraEditor::port() const
{
    return QString::number(_portSpinBox.value());
}

QString CameraEditor::mountPath() const
{
    return RtspServer::mountPath(_id);
}

QString CameraEditor::launch() const
{
    switch (_typesComboBox.currentData().value<VideoSourceType>())
    {
        case VideoSourceType::Fake: return QStringLiteral("( videotestsrc is-live=1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
    }
}
