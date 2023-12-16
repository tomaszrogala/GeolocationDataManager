#pragma once
#include <QSqlDatabase>
#include "Interface\IDatabaseConnectionFactory.h"

namespace Persistence
{
    class DatabaseConnectionFactory : public IDatabaseConnectionFactory
    {
    public:
        DatabaseConnectionFactory(const QString& databasePath);

        QSqlDatabase CreateSqliteConnection(const QString& databaseName, const QString& connectionName) const override;

    private:
        QString mDatabasePath;
    };
}
