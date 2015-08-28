
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#ifdef _WIN32
typedef __int64 int64_t;
#else
#include <inttypes.h>
#endif

#include <string>
#include <sstream>
#include <iomanip>

namespace AVN
{

//Return the timestamp as a string.
//This is the format that is typically used for PXGF and ARD files.
inline std::string stringFromTimestamp(int64_t i64Timestamp_us)
{
    //make filename from zTime
    time_t ztime = i64Timestamp_us / 1000000;
    struct tm* timeInfo;
    timeInfo = localtime ( &ztime );

    char caTimeStrA[21];

    strftime ( caTimeStrA, 21, "%Y-%m-%dT%H.%M.%S.", timeInfo );

    char caTimeStrB[31];
    sprintf(caTimeStrB, "%s%.6llu", caTimeStrA, (long long unsigned int)i64Timestamp_us % 1000000 );

    return std::string(caTimeStrB, 26);
}

//This return the time in a similar for except without the date. This is useful for printing the duration
//output when substract 1 timestamp from another
inline std::string stringFromTimeDuration(int64_t i64Timestamp_us)
{
    int iNMicroSeconds = i64Timestamp_us % 1000000;
    int iNSeconds = (i64Timestamp_us / 1000000) % 60;
    int iNMinutes = (i64Timestamp_us / 60000000) % 60;
    int iNHours = (i64Timestamp_us / 3600000000) % 24;
    int iNDays = (i64Timestamp_us / 3600000000 / 24);

    //For negative time duration value all quatities end up as negative in above calculations
    //Only largest none zero quatity should be negative where applicable

    if(iNDays)
    {
        iNHours = abs(iNHours);
        iNMinutes = abs(iNMinutes);
        iNSeconds = abs(iNSeconds);
        iNMicroSeconds = abs(iNMicroSeconds);
    }
    if(iNHours)
    {
        iNMinutes = abs(iNMinutes);
        iNSeconds = abs(iNSeconds);
        iNMicroSeconds = abs(iNMicroSeconds);
    }
    if(iNMinutes)
    {
        iNSeconds = abs(iNSeconds);
        iNMicroSeconds = abs(iNMicroSeconds);
    }
    if(iNSeconds)
    {
        iNMicroSeconds = abs(iNMicroSeconds);
    }


    std::stringstream oSS;
    oSS << iNDays;
    oSS << "T";
    oSS << std::setfill('0') << std::setw(2) << iNHours;
    oSS << ".";
    oSS << std::setfill('0') << std::setw(2) << iNMinutes;
    oSS << ".";
    oSS << std::setfill('0') << std::setw(2) << iNSeconds;
    oSS << ".";
    oSS << std::setfill('0') << std::setw(6) << iNMicroSeconds;

    return oSS.str();
}

//This function is same as above except it prints the units explicitly in the string
inline std::string stringFromTimeDurationExplicitUnits(int64_t i64Timestamp_us)
{
    int iNMicroSeconds = i64Timestamp_us % 1000000;
    int iNSeconds = (i64Timestamp_us / 1000000) % 60;
    int iNMinutes = (i64Timestamp_us / 60000000) % 60;
    int iNHours = (i64Timestamp_us / 3600000000) % 24;
    int iNDays = (i64Timestamp_us / 3600000000 / 24);

    //For negative time duration value all quatities end up as negative in above calculations
    //Only largest none zero quatity should be negative where applicable

    if(iNDays)
    {
        iNHours = abs(iNHours);
        iNMinutes = abs(iNMinutes);
        iNSeconds = abs(iNSeconds);
        iNMicroSeconds = abs(iNMicroSeconds);
    }
    if(iNHours)
    {
        iNMinutes = abs(iNMinutes);
        iNSeconds = abs(iNSeconds);
        iNMicroSeconds = abs(iNMicroSeconds);
    }
    if(iNMinutes)
    {
        iNSeconds = abs(iNSeconds);
        iNMicroSeconds = abs(iNMicroSeconds);
    }
    if(iNSeconds)
    {
        iNMicroSeconds = abs(iNMicroSeconds);
    }


    std::stringstream oSS;
    if(iNDays)
    {
    oSS << iNDays;
    oSS << "d ";
    }

    if(iNDays || iNHours)
    {
    oSS << std::setfill('0') << std::setw(2) << iNHours;
    oSS << "h ";
    }

    if(iNDays || iNHours || iNMinutes)
    {
    oSS << std::setfill('0') << std::setw(2) << iNMinutes;
    oSS << "min ";
    }

    if(iNDays || iNHours || iNMinutes || iNSeconds)
    {
    oSS << std::setfill('0') << std::setw(2) << iNSeconds;
    oSS << "s ";
    }

    oSS << std::setfill('0') << std::setw(6) << iNMicroSeconds;
    oSS << "us";

    return oSS.str();
}

}


#endif //TIMESTAMP_H
