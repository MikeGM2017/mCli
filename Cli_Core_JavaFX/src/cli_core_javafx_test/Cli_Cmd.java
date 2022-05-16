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
public class Cli_Cmd {

    protected int ID = 0;
    protected int Privilege = Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_ROOT_DEF.ordinal();
    protected String Text = "";
    protected String Level = "";
    protected String Help = "";
    protected boolean Is_Global = false;
    protected boolean Is_Set = false;
    protected int Min = 0;
    protected int Max = 0;

    public List<Cmd_Item_Base> Items = new ArrayList<>();

    public Cli_Cmd(int id) {
        ID = id;
    }

    public Cli_Cmd(int id, Cli_Cmd_Privilege_ID privilege) {
        ID = id;
        Privilege = privilege.ordinal();
    }

    public int ID_Get() {
        return ID;
    }

    public void Privilege_Set(int v) {
        Privilege = v;
    }

    public int Privilege_Get() {
        return Privilege;
    }

    public String Help_Get() {
        return Help;
    }

    public void Help_Set(String help) {
        Help = help;
    }

    public boolean Is_Set_Get() {
        return Is_Set;
    }

    public void Is_Set_Set(boolean is_set) {
        Is_Set = is_set;
    }

    public String Text_Get() {
        return Text;
    }

    public void Text_Set(String text) {
        Text = text;
    }

    public void Item_Add(Cmd_Item_Base item) {
        Items.add(item);
    }

    public int Max_Get() {
        return Max;
    }

    public void Max_Set(int max) {
        Max = max;
    }

    public int Min_Get() {
        return Min;
    }

    public void Min_Set(int min) {
        Min = min;
    }

    public boolean Is_Global_Get() {
        return Is_Global;
    }

    public void Is_Global_Set(boolean is_global) {
        Is_Global = is_global;
    }

    public String Level_Get() {
        return Level;
    }

    public void Level_Set(String level) {
        Level = level;
    }

    public Cmd_Item_Valid_Result Is_Valid(List<Cmd_Token> tokens) {
        if (tokens.size() > Items.size()) {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        if (tokens.size() <= Items.size()) {
            for (int i = 0; i < tokens.size(); i++) {
                Cmd_Item_Valid_Result res_valid = Items.get(i).Parse(tokens.get(i).Text_Get());
                if (i == Items.size() - 1) {
                    // Последний токен может быть введен не до конца или с ошибкой
                    return res_valid;
                } else if (res_valid == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE && (i < Items.size() - 1)) {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                } else if (res_valid != Cmd_Item_Valid_Result.CMD_ITEM_OK
                        && res_valid != Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE
                        && res_valid != Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
                    return res_valid;
                }
            }
        }
        if (tokens.size() == Items.size()) {
            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE;
    }
}
