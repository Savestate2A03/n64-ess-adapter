# n64-ess-adapter
if you want the most free ess ever or need to fix non-perfect diagonals. for arduino nano

# how to use
* hook up the data line for n64 on pin 8
* hook up the data line for the controller on pin 10
* step up 3.3v from n64 to 5v for arduino
* power controller via 3.3v from n64
* hook all ground together

# notes
the adapter runs at 16mhz and uses cycle based timings to get inputs. running at another speed will break things without heavy modification to the included libraries. because of this, the arduino requires 5v to function properly. you'll need to get a step-up adapter to step up the 3.3v to 5v from the n64.

(it's possible to modify the libraries, just takes some work. if you do this to avoid a step up and it works, please make a PR)
