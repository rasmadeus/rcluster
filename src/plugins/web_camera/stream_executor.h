#ifndef STREAM_EXECUTOR_H
#define STREAM_EXECUTOR_H

#include <QThread>

class StreamExecutor : public QThread
{
    Q_OBJECT

public:
    explicit StreamExecutor(QString const &name, QObject *parent = nullptr);

protected:
    void run();

private:
    QString _name;
};

#endif // STREAM_EXECUTOR_H
