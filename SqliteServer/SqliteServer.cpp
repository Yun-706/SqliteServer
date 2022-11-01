#include "SqliteServer.h"
#include <QRegularExpression>
#include <QCryptographicHash>
#include <QDir>
#include <QDebug>

SqliteServer::SqliteServer()
{
}

bool SqliteServer::IsLegalAccount(const QString& account)
{
	QRegularExpression regExp("[a-zA-Z][A-Za-z0-9_-]{5,32}");
	auto match = regExp.match(account, 0, QRegularExpression::PartialPreferCompleteMatch);
	return match.capturedLength() == account.length() && match.hasMatch();
}

bool SqliteServer::IsAccountExists(const QString& account)
{
	QDir accountDir("./database/" + account + "/");
	if (accountDir.exists()) {
		QFile passwordFile("./database/" + account + "/password");
		if (passwordFile.exists()) {
			return true;
		}
	}
	return false;
}

QByteArray SqliteServer::ReadPassword(const QString& account)
{
	QFile passwordFile("./database/" + account + "/password");
	if (passwordFile.open(QIODevice::ReadOnly)) {
		QByteArray password = passwordFile.read(PwdBitSize / 8);
		passwordFile.close();
		if (password.length() == PwdBitSize / 8) {
			return password;
		}
	}
	return QByteArray();
}

bool SqliteServer::CreateAccount(const QString& account, const QString& password)
{
	if (!IsLegalAccount(account)) return false;
	if (IsAccountExists(account)) return false;


	QDir accountDir("./database/" + account + "/");
	if (!accountDir.exists()) {
		if (!accountDir.mkdir(accountDir.absolutePath())) return false;
	}

	QFile passwordFile("./database/" + account + "/password");
	if (!passwordFile.open(QIODevice::ReadWrite)) return false;

	passwordFile.write(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Algorithm::Sha3_512));
	passwordFile.close();
	return true;
}