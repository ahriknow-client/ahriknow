#include "ahriknowwindow.h"

#include "layout.h"

#include <QApplication>
#include <QPluginLoader>
#include <QPushButton>
#include <QDir>
#include <QDebug>
#include <QTabBar>
#include <QSvgWidget>
#include <QJsonObject>

AhriknowWindow::AhriknowWindow(QWidget *parent)
    : QWidget(parent)
{
    this->moduleplugins = new QList<IPluginModule *>();
    this->moduleplugins->append(new PluginManager(this));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->l = new Layout(this);

    connect(this->l, &Layout::removeWidgetFromEdit, this, &AhriknowWindow::removeWidgetFromEdit);

    qApp->setStyleSheet("\
        .ahriknow-titlebar-widget { background-color: #21252B; }\
        .ahriknow-statusbar-widget { background-color: #21252B; }\
        .ahriknow-activity-widget { background-color: #333842; }\
        .ahriknow-splitter::handle { background-color: #333842; }\
        .ahriknow-side-widget { background-color: #21252B; }\
        .ahriknow-sidetab-widget { background-color: #21252B; }\
        .ahriknow-main-splitter::handle { background-color: #333842; }\
        .ahriknow-edit-widget { background-color: #282C34; }\
        .ahriknow-panel-widget { background-color: #282C34; }\
        .ahriknow-edit-widget QTabBar::tab { background-color: #21252B; border: none; color: #D7DAE0; padding: 8px; }\
        .ahriknow-edit-widget QTabBar::tab:selected { background-color: #333842; }\
        .ahriknow-edit-widget QToolButton { background-color: #282C34; }\
        .ahriknow-edit-widget QTabBar::close-button{ border-image: url(:/icons/close-default.png); }\
        .ahriknow-edit-widget QTabBar::close-button:hover{ border-image: url(:/icons/close-active.png); }\
        .ahriknow-edit-widget QTabWidget::pane { background-color: #282C34; border: none; border-top: 2px solid #333842; }\
    ");
    this->loadPlugins();
    this->initModules();
}

bool AhriknowWindow::loadPlugins()
{
    // /home/ahri/projects/ahriknow-plugin-sqlite
    QDir pluginDir(qApp->applicationDirPath());
    pluginDir.cdUp();
    pluginDir.cdUp();
    pluginDir.cd("ahriknow-plugin-sqlite");
    pluginDir.cd("build");
    QString p = pluginDir.absoluteFilePath("sqliteplugin.so");
    qDebug() << "plugin path: " << p;
    return this->loadPlugin(p);

    pluginDir.cd("testplugins");
    pluginDir.cd("themeplugin");
    QString path = pluginDir.absoluteFilePath("libthemeplugin.so");

    return this->loadPlugin(path);
}

bool AhriknowWindow::testPlugins()
{
    // 遍历 themeplugins
    QList<IPluginTheme *>::iterator it;
    for (it = this->themeplugins->begin(); it != this->themeplugins->end(); it++)
    {
        IPluginTheme *plugin = *it;
        qDebug() << "plugin: " << plugin->id();
        qDebug() << "plugin: " << plugin->name();
        qDebug() << "plugin: " << plugin->version();
        QJsonObject theme = plugin->theme();
        qDebug() << "plugin: " << theme;
    }
    return true;
}

bool AhriknowWindow::loadPlugin(const QString &path)
{
    QPluginLoader loader(path);
    QJsonObject loaderdata = loader.metaData();
    if (loaderdata.isEmpty() || !loaderdata.contains("IID"))
    {
        qDebug() << "loaderdata is empty";
        return false;
    }

    QObject *plugin = loader.instance();
    if (plugin == nullptr)
    {
        qDebug() << "plugin is null: " << loader.errorString();
        return false;
    }

    QString iid = loaderdata["IID"].toString();

    int is_theme_plugin = iid.compare(IPluginTheme_iid);
    int is_function_plugin = iid.compare(IPluginFunction_iid);
    int is_module_plugin = iid.compare(IPluginModule_iid);

    if (is_theme_plugin != 0 && is_function_plugin != 0 && is_module_plugin != 0)
    {
        qDebug() << "Unknown plugin type: " << iid;
        return false;
    }

    if (is_theme_plugin == 0)
    {
        this->themeplugins->append(qobject_cast<IPluginTheme *>(plugin));
    }
    else if (is_function_plugin == 0)
    {
        this->functionplugins->append(qobject_cast<IPluginFunction *>(plugin));
    }
    else if (is_module_plugin == 0)
    {
        this->moduleplugins->append(qobject_cast<IPluginModule *>(plugin));
    }
    else
    {
        qDebug() << "Unknown plugin type: " << iid;
        return false;
    }

    return true;
}

bool AhriknowWindow::initModules()
{
    QList<IPluginModule *>::iterator it;
    int index = 0;
    for (it = this->moduleplugins->begin(); it != this->moduleplugins->end(); it++)
    {
        IPluginModule *plugin = *it;
        connect(plugin, &IPluginModule::addWidgetToEdit, this, [=](EditWidget *widget)
                { this->addWidgetToEdit(index, widget); });
        connect(plugin, &IPluginModule::channelSend, this, [=](QString toId, QJsonObject data)
                { this->channelReceive(plugin->id(), toId, data); });

        ActivityButton *btn = plugin->createActivityButton(this, index);
        connect(btn, &ActivityButton::clicked, this, &AhriknowWindow::activeActivity);
        this->l->addWidgetToActivity(index, btn);

        SideWidget *side = plugin->addSideWidget(this, index);
        this->l->addWidgetToSide(index, side);
        index++;
    }

    this->activeActivity(0);

    return true;
}

void AhriknowWindow::addWidgetToEdit(int id, EditWidget *widget)
{
    this->l->addWidgetToEdit(id, widget);
}

void AhriknowWindow::channelReceive(QString fromId, QString toId, QJsonObject data)
{
    if (toId == "ahriknow")
    {
        qDebug() << "ahriknow receive: " << data;
    }
    else
    {
        QList<IPluginModule *>::iterator it;
        for (it = this->moduleplugins->begin(); it != this->moduleplugins->end(); it++)
        {
            IPluginModule *plugin = *it;
            if (plugin->id() == toId)
            {
                plugin->channelReceive(fromId, data);
                break;
            }
        }
    }
}

void AhriknowWindow::activeActivity(int id)
{
    this->l->activeActivity(id);
    if (id == -1)
    {
        this->l->hideSide();
    }
    else
    {
        this->l->showSide();
    }
}

void AhriknowWindow::removeWidgetFromEdit(int id, int oid)
{
    IPluginModule *plugin = this->moduleplugins->at(id);
    plugin->removeWidgetFromEdit(oid);
}

AhriknowWindow::~AhriknowWindow()
{
}
