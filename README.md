# halla_online_beam_check

ROOT scripts to monitor the beam quality for experiments in Hall A

## Beam Monitoring

Code specific to a given beam component is located in its own directory. Inside each 
directory is an associated ROOT macro and bash script that will call the macro with 
appropriate input parameters.  This bash script is to be installed to `~/bin/Linux/` 
so that it is available from any location on the machine. For example, to examine 
raster data, see the directory `raster`.  

## Custom Libraries 

When writing a custom library that links to the Analyzer, put it in the 
directory `customLibrary`.  For an example, see the `~/customLibrary/FadcRasteredBeam` module. 


