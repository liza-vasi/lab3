#include "mainwindow.h"
#include "sqlitereader.h"
#include "linegraph.h"
#include "bargraph.h"
#include "colorexporter.h"
#include "grayexporter.h"
#include "ioc_container.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QDir>
#include <QHeaderView>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPrinter>
#include <QPainter>

MainWindow::MainWindow(std::shared_ptr<IGraph> chart,
                       std::shared_ptr<IExporter> exporter,
                       QWidget *parent)
    : QMainWindow(parent)
    , currentChart(chart)
    , exporter(exporter)
{
    setWindowTitle("Печать графиков");
    resize(1000, 700);

    QWidget* central = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(central);

    // Левая панель
    QWidget* leftPanel = new QWidget(this);
    leftPanel->setMinimumWidth(300);
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    selectBtn = new QPushButton("Выбрать папку", this);
    folderLabel = new QLabel("Папка: " + QDir::homePath(), this);
    folderLabel->setWordWrap(true);
    leftLayout->addWidget(selectBtn);
    leftLayout->addWidget(folderLabel);

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::Files | QDir::NoDotAndDotDot);
    fileModel->setNameFilters({"*.sqlite"});
    fileModel->setNameFilterDisables(false);
    fileModel->setRootPath(QDir::homePath());

    fileTable = new QTableView(this);
    fileTable->setModel(fileModel);
    fileTable->setRootIndex(fileModel->index(QDir::homePath()));
    fileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    fileTable->setSelectionMode(QAbstractItemView::SingleSelection);
    fileTable->setColumnWidth(0, 200);
    fileTable->setColumnWidth(1, 80);
    fileTable->setColumnWidth(2, 100);
    fileTable->hideColumn(3);
    fileTable->setMinimumHeight(200);
    leftLayout->addWidget(fileTable);
    leftLayout->addStretch();

    // Правая панель
    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->addWidget(new QLabel("Тип графика:", this));
    chartCombo = new QComboBox(this);
    chartCombo->addItem("Линейный", "line");
    chartCombo->addItem("Столбчатый", "bar");
    controlLayout->addWidget(chartCombo);

    grayCheck = new QCheckBox("Черно-белый", this);
    controlLayout->addWidget(grayCheck);

    printBtn = new QPushButton("Сохранить PDF", this);
    controlLayout->addWidget(printBtn);
    controlLayout->addStretch();

    rightLayout->addLayout(controlLayout);

    themeWidget = new ThemeWidget(this);
    themeWidget->setMinimumHeight(400);
    rightLayout->addWidget(themeWidget);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(leftPanel);
    splitter->addWidget(rightPanel);
    splitter->setSizes({350, 850});
    mainLayout->addWidget(splitter);
    setCentralWidget(central);

    connect(selectBtn, &QPushButton::clicked, this, &MainWindow::onSelectFolder);
    connect(fileTable, &QTableView::doubleClicked, this, &MainWindow::onFileActivated);
    connect(chartCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onChartTypeChanged);
    connect(grayCheck, &QCheckBox::toggled, this, &MainWindow::onGrayScaleChanged);
    connect(printBtn, &QPushButton::clicked, this, &MainWindow::onExportPdf);

    dataReader = std::make_shared<SQLiteReader>();
}

MainWindow::~MainWindow() {}

void MainWindow::onSelectFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this,
        "Выберите папку с данными",
        currentFolder.isEmpty() ? QDir::homePath() : currentFolder);
    if (dir.isEmpty()) return;

    currentFolder = dir;
    folderLabel->setText("Папка: " + dir);
    fileModel->setRootPath(dir);
    fileTable->setRootIndex(fileModel->index(dir));
    statusBar()->showMessage("Папка: " + dir);
}

void MainWindow::onFileActivated(const QModelIndex &index)
{
    if (!index.isValid()) return;

    QString path = fileModel->filePath(index);
    QFileInfo info(path);
    if (!info.isFile()) return;

    QString ext = info.suffix().toLower();
    if (ext != "sqlite") {
        statusBar()->showMessage("Поддерживаются только .sqlite");
        return;
    }

    loadData(path);
}

void MainWindow::loadData(const QString& path)
{
    currentData = dataReader->readData(path);
    if (currentData.isEmpty()) {
        statusBar()->showMessage("Нет данных или ошибка формата");
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить данные.");
        return;
    }
    updateChart();
   }

void MainWindow::updateChart()
{
    if (currentData.isEmpty() || !currentChart) return;

    themeWidget->setGrayScale(grayCheck->isChecked());
    QChart* chart = currentChart->build(currentData);
    themeWidget->setChart(chart);
}

void MainWindow::onChartTypeChanged(int index)
{
    QString type = chartCombo->itemData(index).toString();
    if (type == "line")
        currentChart = std::make_shared<LineGraph>();
    else
        currentChart = std::make_shared<BarGraph>();

    if (!currentData.isEmpty()) updateChart();
}

void MainWindow::onGrayScaleChanged(bool checked)
{
    if (checked)
        exporter = std::make_shared<GrayExporter>();
    else
        exporter = std::make_shared<ColorExporter>();

    if (!currentData.isEmpty()) updateChart();
}

void MainWindow::onExportPdf()
{
    if (currentData.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет данных для экспорта");
        return;
    }

    exporter->exportPdf(themeWidget->getChartView()->chart());
    statusBar()->showMessage("PDF экспортирован");
    QMessageBox::information(this, "Успех", "График сохранён в PDF");
}
