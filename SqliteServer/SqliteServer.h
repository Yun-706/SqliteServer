#pragma once

#include "sqliteserver_global.h"
#include <Sqlite.h>
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>

class SQLITESERVER_EXPORT SqliteServer : public QObject
{
public:
    SqliteServer();

private:
    Sqlite* m_sqlite = nullptr;
};
