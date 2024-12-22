#ifndef ADAPTER_H
#define ADAPTER_H

#include <iostream>
#include <string>
#include <sstream>
#include <qDebug>
using namespace std;

// Целевой интерфейс (Target)
class GeoTarget {
protected:
    double m_x;
    double m_y;
public:
    virtual ~GeoTarget() = default;
    virtual void displayfromLegacy() const = 0;
    virtual void transformFromLegacy() = 0;
    void getCoordinates() {
        cout << "Координаты:" << "\nШирота: " << m_x << "\nДолгота: " << m_y << endl;
    }
};

// Адаптируемый класс (Adaptee)
class LegacyGPS {
    double m_x;
    double m_y;
public:
    LegacyGPS (double x, double y): m_x(x), m_y(y) {}
    void displayLegacyCords() const {
        cout << "lat:" << m_x << ";lon:" << m_y << ";" << endl;
    }

    string getLegacyCords() const {
        string str = "lat:" + std::to_string(m_x) + ";lon:" + std::to_string(m_y) + ";";
        return str;
    }
};

// Адаптер (Adapter)
class GPSAdapter : public GeoTarget {
private:
    LegacyGPS* adaptee;

public:
    GPSAdapter(LegacyGPS* lib_LegacyGPS) : adaptee(lib_LegacyGPS) {
        transformFromLegacy();
    }

    void displayfromLegacy() const override {
        adaptee->displayLegacyCords();
    }

    void transformFromLegacy() override {
        string legacyFormat = adaptee->getLegacyCords();
        string str = "";
        double values [2];
        int index = 0;
        for (auto i=0; legacyFormat[i] != '\0'; i++) {
            if (isdigit(legacyFormat[i]) || legacyFormat[i] == '.') str += legacyFormat[i];
            if (legacyFormat[i] == ';') {
                stringstream ss;
                ss << str;
                ss >> values[index];
                index++;
                str = "";
            }
        }
        m_x = values[0];
        m_y = values[1];
    }
};

// Клиент (Client)
class GeoClient {
private:
     GeoTarget* m_geotarget;

public:
    GeoClient(GeoTarget* geotarget) : m_geotarget(geotarget) {}

    // координаты в формате LegacyGPS
    void getLegacyCords() const {
        m_geotarget->displayfromLegacy();
    }

    // координаты в формате обычном
    void getStandartCords() const {
        m_geotarget->getCoordinates();
    }
};
#endif // ADAPTER_H
