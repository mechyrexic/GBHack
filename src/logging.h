#include "main.h"
#include <string>

enum msglvls
{
    MSGLVL_CRITICAL = 0,
    MSGLVL_ERROR,
    MSGLVL_WARN,
    MSGLVL_DBG,
    MSGLVL_INFO,
    MSGLVL_NONE
};

void msg(msglvls lvl, const char* msg);