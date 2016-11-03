#ifndef GSCORE_GLOBAL_H
#define GSCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GSCORE_LIBRARY)
#  define GSCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define GSCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GSCORE_GLOBAL_H
