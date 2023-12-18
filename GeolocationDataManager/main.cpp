#include <QApplication>
#include <QSettings>

#include "mainwindow.h"
#include "Persistence/DatabaseConnectionFactory.h"
#include "Persistence/IpBasedLocationDataRepository.h"
#include "Persistence/UrlBasedLocationDataRepository.h"
#include "HttpNetwork/IpStackClient.h"
#include "Helpers/InputValidator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("config.ini", QSettings::IniFormat);

    QString databasePath = settings.value("Database/DatabasePath", "").toString();
    QString apiKey = settings.value("IpStackAPI/ApiKey", "364fd3bbd196e5c709e2d7f3136cfc23").toString();


    auto databaseConnectionFactory = std::make_shared<Persistence::DatabaseConnectionFactory>(databasePath);

    MainWindow w(
        std::make_unique<Persistence::IpBasedLocationDataRepository>(databaseConnectionFactory),
        std::make_unique<Persistence::UrlBasedLocationDataRepository>(databaseConnectionFactory),
        std::make_unique<HttpNetwork::IpStackClient>(apiKey),
        std::make_unique<Helpers::InputValidator>());
    w.show();

    return a.exec();
}
