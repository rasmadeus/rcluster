#ifndef DEVICES_DATA_VIEW_H
#define DEVICES_DATA_VIEW_H

#include <QMdiArea>

class Config;
class Plugins;
class Slave;

class DevicesDataView : public QMdiArea
{
    Q_OBJECT

public:
    explicit DevicesDataView(Config const &config, Plugins const &plugins, QWidget &parent);

public:
    void onSetup(Slave const &slave);
    void appendView(QUuid const &id, QString const &type);

private:
    QWidget *make(QUuid const &id, QString const &type, QWidget &parent) const;

private:
    Config const &_config;
    Plugins const &_plugins;
};

#endif // DEVICES_DATA_VIEW_H
