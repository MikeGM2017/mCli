using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Cli_Output_CS_Test
{
    static class Cli_Output_CS_Test_Main
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Cli_Output_CS_Test_Form());
        }
    }
}
