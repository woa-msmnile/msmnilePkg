# Aarch64 Secure Boot Defaults

This external dependency contains the default values suggested by microsoft the KEK, DB, and DBX UEFI variables.

Additionally, it contains an optional shared PK certificate that may be used as the root of trust for the system.
The shared PK certificate is an offering from Microsoft. Instead of a original equipment manufacturer (OEM)
managed PK, an OEM may choose to use the shared PK certificate managed by Microsoft. Partically, this may be
useful as default on non production code provided to an OEM by an indenpendent vendor (IV).

1. The PK (Platform Key) is a single certificate that is the root of trust for the system. This certificate is used
    to verify the KEK.
2. The KEK (Key Exchange Key) is a list of certificates that verify the signature of other keys attempting to update
   the DB and DBX.
3. The DB (Signature Database) is a list of certificates that verify the signature of a binary attempting to execute
   on the system.
4. The DBX (Forbidden Signature Database) is a list of signatures that are forbidden from executing on the system.

Please review [Microsoft's documentation](https://learn.microsoft.com/en-us/windows-hardware/manufacture/desktop/windows-secure-boot-key-creation-and-management-guidance?view=windows-11#15-keys-required-for-secure-boot-on-all-pcs)
for more information on key requirements if appending to the defaults provided in this external dependency.

## DefaultPk

Contains the OEMA0 PK to enable signature database updates and binary execution.

Files Included:


## DefaultKek

Contains the Microsoft KEKs and OEMA0 KEK to enable signature database updates and binary execution.

Files Included:

* <https://go.microsoft.com/fwlink/?LinkId=321185>
* <https://go.microsoft.com/fwlink/?linkid=2239775>
* <https://github.com/WOA-Project/SurfaceDuoPkg>

## DefaultDb

Contains only Microsoft certificates to verify binaries before execution. More secure than Default3PDb.

Files Included:

* <https://go.microsoft.com/fwlink/p/?linkid=321192>
* <https://go.microsoft.com/fwlink/?linkid=2239776>

## Default3PDb

Contains Microsoft and UEFI third party certificates to verify binaries before execution. More compatible than
DefaultDb.

Files Included:

* <https://go.microsoft.com/fwlink/p/?linkid=321192>
* <https://go.microsoft.com/fwlink/?linkid=2239776>
* <https://go.microsoft.com/fwlink/p/?linkid=321194>
* <https://go.microsoft.com/fwlink/?linkid=2239872>

## DefaultDbx

Contains a list of revoked certificates that will not execute on this system. Filtered per Architecture (ARM, Intel).

Files Included:

* <https://uefi.org/sites/default/files/resources/dbx_info.csv>

---

## License

Terms of Use for Microsoft Secure Boot Objects ("Secure Boot Objects")

By downloading the Secure Boot Objects, you agree to the following terms.
If you do not accept them, do not download or use the Secure Boot Objects.

These terms do not provide you with any legal rights to any intellectual
property in any Microsoft product.

You may copy and use the Secure Boot Objects for your internal, reference
purposes and to design, develop, and test your software, firmware or hardware,
as applicable; and you may distribute the Secure Boot Objects to end users
solely as part of the distribution of an operating system software product, or
as part of the distribution of updates to an operating system software product;
and you may distribute the Secure Boot Objects to end users or through your
distribution channels solely as embodied in a firmware product or hardware
product that embodies nontrivial additional functionality. Without limiting the
foregoing, copying or reproduction of the Secure Boot Objects to any other
server or location for further reproduction or redistribution on a standalone
basis is expressly prohibited.

If you are engaged in the business of developing and commercializing hardware
products that include the UEFI standard
(available at https://uefi.org/specifications), you may copy and use the Secure
Boot Objects for your internal, reference purposes and to design, develop, and
test your software; and you may distribute the Secure Boot Objects end users
solely as part of the distribution of an operating system software product, or
as part of the distribution of updates to an operating system software product.
Without limiting the foregoing, copying or reproduction of the Secure Boot
Objects to any other server or location for further reproduction or
redistribution on a standalone basis is expressly prohibited.
The Secure Boot Objects are provided “as-is.” The information contained in the
Secure Boot Objects may change without notice.  Microsoft does not represent
that the Secure Boot Objects is error free and you bear the entire risk of
using it.  NEITHER MICROSOFT NOR UEFI MAKES ANY WARRANTIES, EXPRESS OR IMPLIED,
WITH RESPECT TO THE SECURE BOOT OBJECTS, AND MICROSOFT AND UEFI EACH EXPRESSLY
DISCLAIMS ALL OTHER EXPRESS, IMPLIED, OR STATUTORY WARRANTIES.  THIS INCLUDES
THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
NON-INFRINGEMENT.
TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, IN NO EVENT SHALL MICROSOFT
OR UEFI BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY
DAMAGES WHATSOEVER ARISING OUT OF OR IN CONNECTION WITH THE USE OR DISTRIBUTION
OF THE SECURE BOOT OBJECTS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION.

YOU AGREE TO RELEASE MICROSOFT (INCLUDING ITS AFFLIATES, CONTRACTORS, AGENTS,
EMPLOYEES, LICENSEES AND ASSIGNEES) AND UEFI (INCLUDING ITS AFFILIATES,
CONTRACTORS, AGENTS, EMPLOYEES, LICENSEES AND SUCCESSORS) FROM ANY AND ALL
CLAIMS OR LIABILITY ARISING OUT OF YOUR USE OR DISTRIBUTION OF THE SECURE
BOOT OBJECTS AND ANY RELATED INFORMATION.
