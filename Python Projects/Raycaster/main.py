import pygame
import sys
import math

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BACKGROUND_COLOR = (76, 76, 76)
M_PI = 3.14159265358979323846

class Raycaster:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("VindelPyCaster")
        self.screen = pygame.display.set_mode((1024, 512))

        self.px = 130
        self.py = 400
        self.pa = 90
        self.pdx = math.cos(self.degToRad(self.pa))
        self.pdy = -math.sin(self.degToRad(self.pa))

        self.clock = pygame.time.Clock()

        #keys
        self.w = 0
        self.a = 0
        self.s = 0
        self.d = 0

        self.mapX = 8
        self.mapY = 8
        self.mapS = self.mapX * self.mapY
        self.map = [
            1, 1, 1, 1, 1, 1, 1, 1,
            1, 0, 1, 0, 0, 0, 0, 1,
            1, 0, 1, 0, 0, 0, 0, 1,
            1, 0, 1, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 1, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 1, 1, 1, 1, 1, 1, 1,
        ]

    def degToRad(self, a):
        return a*M_PI/180.0

    def FixAng(self, a):
        if a > 359:
            a -= 360
        if a < 0:
            a += 359
        return a

    def drawPlayer(self):
        color = (255, 255, 0)
        pygame.draw.circle(self.screen, color, (self.px, self.py), 4)
        pygame.draw.line(self.screen, color, (self.px, self.py),
                         (self.px + self.pdx * 20, self.py + self.pdy * 20))


    def run(self):
        while True:

            self.screen.fill(BACKGROUND_COLOR)
            self.draw()
            self.handleInput()

            if self.a == 1:
                self.pa += 5
                self.pa = self.FixAng(self.pa)
                self.pdx = math.cos(self.degToRad(self.pa))
                self.pdy = -math.sin(self.degToRad(self.pa))
            if self.d == 1:
                self.pa -= 5
                self.pa = self.FixAng(self.pa)
                self.pdx = math.cos(self.degToRad(self.pa))
                self.pdy = -math.sin(self.degToRad(self.pa))
            if self.w == 1:
                self.px += self.pdx*3
                self.py += self.pdy*3
            if self.s == 1:
                self.px -= self.pdx*3
                self.py -= self.pdy*3

            self.clock.tick(60)
            pygame.display.update()

    def draw(self):
        self.drawMap2D()
        self.drawPlayer()
        self.drawRays()

    def handleInput(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_a:
                    self.a = 1
                if event.key == pygame.K_d:
                    self.d = 1
                if event.key == pygame.K_w:
                    self.w = 1
                if event.key == pygame.K_s:
                    self.s = 1
            if event.type == pygame.KEYUP:
                if event.key == pygame.K_a:
                    self.a = 0
                if event.key == pygame.K_d:
                    self.d = 0
                if event.key == pygame.K_w:
                    self.w = 0
                if event.key == pygame.K_s:
                    self.s = 0


    def drawMap2D(self):
        x = 0
        y = 0
        xo = 0
        yo = 0
        color = BLACK
        for y in range(self.mapY):
            for x in range(self.mapX):
                if self.map[y * self.mapX + x] > 0:
                    color = WHITE
                else:
                    color = BLACK
                xo = x*self.mapS
                yo = y*self.mapS
                pygame.draw.rect(self.screen, color, pygame.Rect(xo + 1, yo + 1, self.mapS - 1, self.mapS - 1))

    def drawRays(self):
        pygame.draw.rect(self.screen, (0, 255, 255), pygame.Rect(526, 0, 1006, 160))
        pygame.draw.rect(self.screen, (0, 0, 255), pygame.Rect(526, 160, 1006, 320))

        r = 0
        mx = 0
        my = 0
        mp = 0
        dof = 0
        side = 0

        vx = 0
        vy = 0
        rx = 0
        ry = 0
        ra = 0
        xo = 0
        yo = 0
        disV = 0
        disH = 0

        ra = self.FixAng(self.pa + 30)

        for r in range(60):
            dof = 0
            side = 0
            disV = 100000
            Tan = math.tan(self.degToRad(ra))

            if math.cos(self.degToRad(ra)) > 0.001:
                rx = ((int(self.px) >> 6) << 6) + 64
                ry = (self.px - rx) * Tan + self.py
                xo = 64
                yo = -xo*Tan
            elif math.cos(self.degToRad(ra)) < -0.001:
                rx = ((int(self.px) >> 6) << 6) - 0.0001
                ry = (self.px - rx) * Tan + self.py
                xo = -64
                yo = -xo * Tan
            else:
                rx = self.px
                ry = self.py
                dof = 8

            while dof < 8:
                mx = int(rx) >> 6
                my = int(ry) >> 6
                mp = my * self.mapX + mx
                if mp > 0 and mp < self.mapX * self.mapY and self.map[mp] == 1:
                    dof = 8
                    disH = math.cos(self.degToRad(ra)) * (rx - self.px) - math.sin(self.degToRad(ra)) * (ry - self.py)
                else:
                    rx += xo
                    ry += yo
                    dof += 1

            vx = rx
            vy = ry

            dof = 0
            disH = 100000
            Tan = 1.0/Tan
            if math.sin(self.degToRad(ra)) > 0.001:
                ry = ((int(self.py) >> 6) << 6) - 0.0001
                rx = (self.py - ry) * Tan + self.px
                yo = -64
                xo = -yo * Tan
            elif math.sin(self.degToRad(ra)) < -0.001:
                ry = ((int(self.py) >> 6) << 6) + 64
                rx = (self.py - ry) * Tan + self.px
                yo = -64
                xo = -yo * Tan
            else:
                rx = self.px
                ry = self.py
                dof = 8

            while dof < 8:
                mx = int(rx) >> 6
                my = int(ry) >> 6
                mp = my * self.mapX + mx
                if mp > 0 and mp < self.mapX * self.mapY and self.map[mp] == 1:
                    dof = 8
                    disH = math.cos(self.degToRad(ra)) * (rx - self.px) - math.sin(self.degToRad(ra)) * (ry - self.py)
                else:
                    rx += xo
                    ry += yo
                    dof += 1

            color = (0, 204, 0)
            if disV < disH:
                rx = vx
                ry = vy
                disH = disV
                color = (0, 135, 0)
            pygame.draw.line(self.screen, color, (self.px, self.py), (rx, ry), 2)

            ca = self.FixAng(self.pa - ra)
            disH = disH * math.cos(self.degToRad(ca))
            lineH = (self.mapS * 320) / (disH)
            if lineH > 320:
                lineH = 320
            lineOff = 160 - (int(lineH) >> 1)

            pygame.draw.line(self.screen, color, (r * 8 + 530, lineOff), (r*8 + 530, lineOff + lineH), 8)

            ra = self.FixAng(ra - 1)


def main():
    raycaster = Raycaster()
    raycaster.run()

if __name__ == '__main__':
    main()