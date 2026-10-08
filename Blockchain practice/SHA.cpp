#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include "SHA.h"


std::string sha256(const std::string& str) {
	// Creating array on 32 bytes for hash, массив на 32 байта для хэша
	unsigned char hash[SHA256_DIGEST_LENGTH];

	// Creating hash, создание хэша
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);

	//Converting to 16th NumSystem, перевод в шестнадцатеричную систему
	std::stringstream str_hex;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		str_hex << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
	}

	return str_hex.str();
}
