#include "SqliteServerCreater.h"
#include <QByteArray>
#include <iostream>

SqliteServerCreater::SqliteServerCreater(QTcpSocket* tcpSocket) : m_socket(tcpSocket)
{
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &SqliteServerCreater::socketReadyRead);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &SqliteServerCreater::socketDisconnected);
}

void SqliteServerCreater::socketReadyRead()
{
	std::cout << "SqliteServerCreater TcpSocket ReadyRead.\n";
	QByteArray data = m_socket->readAll();
	std::cout << "SqliteServerCreater Received: " << data.toStdString() << "\n";
	m_socket->write("Hi, I am ServerCreater!");
}

void SqliteServerCreater::socketDisconnected()
{
	std::cout << "SqliteServerCreater TcpSocket Disconnected.\n";
	this->deleteLater();
}