# simpleaes
simple binary to hader file with aes encryption

# decrpytion
use a decryption method like this after adding aes.c and aes.h to your project. <br>
the padding is listed at the top of the header file generated

```c++
__forceinline std::vector<std::uint8_t> decrypt ( std::vector<std::uint8_t> input , std::string_view aes_key_1 , std::string_view aes_key_2,  int paddding )
{
	std::string data ( input.begin ( ) , input.end ( ) );

	AES_ctx ctx {};
	AES_init_ctx_iv ( &ctx , reinterpret_cast<const uint8_t*>( aes_key_1.data(  ) ) , reinterpret_cast<const uint8_t*>( aes_key_2.data(  ) ) );
	AES_CBC_decrypt_buffer ( &ctx , reinterpret_cast<uint8_t*>( data.data ( ) ) , data.size ( ) );

	data.erase ( data.size ( ) - paddding );
	return std::vector<std::uint8_t>{data.begin ( ) , data.end ( )};
}
```
