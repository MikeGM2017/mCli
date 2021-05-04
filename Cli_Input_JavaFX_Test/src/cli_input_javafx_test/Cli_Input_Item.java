/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_input_javafx_test;

/**
 *
 * @author mike
 */
public class Cli_Input_Item {

    protected Input_Cmd_Type Type;
    protected String Text;
    
    Cli_Input_Item(Input_Cmd_Type type, String text) {
        Type = type;
        Text = text;
    }
    
    public Input_Cmd_Type Type_Get() {
        return Type;
    }
    
    public String Text_Get() {
        return Text;
    }

}
