#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QThread>
#include "IpBasedLocationDataRepository.h"
#include "Interface/IDatabaseConnectionFactory.h"


namespace
{
    constexpr auto DATABASE_NAME = "LocationData.sqlite";
    constexpr auto IP_BASED_TABLE_NAME = "ip_based_location_data";

    constexpr auto IP_COLUMN_NAME = "ip";
    constexpr auto TYPE_COLUMN_NAME = "type";
    constexpr auto CONTINENT_CODE_COLUMN_NAME = "continent_code";
    constexpr auto CONTINENT_NAME_COLUMN_NAME = "continent_name";
    constexpr auto COUNTRY_CODE_COLUMN_NAME = "country_code";
    constexpr auto COUNTRY_NAME_COLUMN_NAME = "country_name";
    constexpr auto REGION_CODE_COLUMN_NAME = "region_code";
    constexpr auto REGION_NAME_COLUMN_NAME = "region_name";
    constexpr auto CITY_COLUMN_NAME = "city";
    constexpr auto ZIP_COLUMN_NAME = "zip";
    constexpr auto LATITUDE_COLUMN_NAME = "latitude";
    constexpr auto LONGITUDE_COLUMN_NAME = "longitude";
}

namespace Persistence
{
    IpBasedLocationDataRepository::IpBasedLocationDataRepository(std::shared_ptr<IDatabaseConnectionFactory> databaseConnectionFactory)
    : mDatabaseConnectionFactory(databaseConnectionFactory)
    {
        auto connectionName = QString("Initial");

        auto db = mDatabaseConnectionFactory->CreateSqliteConnection(DATABASE_NAME, connectionName);

        if (!db.open()) {
            qDebug() << "Error opening database. Last error: " << db.lastError().text();
            return;
        }

        QSqlQuery query(QSqlDatabase::database(connectionName));
        QString queryStr = QString(
                               "CREATE TABLE IF NOT EXISTS %1 ("
                               "id INTEGER PRIMARY KEY, %2 TEXT, %3 TEXT, "
                               "%4 TEXT, %5 TEXT, %6 TEXT, "
                               "%7 TEXT, %8 TEXT, %9 TEXT, %10 TEXT, "
                               "%11 TEXT, %12 REAL, %13 REAL, "
                               "UNIQUE(%2, %12, %13))")
                               .arg(IP_BASED_TABLE_NAME)
                               .arg(IP_COLUMN_NAME)
                               .arg(TYPE_COLUMN_NAME)
                               .arg(CONTINENT_CODE_COLUMN_NAME)
                               .arg(CONTINENT_NAME_COLUMN_NAME)
                               .arg(COUNTRY_CODE_COLUMN_NAME)
                               .arg(COUNTRY_NAME_COLUMN_NAME)
                               .arg(REGION_CODE_COLUMN_NAME)
                               .arg(REGION_NAME_COLUMN_NAME)
                               .arg(CITY_COLUMN_NAME)
                               .arg(ZIP_COLUMN_NAME)
                               .arg(LATITUDE_COLUMN_NAME)
                               .arg(LONGITUDE_COLUMN_NAME);

        if (!query.exec(queryStr)) {
            qDebug() << "Error creating table: " << query.lastError().text();
        }

        db.close();
        QSqlDatabase::removeDatabase(connectionName);
    }

    std::vector<Model::IpBasedLocationData> IpBasedLocationDataRepository::GetAll()
    {
        std::vector<Model::IpBasedLocationData> locations;
        QString connectionName = QString("Add_%1").arg((quintptr)QThread::currentThreadId());
        {

            auto db = mDatabaseConnectionFactory->CreateSqliteConnection(DATABASE_NAME, connectionName);

            if (!db.open()) {
                qDebug() << "Error with opening the database: " << db.lastError().text();
                emit errorOccurred("Error with opening the database.\nGet locations from database failed!");
                return {};
            }

            QSqlQuery query(QSqlDatabase::database(connectionName));
            auto queryStr = QString("SELECT * FROM %1").arg(IP_BASED_TABLE_NAME);
            query.prepare(queryStr);

            if (!query.exec()) {
                qDebug() << "Get All Sqlite query failed. Last error: " << query.lastError().text();
                emit errorOccurred("Database error.\nGet all locations from database failed!");
                return {};
            }

            while (query.next()) {
                Model::IpBasedLocationData location;
                location.ip = query.value(IP_COLUMN_NAME).toString();
                location.type = query.value(TYPE_COLUMN_NAME).toString();
                location.continentCode = query.value(CONTINENT_CODE_COLUMN_NAME).toString();
                location.continentName = query.value(CONTINENT_NAME_COLUMN_NAME).toString();
                location.countryCode = query.value(COUNTRY_CODE_COLUMN_NAME).toString();
                location.countryName = query.value(COUNTRY_NAME_COLUMN_NAME).toString();
                location.regionCode = query.value(REGION_CODE_COLUMN_NAME).toString();
                location.regionName = query.value(REGION_NAME_COLUMN_NAME).toString();
                location.city = query.value(CITY_COLUMN_NAME).toString();
                location.zip = query.value(ZIP_COLUMN_NAME).toString();
                location.latitude = query.value(LATITUDE_COLUMN_NAME).toDouble();
                location.longitude = query.value(LONGITUDE_COLUMN_NAME).toDouble();
                locations.push_back(location);
            }

            db.close();
        }

        QSqlDatabase::removeDatabase(connectionName);

        return locations;
    }


