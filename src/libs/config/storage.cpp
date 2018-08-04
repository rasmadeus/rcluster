#include <QVariantHash>
#include "file_storable.h"
#include "storage.h"

std::unique_ptr<Storage> Storage::make(Storage::Type type, QVariantHash const &params)
{
    switch(type)
    {
        case Type::FileStorage:
            return std::make_unique<FileStorable>(params.value(QStringLiteral("path")).toString());
    }
    return nullptr;
}
