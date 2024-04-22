

using System.Collections;

class Program
{
    static void Main(string[] args)
    {
        
        // creating dictionary
        Dictionary<string, Object> D = new Dictionary<string, object>();
        Dictionary<string, Object> R = new Dictionary<string, object>();
        
        D["bla"] = "dafsdfads";
        D["ble"] = "dafsdfads";


        R["rla"] = "rrr1";
        R["rle"] = "rrr2";
        R["rli"] = "rrr3";
        R["rlo"] = "rrr4";


        D["bli"] = R;
        D["blo"] = "dafsdfads";
        D["blu"] = "dafsdfads";
        
        foreach(var d in D)
        {
            Console.WriteLine($"key: {d.Key}, value: {d.Value}");
        }

        Node node = new Node("daniel");
        node.Show();
        Console.WriteLine("mado");
    }
    
    static bool IsDictionary(object o)
    {
        if(o == null) return false;
        // return o is IDictionary &&
        //    o.GetType().IsGenericType &&
        //    o.GetType().GetGenericTypeDefinition().IsAssignableFrom(typeof(Dictionary<,>));
        return o is Dictionary<string, object>;
    }
};

class Node
{
    private string mValue = "";
    public Node(string value)
    {
        mValue = value;
    }
    
    public void Show()
    {
        Console.WriteLine($"meu valor eh: {mValue}");
    }
}
