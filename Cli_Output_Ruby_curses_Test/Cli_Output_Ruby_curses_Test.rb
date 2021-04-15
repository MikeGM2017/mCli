
require 'io/console'

require './Cli_Output_Ruby_curses.rb'

$cli_Output = Cli_Output_Ruby_curses.new

$cli_Output.Output_Init()

$cli_Output.Output_Char('X')
$cli_Output.Output_NewLine()
$cli_Output.Output_Str(" - Ok")
$cli_Output.Output_NewLine()
$cli_Output.Output_Str("End")
$cli_Output.Output_Return()

STDIN.getch()

$res_clear = $cli_Output.Output_Clear()
$cli_Output.Output_NewLine()
if $res_clear
	$cli_Output.Output_Str("Cleared")
else
	$cli_Output.Output_Str("Not Cleared")
end

STDIN.getch()

$cli_Output.Output_NewLine()

$cli_Output.Output_Close()
