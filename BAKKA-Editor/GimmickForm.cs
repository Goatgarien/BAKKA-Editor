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
    public partial class GimmickForm : Form
    {
        private Gimmick gimmick;
        public bool InsertGimmick { get; private set; }
        internal List<Gimmick> Gimmicks { get; private set; }

        float StartMeasure { get { return (float)startMeasureNumeric.Value + (float)startBeat1Numeric.Value / (float)startBeat2Numeric.Value; } }
        float StopEndMeasure { get { return (float)stopEndMeasureNumeric.Value + (float)stopEndBeat1Numeric.Value / (float)stopEndBeat2Numeric.Value; } }
        float RevEnd1Measure { get { return (float)revEnd1MeasureNumeric.Value + (float)revEnd1Beat1Numeric.Value / (float)revEnd1Beat2Numeric.Value; } }
        float RevEnd2Measure { get { return (float)revEnd2MeasureNumeric.Value + (float)revEnd2Beat1Numeric.Value / (float)revEnd2Beat2Numeric.Value; } }


        public enum FormReason
        {
            New,
            Edit
        };

        public GimmickForm()
        {
            InitializeComponent();
        }

        internal DialogResult Show(
            Gimmick baseGimmick, FormReason reason, Gimmick? gim1 = null, Gimmick? gim2 = null)
        {
            var quant = Utils.GetQuantization(baseGimmick.BeatInfo.Beat, 16);

            gimmick = new Gimmick();
            gimmick.BeatInfo = new BeatInfo(baseGimmick.BeatInfo);
            gimmick.GimmickType = baseGimmick.GimmickType;

            switch (gimmick.GimmickType)
            {
                case GimmickType.BpmChange:
                    startMeasureNumeric.Value = gimmick.BeatInfo.Measure;
                    startBeat1Numeric.Value = quant.Item1;
                    startBeat2Numeric.Value = quant.Item2;
                    if (reason == FormReason.Edit)
                        gimmickBpmNumeric.Value = (decimal)baseGimmick.BPM;
                    break;
                case GimmickType.TimeSignatureChange:
                    startMeasureNumeric.Value = gimmick.BeatInfo.Measure;
                    startBeat1Numeric.Value = quant.Item1;
                    startBeat2Numeric.Value = quant.Item2;
                    if (reason == FormReason.Edit)
                    {
                        timeSig1Numeric.Value = baseGimmick.TimeSig.Upper;
                        timeSig2Numeric.Value = baseGimmick.TimeSig.Lower;
                    }
                    break;
                case GimmickType.HiSpeedChange:
                    startMeasureNumeric.Value = gimmick.BeatInfo.Measure;
                    startBeat1Numeric.Value = quant.Item1;
                    startBeat2Numeric.Value = quant.Item2;
                    if (reason == FormReason.Edit)
                        hiSpeedNumeric.Value = (decimal)baseGimmick.HiSpeed;
                    break;
                case GimmickType.ReverseStart:
                    startMeasureNumeric.Value = gimmick.BeatInfo.Measure;
                    startBeat1Numeric.Value = quant.Item1;
                    startBeat2Numeric.Value = quant.Item2;
                    if (reason == FormReason.Edit && gim1 != null && gim2 != null)
                    {
                        var quantMid1 = Utils.GetQuantization(gim1.BeatInfo.Beat, 16);
                        var quantEnd1 = Utils.GetQuantization(gim2.BeatInfo.Beat, 16);
                        revEnd1MeasureNumeric.Value = gim1.BeatInfo.Measure;
                        revEnd1Beat1Numeric.Value = quantMid1.Item1;
                        revEnd1Beat2Numeric.Value = quantMid1.Item2;
                        revEnd2MeasureNumeric.Value = gim2.BeatInfo.Measure;
                        revEnd2Beat1Numeric.Value = quantEnd1.Item1;
                        revEnd2Beat2Numeric.Value = quantEnd1.Item2;
                    }
                    break;
                case GimmickType.ReverseMiddle:
                    var quantStart2 = Utils.GetQuantization(gim1.BeatInfo.Beat, 16);
                    var quantEnd2 = Utils.GetQuantization(gim2.BeatInfo.Beat, 16);
                    startMeasureNumeric.Value = gim1.BeatInfo.Measure; 
                    startBeat1Numeric.Value = quantStart2.Item1;
                    startBeat2Numeric.Value = quantStart2.Item2;
                    revEnd1MeasureNumeric.Value = gimmick.BeatInfo.Measure;
                    revEnd1Beat1Numeric.Value = quant.Item1;
                    revEnd1Beat2Numeric.Value = quant.Item2;
                    revEnd2MeasureNumeric.Value = gim2.BeatInfo.Measure;
                    revEnd2Beat1Numeric.Value = quantEnd2.Item1;
                    revEnd2Beat2Numeric.Value = quantEnd2.Item2;
                    break;
                case GimmickType.ReverseEnd:
                    var quantStart3 = Utils.GetQuantization(gim1.BeatInfo.Beat, 16);
                    var quantMid3 = Utils.GetQuantization(gim2.BeatInfo.Beat, 16);
                    startMeasureNumeric.Value = gim1.BeatInfo.Measure;
                    startBeat1Numeric.Value = quantStart3.Item1;
                    startBeat2Numeric.Value = quantStart3.Item2;
                    revEnd1MeasureNumeric.Value = gim2.BeatInfo.Measure; 
                    revEnd1Beat1Numeric.Value = quantMid3.Item1;
                    revEnd1Beat2Numeric.Value = quantMid3.Item2;
                    revEnd2MeasureNumeric.Value = gimmick.BeatInfo.Measure;
                    revEnd2Beat1Numeric.Value = quant.Item1;
                    revEnd2Beat2Numeric.Value = quant.Item2;
                    break;
                case GimmickType.StopStart:
                    startMeasureNumeric.Value = gimmick.BeatInfo.Measure;
                    startBeat1Numeric.Value = quant.Item1;
                    startBeat2Numeric.Value = quant.Item2;
                    if (reason == FormReason.Edit)
                    {
                        var stopEnd = Utils.GetQuantization(gim1.BeatInfo.Beat, 16);
                        stopEndMeasureNumeric.Value = gim1.BeatInfo.Measure;
                        stopEndBeat1Numeric.Value = stopEnd.Item1;
                        stopEndBeat2Numeric.Value = stopEnd.Item2;
                    }
                    break;
                case GimmickType.StopEnd:
                    var stopStart = Utils.GetQuantization(gim1.BeatInfo.Beat, 16);
                    startMeasureNumeric.Value = gim1.BeatInfo.Measure;
                    startBeat1Numeric.Value = stopStart.Item1;
                    startBeat2Numeric.Value = stopStart.Item2;
                    stopEndMeasureNumeric.Value = gimmick.BeatInfo.Measure;
                    stopEndBeat1Numeric.Value = quant.Item1;
                    stopEndBeat2Numeric.Value = quant.Item2;
                    break;
                default:
                    break;
            }

            gimmickBpmNumeric.Enabled = gimmick.GimmickType == GimmickType.BpmChange;

            timeSig1Numeric.Enabled = gimmick.GimmickType == GimmickType.TimeSignatureChange;
            timeSig2Numeric.Enabled = gimmick.GimmickType == GimmickType.TimeSignatureChange;

            hiSpeedNumeric.Enabled = gimmick.GimmickType == GimmickType.HiSpeedChange;

            stopEndMeasureNumeric.Enabled = gimmick.IsStop;
            stopEndBeat1Numeric.Enabled = gimmick.IsStop;
            stopEndBeat2Numeric.Enabled = gimmick.IsStop;

            revEnd1MeasureNumeric.Enabled = gimmick.IsReverse;
            revEnd1Beat1Numeric.Enabled = gimmick.IsReverse;
            revEnd1Beat2Numeric.Enabled = gimmick.IsReverse;
            revEnd2MeasureNumeric.Enabled = gimmick.IsReverse;
            revEnd2Beat1Numeric.Enabled = gimmick.IsReverse;
            revEnd2Beat2Numeric.Enabled = gimmick.IsReverse;

            Gimmicks = new List<Gimmick>();

            InsertGimmick = false;

            switch (reason)
            {
                case FormReason.New:
                    insertGimmickButton.Text = "Insert Gimmick";
                    break;
                case FormReason.Edit:
                    insertGimmickButton.Text = "Edit Gimmick";
                    break;
                default:
                    break;
            }
            return ShowDialog();
        }

        private void GimmickForm_FormClosing(object sender, FormClosingEventArgs e)
        {
        }

        private void insertGimmickButton_Click(object sender, EventArgs e)
        {
            switch (gimmick.GimmickType)
            {
                case GimmickType.BpmChange:
                    gimmick.BeatInfo = new BeatInfo((int)startMeasureNumeric.Value, (int)startBeat1Numeric.Value * 1920 / (int)startBeat2Numeric.Value);
                    gimmick.BPM = (double)gimmickBpmNumeric.Value;
                    Gimmicks.Add(gimmick);
                    break;
                case GimmickType.TimeSignatureChange:
                    gimmick.BeatInfo = new BeatInfo((int)startMeasureNumeric.Value, (int)startBeat1Numeric.Value * 1920 / (int)startBeat2Numeric.Value);
                    gimmick.TimeSig.Upper = (int)timeSig1Numeric.Value;
                    gimmick.TimeSig.Lower = (int)timeSig2Numeric.Value;
                    Gimmicks.Add(gimmick);
                    break;
                case GimmickType.HiSpeedChange:
                    gimmick.BeatInfo = new BeatInfo((int)startMeasureNumeric.Value, (int)startBeat1Numeric.Value * 1920 / (int)startBeat2Numeric.Value);
                    gimmick.HiSpeed = (double)hiSpeedNumeric.Value;
                    Gimmicks.Add(gimmick);
                    break;
                case GimmickType.ReverseStart:
                case GimmickType.ReverseMiddle:
                case GimmickType.ReverseEnd:
                    Gimmicks.Add(new Gimmick()
                    {
                        BeatInfo = new BeatInfo((int)startMeasureNumeric.Value, (int)startBeat1Numeric.Value * 1920 / (int)startBeat2Numeric.Value),
                        GimmickType = GimmickType.ReverseStart
                    });
                    Gimmicks.Add(new Gimmick()
                    {
                        BeatInfo = new BeatInfo((int)revEnd1MeasureNumeric.Value, (int)revEnd1Beat1Numeric.Value * 1920 / (int)revEnd1Beat2Numeric.Value),
                        GimmickType = GimmickType.ReverseMiddle
                    });
                    Gimmicks.Add(new Gimmick()
                    {
                        BeatInfo = new BeatInfo((int)revEnd2MeasureNumeric.Value, (int)revEnd2Beat1Numeric.Value * 1920 / (int)revEnd2Beat2Numeric.Value),
                        GimmickType = GimmickType.ReverseEnd
                    });
                    break;
                case GimmickType.StopStart:
                case GimmickType.StopEnd:
                    Gimmicks.Add(new Gimmick()
                    {
                        BeatInfo = new BeatInfo((int)startMeasureNumeric.Value, (int)startBeat1Numeric.Value * 1920 / (int)startBeat2Numeric.Value),
                        GimmickType = GimmickType.StopStart
                    });
                    Gimmicks.Add(new Gimmick()
                    {
                        BeatInfo = new BeatInfo((int)stopEndMeasureNumeric.Value, (int)stopEndBeat1Numeric.Value * 1920 / (int)stopEndBeat2Numeric.Value),
                        GimmickType = GimmickType.StopEnd
                    });
                    break;
                default:
                    break;
            }
            DialogResult = DialogResult.OK;
        }

        private void startMeasureNumeric_ValueChanged(object sender, EventArgs e)
        {
            if (stopEndMeasureNumeric.Enabled && StopEndMeasure < StartMeasure)
            {
                stopEndMeasureNumeric.Value = startMeasureNumeric.Value + 1;
            }
            if (revEnd1MeasureNumeric.Enabled && RevEnd1Measure < StartMeasure)
            {
                revEnd1MeasureNumeric.Value = startMeasureNumeric.Value + 1;
            }
        }

        private void startBeat1Numeric_ValueChanged(object sender, EventArgs e)
        {
            if (startBeat1Numeric.Value >= startBeat2Numeric.Value)
            {
                startMeasureNumeric.Value++;
                startBeat1Numeric.Value = 0;
            }
            else if (startBeat1Numeric.Value < 0)
            {
                if (startMeasureNumeric.Value > 0)
                {
                    startMeasureNumeric.Value--;
                    startBeat1Numeric.Value = startBeat2Numeric.Value - 1;
                }
                else if (startMeasureNumeric.Value == 0)
                {
                    startBeat1Numeric.Value = 0;
                }
            }
        }

        private void stopEndMeasureNumeric_ValueChanged(object sender, EventArgs e)
        {
            if (StopEndMeasure < StartMeasure)
            {
                stopEndMeasureNumeric.Value = startMeasureNumeric.Value;
                stopEndBeat1Numeric.Value = startBeat1Numeric.Value;
                stopEndBeat2Numeric.Value = startBeat2Numeric.Value;
                return;
            }
        }

        private void stopEndBeat1Numeric_ValueChanged(object sender, EventArgs e)
        {
            if (StopEndMeasure < StartMeasure)
            {
                stopEndMeasureNumeric.Value = startMeasureNumeric.Value;
                stopEndBeat1Numeric.Value = startBeat1Numeric.Value;
                stopEndBeat2Numeric.Value = startBeat2Numeric.Value;
                return;
            }

            if (stopEndBeat1Numeric.Value >= stopEndBeat2Numeric.Value)
            {
                stopEndMeasureNumeric.Value++;
                stopEndBeat1Numeric.Value = 0;
            }
            else if (stopEndBeat1Numeric.Value < 0)
            {
                if (stopEndMeasureNumeric.Value > 0)
                {
                    stopEndMeasureNumeric.Value--;
                    stopEndBeat1Numeric.Value = stopEndBeat2Numeric.Value - 1;
                }
                else if (stopEndMeasureNumeric.Value == 0)
                {
                    stopEndBeat1Numeric.Value = 0;
                }
            }
        }

        private void revEnd1MeasureNumeric_ValueChanged(object sender, EventArgs e)
        {
            if (RevEnd1Measure < StartMeasure)
            {
                revEnd1MeasureNumeric.Value = startMeasureNumeric.Value;
                revEnd1Beat1Numeric.Value = startBeat1Numeric.Value;
                revEnd1Beat2Numeric.Value = startBeat2Numeric.Value;
            }
            if (RevEnd2Measure < RevEnd1Measure)
            {
                revEnd2MeasureNumeric.Value = revEnd1MeasureNumeric.Value;
                revEnd2Beat1Numeric.Value = revEnd1Beat1Numeric.Value;
                revEnd2Beat2Numeric.Value = revEnd1Beat2Numeric.Value;
            }
        }        

        private void revEnd1Beat1Numeric_ValueChanged(object sender, EventArgs e)
        {
            if (RevEnd1Measure < StartMeasure)
            {
                revEnd1MeasureNumeric.Value = startMeasureNumeric.Value;
                revEnd1Beat1Numeric.Value = startBeat1Numeric.Value;
                revEnd1Beat2Numeric.Value = startBeat2Numeric.Value;
                return;
            }

            if (revEnd1Beat1Numeric.Value >= revEnd1Beat2Numeric.Value)
            {
                revEnd1MeasureNumeric.Value++;
                revEnd1Beat1Numeric.Value = 0;
            }
            else if (revEnd1Beat1Numeric.Value < 0)
            {
                if (revEnd1MeasureNumeric.Value > 0)
                {
                    revEnd1MeasureNumeric.Value--;
                    revEnd1Beat1Numeric.Value = revEnd1Beat2Numeric.Value - 1;
                }
                else if (revEnd1MeasureNumeric.Value == 0)
                {
                    revEnd1Beat1Numeric.Value = 0;
                }
            }
        }

        private void revEnd2MeasureNumeric_ValueChanged(object sender, EventArgs e)
        {
            if (RevEnd2Measure < RevEnd1Measure)
            {
                revEnd2MeasureNumeric.Value = revEnd1MeasureNumeric.Value;
                revEnd2Beat1Numeric.Value = revEnd1Beat1Numeric.Value;
                revEnd2Beat2Numeric.Value = revEnd1Beat2Numeric.Value;
                return;
            }
        }

        private void revEnd2Beat1Numeric_ValueChanged(object sender, EventArgs e)
        {
            if (RevEnd2Measure < RevEnd1Measure)
            {
                revEnd2MeasureNumeric.Value = revEnd1MeasureNumeric.Value;
                revEnd2Beat1Numeric.Value = revEnd1Beat1Numeric.Value;
                revEnd2Beat2Numeric.Value = revEnd1Beat2Numeric.Value;
                return;
            }

            if (revEnd2Beat1Numeric.Value >= revEnd2Beat2Numeric.Value)
            {
                revEnd2MeasureNumeric.Value++;
                revEnd2Beat1Numeric.Value = 0;
            }
            else if (revEnd2Beat1Numeric.Value < 0)
            {
                if (revEnd2MeasureNumeric.Value > 0)
                {
                    revEnd2MeasureNumeric.Value--;
                    revEnd2Beat1Numeric.Value = revEnd2Beat2Numeric.Value - 1;
                }
                else if (revEnd2MeasureNumeric.Value == 0)
                {
                    revEnd2Beat1Numeric.Value = 0;
                }
            }
        }
    }
}
