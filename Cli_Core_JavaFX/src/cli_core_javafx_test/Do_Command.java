/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

/**
 *
 * @author mike
 */
public class Do_Command extends Do_Abstract {

    protected Cli_Module_Base_Script Module_Script;

    public Do_Command(Cli_Module_Base_Script module_script) {
        Module_Script = module_script;
    }

    @Override
    public void Do() {
        boolean is_debug;
        Ref_Boolean debug_res = new Ref_Boolean(false);
        Module_Script.Execute_Script_Command(is_debug = false, debug_res);
    }
}
