///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MANAGER_H
#define MANAGER_H

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "config.h"
#include "x11.h"

#include <QObject>
#include <QString>

///////////////////////////////////////////////////////////////////////////////////////////////////
class Manager: public QObject
{
    Q_OBJECT
public:
    explicit Manager(QString config_path= QString(), QObject* parent= nullptr);
    int exec();

private:
    Config config;
    X11::Server server;
    QString username, password;

    void render();

private slots:
    void get_cred(const QString& username, const QString& password);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
#endif // MANAGER_H
