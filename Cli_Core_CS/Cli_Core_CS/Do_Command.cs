namespace Cli_Core_CS
{
    class Do_Command : Do_Abstract
    {
        protected Cli_Module_Base_Script Module_Script;

        public Do_Command(Cli_Module_Base_Script module_script)
        {
            Module_Script = module_script;
        }

        public override void Do()
        {
            bool is_debug;
            Ref_Boolean debug_res = new Ref_Boolean(false);
            Module_Script.Execute_Script_Command(is_debug = false, debug_res);
        }
    }
}
