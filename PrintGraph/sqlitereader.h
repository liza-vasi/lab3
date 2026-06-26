#ifndef SQLITEREADER_H
#define SQLITEREADER_H

#include "idatareader.h"

class SQLiteReader : public IDataReader
{
public:
    SQLiteReader();
    QVector<DataPoint> readData(const QString& path) override;
};

#endif // SQLITEREADER_H
