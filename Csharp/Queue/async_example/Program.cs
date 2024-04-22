
namespace AsyncExample
{
    class Program
    {
        static void Main(string[] args)
        {
            AnotherMethodHere();

            Console.ReadKey();
        }
        
        public static async void AnotherMethodHere()
        {
            var egg = await CookEggs();
            CookBacons();
            CookAny("bla 1");
            Console.WriteLine("escrevendo na tela 1");
            CookAny("bla 2");
            Console.WriteLine("escrevendo na tela 2");
            CookAny("bla 3");
            Console.WriteLine("escrevendo na tela 3");
            CookAny("bla 4");
            Console.WriteLine("escrevendo na tela 4");
            CookAny("bla 5");
            Console.WriteLine("escrevendo na tela 5");
            CookAny("bla 6");
            Console.WriteLine("escrevendo na tela 6");
        }
        
        public static async Task<bool> CookEggs()
        {
            bool result = false;

            await Task.Run(() => {
                Thread.Sleep(2000);
                Console.WriteLine("eggs cooked");
            });
            return result;
        }

        public static async void CookBacons()
        {
            await Task.Run(() => {
                Thread.Sleep(2000);
                Console.WriteLine("bacons cooked");
            });
        }
        
        public static async void CookAny(string msg)
        {
            await Task.Run(() => {
                Thread.Sleep(2000);
                Console.WriteLine($"{msg} cooked!");
            });
        }
    }
}