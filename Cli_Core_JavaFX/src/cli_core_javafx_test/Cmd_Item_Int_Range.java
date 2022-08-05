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
public class Cmd_Item_Int_Range extends Cmd_Item_Int {

    protected int Min;
    protected int Max;

    public Cmd_Item_Int_Range(int min, int max, String text, String help) {
        super(text, help);
        Min = min;
        Max = max;
        Type = "Int_Range";
    }

    @Override
    public String Debug_Value_Get() {
        return Integer.toString(Min);
    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;
        Value_Int = 0;

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        Cmd_Item_Valid_Result res = super.Parse(s);
        if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK) {
            int v = Integer.valueOf(s);
            if (v >= Min && v <= Max) {
                Value_Int = v;
                return Cmd_Item_Valid_Result.CMD_ITEM_OK;
            }
            return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
        }
        return res;
    }

    @Override
    public String To_String() {
        return "Int_Range: " + Integer.toString(Min) + "..." + Integer.toString(Max) + ": " + super.To_String();
    }

}
