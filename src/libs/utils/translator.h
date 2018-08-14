#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "utils_global.h"

class UTILS_SHARED_EXPORT Translator
{
public:
    enum class Type
    {
        AppOnly,
        AppAndPlugins,
    };

public:
    Translator(Translator::Type type = Type::AppOnly);
    Translator(QString const &type);

private:
    void load(QString const &fileName, QString const &dir);
    void load(QString const &subDir);
    QString translationsDir() const;
};

#endif // TRANSLATOR_H