    Model::IpBasedLocationData IpBasedLocationDataRepository::GetByIp(const QString& ip)
    {
        Model::IpBasedLocationData location;
        QString connectionName = QString("Add_%1").arg((quintptr)QThread::currentThreadId());
        {
            auto db = mDatabaseConnectionFactory->CreateSqliteConnection(DATABASE_NAME, connectionName);

            if (!db.open()) {
                qDebug() << "Error with opening the database: " << db.lastError().text();
                emit errorOccurred("Error with opening the database.\nGet locations from database failed!");
                return {};
            }

            QSqlQuery query(QSqlDatabase::database(connectionName));
            QString queryStr = QString("SELECT * FROM %1 WHERE %2 = ?").arg(IP_BASED_TABLE_NAME, IP_COLUMN_NAME);
            query.prepare(queryStr);
            query.addBindValue(ip);

            if (!query.exec()) {
                qDebug() << "Błąd dodawania lokalizacji: " << query.lastError().text();
                emit errorOccurred("Error with opening the database.\nGet locations from database failed!");
                return {};
            }

            if(!query.next())
            {
                return Model::IpBasedLocationData();
            }

            location.ip = query.value(IP_COLUMN_NAME).toString();
            location.type = query.value(TYPE_COLUMN_NAME).toString();
            location.continentCode = query.value(CONTINENT_CODE_COLUMN_NAME).toString();
            location.continentName = query.value(CONTINENT_NAME_COLUMN_NAME).toString();
            location.countryCode = query.value(COUNTRY_CODE_COLUMN_NAME).toString();
            location.countryName = query.value(COUNTRY_NAME_COLUMN_NAME).toString();
            location.regionCode = query.value(REGION_CODE_COLUMN_NAME).toString();
            location.regionName = query.value(REGION_NAME_COLUMN_NAME).toString();
            location.city = query.value(CITY_COLUMN_NAME).toString();
            location.zip = query.value(ZIP_COLUMN_NAME).toString();
            location.latitude = query.value(LATITUDE_COLUMN_NAME).toDouble();
            location.longitude = query.value(LONGITUDE_COLUMN_NAME).toDouble();

            db.close();
        }
        QSqlDatabase::removeDatabase(connectionName);

        return location;
    }

    void IpBasedLocationDataRepository::Add(const Model::IpBasedLocationData& data)
    {
        QString connectionName = QString("Add_%1").arg((quintptr)QThread::currentThreadId());
        {
            auto db = mDatabaseConnectionFactory->CreateSqliteConnection(DATABASE_NAME, connectionName);

            if (!db.open()) {
                qDebug() << "Error with opening the database: " << db.lastError().text();
                emit errorOccurred("Error with opening the database.\nAdd location data failed!");
                return;
            }

            QSqlQuery query(QSqlDatabase::database(connectionName));
            QString queryStr = QString("INSERT OR IGNORE INTO %1 (%2, %3, %4, %5, %6, "
                                       "%7, %8, %9, %10, %11, %12, %13) "
                                       "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
                                   .arg(IP_BASED_TABLE_NAME)
                                   .arg(IP_COLUMN_NAME)
                                   .arg(TYPE_COLUMN_NAME)
                                   .arg(CONTINENT_CODE_COLUMN_NAME)
                                   .arg(CONTINENT_NAME_COLUMN_NAME)
                                   .arg(COUNTRY_CODE_COLUMN_NAME)
                                   .arg(COUNTRY_NAME_COLUMN_NAME)
                                   .arg(REGION_CODE_COLUMN_NAME)
                                   .arg(REGION_NAME_COLUMN_NAME)
                                   .arg(CITY_COLUMN_NAME)
                                   .arg(ZIP_COLUMN_NAME)
                                   .arg(LATITUDE_COLUMN_NAME)
                                   .arg(LONGITUDE_COLUMN_NAME);


            query.prepare(queryStr);

            query.addBindValue(data.ip);
            query.addBindValue(data.type);
            query.addBindValue(data.continentCode);
            query.addBindValue(data.continentName);
            query.addBindValue(data.countryCode);
            query.addBindValue(data.countryName);
            query.addBindValue(data.regionCode);
            query.addBindValue(data.regionName);
            query.addBindValue(data.city);
            query.addBindValue(data.zip);
            query.addBindValue(data.latitude);
            query.addBindValue(data.longitude);

            if (!query.exec()) {
                qDebug() << "Add query error: " << query.lastError().text();
                emit errorOccurred("Add query error.\nAdd location data failed");
            }

            db.close();
        }
        QSqlDatabase::removeDatabase(connectionName);
    }

    void IpBasedLocationDataRepository::DeleteByIp(const QString& ip)
    {
        QString connectionName = QString("Add_%1").arg((quintptr)QThread::currentThreadId());
        {
            auto db = mDatabaseConnectionFactory->CreateSqliteConnection(DATABASE_NAME, connectionName);

            if (!db.open()) {
                qDebug() << "Error with opening the database: " << db.lastError().text();
                emit errorOccurred("Error with opening the database.\nDelete location data failed!");
                return;
            }

            QSqlQuery query(QSqlDatabase::database(connectionName));
            QString queryStr = QString("DELETE FROM %1 WHERE %2 = ?").arg(IP_BASED_TABLE_NAME, IP_COLUMN_NAME);

            query.prepare(queryStr);
            query.addBindValue(ip);

            if (!query.exec()) {
                qDebug() << "Sql query error. Last error: " << query.lastError().text();
                emit errorOccurred("Database error.\nDelete location data failed!");
            }

            db.close();
        }
        QSqlDatabase::removeDatabase(connectionName);
    }
}
