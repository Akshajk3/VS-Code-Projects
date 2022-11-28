using OpenGL_Test;
using OpenGL_Test.GameLoop;


namespace OpenGLTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Game game = new TestGame(800, 600, "Test Game");
            game.Run();
        }
    }
}