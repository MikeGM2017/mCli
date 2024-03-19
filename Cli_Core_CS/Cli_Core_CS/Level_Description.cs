using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Level_Description
    {
        public String Level = "";
        public string Parameter = "";

        public Level_Description() { }

        public Level_Description(String level)
        {
            Level = level;
        }

        public Level_Description(String level, String parameter)
        {
            Level = level;
            Parameter = parameter;
        }
    }
}
