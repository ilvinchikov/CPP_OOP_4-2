#include <QCoreApplication>
#include <windows.h>
#include "FactoryMethod.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    unique_ptr<Logistics> logistics = make_unique<AirDLogistics>();
    logistics->planDelivery("DJI Maveric", 5.5, "Универсальный дрон, не умеющий ничего кроме как занимать свободное место", 38);

    logistics = make_unique<AirLogistics>();
    logistics->planDelivery("Boeing A45", 2500000, "Самолёт гвинейского производства, имеющий высокий шанс развалиться в воздухе.", 1500);


    return 0;
}
