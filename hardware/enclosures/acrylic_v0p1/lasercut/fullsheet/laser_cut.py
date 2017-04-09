from __future__ import print_function
import sys
import os
from py2gcode import gcode_cmd
from py2gcode import cnc_laser

dxfFileName = sys.argv[1]

layerList = ['vector{0}'.format(i) for i in range(5)]

# Create full sheet cut job
prog = gcode_cmd.GCodeProg()
prog.add(gcode_cmd.GenericStart())
prog.add(gcode_cmd.Space())
param = {
        'fileName'    :  dxfFileName,
        'layers'      :  layerList,
        'dxfTypes'    :  ['CIRCLE','LINE','ARC'],
        'laserPower'  :  600,
        'feedRate'    :  25,
        'convertArcs' :  True,
        'startCond'   : 'minX',
        'direction'   : 'ccw',
        'ptEquivTol'  :  0.4e-3,
        }

vectorCut = cnc_laser.VectorCut(param)
prog.add(vectorCut)

prog.add(gcode_cmd.Space())
prog.add(gcode_cmd.End(),comment=True)

baseName, ext = os.path.splitext(dxfFileName)
ngcFileName = '{0}.ngc'.format(baseName)
print(ngcFileName)
prog.write(ngcFileName)

# Create cut jobs for each layer (split jobs)
for layer in layerList:
    prog = gcode_cmd.GCodeProg()
    prog.add(gcode_cmd.GenericStart())
    prog.add(gcode_cmd.Space())
    param = {
            'fileName'    :  dxfFileName,
            'layers'      :  [layer],
            'dxfTypes'    :  ['CIRCLE','LINE','ARC'],
            'laserPower'  :  600,
            'feedRate'    :  25,
            'convertArcs' :  True,
            'startCond'   : 'minX',
            'direction'   : 'ccw',
            'ptEquivTol'  :  0.4e-3,
            }
    
    vectorCut = cnc_laser.VectorCut(param)
    prog.add(vectorCut)
    
    prog.add(gcode_cmd.Space())
    prog.add(gcode_cmd.End(),comment=True)
    
    baseName, ext = os.path.splitext(dxfFileName)
    ngcFileName = '{0}_{1}.ngc'.format(baseName,layer)
    print(ngcFileName)
    prog.write(ngcFileName)
