
We buildt a shabby Duo-devices Framework for now.

## 1.Add a device in Platforms/SurfaceDuoPkg/SurfaceDuo.dsc
	You may have found there is a macro defined in it:

	 #
	 # Build ID Tables
	 #
	 #
	 #    0. Xiaomi Mix3 5g (andromeda)
	 #    1. Xiaomi Pad 5   (nabu)
	 #    2. LG G8          (waiting...)
	 #
	      ^----------------------------- Define your device here. (1,2,3,4,5.... are BUILD_DEVICE_ID.)
	                                     For example,if I have a Op7.
	                                     Write a new line in the table and comment it:
	                                        #    3.OnePlus 7	(guacamoleb)
	   DEFINE BUILD_DEVICE_ID        = 3
	   ^---------------------------------   By changing the ID of the macro, you can set which device you want to build.
						It's also used to switch configuration.
						Set the value to the ID you set above.

	
## 2. Set Your Device's Revolution in Platforms/SurfaceDuoPkg/SurfaceDuo.dsc
	After adding a device ID , then you should write some configs for it.
	It is easy to do.
	Open this file and add it.

	   An example:

	     #
	     # Screen Resolution Config (Do Not Edit)
	     #

	   #Mix 3 5G
	   ^---------                                                         Here is your device name 
 
	     !if $(BUILD_DEVICE_ID) == 0 
				       ^--                                    This is the ID you defined for your device before.

	           gSurfaceDuoPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1080    
	                                                          ^---------- This is Width. 

	           gSurfaceDuoPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|2340
								  ^---------- This is Height. Don't mix them up.
	   !endif

	Hey,Please attach your config below the last one instead of just changing original configuration.
	You are not lazy, right?


## 3.Get Your Device's Firmware Binaries

	Each device has its own firmwares and you need to add it before building.

	 You can also see Readme file under Platforms/SurfaceDuoPkg/FirmwareBinaries/,which tells a way to get firmware binaries.

	 (But I prefer to use 7z it extract binaries form xbl.elf :D)

	Anyway, you should get your device's EFI files finanlly.
	Put these files under CustomizedBinaries/BAND/CODENAME_NAME_XXX/

	Then, please do as follows:

	 First, copy DXE0.inc to DXEx.inc(x is the ID you set before.). 
	 Second, open DXEx.inc.
	 Third, find "SECTION PE32 = SurfaceDuoPkg/CustomizedBinaries/XXXXX/XXXXX/XXXXX.efi" 
	 What you need to do now is just editing the path.
	 REMEMBER , DO NOT REMOVE ANY PARTS IF NOT NECESSARY.

	!!!! WARNING
	 ! What I want to say, this step maybe important.
	 ! I add Xiaomi MIX 3 5G's firmware binaries and test uefi on qrd 855.
	 ! However, after some tests,its small board burnt.
	 ! Another qrd also met this problem.
	 ! I can not determine what caused the death.
	 ! But it was certainly not caused by PEP because I haven't install it.
	 ! So,don't be lazy.


## 4.Config Your Device-specific Binaries
 
	Open the Platforms/SurfaceDuoPkg/SurfaceDuo.fdf and find this part:

	  #
	  # Choose Binaries Configuration Here.
	  #

	   #MIX3 5G
	   ^-------  Your device's name

	    !if $(BUILD_DEVICE_ID) == 0
				     ^-- Your device's ID.
	      !include SurfaceDuoPkg/Include/DXE0.inc
			^---------------------------- A Firmware Binaries configuration, is used to set what you want to add and where are them.
							Set it to the one you just modified.
	    !endif

## 5.You have finished all the work.Just GO and BUILD!

## 6. Additional Step.
	If you find that your phone can't boot uefi, you may have to patch dxes.
	Check "Platforms/SurfaceDuoPkg/PatchedBinaries/Readme.md" and patch your device's binanries.

## NOTICE
	This is only a guide for you to port uefi.
	If you want windows support, you'll have to to adapt DSDT for your device.
	A set of generic acpi is for you by default.
	For newer ACPI,please check SDPKG and modify it yourself.

	(Cost sunflower2333 2 hours to write this doc.)
	Help me correct it if you find any mistake in it.Thank you!
