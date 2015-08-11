// Copyright (c) 2013, Richard Eakin and the Dart project authors.
// Use of this source code (and the Dart VM) is governed by a
// BSD-style license that can be found in the LICENSE.txt file.

#include "cidart/Types.h"
#include "cidart/Debug.h"

#include "include/dart_mirrors_api.h"

#include <sstream>

using namespace ci;
using namespace std;

namespace cidart {

namespace {

template<typename T>
void getNumberValueImpl( Dart_Handle handle, T *value )
{
	if( Dart_IsDouble( handle ) ) {
		double result;
		CIDART_CHECK( Dart_DoubleValue( handle, &result ) );
		*value = static_cast<T>( result );
	}
	else if( Dart_IsInteger( handle ) ) {
		int64_t result;
		CIDART_CHECK( Dart_IntegerToInt64( handle, &result ) );
		*value = static_cast<T>( result );
	}
	else {
		if( Dart_IsError( handle ) )
			throwException( string( "handle error: " ) + Dart_GetError( handle ) );
		else
			throwException( "cannot make number from handle of type: " + getTypeName( handle ) );
	}
}
	
} // anonymous namespace

Dart_Handle toDart( const char *str )
{
	return Dart_NewStringFromCString( str );
}

Dart_Handle toDart( const std::string &str )
{
	return toDart( str.c_str() );
}

float getFloatForKey( Dart_Handle mapHandle, const char *key )
{
	CI_ASSERT( Dart_IsMap( mapHandle ) );

	Dart_Handle args[] = { cidart::toDart( key ) };
	Dart_Handle valueHandle = cidart::callFunction( mapHandle, "[]", 1, args );
	CIDART_CHECK( valueHandle );

	return cidart::getValue<float>( valueHandle );
}

void getValue( Dart_Handle handle, bool *value )
{
	CIDART_CHECK( Dart_BooleanValue( handle, value ) );
}

void getValue( Dart_Handle handle, int *value )
{
	getNumberValueImpl( handle, value );
}

void getValue( Dart_Handle handle, size_t *value )
{
	getNumberValueImpl( handle, value );
}

void getValue( Dart_Handle handle, float *value )
{
	getNumberValueImpl( handle, value );
}

void getValue( Dart_Handle handle, double *value )
{
	getNumberValueImpl( handle, value );
}

void getValue( Dart_Handle handle, ci::Color *value )
{
	Dart_Handle r = getField( handle, "r" );
	Dart_Handle g = getField( handle, "g" );
	Dart_Handle b = getField( handle, "b" );

	if( Dart_IsError( r ) || Dart_IsError( g ) || Dart_IsError( b ) ) {
		CI_LOG_E( "expected handle to have fields 'r', 'g' and 'b'" );
		return;
	}

	value->r = getValue<float>( r );
	value->g = getValue<float>( g );
	value->b = getValue<float>( b );
}

void getValue( Dart_Handle handle, ci::ColorA *value )
{
	Dart_Handle r = getField( handle, "r" );
	Dart_Handle g = getField( handle, "g" );
	Dart_Handle b = getField( handle, "b" );
	Dart_Handle a = getField( handle, "a" );

	if( Dart_IsError( r ) || Dart_IsError( g ) || Dart_IsError( b ) || Dart_IsError( a ) ) {
		CI_LOG_E( "expected handle to have fields 'r', 'g', 'b' and 'a'" );
		return;
	}

	value->r = getValue<float>( r );
	value->g = getValue<float>( g );
	value->b = getValue<float>( b );
	value->a = getValue<float>( a );
}

void getValue( Dart_Handle handle, ci::ivec2 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );

	if( Dart_IsError( x ) || Dart_IsError( y ) ) {
		CI_LOG_E( "expected handle to have fields 'x' and 'y'" );
		return;
	}

	value->x = getValue<int>( x );
	value->y = getValue<int>( y );
}

void getValue( Dart_Handle handle, ci::vec2 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );

	if( Dart_IsError( x ) || Dart_IsError( y ) ) {
		CI_LOG_E( "expected handle to have fields 'x' and 'y'" );
		return;
	}

	value->x = getValue<float>( x );
	value->y = getValue<float>( y );
}

void getValue( Dart_Handle handle, ci::dvec2 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );

	if( Dart_IsError( x ) || Dart_IsError( y ) ) {
		CI_LOG_E( "expected handle to have fields 'x' and 'y'" );
		return;
	}

	value->x = getValue<double>( x );
	value->y = getValue<double>( y );
}

void getValue( Dart_Handle handle, ci::ivec3 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );
	Dart_Handle z = getField( handle, "z" );

	if( Dart_IsError( x ) || Dart_IsError( y ) || Dart_IsError( z ) ) {
		CI_LOG_E( "expected handle to have fields 'x', 'y', and 'z'" );
		return;
	}

	value->x = getValue<int>( x );
	value->y = getValue<int>( y );
	value->z = getValue<int>( z );
}

