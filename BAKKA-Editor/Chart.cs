using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAKKA_Editor
{
    internal class Chart
    {
        public List<Note> Notes { get; set; }
        public List<Gimmick> Gimmicks { get; set; }
        /// <summary>
        /// Offset in seconds.
        /// </summary>
        public double Offset { get; set; }
        /// <summary>
        /// Movie offset in seconds
        /// </summary>
        public double MovieOffset { get; set; }
        String SongFileName { get; set; }
        List<Gimmick> TimeEvents { get; set; }
        public bool HasInitEvents
        {
            get
            {
                return TimeEvents != null &&
                    TimeEvents.Count > 0 &&
                    Gimmicks.Count(x => x.Measure == 0 && x.GimmickType == GimmickType.BpmChange) >= 1 &&
                    Gimmicks.Count(x => x.Measure == 0 && x.GimmickType == GimmickType.TimeSignatureChange) >= 1;
            }
        }
        public bool IsSaved { get; set; }

        public Chart()
        {
            Notes = new();
            Gimmicks = new();
            Offset = 0;
            MovieOffset = 0;
            SongFileName = "";
            IsSaved = true;
        }

        public bool ParseFile(string filename)
        {
            var file = File.ReadAllLines(filename);

            int index = 0;

            do
            {
                var line = file[index];

                var path = Utils.GetTag(line, "#MUSIC_FILE_PATH ");
                if (path != null)
                    SongFileName = path;

                var offset = Utils.GetTag(line, "#OFFSET");
                if (offset != null)
                    Offset = Convert.ToDouble(offset);

                offset = Utils.GetTag(line, "#MOVIEOFFSET");
                if (offset != null)
                    MovieOffset = Convert.ToDouble(offset);


                if (line.Contains("#BODY"))
                {
                    index++;
                    break;
                }

            } while(++index < file.Length);

            int lineNum;
            Gimmick gimmickTemp;
            Note noteTemp;
            Dictionary<int, Note> notesByLine = new();
            Dictionary<int, int> refByLine = new();
            for (int i = index; i < file.Length; i++)
            {
                var parsed = file[i].Split(new string[] {" "}, StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries);
                NoteBase temp = new();
                temp.BeatInfo = new BeatInfo(Convert.ToInt32(parsed[0]), Convert.ToInt32(parsed[1]));
                temp.GimmickType = (GimmickType)Convert.ToInt32(parsed[2]);

                switch (temp.GimmickType)
                {
                    case GimmickType.NoGimmick:
                        noteTemp = new Note(temp.BeatInfo);
                        noteTemp.NoteType = (NoteType)Convert.ToInt32(parsed[3]);
                        lineNum = Convert.ToInt32(parsed[4]);
                        noteTemp.Position = Convert.ToInt32(parsed[5]);
                        noteTemp.Size = Convert.ToInt32(parsed[6]);
                        noteTemp.HoldChange = Convert.ToBoolean(Convert.ToInt32(parsed[7]));
                        if (noteTemp.NoteType == NoteType.MaskAdd || noteTemp.NoteType == NoteType.MaskRemove)
                        {
                            noteTemp.MaskFill = (MaskType)Convert.ToInt32(parsed[8]);
                        }
                        else if (noteTemp.NoteType == NoteType.HoldStartNoBonus ||
                            noteTemp.NoteType == NoteType.HoldJoint ||
                            noteTemp.NoteType == NoteType.HoldStartBonusFlair)
                        {
                            refByLine[lineNum] = Convert.ToInt32(parsed[8]);
                        }
                        Notes.Add(noteTemp);
                        notesByLine[lineNum] = Notes.Last();
                        break;
                    case GimmickType.BpmChange:
                        gimmickTemp = new Gimmick(temp.BeatInfo, temp.GimmickType);
                        gimmickTemp.BPM = Convert.ToDouble(parsed[3]);
                        Gimmicks.Add(gimmickTemp);
                        break;
                    case GimmickType.TimeSignatureChange:
                        gimmickTemp = new Gimmick(temp.BeatInfo, temp.GimmickType);
                        gimmickTemp.TimeSig = new TimeSignature() { Upper = Convert.ToInt32(parsed[3]), Lower = Convert.ToInt32(parsed[4]) };
                        Gimmicks.Add(gimmickTemp);
                        break;
                    case GimmickType.HiSpeedChange:
                        gimmickTemp = new Gimmick(temp.BeatInfo, temp.GimmickType);
                        gimmickTemp.HiSpeed = Convert.ToDouble(parsed[3]);
                        Gimmicks.Add(gimmickTemp);
                        break;
                    case GimmickType.ReverseStart:
                    case GimmickType.ReverseMiddle:
                    case GimmickType.ReverseEnd:
                    case GimmickType.StopStart:
                    case GimmickType.StopEnd:
                    default:
                        Gimmicks.Add(new Gimmick(temp.BeatInfo, temp.GimmickType));
                        break;
                }

            }

            // Generate hold references
            for (int i = 0; i < Notes.Count; i++)
            {
                if (refByLine.ContainsKey(i))
                {
                    Notes[i].NextNote = notesByLine[refByLine[i]];
                    Notes[i].NextNote.PrevNote = Notes[i];
                }
            }

            RecalcTime();

            IsSaved = true;
            return true;
        }

        public bool WriteFile(string filename, bool setSave = true)
        {
            using (StreamWriter sw = new StreamWriter(new FileStream(filename, FileMode.Create), new UTF8Encoding(false)))
            {
                // LF line ending
                sw.NewLine = "\n";

                sw.WriteLine("#MUSIC_SCORE_ID 0");
                sw.WriteLine("#MUSIC_SCORE_VERSION 0");
                sw.WriteLine("#GAME_VERSION ");
                sw.WriteLine($"#MUSIC_FILE_PATH {SongFileName}");
                sw.WriteLine($"#OFFSET {Offset:F6}");
                sw.WriteLine($"#MOVIEOFFSET {MovieOffset:F6}");
                sw.WriteLine("#BODY");

                foreach (var gimmick in Gimmicks)
                {
                    sw.Write($"{gimmick.BeatInfo.Measure,4:F0}{gimmick.BeatInfo.Beat,5:F0}{((int)gimmick.GimmickType),5:F0}");
                    switch (gimmick.GimmickType)
                    {
                        case GimmickType.BpmChange:
                            sw.WriteLine($" {gimmick.BPM:F6}");
                            break;
                        case GimmickType.TimeSignatureChange:
                            sw.WriteLine($"{gimmick.TimeSig.Upper,5:F0}{gimmick.TimeSig.Lower,5:F0}");
                            break;
                        case GimmickType.HiSpeedChange:
                            sw.WriteLine($" {gimmick.HiSpeed:F6}");
                            break;
                        default:
                            sw.WriteLine("");
                            break;
                    }
                }

                foreach (var note in Notes)
                {
                    sw.Write($"{note.BeatInfo.Measure,4:F0}{note.BeatInfo.Beat,5:F0}{((int)note.GimmickType),5:F0}{(int)note.NoteType,5:F0}");
                    sw.Write($"{Notes.IndexOf(note),5:F0}{note.Position,5:F0}{note.Size,5:F0}{Convert.ToInt32(note.HoldChange),5:F0}");
                    if (note.IsMask)
                        sw.Write($"{(int)note.MaskFill,5:F0}");
                    if (note.NextNote != null)
                        sw.Write($"{Notes.IndexOf(note.NextNote),5:F0}");
                    sw.WriteLine("");
                }
            }

            IsSaved = setSave;
            return true;
        }

        public void RecalcTime()
        {
            Gimmicks = Gimmicks.OrderBy(x => x.Measure).ToList();
            var timeSig = Gimmicks.FirstOrDefault(x => x.GimmickType == GimmickType.TimeSignatureChange && x.Measure == 0.0f);
            var bpm = Gimmicks.FirstOrDefault(x => x.GimmickType == GimmickType.BpmChange && x.Measure == 0.0f);
            if (timeSig == null || bpm == null)
                return;     // Cannot calculate times without either starting value

            TimeEvents = new();
            for (int i = 0; i < Gimmicks.Count; i++)
            {
                var evt = TimeEvents.FirstOrDefault(x => x.BeatInfo.MeasureDecimal == Gimmicks[i].BeatInfo.MeasureDecimal);

                if (Gimmicks[i].GimmickType == GimmickType.BpmChange)
                {
                    if (evt == null)
                    {
                        TimeEvents.Add(new Gimmick()
                        {
                            BeatInfo = new BeatInfo(Gimmicks[i].BeatInfo),
                            BPM = Gimmicks[i].BPM,
                            TimeSig = new TimeSignature(timeSig.TimeSig)
                        });
                    }
                    else
                    {
                        evt.BPM = Gimmicks[i].BPM;
                    }
                    bpm = Gimmicks[i];
                }
                if (Gimmicks[i].GimmickType == GimmickType.TimeSignatureChange)
                {
                    if (evt == null)
                    {
                        TimeEvents.Add(new Gimmick()
                        {
                            BeatInfo = new BeatInfo(Gimmicks[i].BeatInfo),
                            BPM = bpm.BPM,
                            TimeSig = new TimeSignature(Gimmicks[i].TimeSig)
                        });
                    }
                    else
                    {
                        evt.TimeSig = new TimeSignature(Gimmicks[i].TimeSig);
                    }
                    timeSig = Gimmicks[i];
                }
            }

            // Run through all time events and generate valid start times
            TimeEvents[0].StartTime = Offset * 1000.0;
            for (int i = 1; i < TimeEvents.Count; i++)
            {
                TimeEvents[i].StartTime = ((TimeEvents[i].Measure - TimeEvents[i - 1].Measure) * 4 * TimeEvents[i - 1].TimeSig.Ratio * 60000.0 / TimeEvents[i].BPM) + TimeEvents[i - 1].StartTime;
            }
        }

        /// <summary>
        /// Translate clock time to beats
        /// </summary>
        /// <param name="time">Current timestamp in ms</param>
        /// <returns></returns>
        public BeatInfo GetBeat(float time)
        {
            if (TimeEvents == null || TimeEvents.Count == 0)
                return new BeatInfo(-1, 0);

            var evt = TimeEvents.Where(x => time >= x.StartTime).LastOrDefault();
            if (evt == null)
                evt = TimeEvents[0];
            return new BeatInfo((float)(evt.BPM * (time - evt.StartTime) / (60000.0f * evt.TimeSig.Ratio * 4)) + evt.Measure);
        }

        /// <summary>
        /// Translate measures into clock time
        /// </summary>
        /// <param name="beat"></param>
        /// <returns></returns>
        public int GetTime(BeatInfo beat)
        {
            if (TimeEvents == null || TimeEvents.Count == 0)
                return 0;

            var evt = TimeEvents.Where(x => beat.MeasureDecimal >= x.Measure).LastOrDefault();
            if (evt == null)
                evt = TimeEvents[0];
            return (int)((60000.0 * 4.0 * evt.TimeSig.Ratio / evt.BPM) * (beat.MeasureDecimal - evt.Measure) + evt.StartTime);
        }
    }
}
