#pragma once

#include "../GeolocationDataManager/Persistence/UrlBasedLocationDataRepository.h"
#include "../GeolocationDataManager/Persistence/Model/UrlBasedLocationData.h"


class UrlBasedLocationDataRepository_Should : public QObject
{
    Q_OBJECT

public:
    UrlBasedLocationDataRepository_Should();

    ~UrlBasedLocationDataRepository_Should();

private slots:
    void initTestCase();

    void AddLocationDataAndGetLocationDataByUrl();
    void GetAllLocationData();
    void DeleteLocationDataByUrl();

    void cleanupTestCase();

private:
    void PerformAssertions(const Persistence::Model::UrlBasedLocationData& result, const Persistence::Model::UrlBasedLocationData& testData);

    void CleanDatabaseTable();

private:
    std::unique_ptr<Persistence::UrlBasedLocationDataRepository> mSut;
    std::vector<Persistence::Model::UrlBasedLocationData> mTestDataList;
};
