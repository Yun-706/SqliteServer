#include "SqliteServerMgr.h"
#include <iostream>

SqliteServerMgr::SqliteServerMgr()
{
	m_tcpServer.setMaxPendingConnections(1);
	quint16 port = m_tcpServer.listen(QHostAddress::Any, SqliteServer::Port);
	if (port == 0) {
		std::cout << "SqliteServerMgr failed to listen on port " << port << " .\n";
	}

	QObject::connect(&m_tcpServer, &QSslServer::newConnection, this, &SqliteServerMgr::newConnection);
}

void SqliteServerMgr::newConnection()
{
	std::cout << "SqliteServerMgr New Connection.\n";
	while (m_tcpServer.hasPendingConnections()) {
		new SqliteServerCreater(m_tcpServer.nextPendingConnection());
	}
}