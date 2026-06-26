#include "colorexporter.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QtCharts/QChartView>

void ColorExporter::exportPdf(QChart* chart) {
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    "Сохранить PDF", "graph.pdf", "PDF files (*.pdf)");

    if (fileName.isEmpty()) return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&writer);

    QChartView view(chart);
    view.render(&painter);
    painter.end();
}
