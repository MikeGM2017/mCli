
require 'io/console'

require 'curses'
include Curses

$quit_Count = 0
$quit_Count_Max = 10
$stop = false

trap "SIGINT" do
	printf("Ctrl+C\n\r");
	$quit_Count = 0
end

trap "SIGTSTP" do
	printf("Ctrl+Z\n\r");
	$quit_Count = 0
end

trap "SIGQUIT" do
	printf("Ctrl+Backslash\n\r");
	$quit_Count = $quit_Count + 1
	if $quit_Count > $quit_Count_Max
		if($stop != true)
			$stop = true
			printf("Finished - Press Any Key to Quit")
		else
			$cli_Output.Output_Str("Interrupted")
			exit(0)
		end
	end
end

def Input_Init()
	Curses.noecho # do not show typed keys
	Curses.init_screen()
	Curses.stdscr.keypad(true) # enable arrow keys (required for pageup/down)
	Curses.setpos(0,0)
end

def Input_Restore()
	Curses.close_screen()
end

def Input_Char_Get()
	return Curses.getch
end



Input_Init()

Curses.addstr("Test Key Codes: Ruby curses\n")

loop do

	$c = Input_Char_Get()
	if $c != nil
		print "%3s %3d 0x%02X\n\r" % [ $c, $c.ord, $c.ord ]
	end

	if($stop)
		break
	end

end

Input_Restore()
