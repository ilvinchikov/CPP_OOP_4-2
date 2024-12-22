#include <QCoreApplication>
#include <windows.h>
#include "Adapter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // создаем LegacyGPS
    LegacyGPS legacyGPS(14.52, 28.11);
    // создаем GPSAdapter
    GPSAdapter adapter(&legacyGPS);
    // создаем клиентский объект GeoClient
    GeoClient client(&adapter);

    // координаты
    client.getLegacyCords();
    client.getStandartCords();

    return 0;
}
