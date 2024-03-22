using System.Collections.Generic;

namespace Cli_Core_CS
{
    abstract class Cli_Module
    {
        protected string Name;
        protected string Version;

        protected List<Cli_Cmd> Module_Cmd_List = new List<Cli_Cmd>();

        public Cli_Module(string name)
        {
            Name = name;
            Version = "0.01"; //@Warning: Dummy value - Version is not set
        }

        public string Name_Get()
        {
            return Name;
        }

        public void Cmd_Add(Cli_Cmd cmd)
        {
            Module_Cmd_List.Add(cmd);
        }

        public virtual bool end(List<Level_Description> Levels)
        {
            if (Levels.Count > 0) Levels.RemoveAt(Levels.Count - 1);
            return true;
        }

        abstract public bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug);

        // @Example: virtual bool Execute(...) {...}
        //virtual bool Execute(CliCmd_ID cmd_id, CliCmd *cmd, vector<LevelDescription> &Levels, bool is_debug) {
        //    return false; // Not Implemented
        //}

        abstract public int Cmd_ID_Count_Get();

        public int Cmd_Count_Get()
        {
            return Module_Cmd_List.Count;
        }

        public Cli_Cmd Cmd_Get(int cmd_index)
        {
            if (cmd_index >= 0 && cmd_index < Module_Cmd_List.Count)
            {
                return Module_Cmd_List[cmd_index];
            }
            return null;
        }

        public string Version_Get()
        {
            return Version;
        }

        abstract public void To_Map(Dictionary<string, string> values_map);
    }
}
