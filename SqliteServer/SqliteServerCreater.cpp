#include "SqliteServerCreater.h"
#include <QRandomGenerator64>
#include <QCryptographicHash>
#include <QDebug>

SqliteServerCreater::SqliteServerCreater(QTcpSocket* tcpSocket) : m_socket(tcpSocket)
{
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &SqliteServerCreater::socketReadyRead);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &SqliteServerCreater::socketDisconnected);
}

void SqliteServerCreater::socketReadyRead()
{
	QByteArray data = m_socket->readAll();
	if (m_account.isEmpty()) {
		if (data.length() < 5 || data[0] != 'a' || data[1] != ':') {
			return closeSocket();;
		}
		QString account = QString::fromUtf8(data.mid(2, 32));
		if (!SqliteServer::IsAccountExists(account)) {
			return closeSocket();;
		}
		m_account = account;
		quint32* random = new quint32[RandBitSize / 32];
		QRandomGenerator::global()->generate(random, random + RandBitSize / 32);
		m_random = QByteArray::fromRawData(reinterpret_cast<char*>(random), RandBitSize / 8);
		m_socket->write(reinterpret_cast<const char*>(random), RandBitSize / 8);
		return;
	}
	else {
		if (data.length() != SqliteServer::PwdBitSize/8) {
			return closeSocket();
		}
		if (!isPasswordCorrect(data)) {
			return closeSocket();
		}
		qInfo() << "Login Succeeded:" << m_account;
		m_socket->write("ok");
		return;
	}
	//m_socket->write("Hi, I am ServerCreater!");
}

void SqliteServerCreater::socketDisconnected()
{
	closeSocket();
	this->deleteLater();
}

bool SqliteServerCreater::isPasswordCorrect(const QByteArray& password)
{
	QByteArray localPassword = SqliteServer::ReadPassword(m_account) + m_random;
	return password == QCryptographicHash::hash(localPassword, QCryptographicHash::Algorithm::Sha3_512);
}

void SqliteServerCreater::closeSocket()
{
	m_account.clear();
	m_random.clear();
	if (m_socket) {
		m_socket->close();
	}
}