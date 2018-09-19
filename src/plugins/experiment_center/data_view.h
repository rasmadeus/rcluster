#ifndef DATA_VIEW_H
#define DATA_VIEW_H

#include <QTabWidget>

class Config;
class Plugins;
class Slave;

class DataView : public QWidget
{
    Q_OBJECT

public:
    explicit DataView(Config const &config, Plugins const &plugins, QWidget &parent);

public:
    void onSetup(Slave const &slave);
    void appendTab();
    void appendDeviceView(QUuid const &id, QString const &type);
    void arrangeTile();
    void arrangeCascade();

private:
    void removeTab(int index);
    void updateTabTitles();
    QString makeTabText(int i) const { return tr("Devices' data %1").arg(i + 1); }

private:
    Config const &_config;
    Plugins const &_plugins;
    QTabWidget _tabs;
};

#endif // DATA_VIEW_H
