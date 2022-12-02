#include "logging.h"
#include <iostream>

void msg(msglvls lvl, const char* msg)
{
    switch (lvl)
    {
    case MSGLVL_CRITICAL:
        std::cout << "### CRITICAL ###: " << msg << '\n';
        break;
    case MSGLVL_ERROR:
        std::cout << "### ERROR: " << msg << '\n';
        break;
    case MSGLVL_WARN:
        std::cout << "# WARNING: " << msg << '\n';
        break;
    case MSGLVL_DBG:
        std::cout << "DBG: " << msg << '\n';
        break;
    case MSGLVL_INFO:
        std::cout << "INFO: " << msg << '\n';
        break;
    case MSGLVL_NONE:
        std::cout << msg << '\n';
        break;
    default:
        break;
    }
}