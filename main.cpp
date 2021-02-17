#include <iostream>
#include <memory>
#include <fstream>

#include "aes_fx.hpp"


auto generate_header( const std::vector<std::uint8_t>& in_buffer , int padding ) -> std::string
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

inline void open_binary_file( const std::string& file , std::vector<uint8_t>& data )
{
	std::ifstream fstr( file , std::ios::binary );
	fstr.unsetf( std::ios::skipws );
	fstr.seekg( 0 , std::ios::end );

	const auto file_size = fstr.tellg( );

	fstr.seekg( NULL , std::ios::beg );
	data.reserve( static_cast<uint32_t>( file_size ) );
	data.insert( data.begin( ) , std::istream_iterator<uint8_t>( fstr ) , std::istream_iterator<uint8_t>( ) );
}

auto main( int argument_count , char** argument_array ) -> int
{
	if ( argument_count < 3 )
	{
		printf( "[=] usage: simpleaes.exe binary_name.exe aes_iv aes_key" );
		return -1;
	}
	
	std::vector<std::uint8_t> in_buffer { };
	open_binary_file( argument_array[ 0 ] , in_buffer );

	auto [encypted , padding] = encrypt( in_buffer , argument_array[ 1 ] , argument_array[ 2 ] );

	const auto enc_buffer_string = generate_header( encypted , padding );

	std::ofstream encrypted_file( std::string( "output" ) + ".hpp" );
	encrypted_file << enc_buffer_string;
	encrypted_file.close( );

	std::cout << "[+] AES PADDING : " << padding << std::endl;

	const auto bytes = decrypt( encypted , argument_array[ 1 ] , argument_array[ 2 ] , padding );

	if ( bytes != in_buffer )
	{
		std::cout << "[-] encrypted file decrypted does not match original" << std::endl;
		return 0;
	}

	std::cout << "\ndone" << std::endl;
	getchar( );
}
