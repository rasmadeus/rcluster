#include <QDebug>
#include <QProcess>
#include <QProcessEnvironment>
#include <QTimerEvent>
#include "supervisor.h"

Supervisor::Supervisor(Plugin* plugin, QUuid const &id, QString const &host, QString const &port, QObject &parent)
    : QObject{ &parent }
    , _plugin{ plugin }
    , _id{ id }
    , _host{ host }
    , _port{ port }
{
}

Supervisor::~Supervisor()
{
    stop();
}

void Supervisor::start()
{
	auto env = QProcessEnvironment::systemEnvironment();
	env.insert(QStringLiteral("GST_PLUGIN_PATH"), QStringLiteral("%1/gst_plugins").arg(qApp->applicationDirPath()));

    _process = new QProcess{ this };
	_process->setProcessEnvironment(env);

    connect(_process, &QProcess::stateChanged, [this](QProcess::ProcessState state){ emit processStateChanged(_id, state); });
    connect(_process, &QProcess::stateChanged, this, &Supervisor::restart);
    connect(_process, &QProcess::errorOccurred, this, &Supervisor::processError);

    _process->start(QStringLiteral("node"), { _plugin->type(), _id.toString(), _host, _port });

    qDebug() << toString() << "has been started.";
}

void Supervisor::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == _antiFluctuateTimer)
    {
        killTimer(_antiFluctuateTimer);
        _antiFluctuateTimer = -1;
        start();
    }
    else
    {
        QObject::timerEvent(ev);
    }
}

void Supervisor::stop()
{
    disconnect(_process, &QProcess::stateChanged, this, &Supervisor::restart);
    disconnect(_process, &QProcess::errorOccurred, this, &Supervisor::processError);

    _process->terminate();
    _process->write("terminate\n");
    _process->waitForBytesWritten();

    std::this_thread::sleep_for(std::chrono::seconds{ 1 });

    static int const waitWhileProcessQuitMs = 10000;
    if (!_process->waitForFinished(waitWhileProcessQuitMs))
    {
        qWarning() << "Failed to stop process" << _id << "The one will be killed.";
        _process->kill();
        _process->waitForFinished();
    }

    _process->deleteLater();
    _process = nullptr;

    qDebug() << toString() << "has been stopped.";
}

void Supervisor::restart(QProcess::ProcessState state)
{
    qDebug() << toString() << "has changed a state:" << state;

    if (state == QProcess::NotRunning)
    {
        stop();
        Q_ASSERT(_antiFluctuateTimer == -1);
        _antiFluctuateTimer = startTimer(100);
    }
}

void Supervisor::processError(QProcess::ProcessError er)
{
    qInfo() << "Error" << er << "occured with process" << toString();
}
