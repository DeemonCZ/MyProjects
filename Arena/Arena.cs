using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Arena
{
    class Arena
    {
        /// <summary>
        /// prvni bojovnik
        /// </summary>
        private Bojovnik bojovnik_1;
        /// <summary>
        /// druhy bojovnik
        /// </summary>
        private Bojovnik bojovnik_2;
        /// <summary>
        /// hraci kostka
        /// </summary>
        private Kostka kostka;

        /// <summary>
        /// konstruktor areny (inicializace)
        /// </summary>
        /// <param name="bojovnik_1"></param>
        /// <param name="bojovnik_2"></param>
        /// <param name="kostka"></param>
        public Arena(Bojovnik bojovnik_1, Bojovnik bojovnik_2, Kostka kostka)
        {
            this.bojovnik_1 = bojovnik_1;
            this.bojovnik_2 = bojovnik_2;
            this.kostka = kostka;
        }

        public void VypisBojovnika(Bojovnik b)
        {
            Console.WriteLine(b);
            Console.Write("Zivot: ");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(b.Grafickyzivot());
            if (b is Mag)
            {
                Console.ForegroundColor = ConsoleColor.White;
                Console.Write("Mana: ");
                Console.ForegroundColor = ConsoleColor.Blue;
                Console.WriteLine(((Mag)b).GrafickaMana());
            }
            Console.ForegroundColor = ConsoleColor.White;
        }

        /// <summary>
        /// metoda vypise zdravi obou bojovniku
        /// </summary>
        private void Vykresli()
        {
            Console.Clear();
            Console.WriteLine("---------------------------Arena----------------------------\n");
            Console.WriteLine("Bojovnici: \n");
            VypisBojovnika(bojovnik_1);
            Console.WriteLine();
            VypisBojovnika(bojovnik_2);
            Console.WriteLine();          
        }

        /// <summary>
        /// metoda vypise zpravu
        /// </summary>
        /// <param name="zprava"></param>
        private void VypisZpravu(string zprava)
        {
            Console.WriteLine(zprava);
            Thread.Sleep(500);
        }
        /// <summary>
        /// metoda samotneho zapasu
        /// </summary>
        public void Zapas()
        {
            Console.WriteLine("Vitejte v Arene!");
            Console.WriteLine("Dnes se utkají {0} s {1}! \n", bojovnik_1, bojovnik_2);
            Console.WriteLine("Zápas může začít...");
            Console.ReadKey();

            //cyklus s bojem
            while(bojovnik_1.Nazivu() && bojovnik_2.Nazivu())
            {
                Vykresli();         //aby nebyl výsledek vidět už před výpisem útoku a zranění
                bojovnik_1.Utoc(bojovnik_2);               
                VypisZpravu(bojovnik_1.VratPosledniZpravu()); //zprava o utoku
                VypisZpravu(bojovnik_2.VratPosledniZpravu()); //zprava o obrane
                
                if (bojovnik_2.Nazivu())
                {
                    Vykresli();     //aby nebyl výsledek vidět už před výpisem útoku a zranění
                    bojovnik_2.Utoc(bojovnik_1);
                    
                    VypisZpravu(bojovnik_2.VratPosledniZpravu()); //zprava o utkoku
                    VypisZpravu(bojovnik_1.VratPosledniZpravu()); // zprava o obrane                   
                }
                else
                {
                    Vykresli();     //zobrazení životů v případě výhry b1
                    VypisZpravu(bojovnik_1.VratPosledniZpravu()); //zprava o utoku
                    VypisZpravu(bojovnik_2.VratPosledniZpravu()); //zprava o obrane
                }
                Console.WriteLine();

            }
        }

    }
}
