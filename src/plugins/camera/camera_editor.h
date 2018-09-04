#ifndef CAMERA_EDITOR_H
#define CAMERA_EDITOR_H

#include <QComboBox>
#include <QLabel>
#include <default_base_editor.h>
#include <port_spin_box.h>
#include <message_router.h>

class CameraEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit CameraEditor(QWidget &parent);

public:
    void init() override;
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;

private:
    void updateUrlLabel();
    QString host() const;
    QString port() const;
    QString mountPath() const;
    QString launch() const;

private:
    QComboBox _typesComboBox;
    PortSpinBox _portSpinBox;
    QLabel _urlLabel;

};

#endif // CAMERA_EDITOR_H
