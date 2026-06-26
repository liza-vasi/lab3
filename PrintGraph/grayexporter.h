#ifndef GRAYEXPORTER_H
#define GRAYEXPORTER_H

#include "iexporter.h"

class GrayExporter : public IExporter {
public:
    void exportPdf(QChart* chart) override;
};

#endif // GRAYEXPORTER_H
