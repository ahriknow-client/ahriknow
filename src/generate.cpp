#include "generate.h"

#include <QVariant>

QWidget *createTitlebar(QWidget *parent)
{
    // Create titlebar widget
    QWidget *titlebarWidget = new QWidget(parent);
    titlebarWidget->setObjectName("titlebarWidget");
    titlebarWidget->setFixedHeight(30);
    titlebarWidget->setProperty("class", QVariant("ahriknow-titlebar-widget"));
    return titlebarWidget;
}

QWidget *createC(QWidget *parent)
{
    // Create container widget
    QWidget *c = new QWidget(parent);
    c->setObjectName("c");
    return c;
}

QWidget *createStatusbar(QWidget *parent)
{
    // Create statusbar widget
    QWidget *statusbarWidget = new QWidget(parent);
    statusbarWidget->setObjectName("statusbarWidget");
    statusbarWidget->setFixedHeight(20);
    statusbarWidget->setProperty("class", QVariant("ahriknow-statusbar-widget"));
    return statusbarWidget;
}

QHBoxLayout *createLayout(QWidget *parent)
{
    // Create horizontal layout
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setObjectName("layout");
    layout->setMargin(0);
    layout->setSpacing(0);
    return layout;
}

QWidget *createActivityWidget(QWidget *parent)
{
    // Create activity widget
    QWidget *activityWidget = new QWidget(parent);
    activityWidget->setObjectName("activityWidget");
    activityWidget->setFixedWidth(60);
    activityWidget->setProperty("class", QVariant("ahriknow-activity-widget"));

    QVBoxLayout *activityLayout = new QVBoxLayout();
    activityLayout->setMargin(0);
    activityLayout->setSpacing(0);
    activityWidget->setLayout(activityLayout);

    QWidget *custome = new QWidget(activityWidget);
    QWidget *system = new QWidget(activityWidget);
    QVBoxLayout *systemLayout = new QVBoxLayout();
    systemLayout->setMargin(0);
    systemLayout->setSpacing(0);
    system->setLayout(systemLayout);

    QGridLayout *customeLayout = new QGridLayout();
    customeLayout->setMargin(0);
    customeLayout->setSpacing(0);
    custome->setLayout(customeLayout);

    QGridLayout *systemGrid = new QGridLayout();
    systemGrid->setMargin(0);
    systemGrid->setSpacing(0);
    systemLayout->addLayout(systemGrid);

    activityLayout->addWidget(custome);
    activityLayout->addWidget(system);

    systemLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    return activityWidget;
}

QWidget *createContainerWidget(QWidget *parent)
{
    // Create container widget
    QWidget *containerWidget = new QWidget(parent);
    containerWidget->setObjectName("containerWidget");
    return containerWidget;
}

QHBoxLayout *createContainerLayout(QWidget *parent)
{
    // Create container layout
    QHBoxLayout *containerLayout = new QHBoxLayout();
    containerLayout->setObjectName("containerLayout");
    containerLayout->setMargin(0);
    containerLayout->setSpacing(0);
    return containerLayout;
}

QSplitter *createSplitter(QWidget *parent)
{
    // Create splitter
    QSplitter *splitter = new QSplitter(Qt::Horizontal, parent);
    splitter->setObjectName("splitter");
    splitter->setProperty("class", QVariant("ahriknow-splitter"));
    return splitter;
}

QStackedWidget *createSideWidget(QWidget *parent)
{
    // Create side widget
    QStackedWidget *sideWidget = new QStackedWidget(parent);
    sideWidget->setObjectName("sideWidget");
    sideWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sideWidget->setMinimumWidth(200);
    sideWidget->setProperty("class", QVariant("ahriknow-side-widget"));
    return sideWidget;
}

QWidget *createMainWidget(QWidget *parent)
{
    // Create main widget
    QWidget *mainWidget = new QWidget(parent);
    mainWidget->setObjectName("mainWidget");
    mainWidget->setMinimumWidth(100);
    return mainWidget;
}

QVBoxLayout *createMainLayout(QWidget *parent)
{
    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setObjectName("mainLayout");
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    return mainLayout;
}

QSplitter *createMainSplitter(QWidget *parent)
{
    // Create main splitter
    QSplitter *mainSplitter = new QSplitter(Qt::Vertical, parent);
    mainSplitter->setObjectName("mainSplitter");
    mainSplitter->setProperty("class", QVariant("ahriknow-main-splitter"));
    return mainSplitter;
}

QWidget *createEditWidget(QWidget *parent)
{
    // Create edit widget
    QWidget *editWidget = new QWidget(parent);
    editWidget->setObjectName("editWidget");
    editWidget->setProperty("class", QVariant("ahriknow-edit-widget"));
    editWidget->setMinimumHeight(100);
    editWidget->setMinimumWidth(100);

    QVBoxLayout *editLayout = new QVBoxLayout();
    editLayout->setMargin(0);
    editLayout->setSpacing(0);
    editWidget->setLayout(editLayout);

    QTabWidget *editTabWidget = new QTabWidget(editWidget);
    editTabWidget->setObjectName("editTabWidget");
    editTabWidget->setProperty("class", QVariant("ahriknow-edit-tab-widget"));
    editTabWidget->setTabsClosable(true);

    editLayout->addWidget(editTabWidget);

    return editWidget;
}

QWidget *createPanelWidget(QWidget *parent)
{
    // Create panel widget
    QWidget *panelWidget = new QWidget(parent);
    panelWidget->setObjectName("panelWidget");
    panelWidget->setProperty("class", QVariant("ahriknow-panel-widget"));
    panelWidget->setMinimumHeight(100);
    panelWidget->setMinimumWidth(100);
    return panelWidget;
}
