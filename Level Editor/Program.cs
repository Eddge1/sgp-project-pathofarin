using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SGP_PoA_LevelEditor
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
            //Application.Run(new Form1());
            Form1 myForm = new Form1();

            myForm.Initialize();

            myForm.Show();

            while (myForm.isLooping)
            {
                myForm.Update();
                myForm.Render();

                Application.DoEvents();
            }
        }
    }
}
