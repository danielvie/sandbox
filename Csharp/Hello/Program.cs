using System;

namespace hello
{
    class Program
    {
        public static void Main()
        {
            Guild guild = new Guild();
            MemberWelcomer welcomer = new MemberWelcomer();
            GuildHall hall = new GuildHall();
            
            guild.NewMemberAdded += welcomer.WelcomeMember;
            guild.NewMemberAdded += hall.AddBedroom;
            
            guild.AddMember("Daniel");
        }
    }
    
    public class Guild
    {

        private readonly List<string> _members = new List<string>();

        public event Action<string> NewMemberAdded;
        
        public void AddMember(string memberName)
        {
            _members.Add(memberName);
            
            NewMemberAdded?.Invoke(memberName);
        }
    }
    
    public class MemberWelcomer
    {
        public void WelcomeMember(string memberName)
        {
            Console.WriteLine($"Welcome {memberName}");
        }
    }
    
    public class GuildHall
    {
        public void AddBedroom(string memberName)
        {
            var bla = "dafsdafsdf";

            Console.WriteLine($"A room wa added to the gild hall for {memberName}");
        }
    }
}