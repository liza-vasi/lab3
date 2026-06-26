#ifndef IEXPORTER_H
#define IEXPORTER_H

#include <QtCharts/QChart>
QT_CHARTS_USE_NAMESPACE

class IExporter
{
public:
    virtual ~IExporter() = default;
    virtual void exportPdf(QChart* chart) = 0;
};

#endif // IEXPORTER_H
