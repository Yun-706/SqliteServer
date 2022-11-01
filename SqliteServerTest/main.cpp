#include <QtCore/QCoreApplication>
#include <SqliteClient.h>
#include <SqliteServerMgr.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SqliteClient client;
    SqliteServer server;

    return a.exec();
}
