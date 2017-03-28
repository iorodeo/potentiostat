"""
Creates an enclosure template
"""
from py2scad import *

mm2in = 1.0/25.4

# Inside dimensions
side_margin = 0.05
top_standoff_height = 1.0 
bot_standoff_height = 3.0/8.0 
pcb_thickness = 0.062


x = 5.0 + 2*side_margin
y = 3.5 + 2*side_margin
z = top_standoff_height + bot_standoff_height + pcb_thickness 

params = {
        'inner_dimensions'        : (x,y,z), 
        'wall_thickness'          : 3.0*mm2in, 
        'lid_radius'              : 0.1,  
        'top_x_overhang'          : 0.1,
        'top_y_overhang'          : 0.1,
        'bottom_x_overhang'       : 0.1,
        'bottom_y_overhang'       : 0.1, 
        'lid2front_tabs'          : (0.2,0.5,0.8),
        'lid2side_tabs'           : (0.25, 0.75),
        'side2side_tabs'          : (0.5,),
        'lid2front_tab_width'     : 0.75,
        'lid2side_tab_width'      : 0.75, 
        'side2side_tab_width'     : 0.5,
        'standoff_diameter'       : 0.25,
        'standoff_offset'         : 0.05,
        'standoff_hole_diameter'  : 0.116, 
        'hole_list'               : [],
        }

enclosure = Basic_Enclosure(params)
enclosure.make()

part_assembly = enclosure.get_assembly(
        explode=(0,0,0),
        show_front=True,
        show_top=True,
        show_standoffs=True,
        )
part_projection = enclosure.get_projection(show_ref_cube=False)

prog_assembly = SCAD_Prog()
prog_assembly.fn = 50
prog_assembly.add(part_assembly)
prog_assembly.write('enclosure_assembly.scad')

prog_projection = SCAD_Prog()
prog_projection.fn = 50
prog_projection.add(part_projection)
prog_projection.write('enclosure_projection.scad')
