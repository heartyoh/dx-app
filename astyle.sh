#!/bin/sh -x

astyle -s2 --style=gnu --pad-header --align-pointer=name --indent-col1-comments --pad-first-paren-out --recursive src/*.c
astyle -s2 --style=gnu --pad-header --align-pointer=name --indent-col1-comments --pad-first-paren-out --recursive src/*.h
