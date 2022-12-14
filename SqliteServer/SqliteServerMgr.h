#pragma once

#include "sqliteserver_global.h"
#include "SqliteServerCreater.h"

class SQLITESERVER_EXPORT SqliteServerMgr : public QObject
{
public:
	SqliteServerMgr();
	static constexpr auto IPAcceptableType = QHostAddress::Any;
	static bool CreateAccount(const QString& account, const QString& password);

private:
	SqliteServer server;
	QTcpServer m_tcpServer;

private slots:
	void newConnection();
};

