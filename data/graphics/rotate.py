# Rotate the player and change its jersey color
# (used during batch rendering)

import Blender
Blender.Load("player.blend")

import Blender
import math
import time

time.sleep(1)

rotadd = XX_DEGREE_XX * math.pi / 180

armature = Blender.Object.Get("Armature")
armature.rot.z = rotadd

gloves = Blender.Object.Get("Gloves")
gloves.layers = [XX_LAYER_XX]

material = Blender.Material.Get("Jersey")
material.rgbCol = [ XX_COLOR_XX ]

Blender.Save("playerXX_DEGREE_XX.blend", 1)

Blender.Quit()
