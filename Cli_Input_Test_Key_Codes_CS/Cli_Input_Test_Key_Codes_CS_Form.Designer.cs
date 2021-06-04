namespace Cli_Input_Test_Key_Codes_CS
{
    partial class Cli_Input_Test_Key_Codes_CS_Form
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Cli_Input_textBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // Cli_Input_textBox
            // 
            this.Cli_Input_textBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Cli_Input_textBox.Location = new System.Drawing.Point(0, 0);
            this.Cli_Input_textBox.Multiline = true;
            this.Cli_Input_textBox.Name = "Cli_Input_textBox";
            this.Cli_Input_textBox.Size = new System.Drawing.Size(304, 201);
            this.Cli_Input_textBox.TabIndex = 0;
            this.Cli_Input_textBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Cli_Input_textBox_KeyDown);
            this.Cli_Input_textBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Cli_Input_textBox_KeyPress);
            this.Cli_Input_textBox.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.Cli_Input_textBox_PreviewKeyDown);
            // 
            // Cli_Input_Test_Key_Codes_CS_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(304, 201);
            this.Controls.Add(this.Cli_Input_textBox);
            this.Name = "Cli_Input_Test_Key_Codes_CS_Form";
            this.Text = "Cli Input Test Key Codes CS";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Cli_Input_textBox;
    }
}

