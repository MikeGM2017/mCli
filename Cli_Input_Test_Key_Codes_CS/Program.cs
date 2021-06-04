using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Cli_Input_Test_Key_Codes_CS
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Cli_Input_Test_Key_Codes_CS_Form());
        }
    }
}
