#include "pluginmanager.h"

#include <QDebug>

PluginManager::PluginManager(QWidget *parent) : IPluginModule(parent)
{
}

QString PluginManager::id()
{
    return "PluginManager";
}

QString PluginManager::name()
{
    return "Plugin Manager";
}

QString PluginManager::version()
{
    return "0.0.1";
}

ActivityButton *PluginManager::createActivityButton(QWidget *parent, int id)
{
    ActivityButton *btn = new ActivityButton(parent, ":/icons/plugin-default.png", ":/icons/plugin-active.png", id);
    this->btn = btn;
    return this->btn;
}

SideWidget *PluginManager::addSideWidget(QWidget *parent, int id)
{
    for (int i=0; i<2; i++)
    {
        EditWidget *w0 = new EditWidget(parent, "Plugin Manager" + QString::number(i), i);
        emit this->addWidgetToEdit(w0);
    }
    QJsonObject data;
    data.insert("id", id);
    emit this->channelSend(this->id(), data);
    SideWidget *widget = new SideWidget(parent, id);
    return widget;
}

bool PluginManager::removeWidgetFromEdit(int id)
{
    qDebug() << "removeWidgetFromEdit" << id;
    return true;
}

bool PluginManager::channelReceive(QString fromId, QJsonObject data)
{
    qDebug() << "channelReceive" << fromId << data;
    return true;
}

PluginManager::~PluginManager()
{
}
