import pygame
import math

#initialize pygame package
pygame.init()
fps = 60 # frame rate
timer = pygame.time.Clock() # create timer
font = pygame.font.Font('assets/font/myFont.ttf', 32) # '.Font' creates a new Font object from a file ('filepath', size/height)
big_font = pygame.font.Font('assets/font/myFont.ttf', 60)
# screen width and height
WIDTH = 900
HEIGHT = 800
screen = pygame.display.set_mode([WIDTH, HEIGHT])
bgs = [] # backgrounds
banners = []
guns = []
target_images = [[],[],[]] # list of targets for each level
targets = {1: [10, 5, 3],
           2: [12, 8, 5],
           3: [15, 12, 8, 3]} # dictionary to look up how many of each tier of enemy to put in each level
level = 0
points = 0
total_shots = 0
mode = 0 # game modes: 0 -> freeplay, 1 -> accuracy, 2 -> timed
ammo = 0
time_passed = 0
time_remaining = 0
counter = 1
best_freeplay = 0
best_ammo = 0
best_timed = 0
shot = False
menu = True
game_over = False
pause = False
clicked = False
write_values = False
new_coords = True
# target/enemy coordinates
one_coords = [[], [], []]
two_coords = [[], [], []]
three_coords = [[], [], [], []]
menu_img = pygame.image.load(f'assets/menus/mainMenu.png')
game_over_img = pygame.image.load(f'assets/menus/gameOver.png')
pause_img = pygame.image.load(f'assets/menus/pause.png')
# load images
for i in range(1, 4): # level 1 to 3
    bgs.append(pygame.image.load(f'assets/bgs/{i}.png')) # grab backgrounds 1, 2, and 3
    banners.append(pygame.image.load(f'assets/banners/{i}.png')) # grab banners 1, 2, and 3
    guns.append(pygame.transform.scale(pygame.image.load(f'assets/guns/{i}.png'), (100, 100))) # grab guns 1, 2, and 3
    if i < 3: # grab targets level 1 and 2
        for j in range(1, 4):
            # scale targets by level - higher the level, smaller the target
            target_images[i - 1].append(pygame.transform.scale(pygame.image.load(f'assets/targets/{i}/{j}.png'), (120 - (j*18), 80 - (j*12))))
    else: # grab target level 3
        for j in range(1, 5):
            target_images[i - 1].append(pygame.transform.scale(pygame.image.load(f'assets/targets/{i}/{j}.png'), (120 - (j*18), 80 - (j*12))))

file = open('high_scores.txt', 'r') # collect scores
read_file = file.readlines() # get list of scores
file.close()
best_freeplay = int(read_file[0]) # first line is freeplay (mode 1) score
best_ammo = int(read_file[1]) # second line is best ammo (mode 2) score
best_timed = int(read_file[2]) # third line is best timed (mode 3) score

# set sound
pygame.mixer.init()
pygame.mixer.music.load('assets/sounds/bg_music.mp3') # youtubes royalty free library
plate_sound = pygame.mixer.Sound('assets/sounds/Broken plates.wav')
plate_sound.set_volume(.5)
bird_sound = pygame.mixer.Sound('assets/sounds/Drill Gear.mp3')
bird_sound.set_volume(.5)
laser_sound = pygame.mixer.Sound('assets/sounds/Laser Gun.wav')
laser_sound.set_volume(.7)
pygame.mixer.music.play()

# draw score board on banner on bottom of screen
def draw_score():
    points_text = font.render(f'Points: {points}', True, 'black')
    screen.blit(points_text, (320, 660))
    shots_text = font.render(f'Total Shots: {total_shots}', True, 'black')
    screen.blit(shots_text, (320, 687))
    time_text = font.render(f'Time Elapsed: {time_passed}', True, 'black')
    screen.blit(time_text, (320, 714))
    if mode == 0:
        mode_text = font.render(f'Freeplay!', True, 'black')
    if mode == 1:
        mode_text = font.render(f'Ammo Remaining: {ammo}', True, 'black')
    if mode == 2:
        mode_text = font.render(f'Time Remaining: {time_remaining}', True, 'black')
    screen.blit(mode_text, (320, 741))

