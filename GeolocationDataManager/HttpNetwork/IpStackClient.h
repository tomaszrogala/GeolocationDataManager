#pragma once

#include "IIpStackClient.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QUrlQuery>

namespace HttpNetwork
{
    class IpStackClient : public QObject, public IIpStackClient
    {
        Q_OBJECT

    public:
        explicit IpStackClient(const QString& apiKey);

        void GetLocationDataRequest(const QString &input);

    signals:
        void GetLocationDataResponse(const QString &locationInfo, const QString& url);

    private slots:
        void waitForReply(QNetworkReply *reply, const QString& url);

    private:
        QNetworkAccessManager *manager;
        QString mApiKey;
    };
}
