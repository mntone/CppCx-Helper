#pragma once
#include <Windows.h>

namespace Platform {

// If you can make Rect from float32, Points, or Point and Size,
// use
//  (1) Rect r1 = { 0.0f, 0.0f, 0.0f, 0.0f }
//  (2) Rect r2 = Windows::UI::Xaml::RectHelper::FromCoordinatesAndDimensions( 0.0f, 0.0f, 0.0f, 0.0f )
//  (3) Rect r3 = Windows::UI::Xaml::RectHelper::FromPoints( p0, p0 )
//  (4) Rect r4 = Windows::UI::Xaml::RectHelper::FromLocationAndSize( p0, s0 )
class RectReference
{
public:
	RectReference() { }
	explicit RectReference( int8 x, int8 y, int8 width, int8 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( int16 x, int16 y, int16 width, int16 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( int32 x, int32 y, int32 width, int32 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( int64 x, int64 y, int64 width, int64 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( uint8 x, uint8 y, uint8 width, uint8 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( uint16 x, uint16 y, uint16 width, uint16 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( uint32 x, uint32 y, uint32 width, uint32 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( uint64 x, uint64 y, uint64 width, uint64 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( float64 x, float64 y, float64 width, float64 height )
	{
		rect_.X = static_cast<float32>( x );
		rect_.Y = static_cast<float32>( y );
		rect_.Width = static_cast<float32>( width );
		rect_.Height = static_cast<float32>( height );
	}
	explicit RectReference( RECT value )
	{
		rect_ = {
			static_cast<float32>( value.left ),
			static_cast<float32>( value.top ),
			static_cast<float32>( value.right - value.left ),
			static_cast<float32>( value.bottom - value.top ) };
	}
	explicit RectReference( POINT value1, POINT value2 )
	{
		rect_ = {
			static_cast<float32>( value1.x ),
			static_cast<float32>( value1.y ),
			static_cast<float32>( value2.x - value1.x ),
			static_cast<float32>( value2.y - value1.y ) };
	}
	explicit RectReference( POINT point, SIZE size )
	{
		rect_ = {
			static_cast<float32>( point.x ),
			static_cast<float32>( point.y ),
			static_cast<float32>( size.cx ),
			static_cast<float32>( size.cy ) };
	}

	float32 X() const
	{
		return rect_.X;
	}
	float32 Y() const
	{
		return rect_.Y;
	}
	float32 Width() const
	{
		return rect_.Width;
	}
	float32 Height() const
	{
		return rect_.Height;
	}

	float32 Left() const
	{
		return rect_.X;
	}
	float32 Top() const
	{
		return rect_.Y;
	}
	float32 Right() const
	{
		return rect_.X + rect_.Width;
	}
	float32 Bottom() const
	{
		return rect_.Y + rect_.Height;
	}

	bool IsEmpty() const
	{
		return rect_.Width == 0.0f || rect_.Height == 0.0f;
	}

	operator ::Windows::Foundation::Rect() const
	{
		return rect_;
	}

private:
	::Windows::Foundation::Rect rect_;
};

}