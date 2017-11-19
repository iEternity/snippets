#include <iostream>
#include <stdio.h>
#include <zlib.h>
#include <assert.h>
#include <string.h>


#define CHUNK 16*1024

int compress(FILE* source, FILE* dest, int level)
{
    int ret, flush;
    unsigned have;
    z_stream zstream;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    zstream.zalloc = Z_NULL;
    zstream.zfree  = Z_NULL;
    zstream.opaque = Z_NULL;

    ret = deflateInit(&zstream, level);
    if(ret != Z_OK) return ret;

    do
    {
        zstream.avail_in = static_cast<unsigned int>(fread(in, 1, CHUNK, source));
        if(ferror(source))
        {
            deflateEnd(&zstream);
            return Z_ERRNO;
        }

        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        zstream.next_in = in;

        do
        {
            zstream.avail_out = CHUNK;
            zstream.next_out  = out;
            ret = deflate(&zstream, flush);
            assert(ret != Z_STREAM_ERROR);
            have = CHUNK - zstream.avail_out;
            if(fwrite(out, 1, have, dest) != have || ferror(dest))
            {
                deflateEnd(&zstream);
                return Z_ERRNO;
            }
        }while(zstream.avail_out == 0);

    }while(flush != Z_FINISH);
    assert(ret == Z_STREAM_END);

    deflateEnd(&zstream);

    return Z_OK;
}

int decompress(FILE* source, FILE* dest)
{
    int ret;
    unsigned have;
    z_stream zstream;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    zstream.zalloc  = Z_NULL;
    zstream.zfree   = Z_NULL;
    zstream.opaque  = Z_NULL;

    ret = inflateInit(&zstream);
    if(ret != Z_OK) return ret;

    do {
        zstream.avail_in = fread(in, 1, CHUNK, source);
        if(ferror(source))
        {
            inflateEnd(&zstream);
            return Z_ERRNO;
        }
        if(zstream.avail_in == 0) break;
        zstream.next_in = in;

        do
        {
            zstream.avail_out = CHUNK;
            zstream.next_out = out;

            ret = inflate(&zstream, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);

            switch(ret)
            {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    inflateEnd(&zstream);
                    return ret;
            }

            have = CHUNK - zstream.avail_out;
            if(fwrite(out, 1, have, dest) != have || ferror(dest))
            {
                inflateEnd(&zstream);
                return Z_ERRNO;
            }
        }while(zstream.avail_out == 0);
    }while(ret != Z_STREAM_END);

    inflateEnd(&zstream);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

void zerror(int ret)
{
    fputs("zlibstream: ", stderr);
    switch(ret)
    {
        case Z_ERRNO:
            if(ferror(stdin))
            {
                fputs("error reading stdin\n", stderr);
            }
            if(ferror(stdout))
            {
                fputs("error writing stdout\n", stderr);
            }
            break;
        case Z_STREAM_ERROR:
            fputs("invalid compression level\n", stderr);
            break;
        case Z_DATA_ERROR:
            fputs("invalid or incomplete defate data\n", stderr);
            break;
        case Z_MEM_ERROR:
            fputs("out of memory\n", stderr);
            break;
        case Z_VERSION_ERROR:
            fputs("zlib version mismatch\n", stderr);
            break;
    }
}

void testCompress()
{
    /*compress*/
    FILE* fp1 = fopen("test", "rb");
    if(!fp1) fputs("fopen: test error\n", stderr);

    FILE* fp2 = fopen("compress.data", "wb+");
    if(!fp2) fputs("fopen: output.data error\n", stderr);

    int ret = compress(fp1, fp2, Z_DEFAULT_COMPRESSION);
    if(ret != Z_OK) zerror(ret);

    fclose(fp1);
    fclose(fp2);
}

void testDecompress()
{
    /*decompress*/
    FILE* fp3 = fopen("compress.data", "rb");
    if(!fp3) fputs("fp3 is null\n", stderr);

    FILE* fp4 = fopen("decompress.data", "wb+");
    if(!fp4) fputs("fp4 is null\n", stderr);

    int ret = decompress(fp3, fp4);
    if(ret != Z_OK) zerror(ret);

    fclose(fp3);
    fclose(fp4);
}

int main() {
    testCompress();
    testDecompress();

    return 0;
}