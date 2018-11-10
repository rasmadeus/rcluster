#include <QMessageBox>
#include <QVBoxLayout>
#include <globals.h>
#include <config.h>
#include <corebus.h>
#include <editor.h>
#include <plugins.h>
#include "node_editor.h"

NodeEditor::NodeEditor(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent)
    : QWidget{ &parent }
    , _config{ config }
    , _plugins{ plugins }
    , _corebus{ corebus }
    , _apply{ tr("Apply"), this }
    , _cancel{ tr("Cancel"), this }
    , _default{ tr("Default"), this }
{
    _editorLayout.setMargin(0);
    _editorLayout.setSpacing(0);

    auto buttonsLayout = new QHBoxLayout{};
    buttonsLayout->setMargin(0);
    buttonsLayout->setSpacing(rcluster::layoutGap());
    buttonsLayout->addSpacerItem(new QSpacerItem{ 0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum });
    buttonsLayout->addWidget(&_apply);
    buttonsLayout->addWidget(&_cancel);
    buttonsLayout->addWidget(&_default);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addLayout(&_editorLayout);
    mainLayout->addSpacerItem(new QSpacerItem{ 0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum });
    mainLayout->addLayout(buttonsLayout);

    connect(&_apply, &QPushButton::clicked, this, &NodeEditor::apply);
    connect(&_cancel, &QPushButton::clicked, this, &NodeEditor::cancel);
    connect(&_default, &QPushButton::clicked, this, &NodeEditor::reserve);
}

void NodeEditor::select(QUuid const &id)
{
    auto const node = _config.node(id);

    clear();

    _id = id;
    _editor = _plugins.plugin(node.type())->editor({ id, _config, _plugins, _corebus }, *this);
    _editorLayout.addWidget(_editor);

    cancel();
}

void NodeEditor::clear()
{
    if (_editor)
    {
        _editorLayout.removeWidget(_editor);
        _editor->deleteLater();
        _editor = nullptr;
    }

    _id = QUuid{};
}

void NodeEditor::apply()
{
    Q_ASSERT(_editor != nullptr);

    auto const errors = _editor->errors();
    if (!errors.isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), errors.join('\n'));
        return;
    }

    _corebus.send(QStringLiteral("UPDATE"), QStringLiteral("core"), {
        { QStringLiteral("node"), _id },
        { QStringLiteral("params"), _editor->params() },
    });
}

void NodeEditor::cancel()
{
    Q_ASSERT(_editor != nullptr);

    auto const node = _config.node(_id);
    _editor->setParams(node.params());
}

void NodeEditor::reserve()
{
    Q_ASSERT(_editor != nullptr);

    auto const node = _config.node(_id);
    _editor->setParams(_plugins.plugin(node.type())->defaultParams());
}
