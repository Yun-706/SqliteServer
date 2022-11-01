#pragma once

#include <Sqlite.h>
#include "SqliteConnecter.h"

class SQLITECLIENT_EXPORT SqliteClient : public Sqlite
{
public:
    static constexpr quint16 ServerPort = 3000;
    SqliteClient();

    void connectToServer(const QString& account, const QString& password, const QString& hostName, quint16 port = ServerPort);

private:
    QTcpSocket* m_socket = nullptr;

private slots:
    void socketReadyRead();
    void socketDisconnected();
    void sqliteConnected(QTcpSocket* tcpSocket);
    void sqliteConnectFailed();
};
