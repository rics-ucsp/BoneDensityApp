#include "StackedConstructMesh.h"
#include "ui_StackedConstructMesh.h"

// #include <vtkDataObjectToTable.h>
// #include <vtkElevationFilter.h>
// #include <vtkPolyDataMapper.h>
// #include <vtkQtTableView.h>
// #include <vtkRenderer.h>
// #include <vtkRenderWindow.h>
// #include <vtkSphereSource.h>
// #include <vtkCubeSource.h>
// #include <vtkSmartPointer.h>

StackedConstructMesh::StackedConstructMesh(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedConstructMesh)
{
    ui->setupUi(this);
}

StackedConstructMesh::~StackedConstructMesh()
{
    delete ui;
}

void StackedConstructMesh::constructMesh()
{
//    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
//    sphereSource->Update();
//    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
//    vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
//    sphereActor->SetMapper(sphereMapper);

//    vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
//    leftRenderer->AddActor(sphereActor);

//     ui->stacked_construction_kmeshcm->GetRenderWindow()->AddRenderer(leftRenderer);
}
