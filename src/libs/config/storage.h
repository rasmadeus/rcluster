#ifndef STORAGE_H
#define STORAGE_H

#include <memory>
#include <QJsonObject>
#include "config_global.h"

class Storable;

class CONFIG_SHARED_EXPORT Storage
{
public:
    enum class Type
    {
        FileStorage,
    };

public:
    virtual ~Storage() = default;

public:
    static std::unique_ptr<Storage> make(Storage::Type type, QVariantHash const &params);

public:
    virtual void store(Storable const &storable) = 0;
    virtual void restore(Storable &storable) = 0;
};

#endif // STORAGE_H