void getValue( Dart_Handle handle, ci::vec3 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );
	Dart_Handle z = getField( handle, "z" );

	if( Dart_IsError( x ) || Dart_IsError( y ) || Dart_IsError( z ) ) {
		CI_LOG_E( "expected handle to have fields 'x', 'y', and 'z'" );
		return;
	}

	value->x = getValue<float>( x );
	value->y = getValue<float>( y );
	value->z = getValue<float>( z );
}

void getValue( Dart_Handle handle, ci::dvec3 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );
	Dart_Handle z = getField( handle, "z" );

	if( Dart_IsError( x ) || Dart_IsError( y ) || Dart_IsError( z ) ) {
		CI_LOG_E( "expected handle to have fields 'x', 'y', and 'z'" );
		return;
	}

	value->x = getValue<double>( x );
	value->y = getValue<double>( y );
	value->z = getValue<double>( z );
}

void getValue( Dart_Handle handle, ci::ivec4 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );
	Dart_Handle z = getField( handle, "z" );
	Dart_Handle w = getField( handle, "w" );

	if( Dart_IsError( x ) || Dart_IsError( y ) || Dart_IsError( z ) || Dart_IsError( w ) ) {
		CI_LOG_E( "expected handle to have fields 'x', 'y', 'z' and 'w'" );
		return;
	}

	value->x = getValue<int>( x );
	value->y = getValue<int>( y );
	value->z = getValue<int>( z );
	value->w = getValue<int>( w );
}

void getValue( Dart_Handle handle, ci::vec4 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );
	Dart_Handle z = getField( handle, "z" );
	Dart_Handle w = getField( handle, "w" );

	if( Dart_IsError( x ) || Dart_IsError( y ) || Dart_IsError( z ) || Dart_IsError( w ) ) {
		CI_LOG_E( "expected handle to have fields 'x', 'y', 'z' and 'w'" );
		return;
	}

	value->x = getValue<float>( x );
	value->y = getValue<float>( y );
	value->z = getValue<float>( z );
	value->w = getValue<float>( w );
}

void getValue( Dart_Handle handle, ci::dvec4 *value )
{
	Dart_Handle x = getField( handle, "x" );
	Dart_Handle y = getField( handle, "y" );
	Dart_Handle z = getField( handle, "z" );
	Dart_Handle w = getField( handle, "w" );

	if( Dart_IsError( x ) || Dart_IsError( y ) || Dart_IsError( z ) || Dart_IsError( w ) ) {
		CI_LOG_E( "expected handle to have fields 'x', 'y', 'z' and 'w'" );
		return;
	}

	value->x = getValue<double>( x );
	value->y = getValue<double>( y );
	value->z = getValue<double>( z );
	value->w = getValue<double>( w );
}

void getValue( Dart_Handle handle, ci::mat4 *value )
{
    Dart_Handle r1x = getField( handle, "r1x" );
    Dart_Handle r2x = getField( handle, "r2x" );
    Dart_Handle r3x = getField( handle, "r3x" );
    Dart_Handle r4x = getField( handle, "r4x" );
    Dart_Handle r1y = getField( handle, "r1y" );
    Dart_Handle r2y = getField( handle, "r2y" );
    Dart_Handle r3y = getField( handle, "r3y" );
    Dart_Handle r4y = getField( handle, "r4y" );
    Dart_Handle r1z = getField( handle, "r1z" );
    Dart_Handle r2z = getField( handle, "r2z" );
    Dart_Handle r3z = getField( handle, "r3z" );
    Dart_Handle r4z = getField( handle, "r4z" );
    Dart_Handle r1w = getField( handle, "r1w" );
    Dart_Handle r2w = getField( handle, "r2w" );
    Dart_Handle r3w = getField( handle, "r3w" );
    Dart_Handle r4w = getField( handle, "r4w" );
    
    if( Dart_IsError( r1x ) || Dart_IsError( r2x ) || Dart_IsError( r3x ) || Dart_IsError( r4x ) ||
        Dart_IsError( r1y ) || Dart_IsError( r2y ) || Dart_IsError( r3y ) || Dart_IsError( r4y ) ||
        Dart_IsError( r1z ) || Dart_IsError( r2z ) || Dart_IsError( r3z ) || Dart_IsError( r4z ) ||
        Dart_IsError( r1w ) || Dart_IsError( r2w ) || Dart_IsError( r3w ) || Dart_IsError( r4w ) ) {
        CI_LOG_E( "expected handle to have fields 'r1x', 'r2x', 'r3x', 'r4x', 'r1y', 'r2y', 'r3y', 'r4y', 'r1z', 'r2z', 'r3z', 'r4z', 'r1w', 'r2w', 'r3w', 'r4w'" );
        return;
    }
    float vals[16] = { getValue<float>( r1x ), getValue<float>( r2x ), getValue<float>( r3x ), getValue<float>( r4x ),
                       getValue<float>( r1y ), getValue<float>( r2y ), getValue<float>( r3y ), getValue<float>( r4y ),
                       getValue<float>( r1z ), getValue<float>( r2z ), getValue<float>( r3z ), getValue<float>( r4z ),
                       getValue<float>( r1w ), getValue<float>( r2w ), getValue<float>( r3w ), getValue<float>( r4w ) };
    
    *value = glm::make_mat4( vals );
}
    
