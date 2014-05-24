#pragma once
#include <deque>
#include <collection.h>

#define _COLLECTION_ATTRIBUTES [::Platform::Metadata::RuntimeClassName] [::Windows::Foundation::Metadata::Default]

#define _COLLECTION_TRANSLATE } \
catch( const ::std::bad_alloc& ){throw ref new OutOfMemoryException;} \
catch( const ::std::exception& ){throw ref new FailureException;}

#ifndef _COLLECTION_WUXI
#define _COLLECTION_WUXI 1
#endif

#ifdef _WIN64
#pragma pack( push, 16 )
#else
#pragma pack( push, 8 )
#endif

#pragma warning( push, 4 )
#pragma warning( disable: 4451 )

namespace Platform { namespace Collections {

	namespace Details {

		template<typename T, typename E>
		inline bool DequeIndexOf( const ::std::deque<typename Wrap<T>::type>& v, T value, unsigned int * index )
		{
			auto pred = [&]( const typename Wrap<T>::type& elem ) { return E()( Unwrap( elem ), value ); };

			*index = static_cast<unsigned int>( ::std::find_if( v.begin(), v.end(), pred ) - v.begin() );

			return *index < v.size();
		}

		template<typename T>
		inline unsigned int DequeGetMany( const ::std::deque<typename Wrap<T>::type>& v, unsigned int startIndex, WriteOnlyArray<T>^ dest )
		{
			unsigned int capacity = dest->Length;

			unsigned int actual = static_cast<unsigned int>( v.size() ) - startIndex;

			if( actual > capacity )
			{
				actual = capacity;
			}

			for( unsigned int i = 0; i < actual; ++i )
			{
				dest->set( i, Unwrap( v[startIndex + i] ) );
			}

			return actual;
		}

#if _COLLECTION_WUXI
		template<typename T, typename E>
		inline bool DequeBindableIndexOf( ::std::false_type, const ::std::deque<typename Wrap<T>::type>& v, Object^ o, unsigned int * index )
		{
			IBox<T>^ ib = dynamic_cast<IBox<T>^>( o );

			if( ib )
			{
				return DequeIndexOf<T, E>( v, ib->Value, index );
			}
			else
			{
				*index = static_cast<unsigned int>( v.size() );
				return false;
			}
		}

		template<typename T, typename E>
		inline bool DequeBindableIndexOf( ::std::true_type, const ::std::deque<typename Wrap<T>::type>& v, Object^ o, unsigned int * index )
		{
			T t = dynamic_cast<T>( o );

			if( !o || t )
			{
				return DequeIndexOf<T, E>( v, t, index );
			}
			else
			{
				*index = static_cast<unsigned int>( v.size() );
				return false;
			}
		}

		template <typename T, typename E>
		inline bool DequeBindableIndexOf( const ::std::deque<typename Wrap<T>::type>& v, Object^ o, unsigned int * index )
		{
			return DequeBindableIndexOf<T, E>( is_hat<T>(), v, o, index );
		}
#endif

		template<typename T>
		ref class IteratorForDequeView sealed
			: public _COLLECTION_ATTRIBUTES WFC::IIterator<T>
#if _COLLECTION_WUXI
			, public WUXI::IBindableIterator
#endif
		{
		private:
			typedef ::std::deque<typename Wrap<T>::type> WrappedDeque;
			typedef WFC::IIterator<T> WFC_Base;

#if _COLLECTION_WUXI
			typedef WUXI::IBindableIterator WUXI_Base;
#endif

		internal:
			IteratorForDequeView( const ::std::shared_ptr<unsigned int>& ctr, const ::std::shared_ptr<WrappedDeque>& vec )
				: m_ctr( ctr )
				, m_vec( vec )
				, m_good_ctr( *ctr )
				, m_index( 0 )
			{ }

		public:
			virtual property T Current
			{
				virtual T get() = WFC_Base::Current::get
				{
					ValidateCounter( m_ctr, m_good_ctr );

					ValidateBounds( m_index < m_vec->size() );

					return Unwrap( ( *m_vec )[m_index] );
				}
			}

			virtual property bool HasCurrent
			{
				virtual bool get()
				{
					ValidateCounter( m_ctr, m_good_ctr );

					return m_index < m_vec->size();
				}
			}

			virtual bool MoveNext()
			{
				ValidateCounter( m_ctr, m_good_ctr );

				ValidateBounds( m_index < m_vec->size() );

				++m_index;
				return m_index < m_vec->size();
			}

			virtual unsigned int GetMany( WriteOnlyArray<T>^ dest )
			{
				ValidateCounter( m_ctr, m_good_ctr );

				unsigned int actual = DequeGetMany( *m_vec, m_index, dest );

				m_index += actual;

				return actual;
			}

		private:

#if _COLLECTION_WUXI
			virtual Object^ BindableCurrent() = WUXI_Base::Current::get
			{
				return Current;
			}
#endif

			::std::shared_ptr<unsigned int> m_ctr;
			::std::shared_ptr<WrappedDeque> m_vec;
			unsigned int m_good_ctr;
			unsigned int m_index;
		};

	}

