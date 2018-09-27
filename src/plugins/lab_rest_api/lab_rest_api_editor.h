#ifndef LAB_REST_API_EDITOR_H
#define LAB_REST_API_EDITOR_H

#include <pass_line_edit.h>
#include <default_base_editor.h>

class LabRestApiEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit LabRestApiEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;
    QStringList errors() const override;

private:
    QLineEdit _host;
    QLineEdit _username;
    PassLineEdit _password;
};

#endif // LAB_REST_API_EDITOR_H
