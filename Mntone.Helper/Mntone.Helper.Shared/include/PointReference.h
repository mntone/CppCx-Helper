#pragma once
#include <Windows.h>

namespace Platform {

// If you can make Point from float32,
// use
//  (1) Point p1 = { 0.0f, 0.0f }
//  (2) Point p2 = Windows::UI::Xaml::PointHelper::FromCoordinates( 0.0f, 0.0f )
class PointReference
{
public:
	PointReference() { }
	explicit PointReference( int8 x, int8 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( int16 x, int16 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( int32 x, int32 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( int64 x, int64 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( uint8 x, uint8 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( uint16 x, uint16 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( uint32 x, uint32 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( uint64 x, uint64 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( float64 x, float64 y )
	{
		point_.X = static_cast<float32>( x );
		point_.Y = static_cast<float32>( y );
	}
	explicit PointReference( POINT value )
	{
		point_ = { static_cast<float32>( value.x ), static_cast<float32>( value.y ) };
	}

	float32 X() const
	{
		return point_.X;
	}
	float32 Y() const
	{
		return point_.Y;
	}

	operator ::Windows::Foundation::Point() const
	{
		return point_;
	}

private:
	::Windows::Foundation::Point point_;
};

}