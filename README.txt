# MoodMate-Wellness-Logger-Final-Part

MoodMate - C++ Wellness Logging Application

FILES
-----
MoodMate.cpp
moodmate.txt

REQUIREMENTS
------------
A C++ compiler supporting C++11 or later.

COMPILE
-------
g++ -std=c++11 -Wall -Wextra -pedantic MoodMate.cpp -o MoodMate

RUN
---
Linux/macOS:
./MoodMate

Windows:
MoodMate.exe

DATA FILE
---------
The application reads and writes moodmate.txt in the program's
working directory. Start the application from the directory
containing the data file.

FILE FORMAT
-----------
Each record contains five consecutive lines:
1. Date
2. Integer mood rating
3. Note
4. Sleep hours
5. Integer exercise minutes

Notes can contain spaces. Each note must occupy one line.

PERSISTENCE
-----------
Entries are loaded at startup. Options 5 and 6 save a complete
snapshot of the current log. Saving replaces the previous file
contents rather than appending records.

ERROR HANDLING
--------------
A missing file starts a new empty log. Incomplete records and
invalid numeric fields are reported, and loading stops at the
malformed record. Earlier valid records are retained.
At most 20 records can be loaded or stored.

VALIDATION
----------
Mood rating: 1-5, otherwise 3.
Sleep hours: 0-24, otherwise 0.
Exercise minutes: 0-1440, otherwise 0.
Empty date: Unspecified.
Empty note: No note.
