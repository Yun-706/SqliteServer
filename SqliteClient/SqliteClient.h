#pragma once

#include "sqliteclient_global.h"
#include <Sqlite.h>
#include <QtNetwork>


class SQLITECLIENT_EXPORT SqliteClient : public Sqlite
{
public:
    static constexpr quint16 ServerPort = 3000;
    SqliteClient();

    void connectToServer(QString hostName, quint16 port = ServerPort);

private:
    QTcpSocket* m_socket = nullptr;

private slots:
    void socketReadyRead();
    void socketConnected();
    void socketDisconnected();
};
