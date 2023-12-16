#include "IpStackClient.h"
#include <QtConcurrent>

namespace HttpNetwork
{
    IpStackClient::IpStackClient(const QString& apiKey)
        : QObject(nullptr)
        , manager(new QNetworkAccessManager(this))
        , mApiKey(apiKey)
    {}

    void IpStackClient::GetLocationDataRequest(const QString &input)
    {
        if(mApiKey.isEmpty())
        {
            emit GetLocationDataResponse(nullptr, "Ip stack api key is empty. Write location data to database will not work properly. Please write valid api key in Config.ini file and restart Application");
        }

        QUrl url("http://api.ipstack.com/" + input);
        QUrlQuery query;
        query.addQueryItem("access_key", mApiKey);
        url.setQuery(query);

        QNetworkRequest request(url);
        QNetworkReply *reply = manager->get(request);

        QtConcurrent::run([this, reply, input]() {
            this->waitForReply(reply, input);
        });
    }

    void IpStackClient::waitForReply(QNetworkReply *reply, const QString& input)
    {
        connect(reply, &QNetworkReply::finished, this, [this, reply, input]() {
            if (reply->error())
            {
                qDebug() << "Error:" << reply->errorString();
                emit GetLocationDataResponse(nullptr, "Connection Error! Please check your network settings.");
            }
            else
            {
                QString answer = reply->readAll();
                emit GetLocationDataResponse(answer, input);
            }
            reply->deleteLater();
        });
    }
}
