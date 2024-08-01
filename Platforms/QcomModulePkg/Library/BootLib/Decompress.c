/* Copyright (c) 2015, 2017-2018, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of The Linux Foundation, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <Base.h>
#define true TRUE
#define false FALSE

#define NO_GZIP

#include "zlib/zutil.h"

#ifdef DYNAMIC_CRC_TABLE
#include "crc32.h"
#endif

#include "Decompress.h"
#include "zlib/zlib.h"
#include "zlib/zconf.h"
#include "zlib/inftrees.h"
#include "zlib/inflate.h"
#include "zlib/inffast.h"

#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>

#define GZIP_HEADER_LEN 10
#define GZIP_FILENAME_LIMIT 256

static void
zlib_free (voidpf qpaque, void *addr)
{
  FreePool (addr);
  addr = NULL;
}

// typedef voidpf (*alloc_func) OF((voidpf opaque, uInt items, uInt size));
static void *
zlib_alloc (voidpf qpaque, uInt items, uInt size)
{
  return AllocateZeroPool (items * size);
}

/* decompress gzip file "in_buf", return 0 if decompressed successful,
 * return -1 if decompressed failed.
 * in_buf - input gzip file
 * in_len - input the length file
 * out_buf - output the decompressed data
 * out_buf_len - the available length of out_buf
 * pos - position of the end of gzip file
 * out_len - the length of decompressed data
 */
int
decompress (unsigned char *in_buf,
            unsigned int in_len,
            unsigned char *out_buf,
            unsigned int out_buf_len,
            unsigned int *pos,
            unsigned int *out_len)
{
  struct z_stream_s *stream;
  int rc = -1;
  int i;

  if (in_len <= GZIP_HEADER_LEN) {
    DEBUG ((EFI_D_ERROR, "the input data is not a gzip package.\n"));
    return rc;
  }

  if (out_buf_len <= in_len) {
    DEBUG ((EFI_D_ERROR,
            "the available length: %u of out_buf is not enough, need %u.\n",
            out_buf_len, in_len));
    return rc;
  }

  stream = AllocateZeroPool (sizeof (*stream));
  if (stream == NULL) {
    DEBUG ((EFI_D_ERROR, "allocating z_stream failed.\n"));
    return rc;
  }

  stream->zalloc = zlib_alloc;
  stream->zfree = zlib_free;
  stream->next_out = out_buf;
  stream->avail_out = out_buf_len;

  /* skip over gzip header */
  stream->next_in = in_buf + GZIP_HEADER_LEN;
  stream->avail_in = in_len - GZIP_HEADER_LEN;
  /* skip over ascii filename */
  if (in_buf[3] & 0x8) {
    for (i = 0; i < GZIP_FILENAME_LIMIT && *stream->next_in++; i++) {
      if (stream->avail_in == 0) {
        DEBUG ((EFI_D_ERROR, "header error\n"));
        goto gunzip_end;
      }
      --stream->avail_in;
    }
  }

  rc = inflateInit2 (stream, -MAX_WBITS);
  if (rc != Z_OK) {
    DEBUG ((EFI_D_ERROR, "inflateInit2 failed!\n"));
    goto gunzip_end;
  }

  /* If inflate() returns
   * Z_OK and with zero avail_out: O/P buffer is full
   * Z_STREAM_END: we uncompressed it all
   */
  rc = inflate (stream, Z_NO_FLUSH);
  if (stream->avail_out == 0 && rc == Z_OK) {
    rc = -1;
    DEBUG ((EFI_D_ERROR, "Error in decompression: Output buffer full\n"));
    goto gunzip_end;
  } else if (rc == Z_STREAM_END) {
    rc = 0;
  } else {
    DEBUG (
        (EFI_D_ERROR,
         "Error in decompression: Something went wrong while decompression\n"));
    rc = -1;
    goto gunzip_end;
  }

  inflateEnd (stream);
  if (pos)
    /* alculation the length of the compressed package */
    *pos = stream->next_in - in_buf + 8;

  if (out_len)
    *out_len = stream->total_out;

gunzip_end:
  FreePool (stream);
  stream = NULL;
  return rc; /* returns 0 if decompressed successful */
}

/* check if the input "buf" file was a gzip package.
 * Return true if the input "buf" is a gzip package.
 */
int
is_gzip_package (unsigned char *buf, unsigned int len)
{
  if (len < 10 || !buf || buf[0] != 0x1f || buf[1] != 0x8b || buf[2] != 0x08) {
    return false;
  }

  return true;
}
