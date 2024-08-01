 # Copyright (c) 2015, The Linux Foundation. All rights reserved.
 #
 # Redistribution and use in source and binary forms, with or without
 # modification, are permitted provided that the following conditions are
 # met:
 # * Redistributions of source code must retain the above copyright
 #  notice, this list of conditions and the following disclaimer.
 #  * Redistributions in binary form must reproduce the above
 # copyright notice, this list of conditions and the following
 # disclaimer in the documentation and/or other materials provided
 #  with the distribution.
 #   * Neither the name of The Linux Foundation nor the names of its
 # contributors may be used to endorse or promote products derived
 # from this software without specific prior written permission.
 #
 # THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 # WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 # MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 # ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 # BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 # CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 # SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 # BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 # WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 # OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 # IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import stat
import csv
import itertools
import struct
import os
import shutil

# ELF Definitions
ELF_HDR_COMMON_SIZE       = 24
ELF32_HDR_SIZE            = 52
ELF32_PHDR_SIZE           = 32
ELF64_HDR_SIZE            = 64
ELF64_PHDR_SIZE           = 56
ELFINFO_MAG0_INDEX        = 0
ELFINFO_MAG1_INDEX        = 1
ELFINFO_MAG2_INDEX        = 2
ELFINFO_MAG3_INDEX        = 3
ELFINFO_MAG0              = '\x7f'
ELFINFO_MAG1              = 'E'
ELFINFO_MAG2              = 'L'
ELFINFO_MAG3              = 'F'
ELFINFO_CLASS_INDEX       = 4
ELFINFO_CLASS_32          = '\x01'
ELFINFO_CLASS_64          = '\x02'
ELFINFO_VERSION_INDEX     = 6
ELFINFO_VERSION_CURRENT   = '\x01'
ELF_BLOCK_ALIGN           = 0x1000
ALIGNVALUE_1MB             = 0x100000
ALIGNVALUE_4MB            = 0x400000
ELFINFO_DATA2LSB          = '\x01'
ELFINFO_EXEC_ETYPE        = '\x02\x00'
ELFINFO_ARM_MACHINETYPE   = '\x28\x00'
ELFINFO_VERSION_EV_CURRENT = '\x01\x00\x00\x00'
ELFINFO_SHOFF             = 0x00
ELFINFO_PHNUM             = '\x01\x00'
ELFINFO_RESERVED          = 0x00

# ELF Program Header Types
NULL_TYPE                 = 0x0
LOAD_TYPE                 = 0x1
DYNAMIC_TYPE              = 0x2
INTERP_TYPE               = 0x3
NOTE_TYPE                 = 0x4
SHLIB_TYPE                = 0x5
PHDR_TYPE                 = 0x6
TLS_TYPE                  = 0x7

# Access Type
MI_PBT_RW_SEGMENT                     = 0x0
MI_PBT_RO_SEGMENT                     = 0x1
MI_PBT_ZI_SEGMENT                     = 0x2
MI_PBT_NOTUSED_SEGMENT                = 0x3
MI_PBT_SHARED_SEGMENT                 = 0x4
MI_PBT_RWE_SEGMENT                    = 0x7

#----------------------------------------------------------------------------
# GLOBAL VARIABLES END
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# CLASS DEFINITIONS BEGIN
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
# OS Type ID Class
#----------------------------------------------------------------------------
class OSType:
    ANDROID_BOOT_OS    = 2
    LINUX_BOOT_OS      = 5

#----------------------------------------------------------------------------
# Image Type ID Class - These values must be kept consistent with mibib.h
#----------------------------------------------------------------------------
class ImageType:
   NONE_IMG           = 0
   APPSBL_IMG         = 5

#----------------------------------------------------------------------------
# Header Class Notes:
# In order to properly read and write the header structures as binary data,
# the Python Struct library is used to align and package up the header objects
# All Struct objects are initialized by a special string with the following
# notation. These structure objects are then used to decode binary data in order
# to fill out the appropriate class in Python, or they are used to package up
# the Python class so that we may write the binary data out.
#----------------------------------------------------------------------------
"""
      Format | C Type         | Python Type | Standard Size
      -----------------------------------------------------
    1) 'X's  | char *         | string      | 'X' bytes
    2) H     | unsigned short | integer     | 2 bytes
    3) I     | unsigned int   | integer     | 4 bytes

"""

