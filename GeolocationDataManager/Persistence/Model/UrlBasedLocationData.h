#pragma once

#include <QString>

namespace Persistence
{
    namespace Model
    {
        struct UrlBasedLocationData
        {
            int id;
            QString ip;
            QString url;
            QString type;
            QString continentCode;
            QString continentName;
            QString countryCode;
            QString countryName;
            QString regionCode;
            QString regionName;
            QString city;
            QString zip;
            double latitude;
            double longitude;

            bool FromJson(const QString &locationDataJsonString);

            QString Str() const;
        };
    }
}


