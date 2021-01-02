using System;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFF_77_SadlevičiusEdvinas_L1a.Library
{
    class CustomThread
    {
        public static int numberOfThreads;
        private int id { get; }
        private InformationLine currentInfo;
        private NewMonitor monitor { get; }
        private int sortBy;

        public CustomThread(NewMonitor monitor,int sort)
        {
            id = numberOfThreads++;
            currentInfo = null;
            this.monitor = monitor;
            sortBy = sort;

        }

        public bool Essential()
        {
            switch (sortBy)
            {
                case 0:
                    if (char.IsLetter(currentInfo.GetHash()[0]))
                    {
                        return true;
                    }
                    return false;
                case 1:
                    if (char.IsDigit(currentInfo.GetHash()[0]))
                    {
                        return true;
                    }
                    return false;
                default:
                    return false;
            }
        }

        public bool Start()
        {
            while(monitor.GetInformation(ref currentInfo, id));
            if (currentInfo == null)
            {
                Console.WriteLine("Gija " + id + ": Baigiau darba");
                return false;
            }
            else
            {
                if (Essential())
                {
                    monitor.PutInformation(currentInfo, id);
                    return true;
                }
                else
                {
                    return true; ;
                }
            }
        }
    }
}
