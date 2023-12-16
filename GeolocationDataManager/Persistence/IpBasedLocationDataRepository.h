#pragma once

#include <QObject>
#include "Interface\IIpBasedLocationDataRepository.h"
#include "Interface\IDatabaseConnectionFactory.h"


namespace Persistence
{
    class IpBasedLocationDataRepository : public QObject, public IIpBasedLocationDataRepository
    {
        Q_OBJECT
    public:
        IpBasedLocationDataRepository(std::shared_ptr<IDatabaseConnectionFactory> databaseConnectionFactory);

        std::vector<Model::IpBasedLocationData> GetAll() override;

        Model::IpBasedLocationData GetByIp(const QString& ip) override;

        void Add(const Model::IpBasedLocationData& data) override;

        void DeleteByIp(const QString& ip) override;

        signals:

        void errorOccurred(const QString& errorMessage);

    private:
        std::shared_ptr<IDatabaseConnectionFactory> mDatabaseConnectionFactory;
    };
}
