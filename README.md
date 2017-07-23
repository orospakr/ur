# Usurper's Retribution

This is my attempt at a simple tile-based overhead-view RPG game engine as a
side-project back in my high school days.  The timestamps date back to March
2003, although I think I did the bulk of the work in 2002.

It's written in gcc-flavour C++ (I guess technically C++98?), uses SDL 1.x and
libmodplug for sound, features layers and basic collision detection, and is
pretty portable.  I worked on it on both Linux and Windows, and I recall
building and running it on FreeBSD as well, all admittedly only on x86.

I was building it with an eye for it becoming the core of a fangame set in a
certain canon I was very fond of (Sonic SatAM), although that dream was never
quite realized.

There's a C# port of it that I did a year or so later to support an entry into a
local video game competition run by the local college by myself and a few
friends. That will go in a separate repository.

Licensed GPLv2 for now until I get around to relicensing it to 3-clause BSD or
something.

This first git commit contains no changes after the initial 2002/2003 work.

## Build

    $ cd libmodplug
    $ make
    $ cd ..
    $ make
    $ ./ur
