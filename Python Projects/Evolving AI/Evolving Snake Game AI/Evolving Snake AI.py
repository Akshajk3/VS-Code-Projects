import pygame
import torch
import random
from tkinter import Tk, messagebox
import os
import sys
pygame.init()

SCREEN_WIDTH = 500
SCREEN_HEIGTH = 500
SCREEN = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGTH))
pygame.display.set_caption("Evolving Snake AI")

