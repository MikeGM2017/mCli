using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Cli_Core_CS;
using System.Collections.Generic;
using System.Text;

namespace Test_Cli_Core_CS
{
    [TestClass]
    public class Test_Cmd_Item_Str
    {
        class Test_Cmd_Item_Str_Item
        {
            public string Text;
            public Cmd_Item_Valid_Result Result;
            public Test_Cmd_Item_Str_Item(string text, Cli_Core_CS.Cmd_Item_Valid_Result result)
            {
                Text = text;
                Result = result;
            }
        }
        [TestMethod]
        public void TestMethod1()
        {
            //List<Test_Cmd_Item_Str_Item> Test_Vector = new List<Test_Cmd_Item_Str_Item>();
            //Test_Vector.Add(new Test_Cmd_Item_Str_Item("", Cmd_Item_Valid_Result.CMD_ITEM_EMPTY));
            //Test_Vector.Add(new Test_Cmd_Item_Str_Item("help", Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS));
            //Test_Vector.Add(new Test_Cmd_Item_Str_Item("h", Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS));
            //Test_Vector.Add(new Test_Cmd_Item_Str_Item("\"h", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR));
            //Test_Vector.Add(new Test_Cmd_Item_Str_Item("\"\"", Cmd_Item_Valid_Result.CMD_ITEM_OK));
            //Test_Vector.Add(new Test_Cmd_Item_Str_Item("\"h\"", Cmd_Item_Valid_Result.CMD_ITEM_OK));
            //Test_Vector.Add(new Test_Cmd_Item_Str_Item("\"\"h", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR));

            List<Test_Cmd_Item_Str_Item> Test_Vector = new List<Test_Cmd_Item_Str_Item> {
                new Test_Cmd_Item_Str_Item("", Cmd_Item_Valid_Result.CMD_ITEM_EMPTY),
                new Test_Cmd_Item_Str_Item("help", Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS),
                new Test_Cmd_Item_Str_Item("h", Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS),
                new Test_Cmd_Item_Str_Item("\"h", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
                new Test_Cmd_Item_Str_Item("\"\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
                new Test_Cmd_Item_Str_Item("\"h\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
                new Test_Cmd_Item_Str_Item("\"\"h", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
            };
            System.Console.WriteLine("Test_Cmd_Item_Str: TestMetod1");

            Cmd_Item_Str v = new Cmd_Item_Str("help", "help: help");
            int index = 0;
            foreach (Test_Cmd_Item_Str_Item test_item in Test_Vector)
            {
                Cmd_Item_Valid_Result result = v.Parse(test_item.Text);
                StringBuilder sb = new StringBuilder();
                sb.Append("[" + index.ToString() + "]");
                sb.Append(" Text: \"" + test_item.Text + "\"");
                sb.Append(" " + test_item.Result.ToString() + " ->");
                sb.Append(" " + result.ToString() + " - ");
                if (test_item.Result == result)
                {
                    sb.Append("Ok");
                }
                else
                {
                    sb.Append("Failed");
                }
                System.Console.WriteLine(sb.ToString());
                Assert.AreEqual(test_item.Result, result);
                index++;
            }
        }
    }
}
