#include <QtTest>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "InMemoryDatabaseConnectionFactory.h"
#include "UrlBasedLocationDataRepository_Should.h"

UrlBasedLocationDataRepository_Should::UrlBasedLocationDataRepository_Should()
{
    auto factory = std::make_shared<Persistence::InMemoryDatabaseConnectionFactory>();
    mSut = std::make_unique<Persistence::UrlBasedLocationDataRepository>(factory);
}

UrlBasedLocationDataRepository_Should::~UrlBasedLocationDataRepository_Should()
{
    CleanDatabaseTable();
}

void UrlBasedLocationDataRepository_Should::initTestCase()
{
    mTestDataList = {
        {1, "http://example2.com/1", "192.168.1.1", "Type1", "EU", "Europe",
                      "PL", "Poland", "PL-MA", "Malopolska", "Krakow", "30-001", 50.0619, 19.9368},
                     {2, "http://example3.com/2", "192.168.1.2", "Type2", "NA", "North America",
                      "US", "United States", "US-CA", "California", "Los Angeles", "90001", 34.0522, -118.2437},
                     {3, "https://example.com/3", "192.168.2.1", "Type3", "AS", "Asia",
                      "CN", "China", "CN-BJ", "Beijing", "Beijing", "100000", 39.9042, 116.4074},
                     {4, "http://example.com/4", "10.0.0.1", "Type4", "AN", "Antarctica",
                      "", "", "", "", "", "0", -82.8628, 135.0000},
                     };


    CleanDatabaseTable();
}

void UrlBasedLocationDataRepository_Should::AddLocationDataAndGetLocationDataByUrl()
{
    for (const auto& locationTestData : mTestDataList)
    {
        mSut->Add(locationTestData);
    }

    for (const auto& locationTestData : mTestDataList)
    {
        auto result = mSut->GetByUrl(locationTestData.url);
        PerformAssertions(result, locationTestData);
    }
}

void UrlBasedLocationDataRepository_Should::GetAllLocationData()
{
    auto allData = mSut->GetAll();
    QCOMPARE(allData.size(), mTestDataList.size());

    for (size_t i = 0; i < allData.size(); ++i) {
        PerformAssertions(allData[i], mTestDataList[i]);
    }
}

void UrlBasedLocationDataRepository_Should::DeleteLocationDataByUrl()
{
    auto deletedTestDataIndex = 1;
    auto result = mSut->GetByUrl(mTestDataList[deletedTestDataIndex].url);
    QCOMPARE(result.url, mTestDataList[deletedTestDataIndex].url);

    mSut->DeleteByUrl(mTestDataList[deletedTestDataIndex].url);
    result = mSut->GetByUrl(mTestDataList[deletedTestDataIndex].url);
    QVERIFY(result.url.isEmpty() || result.url.isNull());

    auto allData = mSut->GetAll();
    QCOMPARE(allData.size(), mTestDataList.size() - 1);


    for (const auto& locationTestData : mTestDataList)
    {
        if(locationTestData.url == mTestDataList[deletedTestDataIndex].url)
        {
            continue;
        }

        auto result = mSut->GetByUrl(locationTestData.url);
        PerformAssertions(result, locationTestData);
    }
}

void UrlBasedLocationDataRepository_Should::cleanupTestCase()
{
    CleanDatabaseTable();
}

void UrlBasedLocationDataRepository_Should::PerformAssertions(const Persistence::Model::UrlBasedLocationData &result, const Persistence::Model::UrlBasedLocationData &testData)
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

void UrlBasedLocationDataRepository_Should::CleanDatabaseTable()
{
    for (const auto& locationTestData : mTestDataList)
    {
        mSut->DeleteByUrl(locationTestData.url);
    }
}

#include "UrlBasedLocationDataRepository_Should.moc"

