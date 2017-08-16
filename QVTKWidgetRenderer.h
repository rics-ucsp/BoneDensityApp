#ifndef QVTKWIDGETRENDERER_H
#define QVTKWIDGETRENDERER_H

#include <QVTKWidget.h>

#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>

#include <vtkUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkLookupTable.h>

class QVTKWidgetRenderer{
public:
    static void renderVTK(std::string vtkFilename, QVTKWidget & widget ){
        vtkSmartPointer<vtkUnstructuredGridReader> reader   = vtkSmartPointer<vtkUnstructuredGridReader>::New();
        reader->SetFileName(vtkFilename.c_str());
        reader->Update();
    
        vtkSmartPointer<vtkDataSetMapper> mapper    =	vtkSmartPointer<vtkDataSetMapper>::New();
        mapper->SetInputConnection(reader->GetOutputPort());
      
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->GetProperty()->SetColor(1, 1, 1);
        actor->GetProperty()->SetOpacity(0.05);
        actor->SetMapper(mapper);
        
        vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->AddActor(actor);
        renderer->SetBackground(0, 0,0);
    
        widget.GetRenderWindow()->AddRenderer(renderer);
        widget.show();
    }

    static void renderCube(QVTKWidget & widget){
        vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
        cubeSource->Update();

        vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
        
        vtkSmartPointer<vtkActor> cubeActor =  vtkSmartPointer<vtkActor>::New();
        cubeActor->SetMapper(cubeMapper);
        
        vtkSmartPointer<vtkRenderer> rightRenderer = vtkSmartPointer<vtkRenderer>::New();
        rightRenderer->AddActor(cubeActor);
        
        widget.GetRenderWindow()->AddRenderer(rightRenderer);
        widget.show();
    }
};

#endif // QVTKWIDGETRENDERER_H
