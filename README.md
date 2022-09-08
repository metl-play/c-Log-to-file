# c-Log-to-file
This is a function which can be used as printf() but it will be written into a file in the same directory as the executable.

This Log() function can be used to as printf() but it's content is written to a file (the file name is by default in the following way mmddhh.txt = month day hour.txt).
It can make use of %d, %f, %s, x% others are possible but not tested yet.

If on runtime the hour changes it will generate a new file and then write every following contents to that until the hour changes again.

The librarys stdio.h, stdarg.h and time.h are at least Part of the IDE Visual Studio 2022 Cummunity availble at https://visualstudio.microsoft.com/de/downloads/ as of today 08.09.2022.
These fall under the Copyright of Microsoft as they state:

//
// stdio.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// The C Standard Library <stdio.h> header.
//

//
// stdarg.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// The C Standard Library <stdarg.h> header.
//

//
// time.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// The C Standard Library <time.h> header.
//
