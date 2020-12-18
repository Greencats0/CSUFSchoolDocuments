###Created by Jake Wong
###CWID 888879301

import pygame
import random

class Sort():
    def __init__(self):
        pygame.init()
        self.clock = pygame.time.Clock()
        self.running, self.sorting, self.sortEnd = True, False, False
        self.display = pygame.Surface((1280, 720))
        self.array = []
        self.BLACK = (0, 0, 0)
        self.speed = 10
        num = 256
        for i in range(num):
            self.array.append(random.randint(25, 500))
        self.width, self.height, = 1280, 720
    def display_Prompt(self):
        global color, color_light, color_dark, beginfont, screen
        while self.running:
            # white color
            color = (255, 255, 255)

            # light shade of the button
            color_light = (170, 170, 170)

            # dark shade of the button
            color_dark = (100, 100, 100)
            #font for the text
            beginfont = pygame.font.SysFont('Corbel', 35)
            #the display
            screen = pygame.display.set_mode((1280, 720))
            #the beginning text
            begintxt = beginfont.render("Press start to watch 256 random values between(25-500) sort via Mergesort", True, (255, 255, 255))
            #puts text on the screen
            screen.blit(begintxt, (130, 190))

            mouse = pygame.mouse.get_pos()

            #start button text
            starttxt = beginfont.render('START', True, color)

            #makes button light up when mouse goes over it
            if self.width/2 - 70 <= mouse[0] <= self.width/2 + 70 and self.height/2 <= mouse[1] <= self.height/2 + 40:
                pygame.draw.rect(screen, color_light, [self.width/2 - 70, self.height/2, 140, 40])
            else:
                pygame.draw.rect(screen, color_dark, [self.width/2 - 70, self.height/2, 140, 40])
            #makes text appear on screen
            screen.blit(starttxt, (self.width/2 - 50, self.height / 2 + 5))

            #gets the mouse click so button works
            for event in pygame.event.get():
                if event.type == pygame.MOUSEBUTTONDOWN:
                    # min button
                    if self.width/2 - 70 <= mouse[0] <= self.width/2 + 70 and self.height/2 <= mouse[1] <= self.height/2+40:
                        self.sorting = True
                        self.running = False
            #updates the entire screen
            pygame.display.flip()
    def visual_Sort(self):
        #begins the sort
        if self.sorting:
            self.mergeSort(self.array)
        #makes sure that the final sort is visualized
        self.visualize_values_final()
        #creates a button to quit the program
        while self.sorting:
            mouse = pygame.mouse.get_pos()
            if self.width/2 - 70 <= mouse[0] <= self.width/2 + 70 and self.height/2 <= mouse[1] <= self.height/2 + 40:
                pygame.draw.rect(screen, color_light, [self.width/2 - 70, self.height/2, 200, 40])
            else:
                pygame.draw.rect(screen, color_dark, [self.width/2 - 70, self.height/2, 200, 40])
            endtxt = beginfont.render('QUIT SORT?', True, color)
            screen.blit(endtxt, (self.width/2 - 60, self.height / 2 + 5))
            for event in pygame.event.get():
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if self.width/2 - 70 <= mouse[0] <= self.width/2 + 70 and self.height/2 <= mouse[1] <= self.height/2+40:
                        pygame.quit()
                        return
            pygame.display.flip()
    #the actual sorting program
    def mergeSort(self, arr):
        if len(arr) > 1:

            # Finding the mid of the array
            mid = len(arr) // 2

            # Dividing the array elements
            L = arr[:mid]

            # into 2 halves
            R = arr[mid:]

            # Sorting the first half
            self.mergeSort(L)

            # Sorting the second half
            self.mergeSort(R)

            i = j = k = 0
            # Copy data to temp arrays L[] and R[]
            while i < len(L) and j < len(R):
                if L[i] < R[j]:
                    arr[k] = L[i]
                    i += 1
                else:
                    arr[k] = R[j]
                    j += 1
                k += 1

            # Checking if any element was left
            while i < len(L):
                arr[k] = L[i]
                i += 1
                k += 1
            while j < len(R):
                arr[k] = R[j]
                j += 1
                k += 1
            #so you can see what it is doing on both sides
            self.visualize_values(L,R)

    #the visualization code
    def visualize_values(self, arr, arr2):
        pygame.event.pump()
        screen.fill(self.BLACK)
        lefttxt = beginfont.render('Left Sort', True, color)
        screen.blit(lefttxt, (250, 50))
        righttxt = beginfont.render('Right Sort', True, color)
        screen.blit(righttxt, (750, 50))
        for i in range(len(arr)):
            pygame.draw.rect(screen, color_light, [50+(i*3), 600-arr[i], 2, arr[i]])
        for i in range(len(arr2)):
            pygame.draw.rect(screen, color_light, [self.width/2 + 50 + (i * 3), 600 - arr2[i], 2, arr2[i]])
        pygame.display.flip()
        #sets the speed for how fast the sort updates
        self.clock.tick(self.speed)

    #the end sort visualization
    def visualize_values_final(self):
        pygame.event.pump()
        screen.fill(self.BLACK)
        for i in range(len(self.array)):
            pygame.draw.rect(screen, color_light, [50+(i*3), 600-self.array[i], 2, self.array[i]])
        pygame.display.flip()