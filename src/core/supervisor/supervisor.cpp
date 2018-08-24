#include <QDebug>
#include <QProcess>
#include "supervisor.h"

#ifdef Q_OS_UNIX
#include <QCoreApplication>
#include <QProcessEnvironment>
#endif

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
    _process = new QProcess{ this };
    connect(_process, &QProcess::stateChanged, [this](QProcess::ProcessState state){ emit processStateChanged(_id, state); });
    connect(_process, &QProcess::stateChanged, this, &Supervisor::restart);
    connect(_process, &QProcess::errorOccurred, this, &Supervisor::processError);

    #ifdef Q_OS_UNIX
    auto env = QProcessEnvironment::systemEnvironment();
    env.insert(QStringLiteral("LIBRARY_PATH"), QCoreApplication::applicationDirPath());
    _process->setProcessEnvironment(env);
    #endif

    _process->start(QStringLiteral("slave"), { _plugin->type(), _id.toString(), _host, _port });

    qDebug() << toString() << "has been started.";
}

void Supervisor::stop()
{
    disconnect(_process, &QProcess::stateChanged, this, &Supervisor::restart);
    disconnect(_process, &QProcess::errorOccurred, this, &Supervisor::processError);

    _process->terminate();

    static int const waitWhileProcessQuitMs = 1000;
    if (!_process->waitForFinished(waitWhileProcessQuitMs))
    {
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
        start();
    }
}

void Supervisor::processError(QProcess::ProcessError er)
{
    qInfo() << "Error" << er << "occured with process" << toString();
}
