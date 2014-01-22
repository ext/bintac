#include <stdio.h>
#include <string.h>
#include <errno.h>

#define bufsize 64*1024
static char chunk[bufsize];
static char rev[bufsize];

static int min(int a, int b){
	return (a<b)?a:b;
}

static long fill(FILE* fp, const char* filename, long pos, size_t bytes){
	pos -= bytes;
	fseek(fp, pos, SEEK_SET);
	if ( fread(chunk, bytes, 1, fp) != 1 ){
		fprintf(stderr, "bintac: fread failed on `%s': %s\n", filename, strerror(errno));
		return 0;
	}
	return pos;
}

static void reverse(size_t bytes){
	char* src = chunk + bytes-1;
	char* dst = rev;
	while ( src >= chunk ){
		*dst++ = *src--;
	}
}

static void process(const char* filename){
	FILE* fp = fopen(filename, "r");
	if ( !fp ){
		fprintf(stderr, "bintac: failed to read `%s': %s\n", filename, strerror(errno));
		return;
	}

	fseek(fp, 0, SEEK_END);
	long pos = ftell(fp);

	while ( pos > 0 ){
		const size_t bytes = min(pos, bufsize); /* calc num bytes to read */
		pos = fill(fp, filename, pos, bytes);   /* read chunk */
		reverse(bytes);                         /* reverse bytes */
		fwrite(rev, bytes, 1, stdout);          /* write output */
	}
}

static void show_usage(){
	fprintf(stderr, "bintac FILES.. - cat files in reverse, byte-by-byte\n");
}

int main(int argc, const char* argv[]){
	if ( argc < 2 ){
		show_usage();
		return 1;
	}
	for ( int i = argc-1; i > 0; i-- ){
		const char* filename = argv[i];
		process(filename);
	}
}