	template<typename T, typename E = ::std::equal_to<T>, bool = __is_valid_winrt_type( T )> ref class Deque;
	template<typename T, typename E = ::std::equal_to<T>, bool = __is_valid_winrt_type( T )> ref class DequeView;
	
	template<typename T, typename E>
	ref class DequeView<T, E, false>
	{
		static_assert( Details::AlwaysFalse<T>::value, "Platform::Collections::DequeView<T, E> requires T to be a valid Windows Runtime type." );
	};

	template<typename T, typename E, bool>
	ref class DequeView sealed
		: public _COLLECTION_ATTRIBUTES Details::WFC::IVectorView<T>
#if _COLLECTION_WUXI
		, public Details::WUXI::IBindableVectorView
#endif
	{
	private:
		typedef ::std::deque<typename Details::Wrap<T>::type> WrappedDeque;
		typedef Details::WFC::IVectorView<T> WFC_Base;

#if _COLLECTION_WUXI
		typedef Details::WUXI::IBindableVectorView WUXI_Base;
#endif

	internal:
		DequeView()
		{
			Details::Init( m_ctr, m_vec );

			m_good_ctr = 0;
		}

		explicit DequeView( unsigned int size )
		{
			Details::Init( m_ctr, m_vec, size );

			m_good_ctr = 0;
		}

		DequeView( unsigned int size, T value )
		{
			Details::Init( m_ctr, m_vec, size, Details::MakeWrap( value ) );

			m_good_ctr = 0;
		}

		template<typename U>
		explicit DequeView( const ::std::deque<U>& v, typename Details::VectorEnableIf<T, U>::type = nullptr )
		{
			Details::Init( m_ctr, m_vec, v.begin(), v.end() );

			m_good_ctr = 0;
		}

		template<typename U>
		explicit DequeView( ::std::deque<U>&& v, typename Details::VectorEnableIf<T, U>::type = nullptr )
		{
			Details::InitMoveVector( m_ctr, m_vec, ::std::move( v ) );

			m_good_ctr = 0;
		}

		DequeView( const T * ptr, unsigned int size )
		{
			Details::Init( m_ctr, m_vec, ptr, ptr + size );

			m_good_ctr = 0;
		}

		template<size_t N>
		explicit DequeView( const T( &arr )[N] )
		{
			Details::Init( m_ctr, m_vec, arr, arr + N );

			m_good_ctr = 0;
		}

		template<size_t N>
		explicit DequeView( const ::std::array<T, N>& a )
		{
			Details::Init( m_ctr, m_vec, a.begin(), a.end() );

			m_good_ctr = 0;
		}

		explicit DequeView( const Array<T>^ arr )
		{
			Details::Init( m_ctr, m_vec, arr->begin(), arr->end() );

			m_good_ctr = 0;
		}

		template<typename InIt>
		DequeView( InIt first, InIt last )
		{
			Details::Init( m_ctr, m_vec, first, last );

			m_good_ctr = 0;
		}

		DequeView( ::std::initializer_list<T> il )
		{
			Details::Init( m_ctr, m_vec, il.begin(), il.end() );

			m_good_ctr = 0;
		}

	public:
		virtual Details::WFC::IIterator<T>^ First() = WFC_Base::First
		{
			Details::ValidateCounter( m_ctr, m_good_ctr );

			return ref new Details::IteratorForDequeView<T>( m_ctr, m_vec );
		}

		virtual T GetAt( unsigned int index ) = WFC_Base::GetAt
		{
			Details::ValidateCounter( m_ctr, m_good_ctr );

			Details::ValidateBounds( index < m_vec->size() );

			return Details::Unwrap( ( *m_vec )[index] );
		}

		virtual property unsigned int Size
		{
			virtual unsigned int get()
			{
				Details::ValidateCounter( m_ctr, m_good_ctr );

				return static_cast<unsigned int>( m_vec->size() );
			}
		}

		virtual bool IndexOf( T value, unsigned int * index ) = WFC_Base::IndexOf
		{
			*index = 0;

			Details::ValidateCounter( m_ctr, m_good_ctr );

			return Details::DequeIndexOf<T, E>( *m_vec, value, index );
		}

		virtual unsigned int GetMany( unsigned int startIndex, WriteOnlyArray<T>^ dest )
		{
			Details::ValidateCounter( m_ctr, m_good_ctr );

			Details::ValidateBounds( startIndex <= m_vec->size() );

			return Details::DequeGetMany( *m_vec, startIndex, dest );
		}

	private:
		friend ref class Deque<T, E>;

		DequeView( const ::std::shared_ptr<unsigned int>& ctr, const ::std::shared_ptr<WrappedDeque>& vec )
			: m_ctr( ctr )
			, m_vec( vec )
			, m_good_ctr( *ctr )
		{ }

#if _COLLECTION_WUXI
		virtual Details::WUXI::IBindableIterator^ BindableFirst() = WUXI_Base::First
		{
			return safe_cast<Details::WUXI::IBindableIterator^>( First() );
		}

		virtual Object^ BindableGetAt( unsigned int index ) = WUXI_Base::GetAt
		{
			return GetAt( index );
		}

		virtual bool BindableIndexOf( Object^ value, unsigned int * index ) = WUXI_Base::IndexOf
		{
			*index = 0;

			Details::ValidateCounter( m_ctr, m_good_ctr );

			return Details::DequeBindableIndexOf<T, E>( *m_vec, value, index );
		}
#endif

		::std::shared_ptr<unsigned int> m_ctr;
		::std::shared_ptr<WrappedDeque> m_vec;
		unsigned int m_good_ctr;
	};


