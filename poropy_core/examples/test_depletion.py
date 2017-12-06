"""
This script sets up a simple, three-batch core and estimates the 
core fuel temperature coefficient.
"""

import numpy as np
import matplotlib.pyplot as plt
from poropy_core.src.poropy_core import Core, SimpleDataModel, FlareSolver, Assembly, ParamDB

stencil = [[  0,  1,  2,  3,  4,  5,  6,  7, -1],
           [ -2,  8,  9, 10, 11, 12, 13, 14, -1],
           [ -2, 15, 16, 17, 18, 19, 20, 21, -1],
           [ -2, 22, 23, 24, 25, 26, 27, 28, -1],
           [ -2, 29, 30, 31, 32, 33, 34, -1, -1],
           [ -2, 35, 36, 37, 38, 39, 40, -1, -1],
           [ -2, 41, 42, 43, 44, 45, -1, -1, -1],
           [ -2, 46, 47, 48, -1, -1, -1, -1, -1],
           [ -1, -1, -1, -1, -1, -1, -1, -1, -1]]

# core 
core = Core(stencil, 21.0)
core.build()

bu = [30.0, 15.0,  0.0, 30.0,  0.0, 15.0, 30.0, 30.0, 15.0, 30.0,  0.0, 15.0,
      15.0,  0.0, 30.0, 30.0,  0.0, 15.0, 15.0,  0.0,  0.0, 30.0,  0.0, 15.0,
      15.0, 15.0, 15.0,  0.0, 30.0, 15.0, 15.0, 15.0, 15.0,  0.0, 30.0, 15.0,
       0.0, 15.0,  0.0,  0.0, 30.0,  0.0,  0.0,  0.0, 30.0, 30.0, 30.0, 30.0,
      30.0]

# assemblies 
assemblies = []
for i in range(49) :
    assemblies.append(Assembly(i, 0, 0.5, bu[i]))
core.add_assemblies(assemblies)

db = ParamDB()
db.put_dbl("mixing_factor", 0.98);
db.put_dbl("albedo_one_side", 0.0);
db.put_dbl("albedo_two_side", 0.0);
db.put_int("burnup_option", FlareSolver.CYCLE_LENGTH);
db.put_int("critical_boron", 1);
db.put_int("thermal_hydraulics", 1)

model = SimpleDataModel()
solver = FlareSolver(db, core, model, 3.400)
solver.set_burnup_steps(list(np.ones(30)*1.0))

TF1 = 900.0
solver.set_temperatures([TF1]*49, [580.]*49)
# solver.solve_steady_state()
# 
# print solver.moderator_temperature()
# 
# T=np.asarray(solver.fuel_temperature())
# mean_T = (T[0] + 4*sum(T[1:]))/193.
# print T
# print "mean T = ", mean_T
# print solver.keff()
# exit('lala')

solver.solve()
#print((solver.fuel_temperature()))
#print((solver.moderator_temperature()))
print("finish import")

#exit()


#keff1 = solver.cycle_keff(); 
#bu1 = solver.cycle_core_burnup()
#mappf1 = solver.cycle_max_appf()
#boron1 = solver.cycle_boron()
#print((solver.fuel_temperature()))
#plt.figure(1)
#plt.plot(bu1, keff1)

#exit('lala')

#TF2 = 950.0
#solver.set_temperatures([TF2]*49, [580.]*49)
#solver.solve_cycle()
#keff2 = solver.cycle_keff(); 
#bu2 = solver.cycle_core_burnup()
#mappf2 = solver.cycle_max_appf()
#boron2 = solver.cycle_boron()
#plt.figure(2)
#plt.plot(bu2, keff2)

#plt.figure(3)
#alpha = 1.e5 * 1./np.array(keff1) * (np.array(keff2)-np.array(keff1))/(TF2-TF1)
#plt.plot(bu1, alpha)
#plt.xlabel('burnup (GWd/MTU)')
#plt.ylabel('$\\alpha^F_T$ (pcm/K)')
#plt.grid(True)
#plt.show()
