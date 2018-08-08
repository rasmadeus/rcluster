#ifndef SVG_H
#define SVG_H

#include <QPainter>
#include <QPixmap>
#include <QSvgRenderer>

namespace rcluster
{
    inline QPixmap fromSvg(QString const &res, QSize const &size)
    {
        QPixmap pixmap{ size };
        pixmap.fill(QColor{ 0, 0, 0, 0 });
        QPainter painter{ &pixmap };
        QSvgRenderer{ QStringLiteral(":/res/%1.svg").arg(res) }.render(&painter);
        return pixmap;
    }
}

#endif //SVG_H
