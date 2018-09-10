#ifndef WEB_CAMERA_EDITOR_H
#define WEB_CAMERA_EDITOR_H

#include <data_combo_box.h>
#include <default_base_editor.h>

class Message;

class WebCameraEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit WebCameraEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;
    QStringList errors() const override;

public:
    void fill(Message const &message);

private:
    DataComboBox _camerasComboBox;
};

#endif // WEB_CAMERA_EDITOR_H
