#include "PageDensityAnalysis.h"
#include "ui_PageDensityAnalysis.h"

PageDensityAnalysis::PageDensityAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageDensityAnalysis)
{
    ui->setupUi(this);
}

PageDensityAnalysis::~PageDensityAnalysis()
{
    delete ui;
}
