#pragma once

#include "sqliteserver_global.h"
#include "SqliteServerCreater.h"

class SQLITESERVER_EXPORT SqliteServerMgr : public QObject
{
public:
	SqliteServerMgr();

private:
	SqliteServer server;
	QTcpServer m_tcpServer;

private slots:
	void newConnection();
};

