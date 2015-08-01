#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>

#define LOGGERFILE "/var/log/ccfast.log"

class Logger
{
public:
    static void debug(const char* msg_)
    {
        using namespace std;
        using namespace boost;
        static ofstream _debug;
        if(!_debug.is_open())
        {
            _debug.open(LOGGERFILE, ios_base::out | ios_base::app);
            _debug.imbue(locale(_debug.getloc(), new posix_time::time_facet()));
        }
        _debug << '[' << posix_time::second_clock::local_time() << "] " << msg_ << endl;
    }
};

#endif // LOGGER_H
