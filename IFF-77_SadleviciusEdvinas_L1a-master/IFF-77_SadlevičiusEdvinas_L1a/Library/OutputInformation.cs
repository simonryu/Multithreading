using System;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFF_77_SadlevičiusEdvinas_L1a.Library
{
    class OutputInformation
    {
        private InformationLine[] output;
        bool ascending;
        public int Size { get; private set; }

        public OutputInformation(int size, bool ascending)
        {
            output = new InformationLine[size];
            Size = 0;
            this.ascending = ascending;
        }


        public void PrintInformation(string pathOfFile)
        {
            using (StreamWriter writer = new StreamWriter(pathOfFile, false, Encoding.GetEncoding(1257)))
            {
                string head = String.Format("|{0,20}|{1,20}|{2,20}|{3,100}|", "Pavadinimas", "Parduota", "Kaina", "HASH");
                writer.WriteLine(head);
                writer.WriteLine(new String('-', head.Length));
                if (Size != 0)
                {
                    for (int i = 0; i < Size; i++)
                    {
                        writer.WriteLine(String.Format("|{0,20}|{1,20}|{2,20}|{3,100}|", output[i].word, output[i].zNumber, output[i].rNumber, output[i].GetHash()));
                        writer.WriteLine(new String('-', head.Length));
                    }
                    writer.WriteLine("Viso:" + Size);
                }
            }
        }

        public bool PutAndSort(InformationLine info)
        {
                return MoveToNewField(info, 0);
        }

        private bool MoveToNewField(InformationLine info, int current)
        {
            if (Size == current)
            {
                output[current] = info;
                Size++;
                return true;
            }
            if (ascending)
            {
                switch (info.CompareTo(output[current]))
                {
                    case 1:
                        InformationLine temp = new InformationLine(output[current].word, output[current].zNumber, output[current].rNumber);
                        output[current] = info;
                        return MoveToNewField(temp, ++current);
                    default:
                        return MoveToNewField(info, ++current);
                }

            }
            else
            {
                switch (info.CompareTo(output[current]))
                {
                    case -1:
                        InformationLine temp = new InformationLine(output[current].word, output[current].zNumber, output[current].rNumber);
                        output[current] = info;
                        return MoveToNewField(temp, ++current);
                    default:
                        return MoveToNewField(info, ++current);
                }
            }
        }

    }
}
