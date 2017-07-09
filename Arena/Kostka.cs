using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arena
{
    /// <summary>
    /// třída pro hrací kostku
    /// </summary>
    class Kostka
    {
        /// <summary>
        /// počet stěn na kostce
        /// </summary>
        private int PocetSten;

        /// <summary>
        /// generátor náhodných čísel
        /// </summary>
        private Random random;

        public Kostka(int PocetSten)
        {
            this.PocetSten = PocetSten; 
            random = new Random();
        }

        public Kostka()
        {
            PocetSten = 6;
            random = new Random();
        }

        /// <summary>
        /// vrátí počet stěn
        /// </summary>
        /// <returns>pocet stran hraci kostky</returns>
        public int VratPocetSten()
        {
            return PocetSten;
        }

        /// <summary>
        /// vrati nahodne cislo z kostky
        /// </summary>
        /// <returns></returns>
        public int Hod()
        {
            return random.Next(1, PocetSten + 1);
        }


        public override string ToString()
        {
            return string.Format("Kostka s {0} stenami", PocetSten);
        }
    }
}
