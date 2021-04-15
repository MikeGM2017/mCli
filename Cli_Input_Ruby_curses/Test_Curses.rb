
require 'curses'
include Curses

printf("%s", "Start 1")
STDOUT.flush

Curses.getch

printf("%s", "Start 2")
STDOUT.flush

Curses.getch

