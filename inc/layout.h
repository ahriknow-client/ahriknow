#ifndef LAYOUT_H
#define LAYOUT_H

#include "wrapperwidget.h"
#include "plugin/inc/iplugintheme.h"
#include "plugin/inc/ipluginfunction.h"
#include "plugin/inc/ipluginmodule.h"

#include <QLayout>
#include <QWidget>
#include <QStackedWidget>
#include <QSplitter>

class Layout : public QObject
{
    Q_OBJECT

private:
    /*
    layout
        |- activityWidget
        |- containerWidget (containerLayout)
            |- splitter
                |- sideWidget
                |- mainWidget (mainLayout)
                    |- mainSplitter
                        |- editWidget
                        |- panelWidget
    */
    QWidget *titlebar;
    QWidget *c;
    QWidget *statusbar;
    QHBoxLayout *layout;
    QWidget *activityWidget;
    QWidget *containerWidget;
    QHBoxLayout *containerLayout;
    QSplitter *splitter;
    QStackedWidget *sideWidget;
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QSplitter *mainSplitter;
    QWidget *editWidget;
    QWidget *panelWidget;

public:
    Layout(QWidget *parent = nullptr);

    bool addWidgetToActivity(int id, ActivityButton *btn);

    void showSide();
    void hideSide();
    bool addWidgetToSide(int id, SideWidget *widget);

    bool addWidgetToEdit(int id, EditWidget *widget);

    void activeActivity(int id);

    ~Layout();

signals:
    void removeWidgetFromEdit(int id, int oid);

private slots:
    void editClosed(int index);
    void splitterMoved(int pos, int index);
    void mainSplitterMoved(int pos, int index);
};
#endif // LAYOUT_H
