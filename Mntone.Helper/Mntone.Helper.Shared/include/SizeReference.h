#pragma once
#include <Windows.h>

namespace Platform {

// If you can make Size from float32,
// use
//  (1) Size s1 = { 0.0f, 0.0f }
//  (2) Size s2 = Windows::UI::Xaml::SizeHelper::FromDimensions( 0.0f, 0.0f )
class SizeReference
{
public:
	SizeReference() { }
	explicit SizeReference( int8 width, int8 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( int16 width, int16 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( int32 width, int32 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( int64 width, int64 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( uint8 width, uint8 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( uint16 width, uint16 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( uint32 width, uint32 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( uint64 width, uint64 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( float64 width, float64 height )
	{
		size_.Width = static_cast<float32>( width );
		size_.Height = static_cast<float32>( height );
	}
	explicit SizeReference( SIZE value )
	{
		size_ = { static_cast<float32>( value.cx ), static_cast<float32>( value.cy ) };
	}

	float32 Width() const
	{
		return size_.Width;
	}
	float32 Height() const
	{
		return size_.Height;
	}

	bool IsEmpty() const
	{
		return size_.Width == 0.0f || size_.Height == 0.0f;
	}

	operator ::Windows::Foundation::Size() const
	{
		return size_;
	}

private:
	::Windows::Foundation::Size size_;
};

}