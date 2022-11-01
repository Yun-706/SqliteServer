#pragma once

#include "sqliteserver_global.h"
#include <QObject>
#include <QtNetwork>
#include <Sqlite.h>


class SQLITESERVER_EXPORT SqliteServer : public QObject
{
public:
    static constexpr quint16 Port = 3000;
    SqliteServer();

private:
    Sqlite* m_sqlite = nullptr;
};
