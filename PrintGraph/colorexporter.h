#ifndef COLOREXPORTER_H
#define COLOREXPORTER_H


#include "iexporter.h"

class ColorExporter: public IExporter {
public:
    void exportPdf(QChart* chart) override;
};

#endif // COLOREXPORTER_H
