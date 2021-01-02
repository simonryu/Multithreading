using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;

namespace IFF_77_SadlevičiusEdvinas_L1a.Library
{
    class InformationLine : IComparable<InformationLine>
    {
        public string word { get;}
        public int zNumber { get; }
        public double rNumber { get; }
        private byte[] hash;
        private HashAlgorithm algHash;

        public InformationLine()
        {
            word = "";
            zNumber = 0;
            rNumber = 0;
            algHash = new SHA256CryptoServiceProvider();
            hash = new byte[1];
        }

        public InformationLine(string word, int zNumber, double rNumber)
        {
            this.word = word;
            this.zNumber = zNumber;
            this.rNumber = rNumber;
            algHash = new SHA256CryptoServiceProvider();
            hash = algHash.ComputeHash(Encoding.UTF8.GetBytes(word+zNumber+rNumber));
        }

        public int CompareTo(InformationLine other)
        {
            
            if (other == null || other.GetHash()[0] < this.GetHash()[0])
            {
                return -1;
            }
            if (this.GetHash()[0] < other.GetHash()[0])
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        public string GetHash()
        {
            return BitConverter.ToString(hash);
        }

    }
}
