#pragma once

#include "sqliteserver_global.h"
#include "SqliteServer.h"
//#include <qnetwork.h>

class SQLITESERVER_EXPORT SqliteServerMgr : public QObject
{
public:
	SqliteServerMgr();

private:
	SqliteServer server;
};

