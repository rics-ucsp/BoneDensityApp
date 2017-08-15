#ifndef STACKEDDENSITYANALYSIS_H
#define STACKEDDENSITYANALYSIS_H

#include <QWidget>

namespace Ui {
class StackedDensityAnalysis;
}

class StackedDensityAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit StackedDensityAnalysis(QWidget *parent = 0);
    ~StackedDensityAnalysis();

private:
    Ui::StackedDensityAnalysis *ui;
};

#endif // STACKEDDENSITYANALYSIS_H
