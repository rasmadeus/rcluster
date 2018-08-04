#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <globals.h>
#include "name_dialog.h"

QString NameDialog::getName(QString const &name, QWidget &parent)
{
    NameDialog nameDialog{ name, parent };
    nameDialog.show();
    return nameDialog.exec() == QDialog::Accepted ? nameDialog.name() : QString{};
}

NameDialog::NameDialog(const QString &name, QWidget &parent)
    : QDialog{ &parent }
    , _name{ name, this }
    , _ok{ tr("Ok"), this }
    , _cancel{ tr("Cancel"), this }
{
    setWindowTitle(tr("Name dialog"));

    _name.setPlaceholderText(tr("Write down a name"));
    _name.setText(name);
    _name.selectAll();

    auto buttonsLayout = new QHBoxLayout{};
    buttonsLayout->setMargin(0);
    buttonsLayout->setSpacing(rcluster::layoutGap());
    buttonsLayout->addWidget(&_ok);
    buttonsLayout->addWidget(&_cancel);

    auto mainLayout = new QVBoxLayout{ this };
    mainLayout->setMargin(rcluster::layoutGap());
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addWidget(&_name);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addSpacerItem(new QSpacerItem{ 0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding });

    connect(&_ok, &QPushButton::clicked, this, &NameDialog::accept);
    connect(&_cancel, &QPushButton::clicked, this, &NameDialog::reject);

    resize(200, 61);
}
