#include <QtCore/QCoreApplication>
#include <SqliteClient.h>
#include <SqliteServerMgr.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SqliteClient client;
    SqliteServerMgr serverMgr;

    client.connectToServer("127.0.0.1");

    return a.exec();
}
