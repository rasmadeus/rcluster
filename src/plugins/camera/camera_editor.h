#ifndef CAMERA_EDITOR_H
#define CAMERA_EDITOR_H

#include <QLabel>
#include <QStackedWidget>
#include <default_base_editor.h>
#include <data_combo_box.h>
#include <port_spin_box.h>
#include <message_router.h>
#include "web_camera_editor.h"

class CameraEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit CameraEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;
    QStringList errors() const override;

private:
    void onMessage(Message const &message);

private:
    void onTypeChanged();
    void buildRtspUrl();

private:
    DataComboBox _typeComboBox;
    PortSpinBox _portSpinBox;
    QLabel _rtspServerLabel;
    QStackedWidget _paramsWidgets;
    DefaultBaseEditor _fakeCameraEditor;
    WebCameraEditor _webCameraEditor;
    MessageRouter _router;
};

#endif // CAMERA_EDITOR_H
