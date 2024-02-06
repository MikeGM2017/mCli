using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_History
    {
        protected List<String> History = new List<String>();
        int History_Pos;

        public Cli_History()
        {
            History_Pos = 0;
        }

        public virtual void Clear()
        {
            History.Clear();
            History_Pos = 0;
        }

        public virtual int History_Size_Get()
        {
            return History.Count;
        }

        public virtual string History_Item_Get(int index)
        {
            if (index >= 0 && index < History.Count)
                return History[index];
            return "";
        }

        public virtual void History_Put(string s_trim)
        {
            if (History.Count == 0 || s_trim != History[History.Count - 1])
                History.Add(s_trim);
            History_Pos = History.Count;
        }

        public virtual string History_Up()
        {
            if (History.Count == 0)
            {
                return "";
            }
            else
            {
                if (History_Pos > 0)
                {
                    History_Pos--;
                }
                return History[History_Pos];
            }
        }

        public virtual string History_Down()
        {
            if (History.Count == 0)
            {
                return "";
            }
            else
            {
                if (History_Pos < History.Count - 1)
                {
                    History_Pos++;
                    return History[History_Pos];
                }
                else
                {
                    History_Pos = History.Count;
                    return "";
                }
            }
        }
    }
}
