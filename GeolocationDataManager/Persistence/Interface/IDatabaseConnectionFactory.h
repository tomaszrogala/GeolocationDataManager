#pragma once
#include <QString>
#include <QSqlDatabase>

namespace Persistence
{
    class IDatabaseConnectionFactory
    {
    public:
        virtual ~IDatabaseConnectionFactory() = default;
        virtual QSqlDatabase CreateSqliteConnection(const QString& databaseName, const QString& connectionName) const = 0;
    };
}
