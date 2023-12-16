#ifndef IIPSTACKCLIENT_H
#define IIPSTACKCLIENT_H

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

#endif // IIPSTACKCLIENT_H
