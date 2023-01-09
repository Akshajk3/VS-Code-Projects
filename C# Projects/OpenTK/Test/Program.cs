using System;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            using(Game game = new Game())
            {
                game.Run();
            }
        }
    }
}