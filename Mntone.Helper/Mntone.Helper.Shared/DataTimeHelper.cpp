#include "pch.h"
#include "DateTimeHelper.h"
#include <Windows.h>

using namespace Platform;
using namespace Windows::Foundation;
using namespace Mntone::Helper;

DataTimeHelper::DataTimeHelper()
{ }

bool DataTimeHelper::Equals( DateTime target, DateTime value )
{
	return target.UniversalTime == value.UniversalTime;
}

DateTime DataTimeHelper::FromDate( int32 year, int32 month, int32 day )
{
	auto calendar = ref new Windows::Globalization::Calendar();
	calendar->Year = year;
	calendar->Month = month;
	calendar->Day = day;
	calendar->Hour = 0;
	calendar->Minute = 0;
	calendar->Second = 0;
	calendar->Nanosecond = 0;
	return calendar->GetDateTime();
}

DateTime DataTimeHelper::FromTime( int32 hour, int32 minute, int32 second )
{
	auto calendar = ref new Windows::Globalization::Calendar();
	calendar->Hour = hour;
	calendar->Minute = minute;
	calendar->Second = second;
	calendar->Nanosecond = 0;
	return calendar->GetDateTime();
}

DateTime DataTimeHelper::FromDateTime( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second )
{
	auto calendar = ref new Windows::Globalization::Calendar();
	calendar->Year = year;
	calendar->Month = month;
	calendar->Day = day;
	calendar->Hour = hour;
	calendar->Minute = minute;
	calendar->Second = second;
	calendar->Nanosecond = 0;
	return calendar->GetDateTime();
}

DateTime DataTimeHelper::FromTimeAndNanoseconds( int32 hour, int32 minute, int32 second, int32 nanosecond )
{
	auto calendar = ref new Windows::Globalization::Calendar();
	calendar->Hour = hour;
	calendar->Minute = minute;
	calendar->Second = second;
	calendar->Nanosecond = nanosecond;
	return calendar->GetDateTime();
}

DateTime DataTimeHelper::FromDateTimeAndNanoseconds( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second, int32 nanosecond )
{
	auto calendar = ref new Windows::Globalization::Calendar();
	calendar->Year = year;
	calendar->Month = month;
	calendar->Day = day;
	calendar->Hour = hour;
	calendar->Minute = minute;
	calendar->Second = second;
	calendar->Nanosecond = nanosecond;
	return calendar->GetDateTime();
}

DateTime DataTimeHelper::Now::get()
{
	FILETIME ft;
	GetSystemTimeAsFileTime( &ft );
	return DateTime{ *reinterpret_cast<int64*>( &ft ) };
}