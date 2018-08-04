#ifndef FILE_STORABLE_H
#define FILE_STORABLE_H

#include <QString>
#include "storage.h"

class QFile;
class Storable;

class FileStorable : public Storage
{
public:
    FileStorable(QString const &path);

    void store(Storable const &storable) override;
    void restore(Storable &storable) override;

private:
    QString const _path;
};

#endif // FILE_STORABLE_H
