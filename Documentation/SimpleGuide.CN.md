# msmnilePkg 移植向导. 
## **[English Version](SimpleGuide.md)**
## **⚠ 提示，不要在谷歌、索尼和三星设备上尝试。**

> ### 此向导分为4步。
>> 0. 介绍一些目录和文件。
>> 1. 初步移植和测试。
>> 2. 尝试启动Windows并测试UFS和USB。
>> 3. 补丁二进制驱动文件.
___
## **步骤0.** 介绍一些目录和文件
  - 我们只需要了解`Platform/SurfaceDuo1Pkg/`目录下的一些目录和文件。
    ```
    ~/mu-msmnile$ tree Platforms/SurfaceDuo1Pkg/ -L 2 -d
    Platforms/SurfaceDuo1Pkg/
    |-- AcpiTables                    # 存放ACPI tables
    |   |-- 8150
    |   |-- CustomizedACPI
    |   `-- Include
    |-- Device                        # 存放每个设备独有的驱动/库和配置。子文件夹的名字必须是`品牌-设备代号`
    |   |-- asus-I001DC
    |   |-- kakao-pine
    |   |-- lg-alphaplus
    |   |-- lg-betalm
    |   |-- lg-flashlmdd
    |   |-- lg-mh2lm
    |   |-- lg-mh2lm5g
    |   |-- meizu-m928q
    |   |-- nubia-tp1803
    |   |-- oneplus-guacamole
    |   |-- oneplus-hotdog
    |   |-- samsung-beyond1qlte
    |   |-- xiaomi-andromeda
    |   |-- xiaomi-cepheus
    |   |-- xiaomi-hercules
    |   |-- xiaomi-nabu
    |   |-- xiaomi-raphael
    |   `-- xiaomi-vayu
    |-- Driver                        # 存放UEFI驱动
    |   |-- GpioButtons
    |   `-- KernelErrataPatcher
    |-- FdtBlob                       # 包含SurfaceDuo的扁平设备树文件
    |-- Include                       # 包含C语言头文件
    |   |-- Configuration
    |   |-- Library
    |   `-- Resources
    |-- Library                       # 包含驱动所需的libs。
    |   |-- MemoryInitPeiLib
    |   |-- MsPlatformDevicesLib
    |   |-- PlatformPeiLib
    |   |-- PlatformPrePiLib
    |   |-- PlatformThemeLib
    |   `-- RFSProtectionLib
    |-- PatchedBinaries               # 包含SurfaceDuo1的补丁过后的驱动文件
    `-- PythonLibs                    # 存放一些Python库
    ```

  - 近距离观察一下`Device/nubia-tp1803`。
    ```
    ~/mu-msmnile/Platforms/SurfaceDuo1Pkg/Device$ tree -L 1  nubia-tp1803/
    ├── ACPI                          # 存放设备的dsdt table
    ├── APRIORI.inc                   # Dxe的加载顺序。包含在SurfaceDuo1.fdf内
    ├── Binaries                      # 存放设备的firmware binaries
    ├── Defines.dsc.inc               # 特殊用途的宏指令。详情请参阅[DefinesGuidance.md](DefinesGuidance.md)
    ├── DeviceTreeBlob                # 存放设备的tree blob。
    │                                    # 这里你需要注意的是：
    │                                    # 子文件夹`Linux`存放主线Linux dtb，文件名必须是`linux-设备代号.dtb`
    │                                    # 子文件夹`Android`存放安卓dtb，文件名必须是`android-设备代号.dtb`
    ├── DXE.dsc.inc                   # 声明驱动。该文件被包含于SurfaceDuo1.dsc中
    ├── DXE.inc                       # 声明驱动。该文件被包含于SurfaceDuo1.fdf中
    ├── Library                       # 存放只适用于该设备的库
    ├── PatchedBinaries               # 存放设备的补丁过后的驱动文件
    └── PcdsFixedAtBuild.dsc.inc      # 包含在SurfaceDuo1.fdf内。存放设备特殊的pcds（例如Screen resolution）
    ```

