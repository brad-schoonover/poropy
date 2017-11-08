"""
This script illustrates how a user can define a thermal model on the 
Python side. The model implemented is identical to the base model implemented
on the C++ side.

The value of this capability is that users can easily test new models, or
users could couple to other packages.
"""

import numpy as np
import matplotlib.pyplot as plt
from poropy_core import *

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

# make data model
model = SimpleDataModel()

class ThermalModel(BaseThermalModel) :
    
    def __init__(self, db, core) :
        super(ThermalModel, self).__init__(db, core)
        self.db = db
        self.core = core
        self.h = 30000.0
        self.cp = 5500.0
        self.mdot = 88.00
        self.T_inlet = 563.0
    
    def compute_temperatures(self, powers, burnups, T_F, T_M) :
        # active height, m
        height = self.core.height() / 100.0
        for i in range(self.core.number_assemblies()) :
            B = burnups[i];
            # assembly index
            p = self.core.pattern(i)
            # fuel, inner / outer cladding, and effective gap radii
            r_f = core.assembly(p).fuel_radius() / 100
            r_ci = core.assembly(p).cladding_inner_radius() / 100
            r_co = core.assembly(p).cladding_outer_radius() / 100
            r_g = 0.5 * (r_ci + r_f);
            # average linear heat generation rate, W/m
            qp_avg = 1.e9 * powers[i] / height
            # axial-averaged moderator temperature
            T_M[i] = self.T_inlet + 0.5 * qp_avg * height / (self.mdot * self.cp)
            # cladding average temperate (K) and thermal conductivity W/m.K
            T_C = 0.88 * T_M[i] + 0.12 * T_F[i]
            k_C = self.cladding_conductivity(T_C)
            # gap conductance, W/m^2.K
            h_g = self.gap_conductance(B)
            # effective non-fuel thermal conductivity, W/m.K
            k_NF = 2.0*np.pi / \
                   (1.0/h_g/r_g + np.log(r_co/r_ci)/k_C + 1./r_co/self.h)
            # fuel thermal conductivity, W/m.K
            k_F = self.fuel_conductivity(T_F[i], B)
            # average pin linear heat generation rate, W/m
            qp_pin = qp_avg / self.core.assembly(p).number_pins()
            # axially- and radially-averaged fuel temperature
            T_F[i] = qp_pin * (0.125/np.pi/k_F + 1.0/k_NF) + T_M[i]
     
    def fuel_conductivity(self, T_F, B) :
        return 0.0118340600386467*B + \
               2.10223405878539e-14*T_F**4 + \
               3923.09098668336/(154.72261735884+T_F+20.8225739516707*B) - \
               2.03748805095159e-6 * T_F*B - 4.19053096725081e-5*B**2
               
    def cladding_conductivity(self, T_C) :
        return 7.511 + 2.088e-2 * T_C - 1.45e-5 * T_C * T_C + 7.668e-9 * T_C * T_C * T_C
    
    def gap_conductance(self, B) :
        h = 0.6 + 0.5 * B / 30;
        if B >= 30.0 :
            h = 1.1;
        h *= 100000.
        return h * 10000.0;
                
TH = ThermalModel(db, core)
solver = FlareSolver(db, core, model, 3.400)
solver.set_burnup_steps(list(np.ones(30)*1.0))
solver.set_temperatures([900.0]*49, [580.0]*49)
solver.set_thermal_model(TH)
solver.solve()
exit()
