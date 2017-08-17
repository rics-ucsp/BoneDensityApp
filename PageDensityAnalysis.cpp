#include "PageDensityAnalysis.h"
#include "ui_PageDensityAnalysis.h"

PageDensityAnalysis::PageDensityAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageDensityAnalysis)
{
    ui->setupUi(this);

	std::string filename = "C:\rics - ucsp - project_bmd\bmc\bmc\extremidad";
	///emit multiplanar_reconstruction(filename);

	visible1 = new bool;
	*visible1 = true;

	visible2 = new bool;
	*visible2 = true;

	visible3 = new bool;
	*visible3 = true;

	visible4 = new bool;
	*visible4 = true;

	visible5 = new bool;
	*visible5 = true;

	visible6 = new bool;
	*visible6 = true;

	visible7 = new bool;
	*visible7 = true;
}

PageDensityAnalysis::~PageDensityAnalysis()
{
    delete ui;
}



void PageDensityAnalysis::on_btn2Dselection_clicked() {

	emit selection2D();

}

void PageDensityAnalysis::on_btnView1_clicked() {

	ui->btnView1->setIcon(QIcon("eye_off.png"));
	emit visibility1(visible1);
	
	if (*visible1 == false) {	
		ui->btnView1->setIcon(QIcon("eye_off.png"));
	}
	else {
		ui->btnView1->setIcon(QIcon("eye_on.png"));
	}
}

void PageDensityAnalysis::on_sldOpacity1_sliderMoved(int position) {
	emit opacity1(position);
	
}

void PageDensityAnalysis::on_btnColor1_clicked() {

	QColor newColor = QColorDialog::getColor(Qt::white, this);

	QPalette pal;
	pal.setColor(QPalette::Button, newColor);
	ui->btnColor1->setAutoFillBackground(true);
	ui->btnColor1->setPalette(pal);
	ui->btnColor1->update();

	emit colority1(newColor);

}


void PageDensityAnalysis::on_btnView2_clicked() {

	ui->btnView2->setIcon(QIcon("eye_off.png"));
	emit visibility2(visible2);

	if (*visible2 == false) {
		ui->btnView2->setIcon(QIcon("eye_off.png"));
	}
	else {
		ui->btnView2->setIcon(QIcon("eye_on.png"));
	}
}

void PageDensityAnalysis::on_sldOpacity2_sliderMoved(int position) {
	emit opacity2(position);

}

void PageDensityAnalysis::on_btnColor2_clicked() {

	QColor newColor = QColorDialog::getColor(Qt::white, this);

	QPalette pal;
	pal.setColor(QPalette::Button, newColor);
	ui->btnColor2->setAutoFillBackground(true);
	ui->btnColor2->setPalette(pal);
	ui->btnColor2->update();

	emit colority2(newColor);

}


void PageDensityAnalysis::on_btnView3_clicked() {

	ui->btnView3->setIcon(QIcon("eye_off.png"));
	emit visibility3(visible3);

	if (*visible3 == false) {
		ui->btnView3->setIcon(QIcon("eye_off.png"));
	}
	else {
		ui->btnView3->setIcon(QIcon("eye_on.png"));
	}
}

void PageDensityAnalysis::on_sldOpacity3_sliderMoved(int position) {
	emit opacity3(position);

}

void PageDensityAnalysis::on_btnColor3_clicked() {

	QColor newColor = QColorDialog::getColor(Qt::white, this);

	QPalette pal;
	pal.setColor(QPalette::Button, newColor);
	ui->btnColor3->setAutoFillBackground(true);
	ui->btnColor3->setPalette(pal);
	ui->btnColor3->update();

	emit colority3(newColor);

}



void PageDensityAnalysis::on_btnView4_clicked() {

	ui->btnView4->setIcon(QIcon("eye_off.png"));
	emit visibility4(visible4);

	if (*visible4 == false) {
		ui->btnView4->setIcon(QIcon("eye_off.png"));
	}
	else {
		ui->btnView4->setIcon(QIcon("eye_on.png"));
	}
}

void PageDensityAnalysis::on_sldOpacity4_sliderMoved(int position) {
	emit opacity4(position);

}

void PageDensityAnalysis::on_btnColor4_clicked() {

	QColor newColor = QColorDialog::getColor(Qt::white, this);

	QPalette pal;
	pal.setColor(QPalette::Button, newColor);
	ui->btnColor4->setAutoFillBackground(true);
	ui->btnColor4->setPalette(pal);
	ui->btnColor4->update();

	emit colority4(newColor);
}


void PageDensityAnalysis::on_btnView5_clicked() {

	ui->btnView5->setIcon(QIcon("eye_off.png"));
	emit visibility5(visible5);

	if (*visible5 == false) {
		ui->btnView5->setIcon(QIcon("eye_off.png"));
	}
	else {
		ui->btnView5->setIcon(QIcon("eye_on.png"));
	}
}

void PageDensityAnalysis::on_sldOpacity5_sliderMoved(int position) {
	emit opacity5(position);

}

void PageDensityAnalysis::on_btnColor5_clicked() {

	QColor newColor = QColorDialog::getColor(Qt::white, this);

	QPalette pal;
	pal.setColor(QPalette::Button, newColor);
	ui->btnColor5->setAutoFillBackground(true);
	ui->btnColor5->setPalette(pal);
	ui->btnColor5->update();

	emit colority5(newColor);
}



void PageDensityAnalysis::on_btnView6_clicked() {

	ui->btnView6->setIcon(QIcon("eye_off.png"));
	emit visibility6(visible6);

	if (*visible6 == false) {
		ui->btnView6->setIcon(QIcon("eye_off.png"));
	}
	else {
		ui->btnView6->setIcon(QIcon("eye_on.png"));
	}
}

void PageDensityAnalysis::on_sldOpacity6_sliderMoved(int position) {
	emit opacity6(position);

}

void PageDensityAnalysis::on_btnColor6_clicked() {

	QColor newColor = QColorDialog::getColor(Qt::white, this);

	QPalette pal;
	pal.setColor(QPalette::Button, newColor);
	ui->btnColor6->setAutoFillBackground(true);
	ui->btnColor6->setPalette(pal);
	ui->btnColor6->update();

	emit colority6(newColor);
}


void PageDensityAnalysis::on_btnView7_clicked() {

	ui->btnView7->setIcon(QIcon("eye_off.png"));
	emit visibility7(visible7);

	if (*visible7 == false) {
		ui->btnView7->setIcon(QIcon("eye_off.png"));
	}
	else {
		ui->btnView7->setIcon(QIcon("eye_on.png"));
	}
}

void PageDensityAnalysis::on_sldOpacity7_sliderMoved(int position) {
	emit opacity7(position);

}

void PageDensityAnalysis::on_btnColor7_clicked() {

	QColor newColor = QColorDialog::getColor(Qt::white, this);

	QPalette pal;
	pal.setColor(QPalette::Button, newColor);
	ui->btnColor7->setAutoFillBackground(true);
	ui->btnColor7->setPalette(pal);
	ui->btnColor7->update();

	emit colority7(newColor);
}