using System;
using System.Windows.Forms;

namespace Cli_Input_CS_Test
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
            Application.ApplicationExit += new EventHandler(AppExit);
            Main_Form = new Cli_Input_CS_Test_Form();
            Application.Run(Main_Form);
        }

        static Cli_Input_CS_Test_Form Main_Form = null;

        static void AppExit(object sender, EventArgs e)
        {
            if (Main_Form != null)
            {
                Main_Form.Cli_Input_Close();
            }
        }
    }
}
