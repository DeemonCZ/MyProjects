using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arena
{
    class Bojovnik
    {
        //deklarace proměnných
        /// <summary>
        /// jmeno bojovnika
        /// </summary>
        protected string jmeno;
        /// <summary>
        /// zdravi v hp
        /// </summary>
        protected int zivot;
        /// <summary>
        /// maximalni zdravi
        /// </summary>
        protected int maxZivot;
        /// <summary>
        /// utok v hp
        /// </summary>
        protected int utok;
        /// <summary>
        /// obrana v hp
        /// </summary>
        protected int obrana;
        /// <summary>
        /// instance hraci kostky
        /// </summary>
        protected Kostka kostka;
        /// <summary>
        /// zprava pro vypis udalosti
        /// </summary>
        private string zprava;
 //metody objektu bojovnik -----------------------------------
        public Bojovnik(string jmeno, int zivot, int utok, int obrana, Kostka kostka)
        {
            this.jmeno = jmeno;
            this.zivot = zivot;
            this.maxZivot = zivot;
            this.utok = utok;
            this.obrana = obrana;
            this.kostka = kostka;
        }
        /// <summary>
        /// pojmenovani bojovnika
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return jmeno;
        }
        /// <summary>
        /// odpovi, jestli je bojovnik nazivu
        /// </summary>
        /// <returns></returns>
        public bool Nazivu()
        {
            return (zivot > 0);
        }
        
        protected string GrafickyUkazatel(int aktualni, int maximalni)
        {
            string s = "[";
            int celkem = 20;
            double pocet = Math.Round(((double)aktualni / maximalni) * celkem);
            if ((pocet == 0) && (Nazivu()))
                pocet = 1;
            for (int i = 0; i < pocet; i++)
                s += "█";
            s = s.PadRight(celkem + 1);
            s += "]";
            return s;
        }
        /// <summary>
        /// vykresli bojovnikuv zivot graficky
        /// </summary>
        /// <returns></returns>
        public string  Grafickyzivot()
        {
            return GrafickyUkazatel(zivot, maxZivot);
        }
        
        /// <summary>
        /// metoda pro obranu
        /// </summary>
        /// <param name="uder"></param>
        public void BranSe(int uder)
        {
            int zraneni = uder - (obrana + kostka.Hod());
            if (zraneni > 0)
            {
                zivot -= zraneni;
                zprava = string.Format("{0} utrpel poskozeni {1}", jmeno, zraneni);
                if (zivot <= 0)
                {
                    zivot = 0;
                    zprava += " a zemrel";
                }
            }
            else
                zprava = string.Format("{0} odrazil utok", jmeno);
            NastavZpravu(zprava);
        }
        /// <summary>
        /// metoda pro utok
        /// </summary>
        /// <param name="souper"></param>
        public virtual void Utoc(Bojovnik souper)
        {
            int uder = utok + kostka.Hod();
            NastavZpravu(string.Format("{0} utoci s uderem {1}.", jmeno, uder));    
            souper.BranSe(uder);
        }
        /// <summary>
        /// metoda pro nastavení zprávy
        /// </summary>
        /// <param name="zprava"></param>
        protected void NastavZpravu(string zprava)
        {
            this.zprava = zprava;
        }
        /// <summary>
        /// metoda pro vypsání zprávy události
        /// </summary>
        /// <returns></returns>
        public string VratPosledniZpravu()
        {
            return zprava;
        }

        

    }
}
