namespace Cli_Core_CS
{
    class Str_Get_Without_Commas
    {
        public string Get(string value_str)
        {
            string s = value_str;
            if (value_str.Length >= 2)
            {
                if (
                        (value_str[0] == '\"' && value_str[value_str.Length - 1] == '\"')
                        || (value_str[0] == '\'' && value_str[value_str.Length - 1] == '\'')
                        )
                {
                    s = value_str.Substring(1, value_str.Length - 2);
                }
            }
            return s;
        }
    }
}
