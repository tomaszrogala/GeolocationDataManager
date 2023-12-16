#include "IpBasedLocationData.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace
{
    constexpr auto IP_JSON_KEY = "ip";
    constexpr auto TYPE_JSON_KEY = "type";
    constexpr auto CONTINENT_CODE_JSON_KEY = "continent_code";
    constexpr auto CONTINENT_NAME_JSON_KEY = "continent_name";
    constexpr auto COUNTRY_CODE_JSON_KEY = "country_code";
    constexpr auto COUNTRY_NAME_JSON_KEY = "country_name";
    constexpr auto REGION_CODE_JSON_KEY = "region_code";
    constexpr auto REGION_NAME_JSON_KEY = "region_name";
    constexpr auto CITY_JSON_KEY = "city";
    constexpr auto ZIP_JSON_KEY = "zip";
    constexpr auto LATITUDE_JSON_KEY = "latitude";
    constexpr auto LONGITUDE_JSON_KEY = "longitude";
}

namespace Persistence
{
    namespace Model
    {
        bool IpBasedLocationData::FromJson(const QString &locationDataJsonString)
        {
            QJsonDocument jsonResponse = QJsonDocument::fromJson(locationDataJsonString.toUtf8());

            if (!jsonResponse.isNull()) {
                if (jsonResponse.isObject()) {
                    QJsonObject jsonObj = jsonResponse.object();

                    this->ip = jsonObj[IP_JSON_KEY].toString();
                    this->type = jsonObj[TYPE_JSON_KEY].toString();
                    this->continentCode = jsonObj[CONTINENT_CODE_JSON_KEY].toString();
                    this->continentName = jsonObj[CONTINENT_NAME_JSON_KEY].toString();
                    this->countryCode = jsonObj[COUNTRY_CODE_JSON_KEY].toString();
                    this->countryName = jsonObj[COUNTRY_NAME_JSON_KEY].toString();
                    this->regionCode = jsonObj[REGION_CODE_JSON_KEY].toString();
                    this->regionName = jsonObj[REGION_NAME_JSON_KEY].toString();
                    this->city = jsonObj[CITY_JSON_KEY].toString();
                    this->zip = jsonObj[ZIP_JSON_KEY].toString();
                    this->latitude = jsonObj[LATITUDE_JSON_KEY].toDouble();
                    this->longitude = jsonObj[LONGITUDE_JSON_KEY].toDouble();

                } else {
                    qDebug() << "Response is not an object";
                    return false;
                }
            } else {
                qDebug() << "Invalid JSON Document";
                return false;
            }

            return true;
        }

        QString IpBasedLocationData::Str() const //TODO: Format this data in a more pretie form
        {
            if(this->ip.isNull() || this->ip.isEmpty())
            {
                return QString();
            }

            return QString("IP: %1, Type: %2, Continent Code: %3, Continent Name: %4, Country Code: %5, "
                           "Country Name: %6, Region Code: %7, Region Name: %8, City: %9, ZIP: %10, "
                           "Latitude: %11, Longitude: %12")
                .arg(ip).arg(type).arg(continentCode).arg(continentName)
                .arg(countryCode).arg(countryName).arg(regionCode).arg(regionName)
                .arg(city).arg(zip).arg(latitude).arg(longitude);
        }
    }
}
