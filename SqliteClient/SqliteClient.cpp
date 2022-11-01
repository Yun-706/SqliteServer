#include "SqliteClient.h"
#include <QDebug>

SqliteClient::SqliteClient()
{
}

void SqliteClient::connectToServer(const QString& account, const QString& password, const QString& hostName, quint16 port)
{
	if (m_socket) {
		m_socket->close();
		m_socket->deleteLater();
		m_socket = nullptr;
	}

	SqliteConnecter* connecter = new SqliteConnecter(account, password, hostName, port);
	QObject::connect(connecter, &SqliteConnecter::sqliteConnected, this, &SqliteClient::sqliteConnected);
	QObject::connect(connecter, &SqliteConnecter::sqliteConnectFailed, this, &SqliteClient::sqliteConnectFailed);
}

void SqliteClient::socketReadyRead()
{
	qInfo() << "SqliteClient TcpSocket ReadyRead.";
	QByteArray data = m_socket->readAll();
	qInfo() << "SqliteClient Received: " << data;
}

void SqliteClient::socketDisconnected()
{
	qInfo() << "SqliteClient TcpSocket Disconnected.";
	m_socket->deleteLater();
	m_socket = nullptr;
}

void SqliteClient::sqliteConnected(QTcpSocket* tcpSocket)
{
	qInfo() << "SqliteClient Sqlite Connected.";
	m_socket = tcpSocket;
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &SqliteClient::socketReadyRead);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &SqliteClient::socketDisconnected);
}

void SqliteClient::sqliteConnectFailed()
{
	if (m_socket) {
		m_socket->disconnectFromHost();
		m_socket->deleteLater();
		m_socket = nullptr;
	}
	qWarning() << "SqliteClient TcpSocket Connect Failed.";
}