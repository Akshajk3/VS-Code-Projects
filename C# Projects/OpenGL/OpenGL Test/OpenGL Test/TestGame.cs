using OpenGL_Test.GameLoop;
using static OpenGL.GL;
using GLFW;
using OpenGLTest.Rendering;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenGLTest.Rendering.Display;

namespace OpenGL_Test
{
    class TestGame : Game
    {

        public TestGame(int initalWindowWidth, int initalWindowHeight, string initialWindowTitle) : base(initalWindowWidth, initalWindowHeight, initialWindowTitle)
        {
            
        }

        protected override void Initialize()
        {
            
        }

        protected override void LoadContent()
        {
            
        }
        protected override void Update()
        {
            
        }

        protected override void Render()
        {
            glClearColor(MathF.Sin(GameTime.TotalElapsedSeconds), 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);

            Glfw.SwapBuffers(DisplayManager.Window);
        }

    }
}
