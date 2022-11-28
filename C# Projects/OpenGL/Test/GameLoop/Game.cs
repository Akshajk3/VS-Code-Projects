using GLFW;
using OpenGLTest.Rendering.Display;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpenGL_Test.GameLoop
{
    abstract class Game
    {
        protected int InitalWindowWidth { get; set; }
        protected int InitalWindowHeight { get; set; }
        protected string InitialWindowTitle { get; set; }

        public Game(int initalWindowWidth, int initalWindowHeight, string initialWindowTitle)
        {
            InitalWindowWidth = initalWindowWidth;
            InitalWindowHeight = initalWindowHeight;
            InitialWindowTitle = initialWindowTitle;
        }


        public void Run()
        {
            Initialize();

            DisplayManager.CreateWindow(InitalWindowWidth, InitalWindowHeight, InitialWindowTitle);

            LoadContent();

            while(!Glfw.WindowShouldClose(DisplayManager.Window))
            {
                GameTime.DeltaTime = (float)Glfw.Time - GameTime.TotalElapsedSeconds;
                GameTime.TotalElapsedSeconds = (float)Glfw.Time;

                Update();

                Glfw.PollEvents();

                Render();
            }

            DisplayManager.CloseWindow();
        }

        protected abstract void Initialize();
        protected abstract void LoadContent();

        protected abstract void Update();
        protected abstract void Render();
    }
}
