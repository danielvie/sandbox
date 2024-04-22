// stating a new FuncByRef

namespace FuncByRef
{
    class Program
    {
        static void Main(string[] args)
        {
            CallMessageInt(CallInt1, 10);
            CallMessageInt(CallInt2, 20);
            
            CallMessageStr(CallStr1, "message for callstr1");
            CallMessageStr(CallStr2, "message for callstr2");
        }
        
        static void CallMessageInt(Action<int> func, int value)
        {
            func(value);
        }
        
        static void CallMessageStr(Action<string> func, string msg)
        {
            func(msg);
        }

        static void CallStr1(string msg)
        {
            Console.WriteLine($"CallStr1:: {msg}");
        }
        
        static void CallStr2(string msg)
        {
            Console.WriteLine($"CallMessageStr2:: {msg}");
        }
        
        static void CallInt1(int value)
        {
            int res = value + 10;
            Console.WriteLine($"CallMessageInt1:: value: {value}, value+10: {res}");
        }
        static void CallInt2(int value)
        {
            int res = value + 20;
            Console.WriteLine($"CallMessageInt2:: value: {value}, value+20: {res}");
        }
    }

}