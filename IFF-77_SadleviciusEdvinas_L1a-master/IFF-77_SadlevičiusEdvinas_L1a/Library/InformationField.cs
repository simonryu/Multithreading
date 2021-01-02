using System;
using System.Xml;
using System.Text;
using System.IO;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace IFF_77_SadlevičiusEdvinas_L1a.Library
{
    /// <summary>
    /// Custom data structure for saving InformationLine
    /// </summary>
    class InformationField
    {
        //Attributes
        private List<InformationLine> listOfInformation;
        private Exception error;
        private List<InformationLine> listOfTakenInformation;
        private int left;
        

        /// <summary>
        /// Empty constructor (Initializes 4 Lists)
        /// </summary>
        public InformationField()
        {
            listOfInformation = new List<InformationLine>();
            listOfTakenInformation = new List<InformationLine>();
            left = 0;
        }


        /// <summary>
        /// Constructor to read information from file
        /// </summary>
        /// <param name="locationToReadFrom"></param>
        public InformationField(string locationToReadFrom) : this()
        {
            XmlDocument document = Check_For_Errors(locationToReadFrom);
            if (document != null)
            {
                Console.WriteLine("Reading from file\n");
                if (SaveInformation(document))
                {
                    Console.WriteLine("File reading completed\n");
                }
                else
                {
                    Console.WriteLine(String.Format("Could not read file.\nError: {0}", error.Message));
                }

            }
            else
            {
                Console.WriteLine(String.Format("Could not read file.\nError: {0}", error.Message));
            }
        }

        private XmlDocument Check_For_Errors(string path)
        {
            try
            {
                XmlDocument document = new XmlDocument();
                document.Load(path);
                return document;
            }
            catch (Exception e)
            {
                error = e;
                return null;
            }
        }

        private bool SaveInformation(XmlDocument doc)
        {
            if (true)
            {
                foreach (XmlNode node in doc.LastChild.ChildNodes)
                {
                    left++;
                    listOfInformation.Add(new InformationLine(node.Attributes[0].Value, int.Parse(node.Attributes[1].Value), double.Parse(node.Attributes[2].Value)));
                }
                return true;
            }
            else
            {
                return false;
            }
        }

        public InformationLine GetInformation()
        {
            if (left == 0)
            {
                return null;
            }
            InformationLine get = listOfInformation[left-- - 1];
            listOfTakenInformation.Add(get);
            return get;
        }

    }
}
