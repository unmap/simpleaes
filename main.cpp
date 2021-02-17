#include <iostream>
#include <memory>
#include <fstream>

#include "aes_fx.hpp"
#include "file_utils.hpp"


auto main( int argument_count , char** argument_array ) -> int
{
	if ( argument_count < 3 )
	{
		printf( "[=] usage: simpleaes.exe binary_name.exe aes_iv aes_key" );
		return -1;
	}
	
	std::vector<std::uint8_t> in_buffer { };
	open_binary_file( argument_array[ 0 ] , in_buffer );

	//encrypt file buffer with user inputed iv and key
	auto [encypted , padding] = encrypt( in_buffer , argument_array[ 1 ] , argument_array[ 2 ] );

	//format encrypted buffer into output string
	const auto enc_buffer_string = generate_header( encypted , padding );

	//dump string to disk
	std::ofstream encrypted_file( std::string( "output" ) + ".hpp" );
	encrypted_file << enc_buffer_string;
	encrypted_file.close( );

	std::cout << "[+] AES PADDING : " << padding << std::endl;

	//decrypt the buffer with the same keys to ensure nothing went wrong
	const auto bytes = decrypt( encypted , argument_array[ 1 ] , argument_array[ 2 ] , padding );

	//if there was an error report it
	if ( bytes != in_buffer )
	{
		std::cout << "[-] encrypted file decrypted does not match original" << std::endl;
		return 0;
	}

	std::cout << "\n[+] Done!" << std::endl;
	std::cin.get( );
	return 0;
}
