using System;

namespace Cli_Core_CS
{
    class TAB_Cmd
    {
        public TAB_Cmd_ID ID;
        public String Text;

        public TAB_Cmd(TAB_Cmd_ID id, String text)
        {
            ID = id;
            Text = text;
        }
    }
}
