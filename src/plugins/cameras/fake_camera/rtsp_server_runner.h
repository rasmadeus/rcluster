#ifndef RTSP_SERVER_RUNNER_H
#define RTSP_SERVER_RUNNER_H

#include <atomic>
#include <QThread>

class RtspServerRunner : public QThread
{
    Q_OBJECT

public:
    explicit RtspServerRunner(QString const &host, QString const &mountPath, QString const &launch, QObject *parent = nullptr);

public:
    bool isStopped() const { return _stop; }
    void stop() { _stop = true; }

protected:
    void run() override;

private:
    std::atomic<bool> _stop{ false };
    QString const _host;
    QString const _mountPath;
    QString const _launch;
};

#endif // RTSP_SERVER_RUNNER_H
