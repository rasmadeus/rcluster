#include "rtsp_server_runner.h"
#include "rtsp_server.h"

struct Data
{
    Data(GMainLoop &loop, RtspServerRunner &runner, RtspServer &server)
        : loop{ loop }
        , runner{ runner }
        , server{ server }
    {
    }

    GMainLoop &loop;
    RtspServerRunner &runner;
    RtspServer &server;
};

namespace
{
    gboolean stop(gpointer userData)
    {
        Q_ASSERT(userData != nullptr);

        auto data = static_cast<Data*>(userData);

        if (data->runner.isStopped())
        {
            data->server.stop();
            g_main_loop_quit(&data->loop);
        }

        return TRUE;
    }
}

RtspServerRunner::RtspServerRunner(QString const &host, QString const &mountPath, QString const &launch, QObject *parent)
    : QThread{ parent }
    , _host{ host }
    , _mountPath{ mountPath }
    , _launch{ launch }
{
}

void RtspServerRunner::run()
{
    auto loop = g_main_loop_new(nullptr, FALSE);
    RtspServer server{ _host, _mountPath, _launch };
    Data data{ *loop, *this, server };
    g_timeout_add_seconds(1, ::stop, &data);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);
}
