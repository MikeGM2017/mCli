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
public class Cli_TAB_Result {

    public Cli_Cmd cmd_ptr = null;
    public String s_log = "";
    public List<String> s_add_list = new ArrayList<>();
    public List<String> s_full_list = new ArrayList<>();
    public boolean Is_Enter = false;
    public boolean is_space_after_add = false;

    Cli_TAB_Result() {
    }

}
