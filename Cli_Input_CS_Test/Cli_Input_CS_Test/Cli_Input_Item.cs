using System;

namespace Cli_Input_CS_Test
{
    class Cli_Input_Item
    {
        protected Input_Cmd_Type Type;
        protected String Text;

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
