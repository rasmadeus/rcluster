#ifndef NTP_CLIENT_EDITOR_H
#define NTP_CLIENT_EDITOR_H

#include <QLineEdit>
#include <QSpinBox>
#include <default_base_editor.h>

class NtpClientEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit NtpClientEditor(QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;

private:
    QLineEdit _host;
    QSpinBox _port;
    QSpinBox _updateInterval;
};

#endif // NTP_CLIENT_EDITOR_H
