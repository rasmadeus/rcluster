#ifndef CONFIG_GLOBAL_H
#define CONFIG_GLOBAL_H

#include <QtGlobal>

#if defined(CONFIG_LIBRARY)
    #define CONFIG_SHARED_EXPORT Q_DECL_EXPORT
#else
    #define CONFIG_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CONFIG_GLOBAL_H
