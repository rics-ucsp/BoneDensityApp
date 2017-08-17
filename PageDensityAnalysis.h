#ifndef PAGEDENSITYANALYSIS_H
#define PAGEDENSITYANALYSIS_H

#include <QWidget>
#include<QMessageBox>
#include <iostream>
#include<QIcon>

using namespace std;

namespace Ui {
class PageDensityAnalysis;
}

class PageDensityAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit PageDensityAnalysis(QWidget *parent = 0);
    ~PageDensityAnalysis();

private:
    Ui::PageDensityAnalysis *ui;
	bool* visible;
	float opacity;

private slots:
	void on_btnView1_clicked();

signals:
	//void visibility(Ui::PageDensityAnalysis *);
	void visibility(bool*);

};

#endif // PAGEDENSITYANALYSIS_H