	template<typename T, typename E>
	ref class Deque<T, E, false>
	{
		static_assert( Details::AlwaysFalse<T>::value, "Platform::Collections::Deque<T, E> requires T to be a valid Windows Runtime type." );
	};

	template<typename T, typename E, bool>
	ref class Deque sealed
		: public _COLLECTION_ATTRIBUTES Details::WFC::IObservableVector<T>
#if _COLLECTION_WUXI
		, public Details::WUXI::IBindableObservableVector
#endif
	{
	private:
		typedef ::std::deque<typename Details::Wrap<T>::type> WrappedDeque;
		typedef Details::WFC::IObservableVector<T> WFC_Base;
		typedef Details::WFC::VectorChangedEventHandler<T> WFC_Handler;

#if _COLLECTION_WUXI
		typedef Details::WUXI::IBindableObservableVector WUXI_Base;
		typedef Details::WUXI::BindableVectorChangedEventHandler WUXI_Handler;
#endif

	internal:
		Deque()
		{
			Details::Init( m_ctr, m_vec );

			m_observed = false;
		}

		explicit Deque( unsigned int size )
		{
			Details::Init( m_ctr, m_vec, size );

			m_observed = false;
		}

		Deque( unsigned int size, T value )
		{
			Details::Init( m_ctr, m_vec, size, Details::MakeWrap( value ) );

			m_observed = false;
		}

		template<typename U>
		explicit Deque( const ::std::deque<U>& v, typename Details::VectorEnableIf<T, U>::type = nullptr )
		{
			Details::Init( m_ctr, m_vec, v.begin(), v.end() );

			m_observed = false;
		}

		template<typename U>
		explicit Deque( ::std::deque<U>&& v, typename Details::VectorEnableIf<T, U>::type = nullptr )
		{
			Details::InitMoveVector( m_ctr, m_vec, ::std::move( v ) );

			m_observed = false;
		}

		Deque( const T * ptr, unsigned int size )
		{
			Details::Init( m_ctr, m_vec, ptr, ptr + size );

			m_observed = false;
		}

		template<size_t N>
		explicit Deque( const T( &arr )[N] )
		{
			Details::Init( m_ctr, m_vec, arr, arr + N );

			m_observed = false;
		}

		template<size_t N>
		explicit Deque( const ::std::array<T, N>& a )
		{
			Details::Init( m_ctr, m_vec, a.begin(), a.end() );

			m_observed = false;
		}

		explicit Deque( const Array<T>^ arr )
		{
			Details::Init( m_ctr, m_vec, arr->begin(), arr->end() );

			m_observed = false;
		}

		template<typename InIt>
		Deque( InIt first, InIt last )
		{
			Details::Init( m_ctr, m_vec, first, last );

			m_observed = false;
		}

		Deque( ::std::initializer_list<T> il )
		{
			Details::Init( m_ctr, m_vec, il.begin(), il.end() );

			m_observed = false;
		}

	public:
		virtual Details::WFC::IIterator<T>^ First() = WFC_Base::First
		{
			return ref new Details::IteratorForDequeView<T>( m_ctr, m_vec );
		}

		virtual T GetAt( unsigned int index ) = WFC_Base::GetAt
		{
			Details::ValidateBounds( index < m_vec->size() );

			return Details::Unwrap( ( *m_vec )[index] );
		}

		virtual property unsigned int Size
		{
			virtual unsigned int get()
			{
				return static_cast<unsigned int>( m_vec->size() );
			}
		}

		virtual bool IndexOf( T value, unsigned int * index ) = WFC_Base::IndexOf
		{
			*index = 0;

			return Details::DequeIndexOf<T, E>( *m_vec, value, index );
		}

		virtual unsigned int GetMany( unsigned int startIndex, WriteOnlyArray<T>^ dest )
		{
			Details::ValidateBounds( startIndex <= m_vec->size() );

			return Details::DequeGetMany( *m_vec, startIndex, dest );
		}

		virtual Details::WFC::IVectorView<T>^ GetView() = WFC_Base::GetView
		{
			return ref new DequeView<T, E>( m_ctr, m_vec );
		}

		virtual void SetAt( unsigned int index, T item ) = WFC_Base::SetAt
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				Details::ValidateBounds( index < m_vec->size() );

				( *m_vec )[index] = item;

				NotifyChanged( index );
			_COLLECTION_TRANSLATE
		}

