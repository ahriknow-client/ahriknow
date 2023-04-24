#ifndef AHRIKNOWWINDOW_H
#define AHRIKNOWWINDOW_H

#include <QWidget>
#include <QMap>

#include "layout.h"
#include "wrapperwidget.h"
#include "setting.h"
#include "activitybutton.h"
#include "sidewidget.h"
#include "editwidget.h"
#include "pluginmanager.h"
#include "plugin/inc/iplugintheme.h"
#include "plugin/inc/ipluginfunction.h"
#include "plugin/inc/ipluginmodule.h"

class AhriknowWindow : public QWidget
{
    Q_OBJECT

public:
    AhriknowWindow(QWidget *parent = nullptr);
    ~AhriknowWindow();

private:
    Setting *s;
    Layout *l;
    bool loadPlugins();
    bool testPlugins();
    bool loadPlugin(const QString &path);
    QList<IPluginTheme *> *themeplugins;
    QList<IPluginFunction *> *functionplugins;
    QList<IPluginModule *> *moduleplugins;
    bool initModules();
    void addWidgetToEdit(int id, EditWidget *widget);
    void channelReceive(QString fromId, QString toId, QJsonObject data);

private slots:
    void activeActivity(int id);
    void removeWidgetFromEdit(int id, int oid);
};
#endif // AHRIKNOWWINDOW_H
