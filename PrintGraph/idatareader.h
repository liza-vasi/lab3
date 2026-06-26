#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <QVector>
#include <QString>
#include "datapoint.h"

class IDataReader
{
public:
    virtual ~IDataReader() = default;
    virtual QVector<DataPoint> readData(const QString& path) = 0;
};

#endif // IDATAREADER_H
