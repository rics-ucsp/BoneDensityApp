#include "StackedDensityAnalysis.h"
#include "ui_StackedDensityAnalysis.h"

StackedDensityAnalysis::StackedDensityAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedDensityAnalysis)
{
    ui->setupUi(this);
}

StackedDensityAnalysis::~StackedDensityAnalysis()
{
    delete ui;
}
