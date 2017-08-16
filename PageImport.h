
#ifndef PAGEIMPORT_H
#define PAGEIMPORT_H

#include <QWidget>

namespace Ui {
	class PageImport;
}

class PageImport : public QWidget
{
	Q_OBJECT

public:
	explicit PageImport(QWidget *parent = 0);
	~PageImport();

private slots:
	void on_btnLoadVolume_clicked();

signals:
	void multiplanar_reconstruction(std::string);

private:
	Ui::PageImport *ui;
};


#endif