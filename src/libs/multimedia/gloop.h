#ifndef GLOOP_H
#define GLOOP_H

extern "C"
{
    #include <gst/gst.h>
}

#include <thread>
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT Gloop
{
public:
    Gloop();
    ~Gloop();

private:
    GMainLoop *_loop{ nullptr };
    std::thread _thread;
};

#endif // GLOOP_H
