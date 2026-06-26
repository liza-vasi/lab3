#include "sqlitereader.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SQLiteReader::SQLiteReader() {}

QVector<DataPoint> SQLiteReader::readData(const QString& path)
{
    QVector<DataPoint> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qDebug() << "Ошибка открытия БД:" << db.lastError().text();
                                             return result;
    }

    QStringList tables = db.tables();
    if (tables.isEmpty()) {
        qDebug() << "В БД нет таблиц";
        db.close();
        return result;
    }

    QString tableName = tables.first();

    QSqlQuery pragmaQuery(db);
    pragmaQuery.exec("PRAGMA table_info(" + tableName + ")");
    QStringList columns;
    while (pragmaQuery.next()) {
        columns << pragmaQuery.value(1).toString();
    }

    if (columns.size() < 2) {
        qDebug() << "В таблице меньше двух колонок";
        db.close();
        return result;
    }

    QString dateColumn = columns[0];
    QString valueColumn = columns[1];

    QString sql = QString("SELECT %1, %2 FROM %3")
                      .arg(dateColumn).arg(valueColumn).arg(tableName);
    QSqlQuery query(db);

    if (!query.exec(sql)) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
                                         db.close();
        return result;
    }

    while (query.next()) {
        DataPoint point;
        QString dateStr = query.value(0).toString();
        double value = query.value(1).toDouble();

        point.date = QDateTime::fromString(dateStr, "dd.MM.yyyy hh:mm");
        if (!point.date.isValid())
            point.date = QDateTime::fromString(dateStr, "dd.MM.yyyy h:m");
        if (!point.date.isValid())
            point.date = QDateTime::fromString(dateStr, "dd.MM.yyyy h");
        if (!point.date.isValid())
            point.date = QDateTime::fromString(dateStr, "dd.MM.yyyy hh");
        if (!point.date.isValid())
            point.date = QDateTime::fromString(dateStr, "yyyy-MM-dd hh:mm:ss");
        if (!point.date.isValid())
            point.date = QDateTime::fromString(dateStr, "yyyy-MM-dd hh:mm");
        if (!point.date.isValid())
            point.date = QDateTime::fromString(dateStr, "yyyy-MM-dd");
        if (!point.date.isValid())
            point.date = QDateTime::fromString(dateStr, "dd.MM.yyyy");

        if (point.date.isValid()) {
            point.value = value;
            result.append(point);
        }
    }

    db.close();
    return result;
}