void getValue( Dart_Handle handle, ci::Rectf *value )
{
	Dart_Handle x1 = getField( handle, "x1" );
	Dart_Handle x2 = getField( handle, "x2" );
	Dart_Handle y1 = getField( handle, "y1" );
	Dart_Handle y2 = getField( handle, "y2" );

	if( Dart_IsError( x1 ) || Dart_IsError( x2 ) || Dart_IsError( y1 ) || Dart_IsError( y2 ) ) {
		CI_LOG_E( "expected handle to have fields 'x1', 'x2', 'y1' and 'y2'" );
		return;
	}

	value->x1 = getValue<float>( x1 );
	value->x2 = getValue<float>( x2 );
	value->y1 = getValue<float>( y1 );
	value->y2 = getValue<float>( y2 );
}

void getValue( Dart_Handle handle, log::Level *value )
{
	int index = getField<int>( handle, "index" );

	switch ( index ) {
		case 0:		*value = log::LEVEL_VERBOSE; return;
		case 1:		*value = log::LEVEL_INFO; return;
		case 2:		*value = log::LEVEL_WARNING; return;
		case 3:		*value = log::LEVEL_ERROR; return;
		case 4:		*value = log::LEVEL_FATAL; return;
		default:	CI_ASSERT_NOT_REACHABLE();
	}
}

void getValue( Dart_Handle handle, std::string *value )
{
	if( ! Dart_IsString( handle ) ) {
		CI_LOG_E( "expected handle to be of type string" );
		return;
	}

	const char *result;
	CIDART_CHECK( Dart_StringToCString( handle, &result ) );
	*value = string( result );
}

bool hasFunction( Dart_Handle handle, const string &name )
{
	Dart_Handle result = Dart_LookupFunction( handle, toDart( name ) );
	CIDART_CHECK( result );
	return ! Dart_IsNull( result );
}

Dart_Handle callFunction( Dart_Handle target, const string &name, int numArgs, Dart_Handle *args )
{
	Dart_Handle result = Dart_Invoke( target, toDart( name ), numArgs, args );
	CIDART_CHECK( result );
	return result;
}

Dart_Handle getField( Dart_Handle container, const char *name )
{
	return Dart_GetField( container, toDart( name ) );
}

Dart_Handle getField( Dart_Handle container, const string &name )
{
	return Dart_GetField( container, toDart( name ) );
}

string getTypeName( Dart_Handle handle )
{
	Dart_Handle instanceType = Dart_InstanceGetType( handle );
	CIDART_CHECK( instanceType );
	Dart_Handle typeName = Dart_TypeName( instanceType );
	CIDART_CHECK( typeName );

	return getValue<string>( typeName );
}

void throwException( const std::string &description )
{
	Dart_Handle exceptionHandle = toDart( description );
	CIDART_CHECK( Dart_ThrowException( exceptionHandle ) );
}

// ???: rename to isCinderType?
// - maybe shoud be using Dart_GetType as well
bool isCinderClass( Dart_Handle handle, const char *className )
{
	Dart_Handle cinderLib = Dart_LookupLibrary( toDart( "cinder" ) );
	CIDART_CHECK( cinderLib );
	Dart_Handle cinderClass = Dart_GetClass( cinderLib, toDart( className ) );
	CIDART_CHECK( cinderClass );

	bool result;
	CIDART_CHECK( Dart_ObjectIsType( handle, cinderClass, &result ) );
	return result;
}

string printNativeArgumentsToString( Dart_NativeArguments args, bool printMethodNames )
{
	stringstream stream;

	int argCount = Dart_GetNativeArgumentCount( args );
	stream << "arg count: " << argCount << endl;

	for( int i = 0; i < argCount; i++ ) {
		Dart_Handle handle = Dart_GetNativeArgument( args, i );

		Dart_Handle instanceType = Dart_InstanceGetType( handle );
		CIDART_CHECK( instanceType );
		string typeName = cidart::getValue<string>( Dart_TypeName( instanceType ) );

		stream << "\t[" << i << "]: type: " << typeName << endl;

		if( printMethodNames ) {
			Dart_Handle functionNamesList = Dart_GetFunctionNames( instanceType );
			CIDART_CHECK( functionNamesList );

			CI_ASSERT( Dart_IsList( functionNamesList ) );

			intptr_t length = 0;
			CIDART_CHECK( Dart_ListLength( functionNamesList, &length ) );

			stream << "\t\t funcNames: ";
			for( intptr_t i = 0; i < length; i++ ) {
				Dart_Handle elem = Dart_ListGetAt( functionNamesList, i );
				CIDART_CHECK( elem );

				string funcName = cidart::getValue<string>( elem );
				stream << funcName << ", ";
			}
			stream << endl;
		}
	}

	return stream.str();
}

} // namespace cidart
