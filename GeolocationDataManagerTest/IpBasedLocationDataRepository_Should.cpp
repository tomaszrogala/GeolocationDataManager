#include <QtTest>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "../GeolocationDataManager/Persistence/IpBasedLocationDataRepository.h"
#include "../GeolocationDataManager/Persistence/Interface/IDatabaseConnectionFactory.h"

#include "../GeolocationDataManager/Persistence/Model/IpBasedLocationData.h"

namespace
{
    constexpr auto DATABASE_NAME = "LocationDataTest.sqlite";
}

namespace Persistence
{
    class InMemoryDatabaseConnectionFactory : public IDatabaseConnectionFactory
    {
    public:
        QSqlDatabase CreateSqliteConnection(const QString& databaseName, const QString& connectionName) const override
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
            db.setDatabaseName(DATABASE_NAME);
            return db;
        }
    };
}

class IpBasedLocationDataRepository_Should : public QObject
{
    Q_OBJECT

public:
    IpBasedLocationDataRepository_Should()
    {
        auto factory = std::make_shared<Persistence::InMemoryDatabaseConnectionFactory>();
        mSut = std::make_unique<Persistence::IpBasedLocationDataRepository>(factory);
    }

    ~IpBasedLocationDataRepository_Should()
    {
       CleanDatabaseTable();
    }

private slots:
    void initTestCase()
    {
        mTestDataList = {
            {1, "192.168.1.1", "Type1", "EU", "Europe",
             "PL", "Poland", "PL-MA", "Malopolska", "Krakow", "30-001", 50.0619, 19.9368},
            {2, "192.168.1.2", "Type2", "NA", "North America",
             "US", "United States", "US-CA", "California", "Los Angeles", "90001", 34.0522, -118.2437},
            {3, "192.168.2.1", "Type3", "AS", "Asia",
             "CN", "China", "CN-BJ", "Beijing", "Beijing", "100000", 39.9042, 116.4074},
            {4, "10.0.0.1", "Type4", "AN", "Antarctica",
             "", "", "", "", "", "0", -82.8628, 135.0000},
         };

        CleanDatabaseTable();
    }

    void AddLocationDataAndGetLocationDataByIp();
    void GetAllLocationData();
    void DeleteLocationDataByIp();

    void cleanupTestCase()
    {
        CleanDatabaseTable();
    }

private:
    void PerformAssertions(const Persistence::Model::IpBasedLocationData& result, const Persistence::Model::IpBasedLocationData& testData)
    {
        QCOMPARE(result.ip, testData.ip);
        QCOMPARE(result.type, testData.type);
        QCOMPARE(result.continentCode, testData.continentCode);
        QCOMPARE(result.continentName, testData.continentName);
        QCOMPARE(result.countryCode, testData.countryCode);
        QCOMPARE(result.countryName, testData.countryName);
        QCOMPARE(result.regionCode, testData.regionCode);
        QCOMPARE(result.regionName, testData.regionName);
        QCOMPARE(result.city, testData.city);
        QCOMPARE(result.zip, testData.zip);
        QCOMPARE(result.latitude, testData.latitude);
        QCOMPARE(result.longitude, testData.longitude);
    }

    void CleanDatabaseTable()
    {
        for (const auto& locationTestData : mTestDataList)
        {
            mSut->DeleteByIp(locationTestData.ip);
        }
    }

private:
    std::unique_ptr<Persistence::IIpBasedLocationDataRepository> mSut;
    std::vector<Persistence::Model::IpBasedLocationData> mTestDataList;
};

void IpBasedLocationDataRepository_Should::AddLocationDataAndGetLocationDataByIp()
{
    for (const auto& locationTestData : mTestDataList)
    {
        mSut->Add(locationTestData);
    }

    for (const auto& locationTestData : mTestDataList)
    {
        auto result = mSut->GetByIp(locationTestData.ip);
        PerformAssertions(result, locationTestData);
    }
}

void IpBasedLocationDataRepository_Should::GetAllLocationData()
{
    auto allData = mSut->GetAll();
    QCOMPARE(allData.size(), mTestDataList.size());

    for (size_t i = 0; i < allData.size(); ++i) {
        PerformAssertions(allData[i], mTestDataList[i]);
    }
}

void IpBasedLocationDataRepository_Should::DeleteLocationDataByIp()
{
    auto deletedTestDataIndex = 1;
    auto result = mSut->GetByIp(mTestDataList[deletedTestDataIndex].ip);
    QCOMPARE(result.ip, mTestDataList[deletedTestDataIndex].ip);

    mSut->DeleteByIp(mTestDataList[deletedTestDataIndex].ip);
    result = mSut->GetByIp(mTestDataList[deletedTestDataIndex].ip);
    QVERIFY(result.ip.isEmpty() || result.ip.isNull());

    auto allData = mSut->GetAll();
    QCOMPARE(allData.size(), mTestDataList.size() - 1);


    for (const auto& locationTestData : mTestDataList)
    {
        if(locationTestData.ip == mTestDataList[deletedTestDataIndex].ip)
        {
            continue;
        }

        auto result = mSut->GetByIp(locationTestData.ip);
        PerformAssertions(result, locationTestData);
    }
}

QTEST_MAIN(IpBasedLocationDataRepository_Should)

#include "IpBasedLocationDataRepository_Should.moc"

