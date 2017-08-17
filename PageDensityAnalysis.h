#ifndef PAGEDENSITYANALYSIS_H
#define PAGEDENSITYANALYSIS_H

#include <QWidget>
#include<QMessageBox>
#include <iostream>
#include<QIcon>
#include<QColorDialog>


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
	bool* visible1;
	bool* visible2;
	bool* visible3;
	bool* visible4;
	bool* visible5;
	bool* visible6;
	bool* visible7;

	//int *opacity;

private slots:

	void on_btn2Dselection_clicked();

	void on_btnView1_clicked();
	void on_sldOpacity1_sliderMoved(int position);
	void on_btnColor1_clicked();

	void on_btnView2_clicked();
	void on_sldOpacity2_sliderMoved(int position);
	void on_btnColor2_clicked();

	void on_btnView3_clicked();
	void on_sldOpacity3_sliderMoved(int position);
	void on_btnColor3_clicked();

	void on_btnView4_clicked();
	void on_sldOpacity4_sliderMoved(int position);
	void on_btnColor4_clicked();

	void on_btnView5_clicked();
	void on_sldOpacity5_sliderMoved(int position);
	void on_btnColor5_clicked();

	void on_btnView6_clicked();
	void on_sldOpacity6_sliderMoved(int position);
	void on_btnColor6_clicked();

	void on_btnView7_clicked();
	void on_sldOpacity7_sliderMoved(int position);
	void on_btnColor7_clicked();



signals:

	void selection2D();

	//void visibility(Ui::PageDensityAnalysis *);
	void visibility1(bool*);
	void opacity1(int);
	void colority1(QColor);

	void visibility2(bool*);
	void opacity2(int);
	void colority2(QColor);

	void visibility3(bool*);
	void opacity3(int);
	void colority3(QColor);

	void visibility4(bool*);
	void opacity4(int);
	void colority4(QColor);

	void visibility5(bool*);
	void opacity5(int);
	void colority5(QColor);

	void visibility6(bool*);
	void opacity6(int);
	void colority6(QColor);

	void visibility7(bool*);
	void opacity7(int);
	void colority7(QColor);

};

#endif // PAGEDENSITYANALYSIS_H
