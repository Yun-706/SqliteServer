#include "SqliteClient.h"
#include <iostream>

SqliteClient::SqliteClient()
{
	std::cout << "SqliteClient OK.\n";
}

void SqliteClient::connectToServer(QString hostName, quint16 port)
{
	if (m_socket) {
		m_socket->close();
		m_socket->deleteLater();
		m_socket = nullptr;
	}
	m_socket = new QTcpSocket();
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &SqliteClient::socketReadyRead);
	QObject::connect(m_socket, &QTcpSocket::connected, this, &SqliteClient::socketConnected);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &SqliteClient::socketDisconnected);
	m_socket->connectToHost(hostName, port);
}

void SqliteClient::socketReadyRead()
{
	std::cout << "SqliteClient TcpSocket ReadyRead.\n";
	QByteArray data = m_socket->readAll();
	std::cout << "SqliteClient Received: " << data.toStdString() << "\n";
}

void SqliteClient::socketConnected()
{
	std::cout << "SqliteClient TcpSocket Connected.\n";
	m_socket->write("Hello, I am Client!");
}

void SqliteClient::socketDisconnected()
{
	std::cout << "SqliteClient TcpSocket Disconnected.\n";
}