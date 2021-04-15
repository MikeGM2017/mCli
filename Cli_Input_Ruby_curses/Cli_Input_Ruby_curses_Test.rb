
require 'io/console'

require './Cli_Output_Ruby_curses.rb'
#require './Cli_Output_Ruby_print.rb'
require './Cli_Input_Ruby_curses.rb'

require './Cli_Input_Item.rb'

$cli_Output = Cli_Output_Ruby_curses.new
#$cli_Output = Cli_Output_Ruby_print.new

$cli_Input = Cli_Input_Ruby_curses.new($cli_Output)

$cli_Input.Title_Set("cli demo");
$cli_Input.User_Set("root");
$cli_Input.Level_Set("top level");
$cli_Input.Invitation_Set("> ");
$cli_Input.Divider_L_Set("[");
$cli_Input.Divider_R_Set("]");

$cli_Input.Input_Init();

$quit_Count = 0
$quit_Count_Max = 10

$stop = false

trap "SIGINT" do
	$cli_Input.On_Key_CTRL_C()
	$quit_Count = 0
end

trap "SIGTSTP" do
	$cli_Input.On_Key_CTRL_Z()
	$quit_Count = 0
end

trap "SIGQUIT" do
	$cli_Input.On_Key_CTRL_Backslash()
	$quit_Count = $quit_Count + 1
	if $quit_Count > $quit_Count_Max
		#$cli_Module_Base_Quit.Is_Quit_Set(true)
		if($stop != true)
			$stop = true
			$cli_Output.Output_NewLine()
			$cli_Output.Output_NewLine()
			$cli_Output.Output_Str("Finished - Press Any Key to Quit")
			$cli_Output.Output_NewLine()
			$cli_Output.Output_NewLine()
		else
			$cli_Output.Output_Str("Interrupted")
			exit(0)
		end
	end
end

Curses.addstr($cli_Input.Invitation_Full_Get())
Curses.addstr($cli_Input.Input_Str_Get())

$yes_dictionary = { "y" => true, "yes" => true } # lowercases only!

loop do

	$cli_Output.Output_Str($cli_Input.Invitation_Full_Get());
	$cli_Output.Output_Str($cli_Input.Input_Str_Get());

	$input_item = $cli_Input.Input_Item_Get();
	$input_type = $input_item.Type_Get();
	$input_str = $input_item.Text_Get();
	if($input_type == Cli_Input_Item::INPUT_CMD_ENTER)
		if($input_str == "Q")
			$cli_Output.Output_NewLine();
			$cli_Output.Output_NewLine();
			$cli_Output.Output_Str("Quit - Processed");
			$cli_Output.Output_NewLine();
			$stop = true;
		elsif($input_str == "C")
			$cli_Input.Input_Clear();
			$cli_Output.Output_NewLine();
			$cli_Output.Output_Str("Clear - Processed");
			$cli_Output.Output_NewLine();
			Curses.addstr("Clear - Processed\n\r")
			Curses.addstr($cli_Input.Invitation_Full_Get())
			Curses.addstr($cli_Input.Input_Str_Get())
		elsif($input_str == "A")
			$cli_Output.Output_NewLine();
			$cli_Output.Output_NewLine();
			$prompt_res = $cli_Input.Input_Prompt("Is it right?(y/n)", $yes_dictionary)
			$cli_Output.Output_NewLine();
			$cli_Output.Output_NewLine();
			if($prompt_res == true)
				$cli_Output.Output_Str("Answer: Yes");
			else
				$cli_Output.Output_Str("Answer: No");
			end
			$cli_Output.Output_NewLine();
			$cli_Output.Output_NewLine();
		elsif($input_str == "P")
			$cli_Output.Output_NewLine();
			$cli_Output.Output_NewLine();
			$cli_Output.Output_Str("Password:");
			$input_str_password = $cli_Input.Input_Password()
			$cli_Output.Output_NewLine();
			$cli_Output.Output_NewLine();
			$cli_Output.Output_Str("Password:" + $input_str_password);
			$cli_Output.Output_NewLine();
			$cli_Output.Output_NewLine();
		elsif($input_str == "H")
			$cli_Output.Output_NewLine();
			$cli_Output.Output_Str("Help: Q - quit, C - clear, H - help, A - prompt(y/n), P - password(no echo)");
			$cli_Output.Output_NewLine();
		elsif(!$input_str.empty?)
			$cli_Output.Output_NewLine();
			$cli_Output.Output_Str($input_str);
			$cli_Output.Output_Str(" - Not Processed");
			$cli_Output.Output_NewLine();
		else
			$cli_Output.Output_NewLine();
		end
	elsif($input_type == Cli_Input_Item::INPUT_CMD_TAB)
		$cli_Output.Output_NewLine();
		$cli_Output.Output_Str("TAB: ");
		$cli_Output.Output_Str($input_str);
		$cli_Output.Output_NewLine();
	elsif($input_type == Cli_Input_Item::INPUT_CMD_UP)
		$cli_Output.Output_NewLine();
		$cli_Output.Output_Str("UP: ");
		$cli_Output.Output_Str($input_str);
		$cli_Output.Output_NewLine();
	elsif($input_type == Cli_Input_Item::INPUT_CMD_DOWN)
		$cli_Output.Output_NewLine();
		$cli_Output.Output_Str("DOWN: ");
		$cli_Output.Output_Str($input_str);
		$cli_Output.Output_NewLine();
	elsif($input_type == Cli_Input_Item::INPUT_CMD_QUIT)
		$cli_Output.Output_NewLine();
		$cli_Output.Output_Str("Quit - Processed");
		$cli_Output.Output_NewLine();
		$stop = true;
	end

	if $stop
		break
	end

end

$cli_Output.Output_NewLine();
loop do
	$cli_Output.Output_Str("Press Any Key to stop");
	$cli_Output.Output_NewLine();
	$cli_Input.Input_sleep(1);
	$is_kbhit = $cli_Input.Input_kbhit()
	if $is_kbhit
		break
	end
end

$cli_Output.Output_NewLine();
$cli_Output.Output_Str("Press Enter to exit");
$cli_Output.Output_NewLine();
$cli_Input.Input_sleep(1);
$input_item = $cli_Input.Input_Item_Get();

$cli_Input.Input_Restore()
