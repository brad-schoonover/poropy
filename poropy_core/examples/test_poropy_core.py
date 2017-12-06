import numpy as np

from poropy_core import *


""" Make the biblis problem """
stencil = [[ 0, 7, 1, 5, 0, 6, 0, 3,-1],
           [-2, 0, 7, 1, 7, 0, 0, 3,-1],
           [-2, 7, 0, 7, 1, 6, 0, 3,-1],
           [-2, 1, 7, 1, 7, 0, 7, 3,-1],
           [-2, 7, 1, 7, 1, 4, 3,-1,-1],
           [-2, 0, 6, 0, 4, 3, 3,-1,-1],
           [-2, 0, 0, 7, 3, 3,-1,-1,-1],
           [-2, 3, 3, 3,-1,-1,-1,-1,-1],
           [-1,-1,-1,-1,-1,-1,-1,-1,-1]]
# types
types = [0, 7, 1, 5, 0, 6, 0, 3, 
            0, 7, 1, 7, 0, 0, 3 , 
            7, 0, 7, 1, 6, 0, 3,
            1, 7, 1, 7, 0, 7, 3, 
            7, 1, 7, 1, 4, 3, 
            0, 6, 0, 4, 3, 3, 
            0, 0, 7, 3, 3, 
            3, 3, 3]

# core 
core = Core(stencil, 23.1226)
core.build()
pattern = []
for i in range(0, 49) :
    pattern.append(i)
core.set_pattern(pattern)

# assemblies 
assemblies = []
for i in range(49) :
    assemblies.append(Assembly(i, types[i], 0.0, 0.0))
    #core.add_assembly(assemblies[i])
core.add_assemblies(assemblies)

# setting reflector to zeros; keeping the indexing.
d1 = [1.4360000,1.4366000,0.0,1.4389000,1.4381000,1.4385000,1.4389000,1.4393000]
d2 = [0.3635000,0.3636000,0.0,0.3638000,0.3665000,0.3665000,0.3679000,0.3680000]
r1 = [0.0272582,0.0272995,0.0,0.0274640,0.0272930,0.0273240,0.0272900,0.0273210]
a2 = [0.0750580,0.0784360,0.0,0.0914080,0.0848280,0.0873140,0.0880240,0.0905100]
f1 = [0.0058708,0.0061908,0.0,0.0074527,0.0061908,0.0064285,0.0061908,0.0064285]
f2 = [0.0960670,0.1035800,0.0,0.1323600,0.1035800,0.1091100,0.1035800,0.1091100]
s12= [0.0177540,0.0176210,0.0,0.0171010,0.0172900,0.0171920,0.0171250,0.0170270]
a1 = []
for i in range(len(r1)) :
    a1.append(r1[i]-s12[i])
nu1 = [1.0]*len(r1)
nu2 = [1.0]*len(r1)
kappa1 = [1.0]*len(r1)
kappa2 = [1.0]*len(r1)

db = ParamDB()


class DataModel(BaseDataModel) :
    def __init__(self, db = ParamDB()) :
        super(DataModel, self).__init__(db)
    def update_data(self, assembly, b, t_f, t_m, bc, data) :
        if type(data) is FlareData :
            print("holy cow it works")
            data.kinf = 1.2
            data.migration_area = 60.0 
            data.kappa_over_nu = 1.0
        elif type(data) is TwoGroupData :
            print("two group")
            data.D1 = 1.2345

        
model2 = DataModel()

model = FixedDataModel(d1, d2, f1, f2, a1, a2, s12, nu1, nu2, kappa1, kappa2)
data = FlareData()
data2 = TwoGroupData()

model2.update_data(assemblies[0], 0.0, 900, 580.0, 0.0, data)
print((data.kinf))
model2.update_data(assemblies[0], 0.0, 900, 580.0, 0.0, data2)
print((data2.D1))
exit('lala')
for i in range(49) :
  model.update_data(assemblies[i], 0.0, 900.0, 580.0, 0.0, data)
  print(("i = ", i,  " kinf = ", data.migration_area))


solver = FlareSolver(db, core, model2, 3400.0)
solver.solve_single_state()

s = np.asarray(solver.assembly_powers())
mean_s = (0.25*s[0] + sum(s[1:49])) / (0.25 +49.-1.)
appf = s / mean_s
core.print_assembly_map(vec_dbl(appf), "lala")
print((core.pattern()))
print(("all done, keff = ", solver.keff()))
