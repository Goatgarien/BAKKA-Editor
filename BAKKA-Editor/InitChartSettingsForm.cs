using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BAKKA_Editor
{
    public partial class InitChartSettingsForm : Form
    {
        public double Bpm { get { return (double)initBpmNumeric.Value; } }
        public int TimeSigUpper { get { return (int)initTimeSig1Numeric.Value; } }
        public int TimeSigLower { get { return (int)initTimeSig2Numeric.Value; } }
        public double Offset { get { return (double)initOffsetNumeric.Value; } }
        public double MovieOffset { get { return (double)initMovieOffsetNumeric.Value; } }

        public InitChartSettingsForm()
        {
            InitializeComponent();
        }

        public void SetValues(double bpm, int timeSigUpper, int timeSigLower, double offset, double movieOffset)
        {
            initBpmNumeric.Value = (decimal)bpm;
            initTimeSig1Numeric.Value = timeSigUpper;
            initTimeSig2Numeric.Value = timeSigLower;
            initOffsetNumeric.Value = (decimal)offset;
            initMovieOffsetNumeric.Value = (decimal)movieOffset;
        }

        private void initSaveSettingsButton_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
        }
    }
}
