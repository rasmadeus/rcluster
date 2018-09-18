#ifndef DATA_VIEW_H
#define DATA_VIEW_H

#include <QTabWidget>

class Config;

class DataView : public QWidget
{
    Q_OBJECT

public:
    explicit DataView(Config const &config, QWidget &parent);

public:
    void appendTab();
    void appendDeviceView(QUuid const &id, QString const &type);

private:
    void removeTab(int index);
    void updateTabTitles();
    QString makeTabText(int i) const { return tr("Devices' data %1").arg(i + 1); }

private:
    Config const &_config;
    QTabWidget _tabs;
};

#endif // DATA_VIEW_H
