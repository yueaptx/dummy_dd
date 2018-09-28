#[GlobalParams]
#  displacements = 'disp_x disp_y'
#[]

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

#[MeshModifiers]
#  [./translate]
#  type = Transform
#  transform = TRANSLATE
#  vector_value = '1e-6 0 0'
#  [../]
#  [./rotate]
#  type = Transform
#  transform = ROTATE
#  vector_value = '45 35 45'
#  [../]
#[]

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
