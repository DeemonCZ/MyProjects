using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator
{
    class Computing
    {
        private bool correctOper = true;            //test for correct "switch" key
        private int result = 0;

        public string Calculation(int number1, char oper, int number2)
        {                   
            switch (oper)
            {
                case '+':
                    {                         //sčítání
                        result = number1 + number2;
                        break;
                    }
                case '-':
                    {                         //odčítání
                        result = number1 - number2;
                        break;
                    }

                case '*':
                    {                         //násobení
                        result = number1 * number2;
                        break;
                    }

                case '/':
                    {                         //dělení
                        try { result = number1 / number2; } catch (Exception e) { Console.WriteLine("Dividing with 0 - error"); }   //oeštření pro dělení nulou
                        break;
                    }

                default:
                    {
                        correctOper = false;
                        break;
                    }
            }
            //kontrola spravnosti operandu
            if (correctOper)
                return string.Format("Result: {0} {1} {2} = {3}", number1, oper, number2, result);
            else
                return string.Format("Wrong 'SWITCH' key!");

        }
    }
}
