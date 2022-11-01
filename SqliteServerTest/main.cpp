#include <QtCore/QCoreApplication>
#include <SqliteClient.h>
#include <SqliteServerMgr.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SqliteClient client;
    SqliteServerMgr serverMgr;

    std::cout << (serverMgr.CreateAccount("helloSqlite", "2333") ? "~true\n" : "~false\n");

    client.connectToServer("helloSqlite", "2333", "127.0.0.1");

    return a.exec();
}
