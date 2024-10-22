#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

int main(){
	unsigned char data[] = "Hello, this is a message to hash with MD5";
	unsigned char hash[MD5_DIGEST_LENGTH];

	MD5_CTX md5;
	MD5_Init(&md5);
	MD5_Update(&md5,data,strlen((char *)data));
	MD5_Final(hash,&md5);

	for(int i=0;i<MD5_DIGEST_LENGTH;i++){
		printf("%02x",hash[i]);
	}
}
