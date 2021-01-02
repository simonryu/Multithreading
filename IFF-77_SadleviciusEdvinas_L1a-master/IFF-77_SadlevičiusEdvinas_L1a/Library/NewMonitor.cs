using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace IFF_77_SadlevičiusEdvinas_L1a.Library
{
    class NewMonitor
    {
        private InformationLine[] informationArray;
        private InformationField document;
        private OutputInformation output;
        private List<int> used;
        private bool over;
        private bool full;
        private bool empty;
        private object lockerGet { get; }
        private object lockerPut { get; }

        public NewMonitor(int size, InformationField document, OutputInformation output)
        {
            empty = true;
            over = false;
            full = false;
            used = new List<int>();
            this.output = output;
            informationArray = new InformationLine[size / 2];
            this.document = document;
            lockerGet = new object();
            lockerPut = new object();
        }

        private int FindFreeSpaceIndex()
        {
            for (int i = 0; i < informationArray.Length; i++)
            {
                if (informationArray[i] == null)
                {
                    return i;
                }
            }
            return -1;
        }
        public bool MainIsAddingInformation()
        {
            lock (lockerGet)
            {
                if (full)
                {
                    Console.WriteLine("Pagrindine gija: Pilnas masyvas");
                    Monitor.PulseAll(lockerGet);
                    return true;
                }
                int index = FindFreeSpaceIndex();
                if (index < 0)
                {
                    Console.WriteLine("Pagrindine gija: Nera vietos masyve");
                    full = true;
                    Monitor.PulseAll(lockerGet);
                    return true;
                }
                else
                {
                    Console.WriteLine("Pagrindine gija: įdedu informaciją");
                    InformationLine newInfo = document.GetInformation();
                    if (newInfo == null)
                    {
                        Console.WriteLine("Pagrindine gija: Pasibaige, nes gautas null");
                        over = true;
                        Monitor.PulseAll(lockerGet);
                        return false;
                    }
                    else
                    {
                        if (empty)
                        {
                            empty = false;
                        }
                        used.Add(index);
                        informationArray[index] = newInfo;
                        Monitor.PulseAll(lockerGet);
                        return true;
                    }
                }
            }
        }
        public void PutInformation(InformationLine newLine, int id)
        {
            lock (lockerPut)
            {
                Console.WriteLine("Gija " + id + ": Vykdau PutInformation()");
                output.PutAndSort(newLine);
                Monitor.PulseAll(lockerPut);
            }
        }

        public bool GetInformation(ref InformationLine threadInfo, int id)
        {
            if (over && empty)
            {
                threadInfo = null;
                return false;
            }
            if (empty == true)
            {
                return true;
            }
            lock (lockerGet)
            {
                if (full)
                {
                    full = false;
                }
                if (used.Count == 0)
                {
                    empty = true;
                    Console.WriteLine("Gija " + id + ": Vykdau GetInformation(), bet tuscias masyvas");
                    return true;
                }
                else
                {
                    Console.WriteLine("Gija " + id + ": Vykdau GetInformation()");
                    int index = used.First();
                    used.Remove(index);
                    threadInfo = informationArray[index];
                    informationArray[index] = null;
                    Monitor.PulseAll(lockerGet);
                    return false;
                }
            }
        }
    }
}
