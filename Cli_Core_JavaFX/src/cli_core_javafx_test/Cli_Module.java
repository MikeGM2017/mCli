/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 *
 * @author mike
 */
public class Cli_Module {

    protected String Name;

    public List<Cli_Cmd> Module_Cmd_List;

    public int Cmd_ID_Count_Get() {
        return 0;
    }

    public Cli_Module(String name) {
        Name = name;
        Module_Cmd_List = new ArrayList<>();
    }

    public String Name_Get() {
        return Name;
    }

    public void Cmd_Add(Cli_Cmd cmd) {
        Module_Cmd_List.add(cmd);
    }

    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        return false;
    }

    public int Cmd_Count_Get() {
        return Module_Cmd_List.size();
    }

    public Cli_Cmd Cmd_Get(int cmd_index) {
        if (cmd_index >= 0 && cmd_index < Module_Cmd_List.size()) {
            return Module_Cmd_List.get(cmd_index);
        }
        return null;
    }

    public void To_Map(Map<String, String> values_map) {
        // Nothing
    }

}
