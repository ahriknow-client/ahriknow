#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "plugin/inc/ipluginmodule.h"

#include <QWidget>
#include <QJsonObject>

class PluginManager : public IPluginModule
{
    Q_OBJECT

private:

public:
    PluginManager(QWidget *parent = nullptr);

    ActivityButton *btn;
    QString id() override;
    QString name() override;
    QString version() override;
    ActivityButton *createActivityButton(QWidget *parent, int id) override;
    SideWidget *addSideWidget(QWidget *parent, int id) override;
    bool removeWidgetFromEdit(int id) override;
    bool channelReceive(QString fromId, QJsonObject data) override;

    ~PluginManager();
};
#endif // PLUGIN_MANAGER_H
