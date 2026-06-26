#include "themewidget.h"
#include <QVBoxLayout>

ThemeWidget::ThemeWidget(QWidget *parent)
    : QWidget(parent), isGrayScale(false)
{
    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);

    QChart* emptyChart = new QChart();
    emptyChart->setTitle("Выберите файл с данными");
    chartView->setChart(emptyChart);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

void ThemeWidget::setGrayScale(bool enabled)
{
    isGrayScale = enabled;
}

void ThemeWidget::setChart(QChart* chart)
{
    if (isGrayScale) {
        chart->setTheme(QChart::ChartThemeHighContrast);
    } else {
        chart->setTheme(QChart::ChartThemeLight);
    }

    QChart* oldChart = chartView->chart();
    chartView->setChart(chart);
    delete oldChart;
}

QChartView* ThemeWidget::getChartView()
{
    return chartView;
}
