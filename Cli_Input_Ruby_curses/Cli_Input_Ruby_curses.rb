
require 'curses'
include Curses

require './Cli_Input_Item.rb'

class Cli_Input_Ruby_curses

	def initialize(cli_output)

		@title = ""
		@user = ""
		@level = ""
		@invitation = ">"
		@divider_L = "["
		@divider_R = "]"
		@input_Str = ""

		@prompt_Str = ""

		@is_Echo = true

		@cli_Output = cli_output

		@input_Str_Pos = 0

		$is_Quit = false

	end

	def Title_Set(s)
		@title = s
	end

	def Title_Get()
		return @title
	end

	def User_Set(s)
		@user = s
	end

	def User_Get()
		return @user
	end

	def Level_Set(s)
		@Level = s
	end

	def Level_Get()
		return @Level
	end

	def Invitation_Set(s)
		@invitation = s
	end

	def Invitation_Get()
		return @invitation
	end

	def Divider_L_Set(s)
		@divider_L = s
	end

	def Divider_L_Get()
		return @divider_L
	end

	def Divider_R_Set(s)
		@divider_R = s
	end

	def Divider_R_Get()
		return @divider_R
	end

	def Prompt_Str_Set(s)
		@prompt_Str = s
	end

	def Prompt_Str_Get()
		return @prompt_Str
	end

	def Is_Echo_Set(v)
		@is_Echo = v
	end

	def Is_Echo_Get()
		return @is_Echo
	end

	def Input_Init()
		if(!@cli_Output.Output_Init())
			Curses.noecho # do not show typed keys
			Curses.init_screen()
			Curses.stdscr.keypad(true) # enable arrow keys (required for pageup/down)
			Curses.setpos(0,0)
		end
		return true
	end

	def Input_Restore()
		if(!@cli_Output.Output_Close())
			Curses.close_screen()
                end
		return true
	end

	def Input_Clear()
		if(!@cli_Output.Output_Clear())
			Curses.clear()
		end
		return true
	end

	def Invitation_Full_Get() # Attention: Should be used for print cli invitation

		if(@prompt_Str != nil)
			if(@prompt_Str != "")
				return @prompt_Str
			end
		end

		s = "";
		if (!@title.empty?)
			s += @divider_L + @title + @divider_R;
		end
		if (!@user.empty?)
			s += @divider_L + @user + @divider_R;
		end
		if (!@level.empty?)
			s += @divider_L + @level + @divider_R;
		end
		if (!@invitation.empty?)
			s += @invitation;
		end
		return s;
	end

	def Invitation_Print()
		@cli_Output.Output_Str(Invitation_Full_Get())
	end

	def Input_Str_Get()
		return @input_Str;
	end

	def Input_Str_Set(s)
		@input_Str = s;
	end

	def Input_Str_Set_Empty()
		@input_Str = ""
		@input_Str_Pos = 0;
	end

	def Input_Print()
		if @input_Str_Pos == @input_Str.size

			@cli_Output.Output_Return()
			Invitation_Print()
			@cli_Output.Output_Str(@input_Str)

		else

			@cli_Output.Output_Return()
			Invitation_Print()
			@cli_Output.Output_Str(@input_Str)

			@cli_Output.Output_Return()
			Invitation_Print()
			if @input_Str_Pos > 0
				s = @input_Str[0..@input_Str_Pos-1]
				@cli_Output.Output_Str(s)
			end

		end
	end

	def Input_Print_Clear()
		@cli_Output.Output_Return()
		Invitation_Print()
		s = sprintf("%*.*s", @input_Str.size, 1, " ")
		@cli_Output.Output_Str(s)
	end

	def Input_Add_Char_To_End(c)
		@input_Str = @input_Str + c
		@input_Str_Pos = @input_Str_Pos + 1
	end

	def Input_Add_Char_Middle(c)
		s1 = ""
		if @input_Str_Pos > 0
			s1 = @input_Str[0...@input_Str_Pos]
		end

		s2 = ""
		if @input_Str_Pos < @input_Str.size
			s2 = @input_Str[@input_Str_Pos...@input_Str.size]
		end

		@input_Str = s1 + c + s2
		@input_Str_Pos = @input_Str_Pos + 1
	end

	def Input_Back()

		if @input_Str_Pos == @input_Str.size

			if @input_Str_Pos <= 1
				@input_Str = ""
				@input_Str_Pos = 0
			end
			if @input_Str_Pos > 1
				@input_Str = @input_Str[0..-2]
				@input_Str_Pos = @input_Str.size
			end

		else

			if @input_Str_Pos >= 0 && @input_Str_Pos < @input_Str.size

				s1 = ""
				if @input_Str_Pos > 1
					s1 = @input_Str[0..@input_Str_Pos-2]
				end

				s2 = ""
				if @input_Str_Pos < @input_Str.size
					s2 = @input_Str[@input_Str_Pos...@input_Str.size]
				end

				@input_Str = s1 + s2
				@input_Str_Pos = @input_Str_Pos - 1

			end

		end

	end

	def Input_Delete()

		if @input_Str_Pos < @input_Str.size

			s1 = ""
			if @input_Str_Pos >= 1
				s1 = @input_Str[0..@input_Str_Pos-1]
			end

			s2 = ""
			if @input_Str_Pos+1 < @input_Str.size
				s2 = @input_Str[@input_Str_Pos+1...@input_Str.size]
			end

			@input_Str = s1 + s2

		end

	end

	def On_Key_ENTER()
		s = @input_Str.strip
		input_item = Cli_Input_Item.new(Cli_Input_Item::INPUT_CMD_ENTER, s)
		Input_Str_Set_Empty()
		return input_item
	end

	def On_Key_TAB()
		s = @input_Str.strip
		input_item = Cli_Input_Item.new(Cli_Input_Item::INPUT_CMD_TAB, s)
		return input_item
	end

	def On_Key_UP()
		s = @input_Str.strip
		input_item = Cli_Input_Item.new(Cli_Input_Item::INPUT_CMD_UP, s)
		return input_item
	end

	def On_Key_DOWN()
		s = @input_Str.strip
		input_item = Cli_Input_Item.new(Cli_Input_Item::INPUT_CMD_DOWN, s)
		return input_item
	end

	def On_Key_LEFT()
		if @input_Str_Pos > 0
			@input_Str_Pos = @input_Str_Pos - 1
			Input_Print()
		end
		return nil
	end

	def On_Key_RIGHT()
		if @input_Str_Pos < @input_Str.size
			@input_Str_Pos = @input_Str_Pos + 1
			Input_Print()
		end
		return nil
	end

	def On_Key_HOME()
		if @input_Str_Pos > 0
			@input_Str_Pos = 0
			Input_Print()
		end
		return nil
	end

	def On_Key_END()
		if @input_Str_Pos < @input_Str.size
			@input_Str_Pos = @input_Str.size
			Input_Print()
		end
		return nil
	end

	def On_Key_DELETE()
		Input_Print_Clear()
		Input_Delete()
		Input_Print()
		return nil
	end

	def On_Key_BACK()
		Input_Print_Clear()
		Input_Back()
		Input_Print()
		return nil
	end

	def On_Key_CTRL_C()
		@cli_Output.Output_NewLine()
		Invitation_Print()
		Input_Str_Set_Empty()
		return nil
	end

	def On_Key_CTRL_Z()
		@cli_Output.Output_NewLine()
		Invitation_Print()
		Input_Str_Set_Empty()
		return nil
	end

	def On_Key_CTRL_Backslash()
		@cli_Output.Output_NewLine()
		Invitation_Print()
		Input_Str_Set_Empty()
		return nil
	end

	def Is_Char_Valid(c)
		return true
	end

	def On_Key_Any(c)
		if c != nil
			if c.size == 1
				#print "\n\rDEBUG: %s %3d 0x%02X\n\r" % [ c, c.ord, c.ord ]
				if Is_Char_Valid(c)
					if @input_Str_Pos == @input_Str.size
						# Add To End - Optimized: print only c (no Input_Clear)
						Input_Add_Char_To_End(c)
						if(Is_Echo_Get())
							@cli_Output.Output_Char(c)
						end
					else
						# Add To Begin / Middle
						Input_Add_Char_Middle(c)
						if(Is_Echo_Get())
							Input_Print()
						end
					end
				end
			end
		end
		return nil
	end

	def On_Key_Pressed(c)

		case c
		when Curses::Key::ENTER, 0x0A then return On_Key_ENTER()
		when 0x09 then return On_Key_TAB()
		when Curses::Key::UP then return On_Key_UP()
		when Curses::Key::DOWN then return On_Key_DOWN()
		when Curses::Key::LEFT then return On_Key_LEFT()
		when Curses::Key::RIGHT then return On_Key_RIGHT()
		when Curses::Key::BACKSPACE then return On_Key_BACK()
		when Curses::Key::DC then return On_Key_DELETE()
		when Curses::Key::HOME then return On_Key_HOME()
		when Curses::Key::END then return On_Key_END()
		else
			return On_Key_Any(c)
		end

	end

	def Input_Item_Get()

		@input_Str_Pos = @input_Str.size

		input_item = nil
		is_stop = false
		while !is_stop

			c = Curses.getch
			if c != nil
				#print "\n\rDEBUG: %s %3d 0x%02X\n\r" % [ c, c.ord, c.ord ]
				input_item = On_Key_Pressed(c)
			end

			if input_item != nil
				is_stop = true
			end

		end

		return input_item

	end

	def Input_sleep(n)
		sleep n
	end

	def Input_kbhit()
		Curses.stdscr.nodelay = 1
		c = Curses.getch
		Curses.stdscr.nodelay = 0
		if (c != nil)
			return true;
		end
		return false;
	end

	def Input_Prompt(prompt_str, yes_dictionary)
		prompt_res = false
		Prompt_Str_Set(prompt_str)
		@cli_Output.Output_Str(prompt_str)
		input_item = Input_Item_Get()
		if(input_item !=nil)
			if(input_item.Type_Get() == Cli_Input_Item::INPUT_CMD_ENTER)
				input_str = input_item.Text_Get()
				input_str.downcase!
				if(yes_dictionary[input_str] == true)
					prompt_res = true
				end
			end
		end
		Prompt_Str_Set("")
		return prompt_res
	end

	def Input_Password()
		input_str = ""
		Is_Echo_Set(false)
		input_item = Input_Item_Get()
		Is_Echo_Set(true)
		if(input_item !=nil)
			if(input_item.Type_Get() == Cli_Input_Item::INPUT_CMD_ENTER)
				input_str = input_item.Text_Get()
			end
		end
		return input_str
	end

end

