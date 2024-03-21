using System;
using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cli_TAB_Result
    {
        public Cli_Cmd cmd_ptr = null;
        public String s_log = "";
        public List<String> s_add_list = new List<String>();
        public List<String> s_full_list = new List<String>();
        public bool Is_Enter = false;
        public bool is_space_after_add = false;

        public Cli_TAB_Result()
        {
        }
    }
}
