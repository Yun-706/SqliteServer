#pragma once

#include "SqliteServer.h"

class SQLITESERVER_EXPORT SqliteServerCreater : public QObject
{
	QTcpSocket* m_socket;
	QString m_account;
	QByteArray m_random;
	static constexpr int RandBitSize = SqliteServer::PwdBitSize / 4;
public:
	SqliteServerCreater(QTcpSocket* tcpSocket);


private slots:
	void socketReadyRead();
	void socketDisconnected();

private:
	bool isPasswordCorrect(const QByteArray& password);
	void closeSocket();
};

