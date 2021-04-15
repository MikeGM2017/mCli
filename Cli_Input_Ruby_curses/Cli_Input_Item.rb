
class Cli_Input_Item

	INPUT_CMD_ENTER = 1
	INPUT_CMD_TAB = 2
	INPUT_CMD_UP = 3
	INPUT_CMD_DOWN = 4

	def initialize(type, text)
		@type = type
		@text = text
	end

	def Type_Get()
		return @type
	end

	def Text_Get()
		return @text
	end

end

