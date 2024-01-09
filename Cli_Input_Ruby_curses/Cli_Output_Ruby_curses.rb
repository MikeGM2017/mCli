
require 'curses'
include Curses

class Cli_Output_Ruby_curses

	def Output_Init()

		Curses.noecho # do not show typed keys
		Curses.init_screen()
		Curses.stdscr.keypad(true) # enable arrow keys (required for pageup/down)

		Curses.setpos(0,0)

		return true
	end

	def Output_Close()
		Curses.close_screen()
		return true
	end

	def Output_Clear()
		Curses.clear()
		return true
	end

	def Output_Char(c)
		printf("%c", c)
		STDOUT.flush
	end

	def Output_NewLine()
		printf("\n\r")
		STDOUT.flush
	end

	def Output_Str(s)
		printf("%s", s)
		STDOUT.flush
	end

	def Output_Return()
		printf("\r")
		STDOUT.flush
	end

end