# draw gun to screen with rotating movement
def draw_gun():
    mouse_pos = pygame.mouse.get_pos()
    gun_point = (WIDTH/2, HEIGHT - 200) # gun will be at top middle of banner
    lasers = ['red', 'purple', 'green'] # mathes colors of the guns for each level
    clicks = pygame.mouse.get_pressed() # returns a list that tells left mouse button, scroll wheel click, and right mouse button
    if mouse_pos[0] != gun_point[0]: # mouse is anywhere but middle of screen
        slope = (mouse_pos[1] - gun_point[1])/(mouse_pos[0] - gun_point[0]) # calculate slope of line from mouse position through gun position (y2 - y1)/(x2 - x1)
    else: # mouse is directly in line vertically with gun
        slope = -100000 # can't be zero, closest can be to infinity
    angle = math.atan(slope)# angle slope corelates with. inverse tangent of a slope of a line tells you angle between horizontal axis and the line (radians)
    rotation = math.degrees(angle) # convert to degrees
    
    if mouse_pos[0] < WIDTH/2: # x coordinate of mouse is on left side of screen/gun 
        gun = pygame.transform.flip(guns[level - 1], True, False) # flip orientation of gun horizontally when mouse on left side of it
        if mouse_pos[1] < 600: # > 600 is the menu, don't want to be shooting when mouse on menu
            screen.blit(pygame.transform.rotate(gun, 90 - rotation), (WIDTH/2 - 90, HEIGHT - 250)) 
            if clicks[0]:
                pygame.draw.circle(screen, lasers[level - 1], mouse_pos, 5) # gun shot circle with radius 5
    else:
        gun = guns[level - 1] # don't need to rotate when mouse on right side of gun
        if mouse_pos[1] < 600:
            screen.blit(pygame.transform.rotate(gun, 270 - rotation), (WIDTH/2 - 30, HEIGHT - 250)) # flip it
            if clicks[0]:
                pygame.draw.circle(screen, lasers[level - 1], mouse_pos, 5)
    
# get targets to move
def move_level(coords):
    if level == 1 or level == 2:
        max_val = 3
    else:
        max_val = 4
    
    for i in range(max_val):
        for j in range(len(coords[i])):
            my_coords = coords[i][j]
            if my_coords[0] < -150: # if target got off screen to left
                coords[i][j] = (WIDTH, my_coords[1]) # move over to the right. keep cycling till target is clicked/shot
            else: # if on screen, move to left based on enemy tier
                coords[i][j] = (my_coords[0] - 2**i, my_coords[1]) # speed of target movement based on tier

    return coords

# draw targets to screen
def draw_level(coords):
    if level == 1 or level == 2:
        target_rects = [[], [], []]
    else: # level 3
        target_rects = [[], [], [], []]

    for i in range(len(coords)): # iterate through number of tiers, 3 or 4
        for j in range(len(coords[i])): # iterate through number of enemies of tier. 
            # append rectangles where targets are for collision detection. will get smaller with enemies
            target_rects[i].append(pygame.rect.Rect((coords[i][j][0] + 20, coords[i][j][1]), (60 - i*12, 60 - i*12)))
            screen.blit(target_images[level - 1][i], coords[i][j]) # draw image onto screen at its coordinate
    
    return target_rects

# check if target shot
def check_shot(targets, coords):
    # check to see if rectangular boxes in target list is clicked, if hit then delete coordinate for that enemy in coordinates list
    # track enemies left in coordinates list
    global points
    mouse_pos = pygame.mouse.get_pos()
    for i in range(len(targets)):
        for j in range(len(targets[i])):
            if targets[i][j].collidepoint(mouse_pos): # target hit?
                coords[i].pop(j) # delete target coordinate from list
                points += 10 + 10 * (i**2) # level 1 -> 10pts, level 2 -> 20pts, level 3 -> 50pts, level 4 -> 100pts
                # play sounds when targets shot
                if level == 1:
                    bird_sound.play()
                elif level == 2:
                    plate_sound.play()
                else:
                    laser_sound.play()

    return coords # new updated list of targets on screen

