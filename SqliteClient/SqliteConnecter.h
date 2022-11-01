#pragma once

#include "sqliteclient_global.h"
#include <QtNetwork>

class SqliteConnecter : public QObject
{
	Q_OBJECT
	static constexpr int PwdBitSize = 512;
	static constexpr int RandBitSize = PwdBitSize / 4;
	QTcpSocket* m_socket = nullptr;
	QString m_account, m_password;
	int m_step = 0;

public:
	SqliteConnecter(const QString& account, const QString& password, const QString& hostName, quint16 port);

signals:
	void sqliteConnected(QTcpSocket* tcpSocket);
	void sqliteConnectFailed();

private slots:
	void socketReadyRead();
	void socketConnected();
	void socketDisconnected();

private:
	void sendAccount();
};

