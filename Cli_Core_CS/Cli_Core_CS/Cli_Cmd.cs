using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cli_Cmd
    {

        protected int ID;
        protected int Privilege;
        protected string Text;
        protected string Level;
        protected string Help;
        protected bool Is_Global;
        protected bool Is_Set;
        protected int Min;
        protected int Max;

        public List<Cmd_Item_Base> Items = new List<Cmd_Item_Base>();

        public Cli_Cmd(int id)
        {
            ID = id;
            Privilege = (int)Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_ROOT_DEF;
            Is_Set = false;
            Is_Global = false;
        }

        public Cli_Cmd(int id, Cli_Cmd_Privilege_ID privilege)
        {
            ID = id;
            Privilege = (int)privilege;
            Is_Set = false;
            Is_Global = false;
        }

        public int ID_Get()
        {
            return ID;
        }

        public void Privilege_Set(int v)
        {
            Privilege = v;
        }

        public int Privilege_Get()
        {
            return (int)Privilege;
        }

        public string Help_Get()
        {
            return Help;
        }

        public void Help_Set(string Help)
        {
            this.Help = Help;
        }

        public bool Is_Set_Get()
        {
            return Is_Set;
        }

        public void Is_Set_Set(bool Is_Set)
        {
            this.Is_Set = Is_Set;
        }

        public string Text_Get()
        {
            return Text;
        }

        public void Text_Set(string text)
        {
            Text = text;
        }

        public void Item_Add(Cmd_Item_Base item)
        {
            Items.Add(item);
        }

        public int Max_Get()
        {
            return Max;
        }

        public void Max_Set(int max)
        {
            Max = max;
        }

        public int Min_Get()
        {
            return Min;
        }

        public void Min_Set(int min)
        {
            Min = min;
        }

        public bool Is_Global_Get()
        {
            return Is_Global;
        }

        public void Is_Global_Set(bool is_global)
        {
            Is_Global = is_global;
        }

        public string Level_Get()
        {
            return Level;
        }

        public void Level_Set(string Level)
        {
            this.Level = Level;
        }

        public virtual Cmd_Item_Valid_Result Is_Valid(List<Cmd_Token> tokens)
        {
            if (tokens.Count > Items.Count) return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;

            if (tokens.Count <= Items.Count)
            {
                for (int i = 0; i < tokens.Count; i++)
                {
                    Cmd_Item_Valid_Result res_valid = Items[i].Parse(tokens[i].Text_Get());
                    if (i == Items.Count - 1)
                    {
                        // Последний токен может быть введен не до конца или с ошибкой
                        return res_valid;
                    }
                    else if (res_valid == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE && (i < Items.Count - 1))
                    {
                        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                    }
                    else if (res_valid != Cmd_Item_Valid_Result.CMD_ITEM_OK
                          && res_valid != Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE
                          && res_valid != Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS)
                    {
                        return res_valid;
                    }
                }
            }
            if (tokens.Count == Items.Count) return Cmd_Item_Valid_Result.CMD_ITEM_OK;

            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;
        }
    }
}
