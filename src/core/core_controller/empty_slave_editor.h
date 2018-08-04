#ifndef EMPTY_SLAVE_EDITOR_H
#define EMPTY_SLAVE_EDITOR_H

#include <QLabel>
#include <QWidget>

class EmptySlaveEditor : public QWidget
{
    Q_OBJECT

public:
    explicit EmptySlaveEditor(QWidget &parent);

private:
    QLabel _info;
};

#endif // EMPTY_SLAVE_EDITOR_H
