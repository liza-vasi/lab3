#ifndef BARGRAPH_H
#define BARGRAPH_H

#include "igraph.h"
class BarGraph: public IGraph {
public:
    QChart* build(const QVector<DataPoint>& data) override;
};

#endif // BARGRAPH_H
