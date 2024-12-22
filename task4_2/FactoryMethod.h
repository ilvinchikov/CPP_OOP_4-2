#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H

#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Продукт
class Transport {
public:
    string m_name;          // название
    double m_maxCapacity;   // грузоподъёмность
    string m_desc;          // описание

    Transport(string name, double maxCapacity, string desc): m_name(name), m_maxCapacity(maxCapacity), m_desc(desc) {}
    virtual ~Transport() = default;
    virtual void deliver() const = 0;       // доставка
    virtual double getPrice(double distance) const = 0; // рассчет стоимости
};

// Конкретные продукты
class Truck : public Transport {
public:
    Truck(string name, double maxCapacity, string desc): Transport(name, maxCapacity, desc) {}
    void deliver() const override {
        cout << "Доставка по суше грузовиком." << endl;
    }
    double getPrice(double distance) const override {
        return distance * 125;
    }
};

class Ship : public Transport {
public:
    Ship(string name, double maxCapacity, string desc): Transport(name, maxCapacity, desc) {}
    void deliver() const override {
        cout << "Доставка по морю кораблем." << endl;
    }
    double getPrice(double distance) const override {
        return distance * 75;
    }
};

class Plane : public Transport {
public:
    Plane(string name, double maxCapacity, string desc): Transport(name, maxCapacity, desc) {}
    void deliver() const override {
        cout << "Доставка по воздуху самолётом." << endl;
    }
    double getPrice(double distance) const override {
        return distance * 250;
    }
};

class Drone : public Transport {
public:
    Drone(string name, double maxCapacity, string desc): Transport(name, maxCapacity, desc) {}
    void deliver() const override {
        cout << "Доставка по воздуху дроном." << endl;
    }
    double getPrice(double distance) const override {
        return distance * 105;
    }
};

// Создатель
class Logistics {
public:
    virtual ~Logistics() = default;
    virtual unique_ptr<Transport> createTransport(string name, double maxCapacity, string desc) const = 0;

    void planDelivery(string name, double maxCapacity, string desc, double distance) const {
        auto transport = createTransport(name, maxCapacity, desc);
        transport->deliver();
        cout << "Общая стоимость доставки: " << transport->getPrice(distance) << endl;
    }
};

// Конкретные создатели
class RoadLogistics : public Logistics {
public:
    unique_ptr<Transport> createTransport(string name, double maxCapacity, string desc) const override {
        return make_unique<Truck>(name, maxCapacity, desc);
    }
};

class SeaLogistics : public Logistics {
public:
    unique_ptr<Transport> createTransport(string name, double maxCapacity, string desc) const override {
        return make_unique<Ship>(name, maxCapacity, desc);
    }
};

class AirLogistics : public Logistics {
public:
    unique_ptr<Transport> createTransport(string name, double maxCapacity, string desc) const override {
        return make_unique<Plane>(name, maxCapacity, desc);
    }
};

class AirDLogistics : public Logistics {
public:
    unique_ptr<Transport> createTransport(string name, double maxCapacity, string desc) const override {
        return make_unique<Drone>(name, maxCapacity, desc);
    }
};

#endif // FACTORYMETHOD_H
