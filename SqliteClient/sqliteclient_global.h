#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SQLITECLIENT_LIB)
#  define SQLITECLIENT_EXPORT Q_DECL_EXPORT
# else
#  define SQLITECLIENT_EXPORT Q_DECL_EXPORT
# endif
#else
# define SQLITECLIENT_EXPORT
#endif
