#pragma once

#include "SqliteServer.h"

class SQLITESERVER_EXPORT SqliteServerCreater : public QObject
{
	QTcpSocket* m_socket;
public:
	SqliteServerCreater(QTcpSocket* tcpSocket);

private slots:
	void socketReadyRead();
	void socketDisconnected();
};

