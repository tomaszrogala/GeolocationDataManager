#pragma once

#include <vector>
#include <QString>
#include "..\Model\IpBasedLocationData.h"

namespace Persistence
{
    class IIpBasedLocationDataRepository
    {
    public:
        virtual ~IIpBasedLocationDataRepository() {}

        virtual std::vector<Model::IpBasedLocationData> GetAll() = 0;

        virtual Model::IpBasedLocationData GetByIp(const QString& ip) = 0;

        virtual void Add(const Model::IpBasedLocationData& data) = 0;

        virtual void DeleteByIp(const QString& ip) = 0;
    };
}
