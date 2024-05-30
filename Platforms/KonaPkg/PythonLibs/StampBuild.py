# ported from build_releaseinfo.ps1

import os
import datetime
import getpass
import socket

def stamp_build():
    print("Stamp build...")
    old_cwd = os.getcwd()
    os.chdir("MU_BASECORE")
    edk2_commit = os.popen("git rev-parse HEAD").read().strip()
    os.chdir(old_cwd)
    commit = os.popen("git rev-parse HEAD").read().strip()

    date = datetime.datetime.now().strftime("%m/%d/%Y")
    user = getpass.getuser()
    hostname = socket.gethostname()
    owner = f"{user}@{hostname}"

    if commit != '':
        commit = f"{commit[:8]}"
        edk2_commit = f"{edk2_commit[:8]}"

    release_info = f"""#ifndef __SMBIOS_RELEASE_INFO_H__
#define __SMBIOS_RELEASE_INFO_H__
#ifdef __IMPL_COMMIT_ID__
#undef __IMPL_COMMIT_ID__
#endif
#define __IMPL_COMMIT_ID__ "{commit}"
#ifdef __RELEASE_DATE__
#undef __RELEASE_DATE__
#endif
#define __RELEASE_DATE__ "{date}"
#ifdef __BUILD_OWNER__
#undef __BUILD_OWNER__
#endif
#define __BUILD_OWNER__ "{owner}"
#ifdef __EDK2_RELEASE__
#undef __EDK2_RELEASE__
#endif
#define __EDK2_RELEASE__ "{edk2_commit}"
#endif"""

    with open("Platforms/SurfaceDuoFamilyPkg/Include/Resources/ReleaseInfo.h", "w") as f:
        f.write(release_info)
        
    
if __name__ == "__main__":
    stamp_build()
    exit(0)