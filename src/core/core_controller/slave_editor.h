#ifndef SLAVE_EDITOR_H
#define SLAVE_EDITOR_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QUuid>

class Config;
class CoreClientSocket;
class Editor;
class Plugins;

class SlaveEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SlaveEditor(Config &config, Plugins &plugins, CoreClientSocket &socket, QWidget &parent);

public:
    void select(QUuid const &id);
    void clear();

private:
    void apply();
    void cancel();
    void reserve();

private:
    QUuid _id;
    Config &_config;
    Plugins &_plugins;
    CoreClientSocket &_socket;

    Editor *_editor{ nullptr };
    QHBoxLayout _editorLayout;
    QPushButton _apply;
    QPushButton _cancel;
    QPushButton _default;
};

#endif // SLAVE_EDITOR_H
