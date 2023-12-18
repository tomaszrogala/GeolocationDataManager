#pragma once

#include <vector>
#include <QString>
#include "..\Model\UrlBasedLocationData.h"

namespace Persistence
{
    class IUrlBasedLocationDataRepository
    {
    public:
        virtual ~IUrlBasedLocationDataRepository() {}

        virtual bool Initialize() = 0;

        virtual std::vector<Model::UrlBasedLocationData> GetAll() = 0;

        virtual void Add(const Model::UrlBasedLocationData& data) = 0;

        virtual Model::UrlBasedLocationData GetByUrl(const QString& url) = 0;

        virtual void DeleteByUrl(const QString& url) = 0;
    };
}
