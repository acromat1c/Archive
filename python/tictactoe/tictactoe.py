from raylib import *

class gameLogic():
    def __init__(self):
        init_window(800, 800, "The Gregorian laberynth of truth")
        init_audio_device()
        self.loadResources()
        self.main()
    def loadResources(self):
        self.objects = []
        self.GridImage = load_texture("grid.png")
        self.XImage = load_texture("X.png")
        self.OImage = load_texture("O.png")
    def main(self):
        while not window_should_close():
            self.controls()
            self.draw()
        close_window()
    def controls(self):
        if(is_mouse_button_pressed(MOUSE_BUTTON_LEFT)):self.objects.append([0,int(get_mouse_position().x-75),int(get_mouse_position().y-75)])
        elif(is_mouse_button_pressed(MOUSE_BUTTON_RIGHT)):self.objects.append([1,int(get_mouse_position().x-75),int(get_mouse_position().y-75)])
        elif(is_key_pressed(KEY_R)):self.objects=[]
    def draw(self):
        begin_drawing()
        clear_background(WHITE)
        draw_texture(self.GridImage,0,0,WHITE)
        for i in self.objects:
            if(i[0]==0):draw_texture(self.XImage,i[1],i[2],WHITE)
            else:draw_texture(self.OImage,i[1],i[2],WHITE)
        end_drawing()

play=gameLogic()