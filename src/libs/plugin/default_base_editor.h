#ifndef DEFAULT_BASE_EDITOR_H
#define DEFAULT_BASE_EDITOR_H

#include "editor.h"

class PLUGIN_SHARED_EXPORT DefaultBaseEditor : public Editor
{
public:
    explicit DefaultBaseEditor(QWidget &parent);

public:
    void init() override;

    SlaveAsParams slaveAsParams() const override;
    void setSlaveAsParams(SlaveAsParams const &slaveAsParams) override;

    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;

    QStringList errors() const override;
};

#endif // DEFAULT_BASE_EDITOR_H
