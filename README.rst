=========================================================================
cencode: encodes a stream or a file into quoted c-string escape sequences
=========================================================================

cencode encodes a stream or a file into quoted c-string escape sequences,
suitable for use directly in C code. It is a universal alternative to dedicated
export formats like XPM, unportable resource forks, linker flags, and Windows
resources where dynamic loading of external data is not possible or undesired. 


Building
========

Just "make".

Compiler optimisations are left to the user. Set your standard compiler flags
(CPPFLAGS/CXXFLAGS/LDFLAGS) before building.

Copy the resulting "cencode" executable and manual "cencode.1" where
appropriate (usually "/usr/local/bin" and "/usr/local/share/man/man1").


Authors and Copyright
=====================

cencode is distributed under the Revised BSD license (see COPYING) WITHOUT ANY
WARRANTY. Use at your own risk.

Copyright(c) 2007-2008 by wave++ "Yuri D'Elia" <wavexx@thregr.org>.
Suggestions/comments are welcome.

The cencode home page is located at:

http://www.thregr.org/~wavexx/software/cencode/
