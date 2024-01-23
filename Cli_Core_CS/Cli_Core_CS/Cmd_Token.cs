namespace Cli_Core_CS
{
    class Cmd_Token
    {
        protected string Text;

        public Cmd_Token(string text)
        {
            Text = text;
        }

        public string Text_Get()
        {
            return Text;
        }

        public string Text_Get_Without_COMMAS()
        {
            if (Text.Length >= 2 && Text[0] == '\"' && Text[Text.Length - 1] == '\"')
            {
                return Text.Substring(1, Text.Length - 2);
            }
            if (Text.Length >= 2 && Text[0] == '\'' && Text[Text.Length - 1] == '\'')
            {
                return Text.Substring(1, Text.Length - 2);
            }
            return Text;
        }

        public string To_String()
        {
            return "Text:" + Text;
        }

    }
}
