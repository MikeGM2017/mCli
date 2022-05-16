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
public class Level_Description {

    public String Level;
    public String Parameter;

    public Level_Description() {
        Level = "";
        Parameter = "";
    }

    public Level_Description(String level) {
        Level = level;
        Parameter = "";
    }

    public Level_Description(String level, String parameter) {
        Level = level;
        Parameter = parameter;
    }

}
