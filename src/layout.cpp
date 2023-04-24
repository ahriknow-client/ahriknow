#include "layout.h"

#include "generate.h"

#include <QSplitter>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QPushButton>
#include <QDebug>

Layout::Layout(QWidget *parent)
    : QObject(parent)
{
    this->titlebar = createTitlebar(parent);
    this->c = createC(parent);
    this->statusbar = createStatusbar(parent);
    parent->layout()->addWidget(this->titlebar);
    parent->layout()->addWidget(this->c);
    parent->layout()->addWidget(this->statusbar);

    this->layout = createLayout(this->c);
    this->activityWidget = createActivityWidget(this->c);
    this->containerWidget = createContainerWidget(this->c);
    this->containerLayout = createContainerLayout(this->containerWidget);
    this->splitter = createSplitter(this->containerWidget);
    connect(this->splitter, &QSplitter::splitterMoved, this, &Layout::splitterMoved);
    this->sideWidget = createSideWidget(this->containerWidget);
    this->mainWidget = createMainWidget(this->containerWidget);
    this->mainLayout = createMainLayout(this->mainWidget);
    this->mainSplitter = createMainSplitter(this->mainWidget);
    connect(this->mainSplitter, &QSplitter::splitterMoved, this, &Layout::mainSplitterMoved);
    this->editWidget = createEditWidget(this->mainWidget);
    connect(qobject_cast<QTabWidget *>(editWidget->layout()->itemAt(0)->widget()), &QTabWidget::tabCloseRequested, this, &Layout::editClosed);
    this->panelWidget = createPanelWidget(this->mainWidget);

    this->containerLayout->addWidget(this->splitter);

    this->containerWidget->setLayout(this->containerLayout);

    this->mainLayout->addWidget(this->mainSplitter);

    this->mainWidget->setLayout(this->mainLayout);

    this->splitter->addWidget(this->sideWidget);
    this->splitter->addWidget(this->mainWidget);

    this->mainSplitter->addWidget(this->editWidget);
    this->mainSplitter->addWidget(this->panelWidget);

    this->layout->addWidget(this->activityWidget);
    this->layout->addWidget(this->containerWidget);

    QMenuBar *menuBar = new QMenuBar(this->layout->parentWidget());
    QMenu *fileMenu = new QMenu("File", this->layout->parentWidget());
    QMenu *editMenu = new QMenu("Edit", this->layout->parentWidget());
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->setVisible(false);
    this->layout->setMenuBar(menuBar);

    this->c->setLayout(this->layout);

    // QPushButton *button = new QPushButton("test", this->sideWidget);
    // connect(button, &QPushButton::clicked, [=]() {
    //     // splitter 设置方向
    //     if (this->mainSplitter->orientation() == Qt::Horizontal) {
    //         this->mainSplitter->setOrientation(Qt::Vertical);
    //     } else {
    //         this->mainSplitter->setOrientation(Qt::Horizontal);
    //     }
    // });

    this->sideWidget->setVisible(false);
}

bool Layout::addWidgetToActivity(int id, ActivityButton *btn)
{
    if (btn == nullptr)
    {
        return false;
    }
    QWidget *custome = this->activityWidget->layout()->itemAt(0)->widget();
    // btn->setParent(custome);
    // custome->layout()->addWidget(btn);

    WrapperWidget *wrapper = new WrapperWidget(custome, id);
    btn->setParent(wrapper);
    wrapper->layout()->addWidget(btn);

    wrapper->setFixedSize(50, 50);
    custome->layout()->addWidget(wrapper);
    return true;
}

/*
 * 侧边栏
 */
void Layout::showSide()
{
    this->sideWidget->setVisible(true);
}

void Layout::hideSide()
{
    this->sideWidget->setVisible(false);
}

/**
 * @brief 添加组件到侧边栏
 *
 * 添加组件到侧边栏
 *
 * @param widget 要添加的组件
 *
 * @return bool 是否添加成功
 */
bool Layout::addWidgetToSide(int id, SideWidget *widget)
{
    if (widget == nullptr)
    {
        return false;
    }
    WrapperWidget *wrapper = new WrapperWidget(this->sideWidget, id);
    wrapper->layout()->addWidget(widget);
    this->sideWidget->layout()->addWidget(wrapper);
    return true;
}

bool Layout::addWidgetToEdit(int id, EditWidget *widget)
{
    if (widget == nullptr)
    {
        return false;
    }
    QTabWidget *tab = qobject_cast<QTabWidget *>(this->editWidget->layout()->itemAt(0)->widget());
    if (tab == nullptr)
    {
        return false;
    }
    WrapperWidget *wrapper = new WrapperWidget(tab, id);
    wrapper->layout()->addWidget(widget);
    tab->addTab(wrapper, widget->getTitle());
    return true;
}

void Layout::activeActivity(int id)
{
    QWidget *custome = this->activityWidget->layout()->itemAt(0)->widget();
    for (int i = 0; i < custome->layout()->count(); i++)
    {
        WrapperWidget *wrapper = qobject_cast<WrapperWidget *>(custome->layout()->itemAt(i)->widget());
        if (wrapper == nullptr)
        {
            qDebug() << id << ": wrapper is null";
            continue;
        }
        QWidget *btnwidget = wrapper->layout()->itemAt(0)->widget();
        ActivityButton *btn = qobject_cast<ActivityButton *>(btnwidget);
        if (btn == nullptr)
        {
            continue;
        }
        if (wrapper->getId() == id)
        {
            btn->setActive();
            int count = this->sideWidget->count();
            if (id >= 0 && id < count)
                this->sideWidget->setCurrentIndex(btn->getId());
        }
        else
        {
            btn->setDefault();
        }
    }
}

void Layout::editClosed(int index)
{
    QWidget *tab = qobject_cast<QTabWidget *>(editWidget->layout()->itemAt(0)->widget())->widget(index);
    WrapperWidget *wrapper = qobject_cast<WrapperWidget *>(tab);
    if (wrapper == nullptr)
    {
        qDebug() << "EditClosed(" << index << "): wrapper is null";
        return;
    }
    EditWidget *edit = qobject_cast<EditWidget *>(wrapper->layout()->itemAt(0)->widget());
    if (edit == nullptr)
    {
        qDebug() << "EditClosed(" << index << "): edit is null";
        return;
    }
    emit this->removeWidgetFromEdit(wrapper->getId(), edit->getId());
    qobject_cast<QTabWidget *>(editWidget->layout()->itemAt(0)->widget())->removeTab(index);
}

void Layout::splitterMoved(int pos, int index)
{
    Q_UNUSED(pos);
    Q_UNUSED(index);
    if (this->splitter->sizes().at(0) < 200)
    {
        this->splitter->setSizes({200, this->splitter->sizes().at(1)});
    }
    if (this->splitter->sizes().at(1) < 100)
    {
        this->splitter->setSizes({this->splitter->sizes().at(0), 100});
    }
}

void Layout::mainSplitterMoved(int pos, int index)
{
    Q_UNUSED(pos);
    Q_UNUSED(index);
    if (this->mainSplitter->sizes().at(0) < 100)
    {
        this->mainSplitter->setSizes({100, this->mainSplitter->sizes().at(1)});
    }
    if (this->mainSplitter->sizes().at(1) < 100)
    {
        this->mainSplitter->setSizes({this->mainSplitter->sizes().at(0), 100});
    }
}

Layout::~Layout()
{
}
