#include "setting.h"

#include <QStandardPaths>
#include <QDir>
#include <QSqlQuery>
#include <QDebug>

Setting::Setting()
{
    this->init();
}

bool Setting::init()
{
    QString userDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    // 创建目录，如果目录不存在
    QString configDir = userDir + "/ahri";
    QDir().mkpath(configDir);

    // 拼接SQLite数据库文件路径
    QString dbPath = configDir + "/setting.sqlite3";

     // 连接SQLite数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setPassword("ahriknow"); // 设置数据库密码
    db.setDatabaseName(dbPath);
    this->db = &db;

    // 如果数据库文件不存在，则创建数据库
    if (!QFile::exists(dbPath)) {
        if (db.open()) {
            QSqlQuery query;
            query.exec("CREATE TABLE config (key TEXT PRIMARY KEY, value TEXT)");
            qDebug() << "Created new SQLite database file: " << dbPath;
            db.close();
        } else {
            qDebug() << "Failed to create SQLite database file: " << dbPath;
        }
    }
    return true;
}

bool Setting::open()
{
    if (!db->isOpen()) {
        return db->open();
    }
    return true;
}

bool Setting::close()
{
    if (db->isOpen()) {
        db->close();
    }
    return true;
}

Setting::~Setting()
{
    this->close();
}
