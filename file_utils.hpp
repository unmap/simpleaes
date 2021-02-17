#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

__forceinline auto generate_header( const std::vector<std::uint8_t>& in_buffer , int padding ) -> std::string
{
	std::string header;
	header.append( "#pragma once\n" );
	header.append( "//padding: " + std::to_string( padding ) + "\n" );
	header.append( "#include <cstdint>\n\n" );
	header.append( "constexpr std::uint8_t image[] = \n" );
	header.append( "{" );

	int counter = 0;
	for ( uint8_t current_char : in_buffer )
	{
		if ( counter % 25 == 0 )
			header.append( "\n    " );

		char hex_string[ 10 ];
		sprintf_s( hex_string , "0x%02X" , current_char );

		header.append( hex_string );

		if ( counter != in_buffer.size( ) - 1 )
			header.append( ", " );

		counter++;
	}

	header.append( "\n};\n" );
	return header;
}

__forceinline auto open_binary_file( const std::string& file , std::vector<uint8_t>& data ) -> void
{
	std::ifstream fstr( file , std::ios::binary );
	fstr.unsetf( std::ios::skipws );
	fstr.seekg( 0 , std::ios::end );

	const auto file_size = fstr.tellg( );

	fstr.seekg( NULL , std::ios::beg );
	data.reserve( static_cast<uint32_t>( file_size ) );
	data.insert( data.begin( ) , std::istream_iterator<uint8_t>( fstr ) , std::istream_iterator<uint8_t>( ) );
}
