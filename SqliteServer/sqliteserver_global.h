#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SQLITESERVER_LIB)
#  define SQLITESERVER_EXPORT Q_DECL_EXPORT
# else
#  define SQLITESERVER_EXPORT Q_DECL_IMPORT
# endif
#else
# define SQLITESERVER_EXPORT
#endif