		virtual void InsertAt( unsigned int index, T item ) = WFC_Base::InsertAt
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				Details::ValidateBounds( index <= m_vec->size() );

				Details::ValidateSize( m_vec->size() + 1 );

				Emplace( m_vec->begin() + index, item, ::std::is_same<T, bool>() );

				NotifyInserted( index );
			_COLLECTION_TRANSLATE
		}

		void Prepend( T item )
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				size_t n = m_vec->size();

				Details::ValidateSize( n + 1 );

				EmplaceFront( item, ::std::is_same<T, bool>() );

				NotifyInserted( static_cast<unsigned int>( 0 ) );
			_COLLECTION_TRANSLATE
		}

		virtual void Append( T item ) = WFC_Base::Append
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				size_t n = m_vec->size();

				Details::ValidateSize( n + 1 );

				EmplaceBack( item, ::std::is_same<T, bool>() );

				NotifyInserted( static_cast<unsigned int>( n ) );
			_COLLECTION_TRANSLATE
		}

		virtual void RemoveAt( unsigned int index )
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				Details::ValidateBounds( index < m_vec->size() );

				m_vec->erase( m_vec->begin() + index );

				NotifyRemoved( index );
			_COLLECTION_TRANSLATE
		}

		virtual void RemoveAtBegin()
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				Details::ValidateBounds( !m_vec->empty() );

				m_vec->pop_front();

				NotifyRemoved( static_cast<unsigned int>( 0 ) );
			_COLLECTION_TRANSLATE
		}

		virtual void RemoveAtEnd()
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				Details::ValidateBounds( !m_vec->empty() );

				m_vec->pop_back();

				NotifyRemoved( static_cast<unsigned int>( m_vec->size() ) );
			_COLLECTION_TRANSLATE
		}

		virtual void Clear()
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				m_vec->clear();

				NotifyReset();
			_COLLECTION_TRANSLATE
		}

		virtual void ReplaceAll( const Array<T>^ arr )
		{
			try
			{
				Details::IncrementCounter( m_ctr );

				Details::ValidateSize( arr->Length );

				m_vec->assign( arr->begin(), arr->end() );

				NotifyReset();
			_COLLECTION_TRANSLATE
		}

		virtual event WFC_Handler^ VectorChanged
		{
			virtual Details::Token add( WFC_Handler^ e ) = WFC_Base::VectorChanged::add
			{
				m_observed = true;
				return m_wfc_event += e;
			}
			virtual void remove( Details::Token t ) = WFC_Base::VectorChanged::remove
			{
				m_wfc_event -= t;
			}
		};

	private:
		template<typename A, typename B>
		void Emplace( A&& a, B&& b, ::std::false_type )
		{
			m_vec->emplace( ::std::forward<A>( a ), ::std::forward<B>( b ) );
		}

		template<typename A, typename B>
		void Emplace( A&& a, B&& b, ::std::true_type )
		{
			m_vec->insert( ::std::forward<A>( a ), ::std::forward<B>( b ) );
		}

		template<typename A>
		void EmplaceFront( A&& a, ::std::false_type )
		{
			m_vec->emplace_front( ::std::forward<A>( a ) );
		}

		template<typename A>
		void EmplaceFront( A&& a, ::std::true_type )
		{
			m_vec->push_front( ::std::forward<A>( a ) );
		}

		template<typename A>
		void EmplaceBack( A&& a, ::std::false_type )
		{
			m_vec->emplace_back( ::std::forward<A>( a ) );
		}

		template<typename A>
		void EmplaceBack( A&& a, ::std::true_type )
		{
			m_vec->push_back( ::std::forward<A>( a ) );
		}

		void Notify( Details::WFC::CollectionChange change, unsigned int index )
		{
			if( m_observed )
			{
				auto args = ref new Details::VectorChangedEventArgs( change, index );
				m_wfc_event( this, args );

#if _COLLECTION_WUXI
				m_wuxi_event( this, args );
#endif
			}
		}

		void NotifyReset()
		{
			Notify( Details::WFC::CollectionChange::Reset, 0 );
		}

		void NotifyInserted( unsigned int index )
		{
			Notify( Details::WFC::CollectionChange::ItemInserted, index );
		}

		void NotifyRemoved( unsigned int index )
		{
			Notify( Details::WFC::CollectionChange::ItemRemoved, index );
		}

		void NotifyChanged( unsigned int index )
		{
			Notify( Details::WFC::CollectionChange::ItemChanged, index );
		}

#if _COLLECTION_WUXI
		virtual Details::WUXI::IBindableIterator^ BindableFirst() = WUXI_Base::First
		{
			return safe_cast<Details::WUXI::IBindableIterator^>( First() );
		}

		virtual Object^ BindableGetAt( unsigned int index ) = WUXI_Base::GetAt
		{
			return GetAt( index );
		}

		virtual bool BindableIndexOf( Object^ value, unsigned int * index ) = WUXI_Base::IndexOf
		{
			*index = 0;

			return Details::DequeBindableIndexOf<T, E>( *m_vec, value, index );
		}

		virtual Details::WUXI::IBindableVectorView^ BindableGetView() = WUXI_Base::GetView
		{
			return safe_cast<Details::WUXI::IBindableVectorView^>( GetView() );
		}

		virtual void BindableSetAt( unsigned int index, Object^ item ) = WUXI_Base::SetAt
		{
			SetAt( index, safe_cast<T>( item ) );
		}

		virtual void BindableInsertAt( unsigned int index, Object^ item ) = WUXI_Base::InsertAt
		{
			InsertAt( index, safe_cast<T>( item ) );
		}

		virtual void BindableAppend( Object^ item ) = WUXI_Base::Append
		{
			Append( safe_cast<T>( item ) );
		}

		virtual Details::Token BindableEventAdd( WUXI_Handler^ e ) = WUXI_Base::VectorChanged::add
		{
			m_observed = true;
			return m_wuxi_event += e;
		}

		virtual void BindableEventRemove( Details::Token t ) = WUXI_Base::VectorChanged::remove
		{
			m_wuxi_event -= t;
		}
#endif // _COLLECTION_WUXI

		::std::shared_ptr<unsigned int> m_ctr;
		::std::shared_ptr<WrappedDeque> m_vec;
		bool m_observed;

		event WFC_Handler^ m_wfc_event;

#if _COLLECTION_WUXI
		event WUXI_Handler^ m_wuxi_event;
#endif
	};

	namespace Details {

		template<typename T, typename I>
		inline ::std::deque<T> ToDeque( I^ v )
		{
			unsigned int size = v->Size;

			::std::deque<T> ret( size );

			for( unsigned int actual = 0; actual < size; )
			{
				Array<T>^ arr = ref new Array<T>( size - actual );

				unsigned int n = v->GetMany( actual, arr );

				if( n == 0 )
				{
					throw ref new FailureException;
				}

				::std::copy_n( arr->begin(), n, ret.begin() + actual );

				actual += n;
			}

			return ret;
		}

	}
} }

namespace Windows { namespace Foundation { namespace Collections {

	template<typename T>
	inline ::std::deque<T> to_deque( IVector<T>^ v )
	{
		return ::Platform::Collections::Details::ToDeque<T>( v );
	}

	template<typename T>
	inline ::std::deque<T> to_deque( IVectorView<T>^ v )
	{
		return ::Platform::Collections::Details::ToDeque<T>( v );
	}

} } }

#undef _COLLECTION_ATTRIBUTES
#undef _COLLECTION_TRANSLATE
#undef _COLLECTION_WUXI

#pragma warning(pop)
#pragma pack(pop)