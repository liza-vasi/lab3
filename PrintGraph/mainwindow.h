#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QFileSystemModel>
#include <QTableView>
#include <memory>
#include "idatareader.h"
#include "igraph.h"
#include "iexporter.h"
#include "datapoint.h"
#include "themewidget.h"

QT_CHARTS_USE_NAMESPACE

    class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<IGraph> chart,
               std::shared_ptr<IExporter> exporter,
               QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectFolder();
    void onFileActivated(const QModelIndex &index);
    void onChartTypeChanged(int index);
    void onGrayScaleChanged(bool checked);
    void onExportPdf();

private:
    void loadData(const QString& path);
    void updateChart();

    QPushButton* selectBtn;
    QLabel* folderLabel;
    QTableView* fileTable;
    QFileSystemModel* fileModel;

    QComboBox* chartCombo;
    QCheckBox* grayCheck;
    QPushButton* printBtn;

    ThemeWidget* themeWidget;

    std::shared_ptr<IGraph> currentChart;
    std::shared_ptr<IExporter> exporter;
    std::shared_ptr<IDataReader> dataReader;

    QVector<DataPoint> currentData;
    QString currentFolder;
};

#endif // MAINWINDOW_H
