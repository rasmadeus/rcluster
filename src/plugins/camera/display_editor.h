#ifndef DISPLAY_EDITOR_H
#define DISPLAY_EDITOR_H

#include <data_combo_box.h>
#include <default_base_editor.h>

class Message;

class DisplayEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit DisplayEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;
    QStringList errors() const override;

public:
    void fill(Message const &message);

private:
    DataComboBox _displayComboBox;
};
#endif // DISPLAY_EDITOR_H
