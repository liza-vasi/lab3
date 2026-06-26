#include "bargraph.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

        QChart* BarGraph::build(const QVector<DataPoint>& data)
{
    int count = qMin(data.size(), 50);

    QChart* chart = new QChart();
    chart->setTitle("Столбчатая диаграмма (" + QString::number(count) + " точек)");

                                                                                          QBarSet* set = new QBarSet("Значения");
    QStringList categories;

                    for (int i = 0; i < count; ++i) {
                        *set << data[i].value;
                        categories << data[i].date.toString("dd.MM");
                    }

                    QBarSeries* series = new QBarSeries();
                    series->append(set);
                    chart->addSeries(series);

                    QBarCategoryAxis* axisX = new QBarCategoryAxis();
                    axisX->append(categories);
                    chart->addAxis(axisX, Qt::AlignBottom);
                    series->attachAxis(axisX);

                    QValueAxis* axisY = new QValueAxis();
                    axisY->setTitleText("Значение");
        chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return chart;
}
