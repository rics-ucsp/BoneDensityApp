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
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_toolBox_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
