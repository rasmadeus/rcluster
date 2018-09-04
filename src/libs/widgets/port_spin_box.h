#ifndef PORT_SPIN_BOX_H
#define PORT_SPIN_BOX_H

#include <QSpinBox>
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT PortSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit PortSpinBox(QWidget *parent = nullptr);
};

#endif // PORT_SPIN_BOX_H
