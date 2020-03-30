#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection(const QString &s)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Mydatabase.db");
    if(!db.open()) return false;
    QSqlQuery query;
    query.exec(s);
    return true;
}


#endif // CREATCONNECTION_H