___
## **步骤1.** 初步移植和测试
  - 我们以魅族16T移植UEFI为例。
    1. 获得设备代号: m928q.
    2. 复制`oneplus-guacamole/`并重命名为`meizu-m928q/`. (品牌-设备代号).
    3. 删除`meizu-m928q/Binaries`和`meizu-m928q/PatchedBinaries`下的所有文件.
    4. 提取设备xbl文件并放置在Binaries文件夹.
        + *下载并完成[UefiReader](https://github.com/WOA-Project/UEFIReader)*
        + *将设备连接电脑，adb命令提取xbl分区*
        + *UefiReader.exe <xbl.img路径> <输出文件夹>*
        + *将输出文件放到`meizu-m928q/Binaries`.*
    5. 编辑 meizu-m928q文件夹中的`DXE.inc`, `APRIORI.inc`, `DXE.dsc.inc`.
        + *使用`diff`对比不同之处*
          ```
          $ diff meizu-m928q/Binaries/DXE.inc oneplus-guacamole/Binaries/DXE.inc 
          23d22
          < INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
          97,102d95
          < FILE FREEFORM = A91D838E-A5FA-4138-825D-455E23030795 {
          <     SECTION UI = "logo2_ChargingMode.bmp"
          <     SECTION RAW = RawFiles/logo2_ChargingMode.bmp
          < }
            ...
          ```
        + *所以你需要编辑`DXE.inc`中的`Raw Files`部分，并在`DXE.inc`和`DXE.dsc.inc`中的添加SimpleTextInOutSerial.inf*
        + *如果SimpleTextInOutSerial在Binaries/APRIORI.inc中也有设置，你需要把它添加进`APRIORI.inc`*
    6. 启用`Defines.dsc.inc`中的MLVM(FALSE改为TRUE)
    7. 编辑`PcdFixedAtBuild.dsc.inc`中的屏幕分辨率.
    8. Patch你的设备的dxe并放置在`PatchedBinaries/`文件夹下.
    9. 用`android-m928q.dtb`替换`android-guacamole.dtb`(你可以在`/sys/firmware/fdt`找到dtb, 或参照[补充说明](#补充说明))
    10. 用 `linux-m928q.dtb`替换`linux-guacamole.dtb`.(如果没有，可以通过`touch linux-m928q.dtb`创建一个假的)
    11. 编译（编译方法参见[README.md](https://github.com/woa-msmnile/msmnilePkg/tree/main#build-instructions)）.
    12. 测试.
        + *建议使用fastboot boot命令热启动UEFI进行测试*
  - 如果移植成功，设备将进入UEFI Shell.
  - 如果设备卡住、重启或崩溃该怎么做 ?
    * 参阅步骤3，补丁你的设备的驱动文件, 或联系我们.
___
## **步骤2.** 尝试启动Windows并测试UFS和USB.
  *有些设备的DSDT是最小的DSDT. 它只包含USB和UFS.*
  - 在你的设备上启动Windows PE.
  - 如果设备卡住、重启或崩溃该怎么做 ?
    * 检查MemoryMap *(brand-codename/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c)*.
    * 检查DeviceConfigurationMap *(brand-codename/Include/Configuration/DeviceConfigurationMap.h)*.
    * 检查`Defines.dsc.inc`中的HAS_MLVM, 尝试将其设为`TRUE`.
  - 使用供电扩展坞后仍然无法使用USB?
    * 补丁驱动.
  *如果移植成功，设备将进入PE.*
___
## **步骤3.** 驱动补丁.
  - 那些驱动需要补丁 ?
    * 如果设备在加载PILDxe时卡住, 你需要补丁 UFSDxe.
    * 如果设备无法通过KDNET连接电脑, 或使用供电扩展坞后仍然无法在Windows内使用USB, 你需要补丁 UsbConfigDxe.
    * 如果设备在uefi菜单无法使用按键, 你需要补丁 ButtonsDxe.
  - 如何找到需要补丁的位置 ?
    * 最简单的方法:
      + 找到另一个设备的原始xxxDxe.efi和它补丁过的 xxxDxe.efi .
      + hex对比一下，就知道应该patch哪里和patch什么了.
        ```
        hexdump -C a_xxxDxe.efi > a.txt
        hexdump -C b_xxxDxe.efi > b.txt
        diff a.txt b.txt
        ```
        - 例: 
            * UFSDxe.efi (nabu):
            ```
            ~/mu-msmnile/Platforms/SurfaceDuo1Pkg/Device/xiaomi-nabu$ diff a.txt b.txt 
            383c383
            < 000025f0  00 00 80 52 c0 03 5f d6  fd 7b 03 a9 fd c3 00 91  |...R.._..{......|
            ---
            > 000025f0  ff 03 01 d1 f4 4f 02 a9  fd 7b 03 a9 fd c3 00 91  |.....O...{......|
            913c913
            < 00004710  20 00 80 52 c0 03 5f d6  fd 43 00 91 e8 7b 00 32  | ..R.._..C...{.2|
            ---
            > 00004710  ff 83 00 d1 fd 7b 01 a9  fd 43 00 91 e8 7b 00 32  |.....{...C...{.2|
            ```
    * 如何patch ?
      + 现在你知道了被补丁的位置是`0x000025f0`和`0x00004710`.
      + 在IDA (或其他工具)打开这两个efi文件, 查找位于或临近`0x000025f0`和`0x00004710`的函数/指令.
      + 看看哪些命令被修改了.
      + 在IDA中打开你的设备的xxxDxe.efi.
      + 找到相同或相似的函数/指令.
      + 给你的设备的xxxDxe.efi应用相同的补丁.
      + 将补丁过的efi驱动文件放到`PatchedBinaries/`.
      + 检查DXE.dsc.inc和DXE.inc中patch过的驱动文件的路径.
___
## **补充说明**
  - 如何获得我的设备的dtb? *默认在termux环境中*
    * 下载Magiskboot. ([Prebuilt](https://github.com/TeamWin/external_magisk-prebuilt/blob/android-11/prebuilt/))
    * 提取设备的boot分区.
      ```
      sudo cp /dev/block/by-name/boot ~/split-appended-dtb/myboot.img
      ```
    * Magsikboot解包boot获得dtb.
      ```
      ./magiskboot_arm unpack myboot.img
      ```
    * 将`kernel_dtb`重命名为`android-设备代号.dtb`并放置在Device/品牌-设备代号/DeviceTreeBlob/Android/.
  - MLVM应该一直为`TRUE`吗?
    * 在早期测试中你可以将其设置为`TRUE`来避免MLVM问题.
    * 如果你可以启动Windows, 请尝试将其恢复`FALSE`.
    * 将MLVM设为`TRUE`会占用大约300MB运行内存.
___
***不要忘记将你的设备和你的名字添加到[README](https://github.com/woa-msmnile/msmnilePkg/tree/main#target-list)中.***  
***感谢你的付出.***


