#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SQLITE_LIB)
#  define SQLITE_EXPORT Q_DECL_EXPORT
# else
#  define SQLITE_EXPORT Q_DECL_EXPORT
# endif
#else
# define SQLITE_EXPORT
#endif