#----------------------------------------------------------------------------
# ELF Header Class
#----------------------------------------------------------------------------
class Elf_Ehdr_common:
   # Structure object to align and package the ELF Header
   s = struct.Struct('16sHHI')

   def __init__(self, data):
      unpacked_data       = (Elf_Ehdr_common.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.e_ident        = unpacked_data[0]
      self.e_type         = unpacked_data[1]
      self.e_machine      = unpacked_data[2]
      self.e_version      = unpacked_data[3]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value


#----------------------------------------------------------------------------
# ELF Header Class
#----------------------------------------------------------------------------
class Elf32_Ehdr:
   # Structure object to align and package the ELF Header
   s = struct.Struct('16sHHIIIIIHHHHHH')

   def __init__(self, data):
      unpacked_data       = (Elf32_Ehdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.e_ident        = unpacked_data[0]
      self.e_type         = unpacked_data[1]
      self.e_machine      = unpacked_data[2]
      self.e_version      = unpacked_data[3]
      self.e_entry        = unpacked_data[4]
      self.e_phoff        = unpacked_data[5]
      self.e_shoff        = unpacked_data[6]
      self.e_flags        = unpacked_data[7]
      self.e_ehsize       = unpacked_data[8]
      self.e_phentsize    = unpacked_data[9]
      self.e_phnum        = unpacked_data[10]
      self.e_shentsize    = unpacked_data[11]
      self.e_shnum        = unpacked_data[12]
      self.e_shstrndx     = unpacked_data[13]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.e_ident,
                self.e_type,
                self.e_machine,
                self.e_version,
                self.e_entry,
                self.e_phoff,
                self.e_shoff,
                self.e_flags,
                self.e_ehsize,
                self.e_phentsize,
                self.e_phnum,
                self.e_shentsize,
                self.e_shnum,
                self.e_shstrndx
               ]

      return (Elf32_Ehdr.s).pack(*values)

#----------------------------------------------------------------------------
# ELF Program Header Class
#----------------------------------------------------------------------------
class Elf32_Phdr:

   # Structure object to align and package the ELF Program Header
   s = struct.Struct('I' * 8)

   def __init__(self, data):
      unpacked_data       = (Elf32_Phdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.p_type         = unpacked_data[0]
      self.p_offset       = unpacked_data[1]
      self.p_vaddr        = unpacked_data[2]
      self.p_paddr        = unpacked_data[3]
      self.p_filesz       = unpacked_data[4]
      self.p_memsz        = unpacked_data[5]
      self.p_flags        = unpacked_data[6]
      self.p_align        = unpacked_data[7]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.p_type,
                self.p_offset,
                self.p_vaddr,
                self.p_paddr,
                self.p_filesz,
                self.p_memsz,
                self.p_flags,
                self.p_align
               ]

      return (Elf32_Phdr.s).pack(*values)

#----------------------------------------------------------------------------
# ELF Header Class
#----------------------------------------------------------------------------
class Elf64_Ehdr:
   # Structure object to align and package the ELF Header
   s = struct.Struct('16sHHIQQQIHHHHHH')

   def __init__(self, data):
      unpacked_data       = (Elf64_Ehdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.e_ident        = unpacked_data[0]
      self.e_type         = unpacked_data[1]
      self.e_machine      = unpacked_data[2]
      self.e_version      = unpacked_data[3]
      self.e_entry        = unpacked_data[4]
      self.e_phoff        = unpacked_data[5]
      self.e_shoff        = unpacked_data[6]
      self.e_flags        = unpacked_data[7]
      self.e_ehsize       = unpacked_data[8]
      self.e_phentsize    = unpacked_data[9]
      self.e_phnum        = unpacked_data[10]
      self.e_shentsize    = unpacked_data[11]
      self.e_shnum        = unpacked_data[12]
      self.e_shstrndx     = unpacked_data[13]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.e_ident,
                self.e_type,
                self.e_machine,
                self.e_version,
                self.e_entry,
                self.e_phoff,
                self.e_shoff,
                self.e_flags,
                self.e_ehsize,
                self.e_phentsize,
                self.e_phnum,
                self.e_shentsize,
                self.e_shnum,
                self.e_shstrndx
               ]

      return (Elf64_Ehdr.s).pack(*values)

#----------------------------------------------------------------------------
# ELF Program Header Class
#----------------------------------------------------------------------------
class Elf64_Phdr:

   # Structure object to align and package the ELF Program Header
   s = struct.Struct('IIQQQQQQ')

   def __init__(self, data):
      unpacked_data       = (Elf64_Phdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.p_type         = unpacked_data[0]
      self.p_flags        = unpacked_data[1]
      self.p_offset       = unpacked_data[2]
      self.p_vaddr        = unpacked_data[3]
      self.p_paddr        = unpacked_data[4]
      self.p_filesz       = unpacked_data[5]
      self.p_memsz        = unpacked_data[6]
      self.p_align        = unpacked_data[7]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.p_type,
                self.p_flags,
                self.p_offset,
                self.p_vaddr,
                self.p_paddr,
                self.p_filesz,
                self.p_memsz,
                self.p_align
               ]

      return (Elf64_Phdr.s).pack(*values)


#----------------------------------------------------------------------------
# ELF Segment Information Class
#----------------------------------------------------------------------------
class SegmentInfo:
   def __init__(self):
      self.flag  = 0
   def printValues(self):
      print 'Flag: ' + str(self.flag)

#----------------------------------------------------------------------------
# CLASS DEFINITIONS END
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# BOOT TOOLS BEGIN
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# Converts integer to bytes. If length after conversion
# is smaller than given length of byte string, returned value is right-filled
# with 0x00 bytes. Use Little-endian byte order.
#----------------------------------------------------------------------------
def convert_int_to_byte_string(n, l):
    return b''.join([chr((n >> ((l - i - 1) * 8)) % 256) for i in xrange(l)][::-1])

#----------------------------------------------------------------------------
# Create default elf header
#----------------------------------------------------------------------------
def create_elf_header( output_file_name,
                       image_dest,
                       image_size,
                       is_elf_64_bit = False):

   if (output_file_name is None):
      raise RuntimeError, "Requires a ELF header file"

   # Create a elf header and program header
   # Write the headers to the output file
   elf_fp = file(output_file_name, "wb")

   if (is_elf_64_bit is True):
      # ELf header
      elf_fp.write(ELFINFO_MAG0)
      elf_fp.write(ELFINFO_MAG1)
      elf_fp.write(ELFINFO_MAG2)
      elf_fp.write(ELFINFO_MAG3)
      elf_fp.write(ELFINFO_CLASS_64)
      elf_fp.write(ELFINFO_DATA2LSB)
      elf_fp.write(ELFINFO_VERSION_CURRENT)
      elf_fp.write(''.rjust(9, chr(ELFINFO_RESERVED)))
      elf_fp.write(ELFINFO_EXEC_ETYPE)
      elf_fp.write(ELFINFO_ARM_MACHINETYPE)
      elf_fp.write(ELFINFO_VERSION_EV_CURRENT)
      elf_fp.write(convert_int_to_byte_string(image_dest, 8))
      elf_fp.write(convert_int_to_byte_string(ELF64_HDR_SIZE, 8))
      elf_fp.write(convert_int_to_byte_string(ELFINFO_SHOFF, 8))
      elf_fp.write(''.rjust(4, chr(ELFINFO_RESERVED)))
      elf_fp.write(convert_int_to_byte_string(ELF64_HDR_SIZE, 2))
      elf_fp.write(convert_int_to_byte_string(ELF64_PHDR_SIZE, 2))
      elf_fp.write(ELFINFO_PHNUM)
      elf_fp.write(''.rjust(6, chr(ELFINFO_RESERVED)))

      # Program Header
      elf_fp.write(convert_int_to_byte_string(LOAD_TYPE, 4))
      elf_fp.write(convert_int_to_byte_string(MI_PBT_RWE_SEGMENT, 4))
      elf_fp.write(convert_int_to_byte_string(ELF64_HDR_SIZE+ELF64_PHDR_SIZE, 8))
      elf_fp.write(convert_int_to_byte_string(image_dest, 8))
      elf_fp.write(convert_int_to_byte_string(image_dest, 8))
      elf_fp.write(convert_int_to_byte_string(image_size, 8))
      elf_fp.write(convert_int_to_byte_string(image_size, 8))
      elf_fp.write(convert_int_to_byte_string(ELF_BLOCK_ALIGN, 8))
   else:
      # ELf header
      elf_fp.write(ELFINFO_MAG0)
      elf_fp.write(ELFINFO_MAG1)
      elf_fp.write(ELFINFO_MAG2)
      elf_fp.write(ELFINFO_MAG3)
      elf_fp.write(ELFINFO_CLASS_32)
      elf_fp.write(ELFINFO_DATA2LSB)
      elf_fp.write(ELFINFO_VERSION_CURRENT)
      elf_fp.write(''.rjust(9, chr(ELFINFO_RESERVED)))
      elf_fp.write(ELFINFO_EXEC_ETYPE)
      elf_fp.write(ELFINFO_ARM_MACHINETYPE)
      elf_fp.write(ELFINFO_VERSION_EV_CURRENT)
      elf_fp.write(convert_int_to_byte_string(image_dest, 4))
      elf_fp.write(convert_int_to_byte_string(ELF32_HDR_SIZE, 4))
      elf_fp.write(convert_int_to_byte_string(ELFINFO_SHOFF, 4))
      elf_fp.write(''.rjust(4, chr(ELFINFO_RESERVED)))
      elf_fp.write(convert_int_to_byte_string(ELF32_HDR_SIZE, 2))
      elf_fp.write(convert_int_to_byte_string(ELF32_PHDR_SIZE, 2))
      elf_fp.write(ELFINFO_PHNUM)
      elf_fp.write(''.rjust(6, chr(ELFINFO_RESERVED)))

      # Program Header
      elf_fp.write(convert_int_to_byte_string(LOAD_TYPE, 4))
      elf_fp.write(convert_int_to_byte_string(ELF32_HDR_SIZE+ELF32_PHDR_SIZE, 4))
      elf_fp.write(convert_int_to_byte_string(image_dest, 4))
      elf_fp.write(convert_int_to_byte_string(image_dest, 4))
      elf_fp.write(convert_int_to_byte_string(image_size, 4))
      elf_fp.write(convert_int_to_byte_string(image_size, 4))
      elf_fp.write(convert_int_to_byte_string(MI_PBT_RWE_SEGMENT, 4))
      elf_fp.write(convert_int_to_byte_string(ELF_BLOCK_ALIGN, 4))

   elf_fp.close()
   return 0

#----------------------------------------------------------------------------
# BOOT TOOLS END
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# HELPER FUNCTIONS BEGIN
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# Concatenates the files listed in 'sources' in order and writes to 'target'
#----------------------------------------------------------------------------
def concat_files (target, sources):
   if type(sources) is not list:
      sources = [sources]

   target_file = OPEN(target,'wb')

   for fname in sources:
      file = OPEN(fname,'rb')
      while True:
         bin_data = file.read(65536)
         if not bin_data:
            break
         target_file.write(bin_data)
      file.close()
   target_file.close()

#----------------------------------------------------------------------------
# Preprocess an ELF file and return the ELF Header Object and an
# array of ELF Program Header Objects
#----------------------------------------------------------------------------
def preprocess_elf_file(elf_file_name):

   # Initialize
   elf_fp = OPEN(elf_file_name, 'rb')
   elf_header = Elf_Ehdr_common(elf_fp.read(ELF_HDR_COMMON_SIZE))

   if verify_elf_header(elf_header) is False:
      raise RuntimeError, "ELF file failed verification: " + elf_file_name

   elf_fp.seek(0)

   if elf_header.e_ident[ELFINFO_CLASS_INDEX] == ELFINFO_CLASS_64:
      elf_header = Elf64_Ehdr(elf_fp.read(ELF64_HDR_SIZE))
   else:
      elf_header = Elf32_Ehdr(elf_fp.read(ELF32_HDR_SIZE))

   phdr_table = []

   # Verify ELF header information
   if verify_elf_header(elf_header) is False:
      raise RuntimeError, "ELF file failed verification: " + elf_file_name

   # Get program header size
   phdr_size = elf_header.e_phentsize

   # Find the program header offset
   file_offset = elf_header.e_phoff
   elf_fp.seek(file_offset)

   # Read in the program headers
   for i in range(elf_header.e_phnum):
      if elf_header.e_ident[ELFINFO_CLASS_INDEX] == ELFINFO_CLASS_64:
         phdr_table.append(Elf64_Phdr(elf_fp.read(phdr_size)))
      else:
         phdr_table.append(Elf32_Phdr(elf_fp.read(phdr_size)))

   elf_fp.close()
   return [elf_header, phdr_table]

#----------------------------------------------------------------------------
# Perform file copy given offsets and the number of bytes to copy
#----------------------------------------------------------------------------
def file_copy_offset(in_fp, in_off, out_fp, out_off, num_bytes):
   in_fp.seek(in_off)
   read_in = in_fp.read(num_bytes)
   out_fp.seek(out_off)
   out_fp.write(read_in)

   return num_bytes

#----------------------------------------------------------------------------
# Helper functions to open a file and return a valid file object
#----------------------------------------------------------------------------
def OPEN(file_name, mode):
    try:
       fp = open(file_name, mode)
    except IOError:
       raise RuntimeError, "The file could not be opened: " + file_name

    # File open has succeeded with the given mode, return the file object
    return fp
#----------------------------------------------------------------------------
# HELPER FUNCTIONS END
#----------------------------------------------------------------------------

