using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cli_Modules
    {
        List<Cli_Module> Modules = new List<Cli_Module>();

        public Cli_Modules()
        {
        }

        public virtual int Get_Size()
        {
            return Modules.Count;
        }

        public virtual Cli_Module Get(int index)
        {
            if (index >= 0 && index < Modules.Count)
                return Modules[index];
            return null;
        }

        public virtual void Add(Cli_Module cli_module)
        {
            Modules.Add(cli_module);
        }
    }
}
