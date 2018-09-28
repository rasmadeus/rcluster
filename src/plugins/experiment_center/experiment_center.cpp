#include <QMessageBox>
#include <config.h>
#include <corebus.h>
#include "experiment_center.h"

ExperimentCenter::ExperimentCenter(Config const &config, Corebus &corebus, QObject &parent)
    : QObject{ &parent }
    , _config{ config }
    , _corebus{ corebus }
{
}

void ExperimentCenter::onSetup(Slave const &slave)
{
    stop();

    auto params = slave.param(QStringLiteral("media_player")).toList();
    _mediaPlayer = params.isEmpty() ? QUuid{} : params.first().toUuid();
}

void ExperimentCenter::start()
{
    if (_mediaPlayer.isNull())
        return;

    _corebus.send(QStringLiteral("START"), _mediaPlayer.toString(), { { QStringLiteral("request_id"), QUuid::createUuid() }, });
}

void ExperimentCenter::stop()
{
    if (_mediaPlayer.isNull())
        return;

    _corebus.send(QStringLiteral("STOP"), _mediaPlayer.toString());
}