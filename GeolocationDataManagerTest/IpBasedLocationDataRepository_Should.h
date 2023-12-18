#pragma once

#include "../GeolocationDataManager/Persistence/IpBasedLocationDataRepository.h"
#include "../GeolocationDataManager/Persistence/Model/IpBasedLocationData.h"

class IpBasedLocationDataRepository_Should : public QObject
{
    Q_OBJECT

public:
    IpBasedLocationDataRepository_Should();

    ~IpBasedLocationDataRepository_Should();

private slots:
    void initTestCase();

    void AddLocationDataAndGetLocationDataByIp();
    void GetAllLocationData();
    void DeleteLocationDataByIp();

    void cleanupTestCase();

private:
    void PerformAssertions(const Persistence::Model::IpBasedLocationData& result, const Persistence::Model::IpBasedLocationData& testData);

    void CleanDatabaseTable();

private:
    std::unique_ptr<Persistence::IIpBasedLocationDataRepository> mSut;
    std::vector<Persistence::Model::IpBasedLocationData> mTestDataList;
};
