#pragma once

#include "sqliteserver_global.h"
#include <QObject>
#include <QtNetwork>
#include <QByteArray>
#include <Sqlite.h>


class SQLITESERVER_EXPORT SqliteServer : public QObject
{
public:
    static constexpr quint16 Port = 3000;
    static constexpr qsizetype PwdBitSize = 512;
    SqliteServer();

    static bool IsLegalAccount(const QString& account);
    static bool IsAccountExists(const QString& account);
    static QByteArray ReadPassword(const QString& account);
    static bool CreateAccount(const QString& account, const QString& password);

private:
    Sqlite* m_sqlite = nullptr;
};
