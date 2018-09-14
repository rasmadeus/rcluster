#ifndef DATA_VIEW_H
#define DATA_VIEW_H

#include <QTabWidget>

class DataView : public QWidget
{
    Q_OBJECT

public:
    explicit DataView(QWidget *parent = nullptr);

private:
    QTabWidget _tabs;
};

#endif // DATA_VIEW_H
