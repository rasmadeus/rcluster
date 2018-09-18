#include "camera_widget.h"

CameraWidget::CameraWidget(QString const &url, QWidget &parent)
    : QWidget{ &parent }
    , _client{ url, winId() }
{
}
