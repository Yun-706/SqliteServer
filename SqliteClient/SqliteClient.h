#pragma once

#include "sqliteclient_global.h"
#include <Sqlite.h>

class SQLITECLIENT_EXPORT SqliteClient : public Sqlite
{
public:
    SqliteClient();
};
