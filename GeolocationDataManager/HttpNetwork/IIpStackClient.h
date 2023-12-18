#pragma once

#include <QString>

namespace HttpNetwork
{
    class IIpStackClient
    {
    public:
        virtual ~IIpStackClient() {}

        virtual void GetLocationDataRequest(const QString &input) = 0;
    };
}

