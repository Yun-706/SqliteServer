#include "SqliteServerMgr.h"
#include <QDebug>

SqliteServerMgr::SqliteServerMgr()
{
	m_tcpServer.setMaxPendingConnections(1);
	quint16 port = m_tcpServer.listen(IPAcceptableType, SqliteServer::Port);
	if (port == 0) {
		qCritical() << "SqliteServerMgr failed to listen on port" << port;
		return;
	}

	QObject::connect(&m_tcpServer, &QSslServer::newConnection, this, &SqliteServerMgr::newConnection);
	qInfo() << "SqliteServerMgr Runing...";
}

void SqliteServerMgr::newConnection()
{
	qInfo() << "SqliteServerMgr New Connection.";
	while (m_tcpServer.hasPendingConnections()) {
		new SqliteServerCreater(m_tcpServer.nextPendingConnection());
	}
}

bool SqliteServerMgr::CreateAccount(const QString& account, const QString& password)
{
	return SqliteServer::CreateAccount(account, password);
}