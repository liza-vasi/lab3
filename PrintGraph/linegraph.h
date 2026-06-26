#ifndef LINEGRAPH_H
#define LINEGRAPH_H


#include "igraph.h"
class LineGraph: public IGraph {
public:
    QChart* build(const QVector<DataPoint>& data) override;
};

#endif // LINEGRAPH_H
