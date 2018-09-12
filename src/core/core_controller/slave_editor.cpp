#include <QMessageBox>
#include <QVBoxLayout>
#include <globals.h>
#include <config.h>
#include <core_bus.h>
#include <editor.h>
#include <plugins.h>
#include <slave_as_params.h>
#include "slave_editor.h"

SlaveEditor::SlaveEditor(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent)
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

    connect(&_apply, &QPushButton::clicked, this, &SlaveEditor::apply);
    connect(&_cancel, &QPushButton::clicked, this, &SlaveEditor::cancel);
    connect(&_default, &QPushButton::clicked, this, &SlaveEditor::reserve);
}

void SlaveEditor::select(QUuid const &id)
{
    auto const slave = _config.slave(id);

    clear();

    _id = id;
    _editor = _plugins.plugin(slave.type())->editor({ id, _config, _plugins, _corebus }, *this);
    _editorLayout.addWidget(_editor);

    cancel();
}

void SlaveEditor::clear()
{
    if (_editor)
    {
        _editorLayout.removeWidget(_editor);
        _editor->deleteLater();
        _editor = nullptr;
    }

    _id = QUuid{};
}

void SlaveEditor::apply()
{
    Q_ASSERT(_editor != nullptr);

    auto const errors = _editor->errors();
    if (!errors.isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), errors.join('\n'));
        return;
    }

    _corebus.send(QStringLiteral("UPDATE"), QStringLiteral("core"), {
        { QStringLiteral("slave"), _id },
        { QStringLiteral("params"), _editor->params() },
        { QStringLiteral("slave_as_params"), SlaveAsParams{ _editor->slaveAsParams() }.toJson() },
    });
}

void SlaveEditor::cancel()
{
    Q_ASSERT(_editor != nullptr);

    auto const slave = _config.slave(_id);
    _editor->setParams(slave.params());
    _editor->setSlaveAsParams(slave.slaveAsParams());
}

void SlaveEditor::reserve()
{
    Q_ASSERT(_editor != nullptr);

    auto const slave = _config.slave(_id);
    _editor->setParams(_plugins.plugin(slave.type())->defaultParams());
    _editor->setSlaveAsParams({});
}
