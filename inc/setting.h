#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QSqlDatabase>

class Setting
{
public:
    Setting();
    bool init();
    bool open();
    bool close();
    ~Setting();

private:
    QSqlDatabase *db;
};
#endif // SETTING_H
