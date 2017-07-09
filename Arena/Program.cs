using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arena
{
    class Program
    {
        static void Main(string[] args)
        {
            //vytvoření objektů
            Kostka kostka = new Kostka(10);
            Bojovnik deemon = new Bojovnik("Deemon", 100, 20, 10, kostka);
            Bojovnik mage = new Mag("Mage", 100, 20, 10, kostka, 55, 25);
            Arena arena = new Arena(deemon, mage, kostka);

            arena.Zapas();

            Console.ReadKey();
        }
    }
}
