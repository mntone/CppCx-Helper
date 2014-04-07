#pragma once
#include <time.h>
#include <chrono>
#include <Windows.h>

namespace Platform {

class DateTimeReference
{
public:
	DateTimeReference() { }
	explicit DateTimeReference( int64 value )
	{
		dateTime_ = value;
	}
	explicit DateTimeReference( ::std::chrono::system_clock::time_point value )
	{
		dateTime_ = value.time_since_epoch().count() + 116444736000000000ll;
	}
	explicit DateTimeReference( const SYSTEMTIME& value )
	{
		FILETIME filetime;
		SystemTimeToFileTime( &value, &filetime );
		dateTime_ = *reinterpret_cast<const int64*>( &filetime );
	}
	explicit DateTimeReference( const FILETIME& value )
	{
		dateTime_ = *reinterpret_cast<const int64*>( &value );
	}

	static DateTimeReference FromTimeT( time_t value )
	{
		return DateTimeReference( 10000000ll * value + 116444736000000000ll );
	}

	int64 UniversalTime() const
	{
		return dateTime_;
	}

	operator ::Windows::Foundation::DateTime() const
	{
		return ::Windows::Foundation::DateTime{ dateTime_ };
	}

private:
	int64 dateTime_;
};

}