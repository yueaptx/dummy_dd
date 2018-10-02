[GlobalParams]
#  displacements = 'disp_x disp_y'
  diffusivity = 1.18e-5 # [m^2/s], diffusion coefficient pre-exponential
  Uvd = 0.61   # [eV], vacancy migration energy
  Uvf = 0.67  # [eV], vacancy formation energy
  kB = 1.3806e-23  # [m^2kg/s^2/K], Boltzmann constant
  eV2J = 1.60218e-19   # [J/eV], convert eV to Joules
  Omega = 16.3e-30  # [m^3], atomic volume
  T = 600     # [K], temperature
  burgers = 0.28567e-9 # [m], burger's vector magnitude
[]

[Mesh]
  # optionsl Type
  # type=<FileMesh | GeneratedMesh>
  # FileMesh
   type = FileMesh     # import mesh from file
   file = circle.msh   # import the mesh file from Gmsh
   #uniform_refine = 1  # refine the mesh
  # displacements = 'disp_x disp_y'
#  type = GeneratedMesh     # import mesh from file
#  dim = 1
#  xmin = 0
#  xmax = 1e-4
#  nx = 20
  parallel_type = replicated
[]

[MeshModifiers]
  [./scale]
    type = Transform
    transform = SCALE
    vector_value = '0.004 0.004 0.004'
  [../]
#  [./translate]
#  type = Transform
#  transform = TRANSLATE
#  vector_value = '1e-6 0 0'
#  [../]
  [./rotate]
  type = Transform
  transform = ROTATE
  #vector_value = '0 0 0'
  vector_value = '0 -54.74 -45' # Z-X-Z, alpha: first rotate w/rt original X, beta: second rotate w/rt original Y, gamma: third rotate w/rt original Z
  [../]
[]

[AuxVariables]
  [./from_master]
#    order = FIRST
#    family = LAGRANGE
  [../]
  [./w_c]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxKernels]
  [./climb_velocity]
    type = ClimbVelocity
    variable = w_c
    coupled = from_master
  [../]
[]

#[UserObjects]
#  [./MasterMesh]
#    # Read in the fine grid solution
#    type = LineIntegral
#    mesh = '../diffusion_master/diffusion_master_out_0000_mesh.xda'
#    es = '../diffusion_master/diffusion_master_out_0000.xda'
#  [../]
#[]

[Problem]
   type = DDproblem # This is the "normal" type of Finite Element Problem in MOOSE
  # coord_type = RZ # Axisymmetric RZ
  # rz_coord_axis = X # Which axis the symmetry is around
[]

[Executioner]
  type = Transient # Transient problem
  #type = Steady # Steady state problem
  solve_type = PJFNK #Preconditioned Jacobian Free Newton Krylov
  num_steps = 2
  dt = 1e-5
  petsc_options_iname = '-pc_type -pc_hypre_type' #Matches with the values below
  petsc_options_value = 'hypre boomeramg'
[]


[Outputs]
  execute_on = 'timestep_end'
  exodus = true # Output Exodus format
  # use_displaced_mesh = true
[]
