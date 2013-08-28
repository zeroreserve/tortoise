Tortoise Plugin

This plugin uses the Retroshare Turtle service. To compile it copy it alongside the other
RS plugins in the source. Build RetroShare and then simly type 
$ qmake && make

Then copy the resulting lib into
%APPDATA%\Retroshare\extensions on Windows
~/.retroshare/extensions on Unix / Mac

on *nix like OSes you need to rename it from libTortoise.so.1.0.0 to something like
Tortoise.so.

Then start Retroshare with at least 3 instances where the friendship graph is like this:
A<->B<->C.

Wait until everyone is connected. Then:
Enter any string in the field "Server Hash" and click "Listen to this". Then enter
the SAME string in the field "Cliend Hash" and click "Monitor this". 
Then send Messages back and forth.

Have Fun!

