#ifndef WEB_CAMERA_EDITOR_H
#define WEB_CAMERA_EDITOR_H

#include <QComboBox>
#include <default_base_editor.h>
#include <port_spin_box.h>
#include <message_router.h>

class WebCameraEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit WebCameraEditor(QWidget &parent);

public:
    void init() override;
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;
    QStringList errors() const override;

private:
    void onMessage(Message const &message);
    void onCameras(Message const &message);

private:
    QComboBox _cameras;
    MessageRouter _router;
};

#endif // WEB_CAMERA_EDITOR_H
