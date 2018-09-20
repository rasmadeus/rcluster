#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QGridLayout>
#include <config.h>
#include <editor_data.h>
#include <globals.h>
#include <message.h>
#include "display_editor.h"

DisplayEditor::DisplayEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
{
    _displayComboBox.addItem(tr("No data"));
    _displayComboBox.setEnabled(false);

    auto mainLayout = new QGridLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(new QLabel{ tr("Displays:"), this }, 0, 0);
    mainLayout->addWidget(&_displayComboBox, 0, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 3);
}

QVariantHash DisplayEditor::params() const
{
    return {
        { QStringLiteral("display_index"), _displayComboBox.currentData() },
    };
}

void DisplayEditor::setParams(QVariantHash const &params)
{
    _displayComboBox.setIndex(params.value(QStringLiteral("display_index")));
    _displayComboBox.setEnabled(_displayComboBox.count() > 1);
}

void DisplayEditor::fill(Message const &message)
{
    _displayComboBox.clear();
    _displayComboBox.addItem(tr("Don't use"));

    for(auto value : message.param(QStringLiteral("displays")).toJsonArray())
    {
        auto const object = value.toObject();
        auto const index = object.value(QStringLiteral("display_index"));
        _displayComboBox.addItem(tr("Display: %1").arg(index.toInt()), index);
    }

    setParams(_config.slave(_id).params());
}
