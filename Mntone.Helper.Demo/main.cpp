#include "pch.h"

#define USE_WIN32_INTEROP
#include "../Mntone.Helper/Mntone.Helper.Shared/include/mnhelper.h"

using namespace std::chrono;
using namespace Platform;
using namespace Windows::Foundation;

// float (max integer 16777216=2^24)
// thus, 32-bit integer (int32/uint32), 64-bit integer (int64/uint64) cannot convert completely!

int main( Array<String^>^ args )
{
	TimeSpan chrono_timespan = TimeSpanReference( seconds( 2 ) );
	TimeSpan winrt_timespan = TimeSpan{ 2 * 10000000 };
	Platform::Details::Console::WriteLine(
		chrono_timespan.Duration == winrt_timespan.Duration
			? "TimeSpanReference is true."
			: "TimeSpanReference is false." );

	DateTime time_t_datetime = DateTimeReference::FromTimeT( ::time( nullptr ) );
	DateTime chrono_datetime = DateTimeReference( system_clock::now() );
	DateTime filetime_datetime;
	{
		FILETIME ft;
		GetSystemTimeAsFileTime( &ft );
		filetime_datetime.UniversalTime = *reinterpret_cast<int64*>( &ft );
	}
	DateTime winrt_datetime = ( ref new Windows::Globalization::Calendar() )->GetDateTime();
	Platform::Details::Console::WriteLine(
		chrono_datetime.UniversalTime / 10000000 == time_t_datetime.UniversalTime / 10000000
		&& chrono_datetime.UniversalTime / 1000000 == filetime_datetime.UniversalTime / 1000000
		&& chrono_datetime.UniversalTime / 1000000 == winrt_datetime.UniversalTime / 1000000
			? "DateTimeReference is true."
			: "DateTimeReference is false." );

	Point number_point = PointReference( 10, 100 );
	Point win32_point = PointReference( POINT{ 10, 100 } );
	Point winrt_point = { 10.0f, 100.0f };
	Platform::Details::Console::WriteLine(
		number_point == win32_point && number_point == winrt_point
			? "PointReference is true."
			: "PointReference is false." );

	Rect number_rect = RectReference( 10, 100, 1000, 10000 );
	Rect win32_rect1 = RectReference( RECT{ 10, 100, 10 + 1000, 100 + 10000 } );
	Rect win32_rect2 = RectReference( POINT{ 10, 100 }, POINT{ 10 + 1000, 100 + 10000 } );
	Rect win32_rect3 = RectReference( POINT{ 10, 100 }, SIZE{ 1000, 10000 } );
	Rect winrt_rect = { 10.0f, 100.0f, 1000.0f, 10000.0f };
	Platform::Details::Console::WriteLine(
		number_rect == win32_rect1 && number_rect == win32_rect2 && number_rect == win32_rect3 && number_rect == winrt_rect
		? "RectReference is true."
		: "RectReference is false." );

	Size number_size = SizeReference( 10, 100 );
	Size win32_size = SizeReference( SIZE{ 10, 100 } );
	Size winrt_size = { 10.0f, 100.0f };
	Platform::Details::Console::WriteLine(
		number_size == win32_size && number_size == winrt_size
		? "SizeReference is true."
		: "SizeReference is false." );


	const auto count = 2000;
	auto timer1 = high_resolution_clock::now();
	auto vector = ref new Platform::Collections::Vector<String^>();
	for( auto i = 0; i < count; ++i )
	{
		vector->Append( "ap1" );
		vector->InsertAt( 0, "pre1" );
	}
	auto vecTime = high_resolution_clock::now() - timer1;
	Platform::Details::Console::WriteLine( vecTime.count() );

	auto timer2 = high_resolution_clock::now();
	auto deque = ref new Platform::Collections::Deque<String^>();
	for( auto i = 0; i < count; ++i )
	{
		deque->Append( "ap1" );
		//deque->Prepend( "pre1" );
		deque->InsertAt( 0, "pre1" );
	}
	auto deqTime = high_resolution_clock::now() - timer2;
	Platform::Details::Console::WriteLine( deqTime.count() );

	return 0;
}