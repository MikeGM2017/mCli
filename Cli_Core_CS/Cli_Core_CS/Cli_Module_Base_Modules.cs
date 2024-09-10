using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Base_Modules : Cli_Module
    {
        protected Ref_Cli_Cmd_Privilege_ID User_Privilege;

        protected Cli_Modules Modules;

        protected Str_Filter Str_Filter;

        protected Cli_Output_CS Cli_Output;

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_modules,
            CMD_ID_modules_by_filter,
            CMD_ID_modules_by_filter_print,
            CMD_ID_modules_by_filter_print_verbose,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        public Cli_Module_Base_Modules(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
                Str_Filter str_filter, Cli_Output_CS cli_output) : base("Base Modules")
        {
            User_Privilege = user_privilege;
            Modules = modules;
            Str_Filter = str_filter;
            Cli_Output = cli_output;
            Version = "0.02";
            {
                // modules
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_modules);
                cmd.Text_Set("modules");
                cmd.Help_Set("modules print (all)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("modules", "modules print (all)"));
                Cmd_Add(cmd);
            }
            {
                // modules <module_name>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_modules_by_filter);
                cmd.Text_Set("modules <module_name>");
                cmd.Help_Set("modules print (by filter)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("modules", "modules"));
                cmd.Item_Add(new Cmd_Item_Str("<module_name>", "modules print (by filter)"));
                Cmd_Add(cmd);
            }
            {
                // modules <module_name> print
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_modules_by_filter_print);
                cmd.Text_Set("modules <module_name> print");
                cmd.Help_Set("modules print (by filter)");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("modules", "modules"));
                cmd.Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
                cmd.Item_Add(new Cmd_Item_Word("print", "modules print (by filter)"));
                Cmd_Add(cmd);
            }
            {
                // modules <module_name> print verbose
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_modules_by_filter_print_verbose);
                cmd.Text_Set("modules <module_name> print verbose");
                cmd.Help_Set("modules print (by filter) verbose");
                cmd.Is_Global_Set(true);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("modules", "modules"));
                cmd.Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
                cmd.Item_Add(new Cmd_Item_Word("print", "modules print (by filter)"));
                cmd.Item_Add(new Cmd_Item_Word("verbose", "modules print (by filter) verbose"));
                Cmd_Add(cmd);
            }
        }

        void cmd_items_print()
        {
            List<Cmd_Item_Base> items = new List<Cmd_Item_Base>();
            List<string> words = new List<String>();
            items.Add(new Cmd_Item_Date("", ""));
            items.Add(new Cmd_Item_DateTime("", ""));
            items.Add(new Cmd_Item_Time("", ""));
            items.Add(new Cmd_Item_EQU("", ""));
            items.Add(new Cmd_Item_EQU_Range("", "", words));
            items.Add(new Cmd_Item_IP4("", ""));
            items.Add(new Cmd_Item_IP6("", ""));
            items.Add(new Cmd_Item_Int_List(1, 8, "", ""));
            items.Add(new Cmd_Item_Int_Range(1, 8, "", ""));
            items.Add(new Cmd_Item_MAC("", ""));
            items.Add(new Cmd_Item_Point_Var_Name("", ""));
            items.Add(new Cmd_Item_Rem("", ""));
            items.Add(new Cmd_Item_Str("", ""));
            //items.Add(new Cmd_Item_Str_Esc("", ""));
            items.Add(new Cmd_Item_Word("", ""));
            items.Add(new Cmd_Item_Word_List("", "", words));
            items.Add(new Cmd_Item_Word_Range("", "", words));

            StringBuilder sb = new StringBuilder();
            sb.Append("Cmd Items[").Append(items.Count).Append("]:");
            Cli_Output.Output_Str(sb.ToString());
            Cli_Output.Output_NewLine();
            Cli_Output.Output_NewLine();
            for (int i = 0; i < items.Count; i++)
            {
                Cmd_Item_Base item = items[i];
                string type = item.Type_Get();
                string version = item.Version_Get();
                Cli_Output.Output_Str(type);
                Cli_Output.Output_Str(" V");
                Cli_Output.Output_Str(version);
                Cli_Output.Output_NewLine();
            }
        }

        bool modules_by_filter_print(string module_filter, Str_Filter str_filter, bool is_verbose)
        {
            Cli_Output.Output_NewLine();
            bool found = false;
            if (is_verbose)
            {
                StringBuilder sb = new StringBuilder();
                sb.Append("Modules[").Append(Modules.Get_Size()).Append("]:");
                Cli_Output.Output_Str(sb.ToString());
                Cli_Output.Output_NewLine();
                Cli_Output.Output_NewLine();
            }
            for (int module = 0; module < Modules.Get_Size(); module++)
            {
                Cli_Module module_ptr = Modules.Get(module);
                if (module_ptr != null)
                {
                    string module_name = module_ptr.Name_Get();
                    string module_name_with_commas = "\"" + module_ptr.Name_Get() + "\"";
                    if (str_filter.Is_Match(module_filter, module_name)
                            || str_filter.Is_Match(module_filter, module_name_with_commas))
                    {
                        if (!is_verbose)
                        {
                            Cli_Output.Output_Str(module_name);
                        }
                        else
                        {
                            Cli_Output.Output_Str(module_name + " V" + module_ptr.Version_Get());
                        }
                        Cli_Output.Output_NewLine();
                        found = true;
                    }
                }
            }
            if (!found)
            {
                Cli_Output.Output_Str(module_filter);
                Cli_Output.Output_Str(" - Not Found");
                Cli_Output.Output_NewLine();
            }
            return true;
        }

        public override bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            Level_Description level = new Level_Description();
            string parameter;
            if (Levels.Count > 0)
            {
                level = Levels[Levels.Count - 1];
                parameter = level.Parameter;
            }
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_modules:
                    if (is_debug) return true;
                    {
                        string module_filter = "*";
                        bool is_verbose;
                        return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
                    }
                case Local_Cmd_ID.CMD_ID_modules_by_filter:
                    if (is_debug) return true;
                    {
                        string module_filter = cmd.Items[1].Value_Str;
                        bool is_verbose;
                        return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
                    }
                case Local_Cmd_ID.CMD_ID_modules_by_filter_print:
                    if (is_debug) return true;
                    {
                        string module_filter = cmd.Items[1].Value_Str;
                        bool is_verbose;
                        return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
                    }
                case Local_Cmd_ID.CMD_ID_modules_by_filter_print_verbose:
                    if (is_debug) return true;
                    {
                        string module_filter = cmd.Items[1].Value_Str;
                        bool is_verbose;
                        Cli_Output.Output_NewLine();
                        cmd_items_print();
                        return modules_by_filter_print(module_filter, Str_Filter, is_verbose = true);
                    }
            }
            return false; // Not Implemented
        }

        public override void To_Map(Dictionary<string, string> values_map)
        {
            // Nothing
        }
    }
}
