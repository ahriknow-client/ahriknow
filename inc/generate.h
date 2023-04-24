#ifndef GENERATE_H
#define GENERATE_H

#include <QLayout>
#include <QWidget>
#include <QStackedWidget>
#include <QTabWidget>
#include <QSplitter>
#include <QMouseEvent>

/*
createLayout
    |- createActivityWidget
    |- createSplitter
        |- createSideWidget
        |- createMainWidget (createMainLayout)
            |- createEditWidget
            |- createPanelWidget
*/
QWidget *createTitlebar(QWidget *parent);
QWidget *createC(QWidget *parent);
QWidget *createStatusbar(QWidget *parent);
QHBoxLayout *createLayout(QWidget *parent);
QWidget *createActivityWidget(QWidget *parent);
QWidget *createContainerWidget(QWidget *parent);
QHBoxLayout *createContainerLayout(QWidget *parent);
QSplitter *createSplitter(QWidget *parent);
QStackedWidget *createSideWidget(QWidget *parent);
QWidget *createMainWidget(QWidget *parent);
QVBoxLayout *createMainLayout(QWidget *parent);
QSplitter *createMainSplitter(QWidget *parent);
QWidget *createEditWidget(QWidget *parent);
QWidget *createPanelWidget(QWidget *parent);
#endif // GENERATE_H
