/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mike
 */
public class Cli_Modules {

    protected List<Cli_Module> Modules;

    public Cli_Modules() {
        Modules = new ArrayList<>();
    }

    public int Get_Size() {
        return Modules.size();
    }

    public Cli_Module Get(int index) {
        if (index >= 0 && index < Modules.size()) {
            return Modules.get(index);
        }
        return null;
    }

    public void Module_Add(Cli_Module cli_module) {
        Modules.add(cli_module);
    }

}
