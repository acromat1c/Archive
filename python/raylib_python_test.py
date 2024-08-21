from pyray import *

class player:
    def __init__(self,x,y,speed):
        self.x = x
        self.y = y
        self.speed = speed

    def input(self):
        if(is_key_down(KEY_S)):self.y += self.speed * get_frame_time()
        if(is_key_down(KEY_W)):self.y -= self.speed * get_frame_time()
        if(is_key_down(KEY_D)):self.x += self.speed * get_frame_time()
        if(is_key_down(KEY_A)):self.x -= self.speed * get_frame_time()

player1 = player(300,300,50)

init_window(800, 800, "Hello")
while not window_should_close():
    player1.input()
    begin_drawing()
    clear_background(BLUE)
    draw_grid(50,50)
    if(is_mouse_button_down(MOUSE_BUTTON_LEFT)):
        draw_circle(int(get_mouse_position().x),int(get_mouse_position().y),25,GREEN)
    end_drawing()
close_window()