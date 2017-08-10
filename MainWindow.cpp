#include "MainWindow.h"
#include "ui_MainWindow.h"

// #include <vtkDataObjectToTable.h>
// #include <vtkElevationFilter.h>
// #include <vtkPolyDataMapper.h>
// #include <vtkQtTableView.h>
// #include <vtkRenderer.h>
// #include <vtkRenderWindow.h>
// #include <vtkSphereSource.h>
// #include <vtkCubeSource.h>
// #include <vtkSmartPointer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolBox->setCurrentIndex(0);

//    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
//    sphereSource->Update();
//    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
//    vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
//    sphereActor->SetMapper(sphereMapper);
 
//    vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
//    leftRenderer->AddActor(sphereActor);

//     ui->imageWidget->GetRenderWindow()->AddRenderer(leftRenderer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
