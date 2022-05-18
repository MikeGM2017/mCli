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
public class Cli_History {

    protected List<String> History = new ArrayList<>();
    protected int History_Pos = 0;

    public Cli_History() {
    }

    public void Clear() {
        History.clear();
        History_Pos = 0;
    }

    public int History_Size_Get() {
        return History.size();
    }

    public String History_Item_Get(int index) {
        if (index >= 0 && index < History.size()) {
            return History.get(index);
        }
        return "";
    }

    public void History_Put(String s_trim) {
        if (History.size() == 0 || s_trim != History.get(History.size() - 1)) {
            History.add(s_trim);
        }
        History_Pos = History.size();
    }

    public String History_Up() {
        if (History.size() == 0) {
            return "";
        } else {
            if (History_Pos > 0) {
                History_Pos--;
            }
            return History.get(History_Pos);
        }
    }

    public String History_Down() {
        if (History.size() == 0) {
            return "";
        } else if (History_Pos < History.size() - 1) {
            History_Pos++;
            return History.get(History_Pos);
        } else {
            History_Pos = History.size();
            return "";
        }
    }
}
