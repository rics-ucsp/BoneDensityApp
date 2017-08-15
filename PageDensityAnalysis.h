#ifndef PAGEDENSITYANALYSIS_H
#define PAGEDENSITYANALYSIS_H

#include <QWidget>

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
};

#endif // PAGEDENSITYANALYSIS_H
