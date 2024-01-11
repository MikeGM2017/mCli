using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Cli_Core_CS
{
    static class Cli_Core_Main
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Cli_Core_CS_Test());
        }
    }
}
