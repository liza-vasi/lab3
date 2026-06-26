#include "linegraph.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

        QChart* LineGraph::build(const QVector<DataPoint>& data)
{
    QChart* chart = new QChart();
    chart->setTitle("Линейный график");

    QLineSeries* series = new QLineSeries();
    for (const DataPoint& p : data) {
        series->append(p.date.toMSecsSinceEpoch(), p.value);
    }

    chart->addSeries(series);

    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setFormat("dd.MM");

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Значение");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->hide();
    return chart;
}
