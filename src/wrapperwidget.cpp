#include "wrapperwidget.h"

#include <QGridLayout>

WrapperWidget::WrapperWidget(QWidget *parent, int id) : QWidget(parent)
{
    this->id = id;
    QGridLayout *layout = new QGridLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

int WrapperWidget::getId()
{
    return this->id;
}

WrapperWidget::~WrapperWidget()
{
}
