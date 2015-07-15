#ifndef MYCOO_GLOBAL_H
#define MYCOO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYCOO_LIBRARY)
#  define MYCOOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MYCOOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MYCOO_GLOBAL_H
