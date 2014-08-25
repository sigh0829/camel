///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CONFIG_H
#define CONFIG_H

///////////////////////////////////////////////////////////////////////////////////////////////////
#include <QStringList>
#include <QString>

///////////////////////////////////////////////////////////////////////////////////////////////////
struct Config
{
    QString server_path;
    QString server_auth;
    QStringList server_args;

    QString theme_path= "/usr/share/camel/theme";
    QString theme_name= "default";

    static const QString default_path;

    void parse(const QString& path= default_path);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
#endif // CONFIG_H
