
//System includes
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdio>

//Library includes
#ifdef BOOST_VERSION
#ifndef Q_MOC_RUN //Qt's MOC and Boost have some issues don't let MOC process boost headers
#include <boost/date_time/posix_time/posix_time.hpp>
#endif
#else
#include <ctime>
#endif

//Local includes
#include "Timestamp.h"

using namespace std;

//Return the full timestamp as a string.
string AVN::stringFromTimestamp_full(int64_t i64Timestamp_us)
{
    //make filename from zTime
    time_t ztime = i64Timestamp_us / 1000000;
    struct tm* timeInfo;
    timeInfo = localtime ( &ztime );

    char caTimeStrA[21];

    strftime ( caTimeStrA, 21, "%Y-%m-%dT%H.%M.%S.", timeInfo );

    char caTimeStrB[31];
    sprintf(caTimeStrB, "%s%.6llu", caTimeStrA, (long long unsigned int)i64Timestamp_us % 1000000 );

    return string(caTimeStrB, 26);
}

//Return the HH:mm:ss timestamp as a string.
string AVN::stringFromTimestamp_HHmmss(int64_t i64Timestamp_us)
{
    //make filename from zTime
    time_t ztime = i64Timestamp_us / 1000000;
    struct tm* timeInfo;
    timeInfo = localtime ( &ztime );

    char caTimeStr[10];

    strftime ( caTimeStr, 10, "%H:%M:%S", timeInfo );

    return string(caTimeStr, 10);
}

//This return the time in a similar for except without the date. This is useful for printing the duration
//output when substract 1 timestamp from another
string AVN::stringFromTimeDuration(int64_t i64Timestamp_us)
{
    int iNMicroSeconds = i64Timestamp_us % 1000000;
    int iNSeconds = (i64Timestamp_us / 1000000) % 60;
    int iNMinutes = (i64Timestamp_us / 60000000) % 60;
    int iNHours = (i64Timestamp_us / 3600000000LL) % 24;
    int iNDays = (i64Timestamp_us / 3600000000LL / 24);
    bool bNegative = i64Timestamp_us < 0;

    //For negative time duration value all quatities end up as negative in above calculations
    //Only largest none zero quatity should be negative where applicable

    iNHours = abs(iNHours);
    iNMinutes = abs(iNMinutes);
    iNSeconds = abs(iNSeconds);
    iNMicroSeconds = abs(iNMicroSeconds);

    stringstream oSS;
    if(bNegative)
        oSS << std::string("-");
    oSS << iNDays;
    oSS << "T";
    oSS << setfill('0') << setw(2) << iNHours;
    oSS << ".";
    oSS << setfill('0') << setw(2) << iNMinutes;
    oSS << ".";
    oSS << setfill('0') << setw(2) << iNSeconds;
    oSS << ".";
    oSS << setfill('0') << setw(6) << iNMicroSeconds;

    return oSS.str();
}

//This function is same as above except it prints the units explicitly in the string
string AVN::stringFromTimeDurationExplicitUnits(int64_t i64Timestamp_us)
{
    int iNMicroSeconds = i64Timestamp_us % 1000000;
    int iNSeconds = (i64Timestamp_us / 1000000) % 60;
    int iNMinutes = (i64Timestamp_us / 60000000) % 60;
    int iNHours = (i64Timestamp_us / 3600000000LL) % 24;
    int iNDays = (i64Timestamp_us / 3600000000LL / 24);
    bool bNegative = i64Timestamp_us < 0;

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


    stringstream oSS;
    if(bNegative)
        oSS << std::string("-");

    if(iNDays)
    {
        oSS << iNDays;
        oSS << "d ";
    }

    if(iNDays || iNHours)
    {
        oSS << setfill('0') << setw(2) << iNHours;
        oSS << "h ";
    }

    if(iNDays || iNHours || iNMinutes)
    {
        oSS << setfill('0') << setw(2) << iNMinutes;
        oSS << "min ";
    }

    if(iNDays || iNHours || iNMinutes || iNSeconds)
    {
        oSS << setfill('0') << setw(2) << iNSeconds;
        oSS << "s ";
    }

    oSS << setfill('0') << setw(6) << iNMicroSeconds;
    oSS << "us";

    return oSS.str();
}

int64_t AVN::getTimeNow_us()
{
    //If boost is available use its microsecond clock.
    //Otherwise use default ctime API (only returns integer seconds)

#ifdef BOOST_VERSION
    boost::posix_time::ptime oTimeNow = boost::posix_time::microsec_clock::universal_time();
    boost::posix_time::ptime oEpoch = boost::posix_time::time_from_string(string("1970-01-01 00:00:00.000"));
    boost::posix_time::time_duration oDuration = oTimeNow - oEpoch;

    int64_t i64TimeNow_us = oDuration.total_microseconds();
#else
    time_t timeNow;
    time ( &timeNow );

    struct tm epoch;
    epoch.tm_hour = 0; //These 3 since midnight
    epoch.tm_min = 0;
    epoch.tm_sec = 0;
    epoch.tm_year = 70; //Years since 1900 (we want 1970)
    epoch.tm_mon = 0; //Months since January
    epoch.tm_mday = 1;  //Day of the month

    int64_t i64TimeNow_us = difftime(timeNow, mktime(&epoch)) * 1000000LL;
#endif

    return i64TimeNow_us;
}
