#!/bin/bash
# 
# Macro that use G4 particle gun to create two particles 
# per event. 

COUNT="10"
source ${DETSIMROOT}/cmt/setup.sh

MACRO=`mktemp -t detsim.XXXXXXXXXX` || exit 1
cat >> $MACRO <<EOF
/dsim/control baseline 1.0
/dsim/update

# Make sure that the GPS generator is it's default state.
/gps/source/clear

# Enable generating multiple particle guns per event.
/gps/source/multiplevertex true

#######################################
# Create the first particle source
#######################################
/gps/source/add 1

# This source will be used to specify the position of the vertex.  The
# any of the GPS direction and energy commands can be used.
/gps/particle mu+
/gps/energy 600 MeV

# This generates the position of the first particle gun.  It will be
# used for the other particle guns.  The /gps/position command must
# come first.
/gps/position 0.0 0.0 0.0 cm
/gps/pos/type Volume
/gps/pos/shape Para
/gps/pos/halfx 50 cm
/gps/pos/halfy 50 cm
/gps/pos/halfz 10 cm

# This generates the direction of the first particle gun.  This aims
# the particle downstream with the directions uniformly distributed in
# a 45 deg cone.
/gps/ang/type iso
/gps/ang/maxtheta 45 deg
/gps/ang/rot1 -1 0 0 
/gps/ang/rot2  0 1 0

#########################################
# Create the second particle source.
#########################################
/gps/source/add 2
/gps/particle mu-
/gps/energy 500 MeV

# This generates the direction of the second particle gun.  This aims
# the particle downstream with the directions uniformly distributed in
# a 45 deg cone.
/gps/ang/type iso
/gps/ang/maxtheta 45 deg
/gps/ang/rot1 -1 0 0 
/gps/ang/rot2  0 1 0

# Create the GPS particle generator so it exists.  This isn't necessary for a
# single particle generator since DETSIM will create it by default,
# but it must be done explicitly when generating multiple GPS
# particles
/generator/add

# The GPS particles will be created like a "stack".  The combine
# command takes the last two particles and combines them into a single
# vertex.  If you have more than two particles, you can use multiple
# combine commands until you get a single vertex.
/generator/combine

/run/beamOn ${COUNT}

EOF

OUTPUT=detsim-double-particle-gun

if [ -f $OUTPUT ]; then
    rm $OUTPUT
fi

DETSIM.exe -o $OUTPUT $MACRO 

rm $MACRO
