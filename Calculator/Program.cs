using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator
{
    class Program
    {
        static void Main(string[] args)
        {
            string continueProgram = "y";
            while (continueProgram == "y")
            {
                Console.Clear();
                Console.WriteLine("Calculator");
                Console.WriteLine("Insert 1.number, confirm, than insert operand(+ - * /) and 2.number and confirm.");

                int number1;
                while (!int.TryParse(Console.ReadLine(), out number1))         //test for first number
                    Console.WriteLine("Wrong number, try again: ");

                char oper = Console.ReadKey().KeyChar;                         //insert operand
                                                                               //Console.WriteLine();

                int number2;
                while (!int.TryParse(Console.ReadLine(), out number2))         //test for second number
                    Console.WriteLine("Wrong number, try again: ");


                Computing computing = new Computing();                              //objekt pro počítání
                Console.WriteLine( computing.Calculation(number1, oper, number2));


                Console.WriteLine("Do you want to continue? [y/n]");
                continueProgram = Console.ReadLine();
            }
            Console.WriteLine("End program with any key.");
            Console.ReadKey();
        }
    }
}
