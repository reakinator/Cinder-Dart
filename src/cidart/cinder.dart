library cinder;

get _printClosure => ( s ) {
	try {
    	printNative( s );
	} catch ( _ ) {
		throw( s );
	}
};

void printNative( String message ) 			native "cidart::printNative";
void toCinder( Map<String, dynamic> data ) 	native "cidart::toCinder";

/// callNativeN methods allow the method to hook up to a std::function. On the C++ side, the first argument recieved will be 'key'.
void callNative0( String key ) native "cidart::callNative0";
void callNative1( String key, arg1 ) native "cidart::callNative1";
void callNative2( String key, arg1, arg2 ) native "cidart::callNative2";
void callNative3( String key, arg1, arg2, arg3 ) native "cidart::callNative3";
void callNative4( String key, arg1, arg2, arg3, arg4 ) native "cidart::callNative4";
void callNative5( String key, arg1, arg2, arg3, arg4, arg5 ) native "cidart::callNative5";
dynamic callNative0Return( String key ) native "cidart::callNative0Return";
dynamic callNative1Return( String key, arg1 ) native "cidart::callNative1Return";
dynamic callNative2Return( String key, arg1, arg2 ) native "cidart::callNative2Return";
dynamic callNative3Return( String key, arg1, arg2, arg3 ) native "cidart::callNative3Return";
dynamic callNative4Return( String key, arg1, arg2, arg3, arg4 ) native "cidart::callNative4Return";
dynamic callNative5Return( String key, arg1, arg2, arg3, arg4, arg5 ) native "cidart::callNative5Return";

vec2i 	getWindowSize() 		native "cidart::getWindowSize";
int 	getWindowWidth() 		native "cidart::getWindowWidth";
int 	getWindowHeight() 		native "cidart::getWindowHeight";
double 	getElapsedSeconds() 	native "cidart::getElapsedSeconds";
int 	getElapsedFrames() 		native "cidart::getElapsedFrames";

class vec2 {
	num x, y;
	
	vec2( this.x, this.y );
}

class ivec2 {
	int x, y;
	
	ivec2( this.x, this.y );
}

class vec3 {
	num x, y, z;
	
	vec3( this.x, this.y, this.z );
}

class ivec3 {
	int x, y;
	
	ivec3( this.x, this.y );
}

class vec4 {
	num x, y, z, w;
	
	vec4( this.x, this.y, this.z, this.w );
}

class Color {
	num r, g, b, a;

	Color( this.r, this.g, this.b, [this.a = 1.0] );
}

class Rect {
	num x1, x2, y1, y2;

	Rect( this.x1, this.y1, this.x2, this.y2 );
}

class mat4 {
	num r1x, r2x, r3x, r4x, r1y, r2y, r3y, r4y, r1z, r2z, r3z, r4z, r1w, r2w, r3w, r4w;
	
	mat4( this.r1x, this.r2x, this.r3x, this.r4x, 
		  this.r1y, this.r2y, this.r3y, this.r4y, 
		  this.r1z, this.r2z, this.r3z, this.r4z, 
		  this.r1w, this.r2w, this.r3w, this.r4w );
}

enum LogLevel {
	VERBOSE,
	INFO,
	WARNING,
	ERROR,
	FATAL
}