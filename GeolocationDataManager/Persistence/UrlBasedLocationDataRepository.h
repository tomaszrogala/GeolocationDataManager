#pragma once

#include <QObject>
#include "Interface\IUrlBasedLocationDataRepository.h"
#include "Interface\IDatabaseConnectionFactory.h"


namespace Persistence
{
    class UrlBasedLocationDataRepository : public QObject, public IUrlBasedLocationDataRepository
    {
        Q_OBJECT
    public:
        UrlBasedLocationDataRepository(std::shared_ptr<IDatabaseConnectionFactory> databaseConnectionFactory);

        std::vector<Model::UrlBasedLocationData> GetAll() override;

        Model::UrlBasedLocationData GetByUrl(const QString& url) override;

        void Add(const Model::UrlBasedLocationData& data) override;

        void DeleteByUrl(const QString& url) override;

        signals:

        void errorOccurred(const QString& errorMessage);

    private:
        std::shared_ptr<IDatabaseConnectionFactory> mDatabaseConnectionFactory;
    };
}
