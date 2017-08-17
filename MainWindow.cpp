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

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::selection2D,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::selection2D);

   //1
   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::visibility1,
					ui->stacked_density_analysis, &StackedDensityAnalysis::visibility1);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::opacity1,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::opacity1);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::colority1,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::colority1);

   //2
   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::visibility2,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::visibility2);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::opacity2,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::opacity2);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::colority2,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::colority2);

   //3
   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::visibility3,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::visibility3);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::opacity3,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::opacity3);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::colority3,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::colority3);

   //4
   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::visibility4,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::visibility4);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::opacity4,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::opacity4);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::colority4,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::colority4);

   //5
   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::visibility5,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::visibility5);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::opacity5,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::opacity5);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::colority5,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::colority5);

   //6
   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::visibility6,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::visibility6);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::opacity6,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::opacity6);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::colority6,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::colority6);

   //7
   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::visibility7,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::visibility7);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::opacity7,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::opacity7);

   QObject::connect(ui->page_density_analysis, &PageDensityAnalysis::colority7,
	   ui->stacked_density_analysis, &StackedDensityAnalysis::colority7);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_toolBox_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
