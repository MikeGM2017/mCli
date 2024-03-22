using System.Collections.Generic;

namespace Cli_Core_CS
{
    public class Cmd_Item_Base
    {
        protected string Type;
        protected string Text;
        protected string Help;
        protected string Version;

        protected virtual bool Is_Char_Valid(char c, int pos, int len)
        {
            return true; // Допустимы любые символы в любой позиции
        }

        public string Value_Str;

        public Cmd_Item_Base(string text, string help)
        {
            Type = "Base";
            Text = text;
            Help = help;
            Version = "0.01"; //@Warning: Dummy value - Version is not set
        }

        public virtual string Debug_Value_Get()
        {
            return Text;
        }

        public string Type_Get()
        {
            return Type;
        }

        public string Text_Get()
        {
            return Text;
        }

        public string Help_Get()
        {
            return Help;
        }

        public string Version_Get()
        {
            return Version;
        }

        public virtual bool Is_Str_Valid(string s)
        {
            for (int pos = 0; pos < s.Length; pos++)
            {
                if (!Is_Char_Valid(s[pos], pos, s.Length)) return false;
            }
            return true;
        }

        public virtual Cmd_Item_Valid_Result Parse(string s)
        {
            Value_Str = s;

            if (s.Length == 0) return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;

            if (Text == s) return Cmd_Item_Valid_Result.CMD_ITEM_OK;

            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        public virtual string To_String()
        {
            string s = Type + ": Text:\"" + Text_Get() + "\" "
                    + ": Value_Str:\"" + Value_Str + "\" ";
            return s;
        }

        public virtual List<string> Incomplete_Tail_List_Get(string s)
        {
            List<string> tail_list = new List<string>();
            return tail_list;
        }

        public virtual bool Is_Space_After_Add(string s)
        {
            return true;
        }
    }
}
