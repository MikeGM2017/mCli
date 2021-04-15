
class Cli_Output_Ruby_print

	def Output_Init()
		return false
	end

	def Output_Close()
		return false
	end

	def Output_Clear()
		return false
	end

	def Output_Char(c)
		print c
		STDOUT.flush
	end

	def Output_NewLine()
		print "\n\r"
		STDOUT.flush
	end

	def Output_Str(s)
		print s
		STDOUT.flush
	end

	def Output_Return()
		print "\r"
		STDOUT.flush
	end

end

