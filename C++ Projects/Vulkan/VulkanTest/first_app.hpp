#pragma once

#include "lve_window.hpp"

namespace lve
{
    class FirstApp
    {
    public:
        static const int WIDHT = 800;
        static const int HEIGHT = 800;

        void Run(){};
    private:
        LveWindow lveWindow{WIDTH, HEIGHT, "Test Vulkan Window"};
    };
}