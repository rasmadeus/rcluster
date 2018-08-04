#ifndef CORE_CONNECT_WIDGET_H
#define CORE_CONNECT_WIDGET_H

#include <QDialog>
#include <transport_global.h>

class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class CoreClientSocket;

class TRANSPORT_SHARED_EXPORT CoreConnectWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CoreConnectWidget(CoreClientSocket &socket, QWidget *parent = nullptr);

private:
    void connectToHost();
    void disconnectFromHost();
    void storeSettings();
    void restoreSettings();
    void onSocketConnected();
    void onSocketDisconnected();

private:
    CoreClientSocket &_socket;
    QLabel *_statusLabel;
    QLineEdit *_hostLineEdit;
    QSpinBox *_portSpinBox;
    QPushButton *_connectButton;
    QPushButton *_disconnectButton;
};

#endif // CORE_CONNECT_WIDGET_H
