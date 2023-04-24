#ifndef WRAPPERWIDGET_H
#define WRAPPERWIDGET_H

#include <QWidget>

class WrapperWidget : public QWidget
{
    Q_OBJECT
private:
    int id;
public:
    WrapperWidget(QWidget *parent, int id);
    int getId();
    ~WrapperWidget();
};
#endif // WRAPPERWIDGET_H
