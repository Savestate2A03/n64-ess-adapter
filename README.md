# n64-ess-adapter
if you want the most free ess ever or need to fix non-perfect diagonals. for arduino nano

# how to wire
* logic level converter for 3.3 / 5v for 3.3v n64/controller logic with 5v arduino
* hook up the data line for n64 on pin 8 (thru llc)
* hook up the data line for the controller on pin 10 (thru llc)
* power controller via 3.3v from n64
* hook all ground together

# how to set thresholds
set these values in the code to modify your thresholds. use an input viewer (like gz) to figure out where you want your ess position to be remapped to and where you want your max value to be remapped to. the included values are my own, feel free to modify to your liking. 
```
/* SET THESE TO CUSTOMIZE YOUR SETTINGS! */

   #define MY_ESS_POSITION 40
   #define MY_MAX_POSITION 62
```

# notes
the adapter runs at 16mhz and uses cycle based timings to get inputs. running at another speed will break things without heavy modification to the included libraries. because of this, the arduino requires 5v to function properly. you'll need to get a step-up adapter to step up the 3.3v to 5v from the n64.

(it's possible to modify the libraries, just takes some work. if you do this to avoid a step up and it works, please make a PR)
