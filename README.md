# simpleaes
simple binary to header file with aes encryption

# Usage
```
simpleaes.exe [path to target file] [iv] [encryption key]
```

# Decryption
Use a decryption method like this after adding aes.c and aes.h to your project. <br>
The padding will be listed at the top of the header file generated.

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
# Credits
tinyaes
