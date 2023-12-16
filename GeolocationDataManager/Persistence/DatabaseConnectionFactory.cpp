#include <QSqlDatabase>
#include "DatabaseConnectionFactory.h"

namespace Persistence
{
DatabaseConnectionFactory::DatabaseConnectionFactory(const QString &databasePath)
    : mDatabasePath(databasePath)
{

}

QSqlDatabase DatabaseConnectionFactory::CreateSqliteConnection(const QString& databaseName, const QString& connectionName) const
    {
        QSqlDatabase db;

        if (QSqlDatabase::contains(connectionName))
        {
            db = QSqlDatabase::database(connectionName);
        }
        else
        {
            db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
            db.setDatabaseName(mDatabasePath+databaseName);
        }

        return db;
    }
}
