#include "mainwindow.h"
#include "ioc_container.h"
#include "linegraph.h"
#include "colorexporter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gContainer.RegisterType<IGraph, LineGraph>();
    gContainer.RegisterType<IExporter, ColorExporter>();

    auto chart = gContainer.GetObject<IGraph>();
    auto exporter = gContainer.GetObject<IExporter>();

    MainWindow w(chart, exporter);
    w.show();

    return a.exec();
}
