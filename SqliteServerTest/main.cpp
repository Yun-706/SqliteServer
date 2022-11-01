#include <QtCore/QCoreApplication>
#include <SqliteClient.h>
#include <SqliteServerMgr.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SqliteClient client;
    SqliteServerMgr serverMgr;

    //std::cout << (serverMgr.CreateAccount("chunlai", "2333") ? "~true\n" : "~false\n");

    client.connectToServer("chunlai", "2333", "fe80::2078:cc10:5a89:97e3%13");

    return a.exec();
}
