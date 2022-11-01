#include "SqliteConnecter.h"
#include <QCryptographicHash>
#include <iostream>

SqliteConnecter::SqliteConnecter(const QString& account, const QString& password, const QString& hostName, quint16 port) : m_account(account), m_password(password)
{
	m_socket = new QTcpSocket();
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &SqliteConnecter::socketReadyRead);
	QObject::connect(m_socket, &QTcpSocket::connected, this, &SqliteConnecter::socketConnected);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &SqliteConnecter::socketDisconnected);
	m_socket->connectToHost(hostName, port);
}

void SqliteConnecter::socketReadyRead()
{
	QByteArray data = m_socket->readAll();
	if (m_step == 0) {
		if (data.length() != RandBitSize / 8) {
			return m_socket->close();
		}
		++m_step;
		QByteArray pwdHash = QCryptographicHash::hash(m_password.toUtf8(), QCryptographicHash::Algorithm::Sha3_512);
		pwdHash = QCryptographicHash::hash(pwdHash + data, QCryptographicHash::Algorithm::Sha3_512);
		m_socket->write(pwdHash);
	}
	else {
		emit sqliteConnected(m_socket);
		this->deleteLater();
	}
}

void SqliteConnecter::socketConnected()
{
	sendAccount();
}

void SqliteConnecter::socketDisconnected()
{
	m_socket->deleteLater();
	emit sqliteConnectFailed();
}

void SqliteConnecter::sendAccount()
{
	m_socket->write(("a:" + m_account).toUtf8());
}