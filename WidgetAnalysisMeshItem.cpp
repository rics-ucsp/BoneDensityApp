#include "WidgetAnalysisMeshItem.h"
#include "ui_WidgetAnalysisMeshItem.h"

WidgetAnalysisMeshItem::WidgetAnalysisMeshItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAnalysisMeshItem)
{
    ui->setupUi(this);
}

WidgetAnalysisMeshItem::~WidgetAnalysisMeshItem()
{
    delete ui;
}
