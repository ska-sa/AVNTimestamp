
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

//System includes
#ifdef _WIN32
typedef __int64 int64_t;
#else
#include <inttypes.h>
#endif

#include <string>

//Library includes

//Local includes

namespace AVN
{

//Return the full timestamp as a string.
std::string stringFromTimestamp_full(int64_t i64Timestamp_us);

//Return the HH:mm:ss timestamp as a string.
std::string stringFromTimestamp_HHmmss(int64_t i64Timestamp_us);

//This return the time in a similar for except without the date. This is useful for printing the duration
//output when substract 1 timestamp from another
std::string stringFromTimeDuration(int64_t i64Timestamp_us);

//This function is same as above except it prints the units explicitly in the string
std::string stringFromTimeDurationExplicitUnits(int64_t i64Timestamp_us);

//Get current time. Uses microsecond clock if boost is available otherwise the <ctime> API with second accuracy
int64_t getTimeNow_us();

} // namespace AVN

#endif //TIMESTAMP_H
