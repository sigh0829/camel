///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CREDENTIALS_H
#define CREDENTIALS_H

///////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <sys/types.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace app
{

///////////////////////////////////////////////////////////////////////////////////////////////////
struct credentials
{
    credentials(const std::string& name);

    void morph_into();

    std::string username;
    std::string fullname;
    std::string password;

    uid_t uid;
    gid_t gid;

    std::string home;
    std::string shell;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#endif // CREDENTIALS_H