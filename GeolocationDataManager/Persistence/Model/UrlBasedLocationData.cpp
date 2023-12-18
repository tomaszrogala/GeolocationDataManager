#include "UrlBasedLocationData.h"
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
        bool UrlBasedLocationData::FromJson(const QString &locationDataJsonString)
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

        QString UrlBasedLocationData::Str() const
        {
            return QString("URL: %1 IP: %2, Type: %3, Continent Code: %4, Continent Name: %5, Country Code: %6, "
                           "Country Name: %7, Region Code: %8, Region Name: %9, City: %10, ZIP: %11, "
                           "Latitude: %12, Longitude: %13")
                .arg(url)
                .arg(ip).arg(type).arg(continentCode).arg(continentName)
                .arg(countryCode).arg(countryName).arg(regionCode).arg(regionName)
                .arg(city).arg(zip).arg(latitude).arg(longitude);
        }
    }
}
