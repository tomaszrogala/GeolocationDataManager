#include <QtTest>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "InMemoryDatabaseConnectionFactory.h"


namespace
{
    constexpr auto DATABASE_NAME = "LocationDataTest.sqlite";
}

namespace Persistence
{
    QSqlDatabase InMemoryDatabaseConnectionFactory::CreateSqliteConnection(const QString& databaseName, const QString& connectionName) const
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName(DATABASE_NAME);
        return db;
    }
}
