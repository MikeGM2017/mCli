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
public class Cmd_Item_Int_List extends Cmd_Item_Int_Range {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        if (c >= '0' && c <= '9') {
            return true;
        }
        if (pos > 0) {
            if (c == ',') {
                return true;
            }
            if (c == '-') {
                return true;
            }
        }
        return false;
    }

    public List<Cmd_Item_Int_List_Item> Values_Int_List_Items = new ArrayList<>();

    public Cmd_Item_Int_List(int min, int max, String text, String help) {
        super(min, max, text, help);
        Type = "Int_List";
    }

    @Override
    public String Debug_Value_Get() {
        String s = Integer.toString(Min) + "-" + Integer.toString(Max);
        return s;
    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;
        Values_Int_List_Items.clear();

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        for (int pos = 0; pos < s.length(); pos++) {
            if (!Is_Char_Valid(s.charAt(pos), pos, s.length())) {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
        }

        int n = 0;
        int n_beg = 0;
        boolean n_beg_Valid = false;
        boolean prev_is_digit = false;
        boolean prev_is_minus = false;
        for (int pos = 0; pos < s.length(); pos++) {
            char c = s.charAt(pos);
            if (c >= '0' && c <= '9') {
                n = n * 10 + Char_To_N(c);
                prev_is_digit = true;
                prev_is_minus = false;
                //n_beg_Valid = false;
            } else if (c == '-') {
                if (prev_is_digit) {
                    if (n < Min || n > Max) {
                        return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                    }
                    n_beg = n;
                    n = 0;
                    prev_is_digit = false;
                    prev_is_minus = true;
                    n_beg_Valid = true;
                } else {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
            } else if (c == ',') {
                if (prev_is_minus) {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
                if (!prev_is_digit) {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
                // Повтор для последнего значения - Beg
                if (n_beg_Valid && prev_is_digit) {
                    if (n < Min || n > Max) {
                        return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                    }
                    //if (n_beg <= n) { @Attention
                    if (n_beg < n) {
                        Values_Int_List_Items.add(new Cmd_Item_Int_List_Item(n_beg, n));
                        n = 0;
                        prev_is_digit = false;
                        prev_is_minus = false;
                        n_beg_Valid = false;
                    } else {
                        return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_ORDER;
                    }
                } else if (prev_is_digit) {
                    if (n < Min || n > Max) {
                        return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                    }
                    Values_Int_List_Items.add(new Cmd_Item_Int_List_Item(n, n));
                    n = 0;
                    prev_is_digit = false;
                    prev_is_minus = false;
                    n_beg_Valid = false;
                }
                // Повтор для последнего значения - End

            }
        }
        // Последнее значение
        if (prev_is_minus) {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }
        if (!prev_is_digit) {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }
        // Повтор для последнего значения - Beg
        if (n_beg_Valid && prev_is_digit) {
            if (n < Min || n > Max) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            //if (n_beg <= n) { @Attention
            if (n_beg < n) {
                Values_Int_List_Items.add(new Cmd_Item_Int_List_Item(n_beg, n));
                n = 0;
                prev_is_digit = false;
                prev_is_minus = false;
                n_beg_Valid = false;
            } else {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_ORDER;
            }
        } else if (prev_is_digit) {
            if (n < Min || n > Max) {
                return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
            }
            Values_Int_List_Items.add(new Cmd_Item_Int_List_Item(n, n));
            n = 0;
            prev_is_digit = false;
            prev_is_minus = false;
            n_beg_Valid = false;
        }
        // Повтор для последнего значения - End

        if (s.charAt(s.length() - 1) == ',') {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }
        if (s.charAt(s.length() - 1) == '-') {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE;

        //return Cmd_Item_Valid_Result.CMD_ITEM_OK; // Список значений, попадающие в Min...Max
    }

    @Override
    public String To_String() {
        StringBuilder sb = new StringBuilder();
        sb.append("Int_List: ");
        sb.append(Integer.toString(Min));
        sb.append("...");
        sb.append(Integer.toString(Max));
        sb.append(": ");
        //sb.append(Cmd_Item_Base::To_String());
        //sb.append(" ");
        for (int i = 0; i < Values_Int_List_Items.size(); i++) {
            Cmd_Item_Int_List_Item item = Values_Int_List_Items.get(i);
            if (i > 0) {
                sb.append(",");
            }
            if (item.Min == item.Max) {
                sb.append(Integer.toString(item.Min));
            } else {
                sb.append(Integer.toString(item.Min) + "-" + Integer.toString(item.Max));
            }
        }
        return sb.toString();
    }

}