# draw menu
def draw_menu():
    global game_over, pause, mode, level, menu, time_passed, total_shots, points, ammo
    global time_remaining, best_freeplay, best_ammo, best_timed, write_values, clicked, new_coords
    game_over = False
    pause = False
    screen.blit(menu_img, (0, 0))
    mouse_pos = pygame.mouse.get_pos()
    clicks = pygame.mouse.get_pressed()

    freeplay_button = pygame.rect.Rect((170, 524), (260, 100)) # define rectangle space for collision detection
    screen.blit(font.render(f'{best_freeplay}', True, 'black'), (340, 580))
    ammo_button = pygame.rect.Rect((475, 524), (260, 100))
    screen.blit(font.render(f'{best_ammo}', True, 'black'), (650, 580))
    timed_button = pygame.rect.Rect((170, 661), (260, 100))
    screen.blit(font.render(f'{best_timed}', True, 'black'), (350, 710))
    reset_button = pygame.rect.Rect((475, 661), (260, 100))
    
    # prevent unwanted double clicking
    if freeplay_button.collidepoint(mouse_pos) and clicks[0] and not clicked: # left click and lifted mouse on button
        mode = 0
        level = 1
        menu = False
        time_passed = 0
        total_shots = 0
        points = 0
        clicked = True
        new_coords = True
    if ammo_button.collidepoint(mouse_pos) and clicks[0] and not clicked:
        mode = 1
        level = 1
        menu = False
        time_passed = 0
        ammo = 81 # targets total in game
        total_shots = 0
        points = 0
        clicked = True
        new_coords = True
    if timed_button.collidepoint(mouse_pos) and clicks[0] and not clicked:
        mode = 2
        level = 1
        menu = False
        time_remaining = 30 
        time_passed = 0
        total_shots = 0
        points = 0
        clicked = True
        new_coords = True
    if reset_button.collidepoint(mouse_pos) and clicks[0] and not clicked:
        best_freeplay = 0
        best_ammo = 0
        best_timed = 0
        clicked = True
        write_values = True # overwrite textfile

# draw game over
def draw_game_over():
    global clicked, level, pause, game_over, menu, points, total_shots, time_passed, time_remaining
    if mode == 0:
        display_score = time_passed
    else:
        display_score = points
    screen.blit(game_over_img, (0, 0))
    mouse_pos = pygame.mouse.get_pos()
    clicks = pygame.mouse.get_pressed()
    exit_button = pygame.rect.Rect((170, 661), (260, 100))
    menu_button = pygame.rect.Rect((475, 661), (260, 100))
    screen.blit(big_font.render(f'{display_score}', True, 'black'), (650, 570))
    if menu_button.collidepoint(mouse_pos) and clicks[0] and not clicked: # go back to menu, reset 
        clicked = True
        level = 0
        pause = False
        game_over = False
        menu = True
        points = 0
        total_shots = 0
        time_passed = 0
        time_remaining = 0
    if exit_button.collidepoint(mouse_pos) and clicks[0] and not clicked:
        global run
        run = False # close out application

# draw pause
def draw_pause():
    global level, pause, menu, points, total_shots, time_passed, time_remaining, clicked, new_coords
    screen.blit(pause_img, (0, 0))
    mouse_pos = pygame.mouse.get_pos()
    clicks = pygame.mouse.get_pressed()
    resume_button = pygame.rect.Rect((170, 661), (260, 100))
    menu_button = pygame.rect.Rect((475, 661), (260, 100))

    if resume_button.collidepoint(mouse_pos) and clicks[0] and not clicked: # left click and lifted mouse on button
        level = resume_level
        pause = False
        clicked = True
    if menu_button.collidepoint(mouse_pos) and clicks[0] and not clicked:
        pygame.mixer.music.play()
        level = 0
        pause = False
        menu = True
        points = 0
        total_shots = 0
        time_passed = 0
        time_remaining = 0
        clicked = True
        new_coords = True





