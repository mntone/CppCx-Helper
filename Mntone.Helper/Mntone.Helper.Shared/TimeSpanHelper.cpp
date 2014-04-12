#include "pch.h"
#include "TimeSpanHelper.h"
#include "include/TimeSpanReference.h"

using namespace std::chrono;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Mntone::Helper;

TimeSpanHelper::TimeSpanHelper()
{ }

bool TimeSpanHelper::Equals( TimeSpan target, TimeSpan value )
{
	return target.Duration == value.Duration;
}

TimeSpan TimeSpanHelper::FromNanoseconds( int64 value )
{
	return TimeSpanReference( nanoseconds( value ) );
}

TimeSpan TimeSpanHelper::FromMicroseconds( int64 value )
{
	return TimeSpanReference( microseconds( value ) );
}

TimeSpan TimeSpanHelper::FromMilliseconds( int64 value )
{
	return TimeSpanReference( milliseconds( value ) );
}

TimeSpan TimeSpanHelper::FromSeconds( int64 value )
{
	return TimeSpanReference( seconds( value ) );
}

TimeSpan TimeSpanHelper::FromMinutes( int64 value )
{
	return TimeSpanReference( minutes( value ) );
}

TimeSpan TimeSpanHelper::FromHours( int64 value )
{
	return TimeSpanReference( hours( value ) );
}


namespace std { namespace chrono {
	
	using days = duration<int, std::ratio<86400>>;
	using weeks = duration<int, std::ratio<604800>>;

} }

TimeSpan TimeSpanHelper::FromDays( int64 value )
{
	return TimeSpanReference( duration_cast<system_clock::duration>( days( value ) ) );
}

TimeSpan TimeSpanHelper::FromWeeks( int64 value )
{
	return TimeSpanReference( duration_cast<system_clock::duration>( weeks( value ) ) );
}


TimeSpan TimeSpanHelper::Add( TimeSpan target, TimeSpan value )
{
	return TimeSpan{ target.Duration + value.Duration };
}

TimeSpan TimeSpanHelper::Subtract( TimeSpan target, TimeSpan value )
{
	return TimeSpan{ value.Duration - target.Duration };
}

int32 TimeSpanHelper::Compare( TimeSpan timeSpan1, TimeSpan timeSpan2 )
{
	return static_cast<int32>( timeSpan2.Duration - timeSpan1.Duration );
}