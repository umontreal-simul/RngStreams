Initial states of g1, g2, and g3:

The current state of the Rngstream g1:
   Cg = { 12345, 12345, 12345, 12345, 12345, 12345 }

The current state of the Rngstream g2:
   Cg = { 3692455944, 1366884236, 2968912127, 335948734, 4161675175, 475798818 }

The current state of the Rngstream g3:
   Cg = { 1015873554, 1310354410, 2249465273, 994084013, 2912484720, 3876682925 }

State of g1 after advancing by 2^5 + 3 = 35 steps:
The current state of the Rngstream g1:
   Cg = { 1040577685, 3747037609, 277208355, 1712706441, 627445683, 2408037141 }

g1.RandU01 () = 0.07941673614985

State of g1 after reset and advancing 35 times by 1:
The current state of the Rngstream g1:
   Cg = { 1040577685, 3747037609, 277208355, 1712706441, 627445683, 2408037141 }

g1.RandU01 () = 0.07941673614985

State of g1 after reset and 35 calls to RandInt (1, 10):
The current state of the Rngstream g1:
   Cg = { 1040577685, 3747037609, 277208355, 1712706441, 627445683, 2408037141 }

   sum of 35 integers in [1, 10] = 186

g1.RandU01 () = 0.07941673614985

State of g1 after reset, IncreasedPrecis (true) and 17 calls to RandInt (1, 10):
The current state of the Rngstream g1:
   Cg = { 2633078466, 1040577685, 3747037609, 3152585150, 1712706441, 627445683 }

State of g1 after IncreasedPrecis (false) and 1 call to RandInt
The current state of the Rngstream g1:
   Cg = { 1040577685, 3747037609, 277208355, 1712706441, 627445683, 2408037141 }

State of g1 after reset, IncreasedPrecis (true) and 17 calls to RandU01:
The current state of the Rngstream g1:
   Cg = { 2633078466, 1040577685, 3747037609, 3152585150, 1712706441, 627445683 }

State of g1 after IncreasedPrecis (false) and 1 call to RandU01
The current state of the Rngstream g1:
   Cg = { 1040577685, 3747037609, 277208355, 1712706441, 627445683, 2408037141 }

Sum of first 100 output values from stream g3:
   sum = 53.98590159232


Reset stream g3 to its initial seed.
First 5 output values from stream g3:
0.7285097861965
0.9655872822837
0.9961841304801
0.1149884161813
0.9731454191297

Reset stream g3 to the next SubStream, 4 times.
First 5 output values from stream g3, fourth SubStream:
0.1734545396358
0.03286351608942
0.2643169129682
0.3059403602117
0.5476303035177

Reset stream g2 to the beginning of SubStream.
 Sum of 100000 values from stream g2 with double precision:   50098.22414959
 Sum of 100000 antithetic output values from stream g3:   50017.2231775

SetPackageSeed to seed = { 1, 1, 1, 1, 1, 1 }

Declare an array of 4 named streams and write their full state
The RngStream Poisson:
   anti = false
   incPrec = false
   Ig = { 1, 1, 1, 1, 1, 1 }
   Bg = { 1, 1, 1, 1, 1, 1 }
   Cg = { 1, 1, 1, 1, 1, 1 }

The RngStream Laplace:
   anti = false
   incPrec = false
   Ig = { 2662865579, 741857976, 4206142246, 3352832365, 2519202871, 655500294 }
   Bg = { 2662865579, 741857976, 4206142246, 3352832365, 2519202871, 655500294 }
   Cg = { 2662865579, 741857976, 4206142246, 3352832365, 2519202871, 655500294 }

The RngStream Galois:
   anti = false
   incPrec = false
   Ig = { 3784663252, 802042081, 160569404, 3391851556, 2150317468, 54240022 }
   Bg = { 3784663252, 802042081, 160569404, 3391851556, 2150317468, 54240022 }
   Cg = { 3784663252, 802042081, 160569404, 3391851556, 2150317468, 54240022 }

The RngStream Cantor:
   anti = false
   incPrec = false
   Ig = { 3276123839, 3170955788, 1470482105, 884064067, 1017894425, 16401881 }
   Bg = { 3276123839, 3170955788, 1470482105, 884064067, 1017894425, 16401881 }
   Cg = { 3276123839, 3170955788, 1470482105, 884064067, 1017894425, 16401881 }

Jump stream Galois by 2^127 steps backward
The current state of the Rngstream Galois:
   Cg = { 2662865579, 741857976, 4206142246, 3352832365, 2519202871, 655500294 }

--------------------------------------
Final Sum = 23.70532386289

