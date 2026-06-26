#ifndef IGRAPH_H
#define IGRAPH_H

#include <QtCharts/QChart>
#include <QVector>
#include "datapoint.h"

QT_CHARTS_USE_NAMESPACE

    class IGraph {
public:
    virtual ~IGraph() = default;
    virtual QChart* build(const QVector<DataPoint>& data) = 0;
};

#endif // IGRAPH_H
