# MSYS2 Configurations

Note: This is for the Windows operating system

Date: 14.03.2018

### C/C++ build


1. Top level -> Build Command

	`python ${IDF_PATH}/tools/windows/eclipse_make.py`

2. Environment Tab

	Add Environment variables

	```
	BATCH_BUILD
	1
	```

	```
	IDF_PATH
	D:/GIT/esp-idf
	```
	Note: Make sure the IDF_PATH has `Forward Slashes` instead of backward slashes

	```
	PATH
	D:\esp32\msys32\usr\bin;D:\esp32\msys32\mingw32\bin;D:\esp32\msys32\opt\xtensa-esp32-elf\bin
	```


### C/C++ General

1. CDT GCC Build Output Parser

	`xtensa-esp32-elf-(g?cc)|([gc]\+\+)|(clang)`

2. CDT GCC Built-in Compiler Settings Cygwin

	`xtensa-esp32-elf-gcc ${FLAGS} -E -P -v -dD "${INPUTS}"`
