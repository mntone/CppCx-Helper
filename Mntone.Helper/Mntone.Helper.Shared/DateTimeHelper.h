﻿#pragma once

namespace Mntone { namespace Helper {
	
	public ref class DataTimeHelper sealed
	{
	public:
		static bool Equals( Windows::Foundation::DateTime target, Windows::Foundation::DateTime value );

		static Windows::Foundation::DateTime FromDate( int32 year, int32 month, int32 day );
		static Windows::Foundation::DateTime FromTime( int32 hour, int32 minute, int32 second );
		static Windows::Foundation::DateTime FromDateTime( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second );
		static Windows::Foundation::DateTime FromTimeAndNanoseconds( int32 hour, int32 minute, int32 second, int32 nanosecond );
		static Windows::Foundation::DateTime FromDateTimeAndNanoseconds( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second, int32 nanosecond );

		static Windows::Foundation::DateTime Add( Windows::Foundation::DateTime target, Windows::Foundation::DateTime value );
		static Windows::Foundation::DateTime AddTimeSpan( Windows::Foundation::DateTime target, Windows::Foundation::TimeSpan value );

		static Windows::Foundation::DateTime Subtract( Windows::Foundation::DateTime target, Windows::Foundation::DateTime value );
		static Windows::Foundation::DateTime SubtractTimeSpan( Windows::Foundation::DateTime target, Windows::Foundation::TimeSpan value );

		static int64 Compare( Windows::Foundation::DateTime dateTime1, Windows::Foundation::DateTime dateTime2 );

		static property Windows::Foundation::DateTime Now
		{
			Windows::Foundation::DateTime get();
		}

	internal:
		DataTimeHelper();
	};

} }