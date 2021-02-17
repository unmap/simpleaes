#pragma once
#include "aes/aes.hpp"
#include <string>
#include <cstdint>
#include <vector>


__forceinline auto encrypt( std::vector<std::uint8_t>& input , std::string_view aes_iv , std::string_view aes_key ) -> std::pair<std::vector<std::uint8_t> , int>
{
	std::string raw( input.begin( ) , input.end( ) );

	const int padding = 16 - raw.size( ) % 16;
	for( auto i = 0u; i < padding; ++i )
		raw += "a";
	AES_ctx ctx { };
	AES_init_ctx_iv( &ctx , reinterpret_cast<const uint8_t*>( aes_iv.data( ) ) ,
							reinterpret_cast<const uint8_t*>( aes_key.data( ) ) );
	
	AES_CBC_encrypt_buffer( &ctx , reinterpret_cast<uint8_t*>( raw.data( ) ) , raw.size( ) );  // NOLINT(clang-diagnostic-shorten-64-to-32)

	return { std::vector<std::uint8_t> { raw.begin( ) , raw.end( ) } , padding };
}

__forceinline auto decrypt( std::vector<std::uint8_t> input , std::string_view aes_iv , std::string_view aes_key , int paddding ) -> std::vector<std::uint8_t>
{
	std::string data( input.begin( ) , input.end( ) );

	AES_ctx ctx { };
	AES_init_ctx_iv( &ctx , reinterpret_cast<const uint8_t*>( aes_iv.data( ) ) ,
							reinterpret_cast<const uint8_t*>( aes_key.data( ) ) );
	
	AES_CBC_decrypt_buffer( &ctx , reinterpret_cast<uint8_t*>( data.data( ) ) , data.size( ) );  // NOLINT(clang-diagnostic-shorten-64-to-32)

	data.erase( data.size( ) - paddding );
	return std::vector<std::uint8_t> { data.begin( ) , data.end( ) };
}
