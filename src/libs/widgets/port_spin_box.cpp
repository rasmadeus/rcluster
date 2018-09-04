#include "port_spin_box.h"

PortSpinBox::PortSpinBox(QWidget *parent)
    : QSpinBox{ parent }
{
    setMinimum(1);
    setMaximum(65535);
}
