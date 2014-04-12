#pragma once

namespace Mntone { namespace Helper {

	public ref class TimeSpanHelper sealed
	{
	public:
		static bool Equals( Windows::Foundation::TimeSpan target, Windows::Foundation::TimeSpan value );

		static Windows::Foundation::TimeSpan FromNanoseconds( int64 value );
		static Windows::Foundation::TimeSpan FromMicroseconds( int64 value );
		static Windows::Foundation::TimeSpan FromMilliseconds( int64 value );
		static Windows::Foundation::TimeSpan FromSeconds( int64 value );
		static Windows::Foundation::TimeSpan FromMinutes( int64 value );
		static Windows::Foundation::TimeSpan FromHours( int64 value );
		static Windows::Foundation::TimeSpan FromDays( int64 value );
		static Windows::Foundation::TimeSpan FromWeeks( int64 value );

		static Windows::Foundation::TimeSpan Add( Windows::Foundation::TimeSpan target, Windows::Foundation::TimeSpan value );
		static Windows::Foundation::TimeSpan Subtract( Windows::Foundation::TimeSpan target, Windows::Foundation::TimeSpan value );

		static int32 Compare( Windows::Foundation::TimeSpan timeSpan1, Windows::Foundation::TimeSpan timeSpan2 );

	internal:
		TimeSpanHelper();
	};

} }