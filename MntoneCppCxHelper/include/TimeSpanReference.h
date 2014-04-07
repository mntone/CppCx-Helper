#pragma once
#include <chrono>

namespace std { namespace chrono { using days = duration<int, std::ratio<86400>>; } }

namespace Platform {

class TimeSpanReference
{
public:
	TimeSpanReference() { }
	explicit TimeSpanReference( const ::std::chrono::nanoseconds& value )
	{
		sysTime_ = ::std::chrono::duration_cast<::std::chrono::system_clock::duration>( value );
	}
	explicit TimeSpanReference( const ::std::chrono::system_clock::duration& value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( const ::std::chrono::microseconds& value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( const ::std::chrono::milliseconds& value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( const ::std::chrono::seconds& value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( const ::std::chrono::minutes& value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( const ::std::chrono::hours& value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( const ::std::chrono::days& value )
	{
		sysTime_ = value;
	}

	int64 Duration() const
	{
		return sysTime_.count();
	}

	operator ::Windows::Foundation::TimeSpan() const
	{
		return ::Windows::Foundation::TimeSpan{ sysTime_.count() };
	}

private:
	::std::chrono::system_clock::duration sysTime_;
};

}