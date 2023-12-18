#pragma once

#include "../GeolocationDataManager/Persistence/Interface/IDatabaseConnectionFactory.h"

namespace Persistence
{
    class InMemoryDatabaseConnectionFactory : public IDatabaseConnectionFactory
    {
    public:
        QSqlDatabase CreateSqliteConnection(const QString& databaseName, const QString& connectionName) const override;
    };
}
