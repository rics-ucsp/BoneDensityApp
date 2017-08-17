#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolBox->setCurrentIndex(0);

    // Connect construction signals
   QObject::connect(ui->page_construct_mesh, &PageConstructMesh::constructMesh,
                    ui->stacked_construct_mesh, &StackedConstructMesh::constructMesh);

   QObject::connect(ui->page_load_volume, &PageImport::multiplanar_reconstruction,
	   ui->stacked_load_volume, &StackedMultiplanarReconstruction::multiplanar_reconstruction);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::visibility,
					ui->stacked_density_analysis, &StackedDensityAnalysis::visibility);

   //connect(	ui->page_density_analysis, SIGNAL(&PageDensityAnalysis::visibility(bool*)),
//			ui->stacked_density_analysis, SLOT(&StackedDensityAnalysis::visibility(bool*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_toolBox_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
