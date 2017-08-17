#include "PageDensityAnalysis.h"
#include "ui_PageDensityAnalysis.h"

PageDensityAnalysis::PageDensityAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageDensityAnalysis)
{
    ui->setupUi(this);
	visible = new bool;
	*visible = true;
}

PageDensityAnalysis::~PageDensityAnalysis()
{
    delete ui;
}

void PageDensityAnalysis::on_btnView1_clicked() {
	
	//emit visibility(this->ui);

	//cout << *visible << endl;
	//emit visibility(ui);
	ui->btnView1->setIcon(QIcon("eye_off.png"));

	emit visibility(visible);
	

	if (*visible == false) {
		cout <<"f:" <<*visible << endl;
		
		ui->btnView1->setIcon(QIcon("eye_off.png"));
	}
	else {
		cout << "t:" << *visible << endl;
		ui->btnView1->setIcon(QIcon("eye_on.png"));
	}
	
	
	



}