# play game
run = True
while run: 
    timer.tick(fps) # make loop run at 60 fps, creates delay to meet target frame rate

    if level != 0:
        if counter < 60:
            counter += 1
        else:
            counter = 1
            time_passed += 1
            if mode == 2:
                time_remaining -= 1

    
    if new_coords: # set or reset target coordinates 
        # initialize enemy coordinates for each level
        one_coords = [[], [], []]
        two_coords = [[], [], []]
        three_coords = [[], [], [], []]
        for i in range(3): # 3 different enemy tiers for level 1
            my_list = targets[1] # [10, 5, 3]
            for j in range(my_list[i]): # each target per tier spaced equally on screen
                one_coords[i].append((WIDTH//(my_list[i]) * j, 300 - (i*150) + 30 * (j%2))) # targets per tier spaced based on level 
        for i in range(3):
            my_list = targets[2] # [12, 8, 5]
            for j in range(my_list[i]):
                two_coords[i].append((WIDTH//(my_list[i]) * j, 300 - (i*150) + 30 * (j%2)))
        for i in range(4):
            my_list = targets[3] # [15, 12, 8, 3]
            for j in range(my_list[i]):
                three_coords[i].append((WIDTH//(my_list[i]) * j, 300 - (i*100) + 30 * (j%2)))
        
        new_coords = False


    screen.fill('black') # background color black as default
    # background and banner match at each level
    screen.blit(bgs[level - 1], (0, 0)) # put banner for each level in background at top left corner (source, dest/coordinates)
    screen.blit(banners[level - 1], (0, HEIGHT - 200)) # banner is 200 pixels up from bottom

    if menu:
        level = 0
        draw_menu()
    if game_over:
        level = 0
        draw_game_over()
    if pause:
        level = 0
        draw_pause()

    if level == 1:
        target_boxes = draw_level(one_coords)
        one_coords = move_level(one_coords) # coordinates replaced 
        if shot:
            one_coords = check_shot(target_boxes, one_coords)
            shot = False
    elif level == 2:
        target_boxes = draw_level(two_coords)
        two_coords = move_level(two_coords)
        if shot:
            two_coords = check_shot(target_boxes, two_coords)
            shot = False
    elif level == 3:
        target_boxes = draw_level(three_coords)
        three_coords = move_level(three_coords)
        if shot:
            three_coords = check_shot(target_boxes, three_coords)
            shot = False

    if level > 0:
        draw_gun()
        draw_score()

    for event in pygame.event.get(): # check each user interaction
        if event.type == pygame.QUIT: # if red X button in top right corner is clicked
            run = False # end loop

        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1: # left click
            mouse_position = pygame.mouse.get_pos()
            if (0 < mouse_position[0] < WIDTH) and (0 < mouse_position[1] < HEIGHT - 200):
                shot = True
                total_shots += 1
                if mode == 1:
                    ammo -=1
            if (670 < mouse_position[0] < 860) and (660 < mouse_position[1] < 715): # if pause clicked on bottom menu
                resume_level = level # store level currently on 
                pause = True
                clicked = True
            if (670 < mouse_position[0] < 860) and (715 < mouse_position[1] < 760): # if restart clicked on bottom menu
                menu = True 
                pygame.mixer.music.play()
                clicked = True
                new_coords = True
        if event.type == pygame.MOUSEBUTTONUP and event.button == 1 and clicked:
            clicked = False


    # when level over
    if level > 0:
        if target_boxes == [[], [], []] and level < 3: # empty list
            level += 1
        # game over? 
        if (level == 3 and target_boxes == [[], [], [], []]) or (mode == 1 and ammo == 0) or (mode == 2 and time_remaining == 0):
            new_coords = True
            pygame.mixer.music.play()
            if mode == 0:
                if time_passed < best_freeplay or best_freeplay == 0: # check for best score
                    best_freeplay = time_passed
                    write_values = True # overwrite in textfile
            if mode == 1:
                if points > best_ammo:
                    best_ammo = points
                    write_values = True
            if mode == 2:
                if points > best_timed:
                    best_timed = points
                    write_values = True
            game_over = True
            
    if write_values:
        file = open('high_scores.txt', 'w')
        file.write(f'{best_freeplay}\n{best_ammo}\n{best_timed}')
        file.close()
        write_values = False



    pygame.display.flip() # get everything onto the screen

pygame.quit() # close program