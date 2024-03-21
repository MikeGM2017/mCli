using System;

namespace Cli_Core_CS
{
    class Cli_Input_Item
    {
        Input_Cmd_Type Type;
        String Text;

        public Cli_Input_Item(Input_Cmd_Type type, String text)
        {
            Type = type;
            Text = text;
        }

        public Input_Cmd_Type Type_Get()
        {
            return Type;
        }

        public String Text_Get()
        {
            return Text;
        }
    }
}
