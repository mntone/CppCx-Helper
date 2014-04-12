#pragma once
#include <chrono>

namespace Platform {

class TimeSpanReference
{
public:
	TimeSpanReference() { }
	explicit TimeSpanReference( ::std::chrono::nanoseconds value )
	{
		sysTime_ = ::std::chrono::duration_cast<::std::chrono::system_clock::duration>( value );
	}
	explicit TimeSpanReference( ::std::chrono::system_clock::duration value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( ::std::chrono::microseconds value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( ::std::chrono::milliseconds value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( ::std::chrono::seconds value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( ::std::chrono::minutes value )
	{
		sysTime_ = value;
	}
	explicit TimeSpanReference( ::std::chrono::hours value )
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