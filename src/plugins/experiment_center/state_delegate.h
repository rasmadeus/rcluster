#ifndef STATE_DELEGATE_H
#define STATE_DELEGATE_H

#include <QStyledItemDelegate>

class Config;

class StateDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit StateDelegate(Config const &config, QObject &parent);

public:
    void paint(QPainter *painter, QStyleOptionViewItem const &option, QModelIndex const &index) const override;

private:
    Config const &_config;
};

#endif // STATE_DELEGATE_H
