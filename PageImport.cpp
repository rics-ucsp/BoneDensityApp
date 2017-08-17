#include "PageImport.h"
#include "ui_PageImport.h"
#include "StackedMultiplanarReconstruction.h"
#include <QFileDialog>

PageImport::PageImport(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PageImport)
{
	ui->setupUi(this);
}

PageImport::~PageImport()
{
	delete ui;
}

void PageImport::on_btnLoadVolume_clicked(){
	QString folderNameDCM = QFileDialog::getExistingDirectory(this, tr("Open DCM Folder"), QDir::currentPath());
	std::string filename = folderNameDCM.toStdString();
	emit multiplanar_reconstruction(filename);

}

