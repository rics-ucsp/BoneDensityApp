#ifndef WIDGETANALYSISMESHITEM_H
#define WIDGETANALYSISMESHITEM_H

#include <QWidget>

namespace Ui {
class WidgetAnalysisMeshItem;
}

class WidgetAnalysisMeshItem : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetAnalysisMeshItem(QWidget *parent = 0);
    ~WidgetAnalysisMeshItem();

private:
    Ui::WidgetAnalysisMeshItem *ui;
};

#endif // WIDGETANALYSISMESHITEM_H
