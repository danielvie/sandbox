
namespace QueueExample
{
    class Program
    {
        static void Main()
        {
            // FIFO data structure
            Queue<string> nameQueue = new Queue<string>();
            
            nameQueue.Enqueue("A");
            nameQueue.Enqueue("B");
            nameQueue.Enqueue("C");
            nameQueue.Enqueue("D");
            nameQueue.Enqueue("E");
            
            string d = nameQueue.Dequeue();
            string p = nameQueue.Peek();
            
            foreach(string name in nameQueue)
            {
                Console.WriteLine(name);
            }
            
            // LIFO data structure
            Stack<string> names = new Stack<string>();
            names.Push("A");
            names.Push("B");
            names.Push("C");
            names.Push("D");
            names.Push("E");

            string popName = names.Pop();
            string peekName = names.Peek();
            
            foreach(string name in names)
            {
                Console.WriteLine(name);
            }
            
            // LIST 
            List<string> nameList = new List<string>(new string[] {"a", "b", "c", "d", "e", "f", "g"});
            
            nameList.Remove("d");
            foreach (string el in nameList)
            {
                Console.WriteLine($"el: {el}");
            }
            
            Console.WriteLine("end of main");
            
            // DICTIONARY
            Dictionary<int, string> nameDict = new Dictionary<int, string>(){
                {1, "een"},
                {2, "twee"},
                {3, "drie"},
                {4, "vier"},
                {5, "vijf"},
                {6, "zes"}
            };
            
            foreach(KeyValuePair<int, string> el in nameDict)
            {
                Console.WriteLine($"id: {el.Key}, val: {el.Value}");
            }
            
        }
    }
}