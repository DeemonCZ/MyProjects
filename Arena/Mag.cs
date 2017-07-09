using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Arena
{
    class Mag : Bojovnik
    {
        private int mana;
        private int maxMana;
        private int magickyUtok;

        public Mag (string jmeno, int zivot, int utok, int obrana, Kostka kostka, int mana, int magickyUtok): base (jmeno, zivot, utok, obrana, kostka)
        {
            this.mana = mana;
            this.maxMana = mana;
            this.magickyUtok = magickyUtok;
        }

        public override void Utoc(Bojovnik souper)
        {
            int uder = 0;
            //mana neni plná
            if (mana < maxMana)
            {
                mana += 10;
                if (mana > maxMana)                
                    mana = maxMana;
                base.Utoc(souper);                                             
            }
            else
            //mana je plna
            {
                uder = magickyUtok + kostka.Hod();
                NastavZpravu(String.Format("{0} použil magii za {1} hp", jmeno, uder));                
                souper.BranSe(uder);
                mana = 0;
            }            
        }

        public string GrafickaMana()
        {
            return GrafickyUkazatel(mana, maxMana);
        }
    }
}
