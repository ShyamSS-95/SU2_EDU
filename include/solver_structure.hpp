/*!
 * \file solver_structure.hpp
 * \brief Headers of the main subroutines for solving partial differential equations.
 *        The subroutines and functions are in the <i>solver_structure.cpp</i>,
 *        <i>solution_direct.cpp</i>, <i>solution_adjoint.cpp</i>, and
 *        <i>solution_linearized.cpp</i> files.
 * \author Aerospace Design Laboratory (Stanford University) <http://su2.stanford.edu>.
 * \version 2.0.9
 *
 * Stanford University Unstructured (SU2).
 * Copyright (C) 2012-2013 Aerospace Design Laboratory (ADL).
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifndef NO_MPI
#include <mpi.h>
#endif

#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "numerics_structure.hpp"
#include "variable_structure.hpp"
#include "geometry_structure.hpp"
#include "config_structure.hpp"
#include "matrix_structure.hpp"
#include "vector_structure.hpp"
#include "linear_solvers_structure.hpp"
#include "grid_movement_structure.hpp"


using namespace std;

/*!
 * \class CSolver
 * \brief Main class for defining the PDE solution, it requires
 * a child class for each particular solver (Euler, Navier-Stokes, Plasma, etc.)
 * \author F. Palacios.
 * \version 2.0.9
 */
class CSolver {
protected:
	unsigned short IterLinSolver;	/*!< \brief Linear solver iterations. */
	unsigned short nVar,					/*!< \brief Number of variables of the problem. */
    nPrimVar,                     /*!< \brief Number of primitive variables of the problem. */
    nPrimVarGrad,                 /*!< \brief Number of primitive variables of the problem in the gradient computation. */
	nDim;													/*!< \brief Number of dimensions of the problem. */
	unsigned long nPoint;					/*!< \brief Number of points of the computational grid. */
    unsigned long nPointDomain; 	/*!< \brief Number of points of the computational grid. */
	double Max_Delta_Time,	/*!< \brief Maximum value of the delta time for all the control volumes. */
	Min_Delta_Time;					/*!< \brief Minimum value of the delta time for all the control volumes. */
	double *Residual_RMS,	/*!< \brief Vector with the mean residual for each variable. */
    *Residual_Max,        /*!< \brief Vector with the maximal residual for each variable. */
	*Residual,						/*!< \brief Auxiliary nVar vector. */
	*Residual_i,					/*!< \brief Auxiliary nVar vector for storing the residual at point i. */
	*Residual_j;					/*!< \brief Auxiliary nVar vector for storing the residual at point j. */
    unsigned long *Point_Max; /*!< \brief Vector with the maximal residual for each variable. */
	double *Solution,		/*!< \brief Auxiliary nVar vector. */
	*Solution_i,				/*!< \brief Auxiliary nVar vector for storing the solution at point i. */
	*Solution_j;				/*!< \brief Auxiliary nVar vector for storing the solution at point j. */
	double *Vector,	/*!< \brief Auxiliary nDim vector. */
	*Vector_i,			/*!< \brief Auxiliary nDim vector to do the reconstruction of the variables at point i. */
	*Vector_j;			/*!< \brief Auxiliary nDim vector to do the reconstruction of the variables at point j. */
	double *Res_Conv,	/*!< \brief Auxiliary nVar vector for storing the convective residual. */
	*Res_Visc,				/*!< \brief Auxiliary nVar vector for storing the viscous residual. */
	*Res_Sour,				/*!< \brief Auxiliary nVar vector for storing the viscous residual. */
	*Res_Conv_i,		  /*!< \brief Auxiliary vector for storing the convective residual at point i. */
	*Res_Visc_i,			/*!< \brief Auxiliary vector for storing the viscous residual at point i. */
	*Res_Conv_j,			/*!< \brief Auxiliary vector for storing the convective residual at point j. */
	*Res_Visc_j;			/*!< \brief Auxiliary vector for storing the viscous residual at point j. */
	double **Jacobian_i,	/*!< \brief Auxiliary matrices for storing point to point Jacobians at point i. */
	**Jacobian_j;			    /*!< \brief Auxiliary matrices for storing point to point Jacobians at point j. */
	double **Jacobian_ii,	/*!< \brief Auxiliary matrices for storing point to point Jacobians. */
	**Jacobian_ij,			  /*!< \brief Auxiliary matrices for storing point to point Jacobians. */
	**Jacobian_ji,			  /*!< \brief Auxiliary matrices for storing point to point Jacobians. */
	**Jacobian_jj;			  /*!< \brief Auxiliary matrices for storing point to point Jacobians. */
  
	double **Smatrix,	/*!< \brief Auxiliary structure for computing gradients by least-squares */
	**cvector;			 /*!< \brief Auxiliary structure for computing gradients by least-squares */

    unsigned short nOutputVariables;  /*!< \brief Number of variables to write. */

public:
  
  CSysVector LinSysSol;		/*!< \brief vector to store iterative solution of implicit linear system. */
  CSysVector LinSysRes;		/*!< \brief vector to store iterative residual of implicit linear system. */
  CSysVector LinSysAux;		/*!< \brief vector to store iterative residual of implicit linear system. */
	CSysMatrix Jacobian; /*!< \brief Complete sparse Jacobian structure for implicit computations. */
  
	CSysMatrix StiffMatrix; /*!< \brief Sparse structure for storing the stiffness matrix in Galerkin computations, and grid movement. */

    CSysVector OutputVariables;		/*!< \brief vector to store the extra variables to be written. */

	CVariable** node;	/*!< \brief Vector which the define the variables for each problem. */
  CVariable* node_infty; /*!< \brief CVariable storing the free stream conditions. */
  
	/*!
	 * \brief Constructor of the class.
	 */
	CSolver(void);
    
	/*!
	 * \brief Destructor of the class.
	 */
	virtual ~CSolver(void);
     
    /*!
	 * \brief Set number of linear solver iterations.
	 * \param[in] val_iterlinsolver - Number of linear iterations.
	 */
	void SetIterLinSolver(unsigned short val_iterlinsolver);
    
	/*!
	 * \brief Set number of linear solver iterations.
	 * \param[in] val_iterlinsolver - Number of linear iterations.
	 */
	virtual void Set_MPI_Solution(CGeometry *geometry, CConfig *config);
  
  /*!
	 * \brief Set number of linear solver iterations.
	 * \param[in] val_iterlinsolver - Number of linear iterations.
	 */
	virtual void Set_MPI_Primitive(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Set the value of the max residual and RMS residual.
	 * \param[in] val_iterlinsolver - Number of linear iterations.
	 */
	void SetResidual_RMS(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Set number of linear solver iterations.
	 * \param[in] val_iterlinsolver - Number of linear iterations.
	 */
	virtual void Set_MPI_Solution_Old(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
    virtual void Set_MPI_Solution_Limiter(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Get number of linear solver iterations.
	 * \return Number of linear solver iterations.
	 */
	unsigned short GetIterLinSolver(void);
    
	/*!
	 * \brief Get the value of the maximum delta time.
	 * \return Value of the maximum delta time.
	 */
	double GetMax_Delta_Time(void);
    
	/*!
	 * \brief Get the value of the minimum delta time.
	 * \return Value of the minimum delta time.
	 */
	double GetMin_Delta_Time(void);
    
    /*!
	 * \brief Get the value of the maximum delta time.
	 * \return Value of the maximum delta time.
	 */
	virtual double GetMax_Delta_Time(unsigned short val_Species);
    
	/*!
	 * \brief Get the value of the minimum delta time.
	 * \return Value of the minimum delta time.
	 */
	virtual double GetMin_Delta_Time(unsigned short val_Species);
    
	/*!
	 * \brief Get the number of variables of the problem.
	 */
	unsigned short GetnVar(void);
  
  /*!
	 * \brief Get the number of variables of the problem.
	 */
	unsigned short GetnPrimVar(void);
  
  /*!
	 * \brief Get the number of variables of the problem.
	 */
	unsigned short GetnPrimVarGrad(void);
  
  /*!
	 * \brief Get the number of variables of the problem.
	 */
	unsigned short GetnOutputVariables(void);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
	 */
	virtual void SetResidual_DualTime(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                                      unsigned short iRKStep, unsigned short iMesh, unsigned short RunTime_EqSystem);
    
	/*!
	 * \brief Set the maximal residual, this is useful for the convergence history.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_residual - Value of the residual to store in the position <i>val_var</i>.
	 */
	void SetRes_RMS(unsigned short val_var, double val_residual);
    
	/*!
	 * \brief Adds the maximal residual, this is useful for the convergence history.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_residual - Value of the residual to store in the position <i>val_var</i>.
	 */
	void AddRes_RMS(unsigned short val_var, double val_residual);
    
	/*!
	 * \brief Get the maximal residual, this is useful for the convergence history.
	 * \param[in] val_var - Index of the variable.
	 * \return Value of the biggest residual for the variable in the position <i>val_var</i>.
	 */
	double GetRes_RMS(unsigned short val_var);
    
    /*!
	 * \brief Set the maximal residual, this is useful for the convergence history.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_residual - Value of the residual to store in the position <i>val_var</i>.
	 */
	void SetRes_Max(unsigned short val_var, double val_residual, unsigned long val_point);
    
	/*!
	 * \brief Adds the maximal residual, this is useful for the convergence history.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_residual - Value of the residual to store in the position <i>val_var</i>.
	 */
	void AddRes_Max(unsigned short val_var, double val_residual, unsigned long val_point);
    
	/*!
	 * \brief Get the maximal residual, this is useful for the convergence history.
	 * \param[in] val_var - Index of the variable.
	 * \return Value of the biggest residual for the variable in the position <i>val_var</i>.
	 */
	double GetRes_Max(unsigned short val_var);
    
    /*!
	 * \brief Get the maximal residual, this is useful for the convergence history.
	 * \param[in] val_var - Index of the variable.
	 * \return Value of the biggest residual for the variable in the position <i>val_var</i>.
	 */
	unsigned long GetPoint_Max(unsigned short val_var);
    
	/*!
	 * \brief Set Value of the residual if there is a grid movement.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetGrid_Movement_Residual(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the Green-Gauss gradient of the auxiliary variable.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void SetAuxVar_Gradient_GG(CGeometry *geometry);
    
	/*!
	 * \brief Compute the Least Squares gradient of the auxiliary variable.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetAuxVar_Gradient_LS(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the Least Squares gradient of an auxiliar variable on the profile surface.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetAuxVar_Surface_Gradient(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the Green-Gauss gradient of the solution.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void SetSolution_Gradient_GG(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the Least Squares gradient of the solution.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetSolution_Gradient_LS(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief MPI gradients.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
    virtual void Set_MPI_Solution_Gradient(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Compute the Least Squares gradient of the grid velocity.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetGridVel_Gradient(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the Least Squares gradient of the solution on the profile surface.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetSurface_Gradient(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute slope limiter.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetSolution_Limiter(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetPrimVar_Limiter(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the pressure laplacian using in a incompressible solver.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] PressureLaplacian - Pressure laplacian.
	 */
	void SetPressureLaplacian(CGeometry *geometry, double *PressureLaplacian);
    
	/*!
	 * \brief Set the old solution variables to the current solution value for Runge-Kutta iteration.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void Set_OldSolution(CGeometry *geometry);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] Iteration - Index of the current iteration.
	 */
	virtual void SetTime_Step(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                              unsigned short iMesh, unsigned long Iteration);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	virtual void Postprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                                unsigned short iMesh);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 */
	virtual void Centered_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                                   CConfig *config, unsigned short iMesh, unsigned short iRKStep);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	virtual void Upwind_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                                 CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
     * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
	 */
	virtual void Preprocessing(CGeometry *geometry, CSolver **solver_container,
                               CConfig *config, unsigned short iMesh, unsigned short iRKStep, unsigned short RunTime_EqSystem);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetUndivided_Laplacian(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Set_MPI_Undivided_Laplacian(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetMax_Eigenvalue(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Set_MPI_MaxEigenvalue(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetDissipation_Switch(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Set_MPI_Dissipation_Switch(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	virtual void BC_Euler_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CConfig *config,
                               unsigned short val_marker);
  
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	virtual void BC_Isothermal_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                                    unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	virtual void BC_HeatFlux_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config, unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	virtual void BC_Far_Field(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                              unsigned short val_marker);
    
	/*!
	 * \brief Impose via the residual the Euler boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Definition of hte solver settings.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	virtual void BC_Sym_Plane(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config, unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	virtual void BC_Inlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                          CConfig *config, unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	virtual void BC_Supersonic_Inlet(CGeometry *geometry, CSolver **solver_container,
                                     CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config, unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	virtual void BC_Outlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                           CConfig *config, unsigned short val_marker);
  
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 */
	virtual void ExplicitRK_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                                      unsigned short iRKStep);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void ExplicitEuler_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void ImplicitEuler_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	virtual void Compute_Residual(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                                  unsigned short iMesh);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Inviscid_Forces(CGeometry *geometry, CConfig *config);
  
  /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Inviscid_Forces_Sections(CGeometry *geometry, CConfig *config);
  
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Inviscid_DeltaForces(CGeometry *geometry, CSolver **solver_container, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Viscous_Forces(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Viscous_DeltaForces(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Wave_Strength(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetPrimVar_Gradient_GG(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetPrimVar_Gradient_LS(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Set_MPI_PrimVar_Gradient(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetPrimVar_Limiter_MPI(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] iPoint - Index of the grid point.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetPreconditioner(CConfig *config, unsigned short iPoint);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 */
	virtual void Viscous_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                                  CConfig *config, unsigned short iMesh, unsigned short iRKStep);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	virtual void Galerkin_Method(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                                 CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] StiffMatrix_Elem - Stiffness matrix of an element
	 */
	virtual void AddStiffMatrix(double **StiffMatrix_Elem, unsigned long Point_0, unsigned long Point_1, unsigned long Point_2, unsigned long Point_3 );
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	virtual void Source_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CNumerics *second_numerics,
                                 CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	virtual void Source_Template(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                                 CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	virtual void Charge_Dist_SourceTerm(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                                        CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \param[in] val_sensitivity - Value of the sensitivity coefficient.
	 */
	virtual void SetCSensitivity(unsigned short val_marker, unsigned short val_vertex, double val_sensitivity);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetForceProj_Vector(CGeometry *geometry, CSolver **solver_container, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetIntBoundary_Jump(CGeometry *geometry, CSolver **solver_container, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_Total_CDrag - Value of the total drag coefficient.
	 */
	virtual void SetTotal_CDrag(double val_Total_CDrag);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_Total_CCharge - Value of the total charge coefficient.
	 */
	virtual void SetTotal_CCharge(double val_Total_CCharge);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_Total_CLift - Value of the total lift coefficient.
	 */
	virtual void SetTotal_CLift(double val_Total_CLift);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_Total_CT - Value of the total thrust coefficient.
	 */
	virtual void SetTotal_CT(double val_Total_CT);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_Total_CQ - Value of the total torque coefficient.
	 */
	virtual void SetTotal_CQ(double val_Total_CQ);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] val_Total_Q - Value of the total heat load.
	 */
	virtual void SetTotal_Q(double val_Total_Q);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] val_Total_MaxQ - Value of the total heat load.
	 */
	virtual void SetTotal_MaxQ(double val_Total_MaxQ);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetDistance(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Inviscid_Sensitivity(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Smooth_Sensitivity(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void Viscous_Sensitivity(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the lift coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCLift_Inv(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the lift coefficient (viscous contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCLift_Visc(unsigned short val_marker);

    /*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the z moment coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCMz_Inv(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the z moment coefficient (viscous contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCMz_Visc(unsigned short val_marker);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the lift coefficient on the surface <i>val_marker</i>.
	 */
	virtual double GetSurface_CLift(unsigned short val_marker);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the drag coefficient on the surface <i>val_marker</i>.
	 */
	virtual double GetSurface_CDrag(unsigned short val_marker);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the x moment coefficient on the surface <i>val_marker</i>.
	 */
	virtual double GetSurface_CMx(unsigned short val_marker);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the y moment coefficient on the surface <i>val_marker</i>.
	 */
	virtual double GetSurface_CMy(unsigned short val_marker);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the z moment coefficient on the surface <i>val_marker</i>.
	 */
	virtual double GetSurface_CMz(unsigned short val_marker);

  /*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the lift coefficient (viscous contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCSideForce_Visc(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the drag coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCDrag_Inv(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the mass flow rate on the surface <i>val_marker</i>.
	 */
	virtual double GetFanFace_MassFlow(unsigned short val_marker);
    
    /*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the mass flow rate on the surface <i>val_marker</i>.
	 */
	virtual double GetExhaust_MassFlow(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the fan face pressure on the surface <i>val_marker</i>.
	 */
	virtual double GetFanFace_Pressure(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the fan face mach on the surface <i>val_marker</i>.
	 */
	virtual double GetFanFace_Mach(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the sideforce coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCSideForce_Inv(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the efficiency coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCEff_Inv(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the drag coefficient (viscous contribution) on the surface <i>val_marker</i>.
	 */
	virtual double GetCDrag_Visc(unsigned short val_marker);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the lift coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CLift(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the sideforce coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CSideForce(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the efficiency coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CEff(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the thrust coefficient (force in the -x direction, inviscid + viscous contribution).
	 */
	virtual double GetTotal_CT(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the torque coefficient (moment in the -x direction, inviscid + viscous contribution).
	 */
	virtual double GetTotal_CQ(void);
    
    /*!
	 * \brief A virtual member.
	 * \return Value of the heat load (integrated heat flux).
	 */
	virtual double GetTotal_Q(void);
    
    /*!
	 * \brief A virtual member.
	 * \return Value of the heat load (integrated heat flux).
	 */
	virtual double GetTotal_MaxQ(void);
    
    /*!
	 * \brief Provide the total (inviscid + viscous) non dimensional drag coefficient.
	 * \return Value of the drag coefficient (inviscid + viscous contribution).
	 */
	virtual double Get_PressureDrag(void);
    
    /*!
	 * \brief Provide the total (inviscid + viscous) non dimensional drag coefficient.
	 * \return Value of the drag coefficient (inviscid + viscous contribution).
	 */
	virtual double Get_ViscDrag(void);
    
    /*!
	 * \brief Provide the total (inviscid + viscous) non dimensional drag coefficient.
	 * \return Value of the drag coefficient (inviscid + viscous contribution).
	 */
	virtual double Get_MagnetDrag(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the rotor Figure of Merit (FM) (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CMerit(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the Equivalent Area coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CEquivArea(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the Free Surface coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CFreeSurface(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the FEA coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CFEA(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the Near-Field Pressure coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CNearFieldOF(void);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_cequivarea - Value of the Equivalent Area coefficient.
	 */
	virtual void SetTotal_CEquivArea(double val_cequivarea);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_cfreesurface - Value of the Free Surface coefficient.
	 */
	virtual void SetTotal_CFreeSurface(double val_cfreesurface);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_cfea - Value of the FEA coefficient.
	 */
	virtual void SetTotal_CFEA(double val_cfea);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_cnearfieldpress - Value of the Near-Field pressure coefficient.
	 */
	virtual void SetTotal_CNearFieldOF(double val_cnearfieldpress);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the linearized lift coefficient (inviscid contribution).
	 */
	virtual double GetTotal_CDeltaLift(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the charge coefficient.
	 */
	virtual double GetTotal_CCharge(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the drag coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CDrag(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the moment x coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CMx(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the moment y coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CMy(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the moment y coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CMz(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the force x coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CFx(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the force y coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CFy(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the force y coefficient (inviscid + viscous contribution).
	 */
	virtual double GetTotal_CFz(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the wave strength.
	 */
	virtual double GetTotal_CWave(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the wave strength.
	 */
	virtual double GetTotal_CHeat(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the linearized drag coefficient (inviscid contribution).
	 */
	virtual double GetTotal_CDeltaDrag(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the lift coefficient (inviscid contribution).
	 */
	virtual double GetAllBound_CLift_Inv(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the drag coefficient (inviscid contribution).
	 */
	virtual double GetAllBound_CDrag_Inv(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the drag coefficient (inviscid contribution).
	 */
	virtual double GetAllBound_CSideForce_Inv(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the drag coefficient (inviscid contribution).
	 */
	virtual double GetAllBound_CEff_Inv(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the lift coefficient (viscous contribution).
	 */
	virtual double GetAllBound_CLift_Visc(void);
  
  /*!
	 * \brief A virtual member.
	 * \return Value of the lift coefficient (viscous contribution).
	 */
	virtual double GetAllBound_CSideForce_Visc(void);
  
	/*!
	 * \brief A virtual member.
	 * \return Value of the drag coefficient (viscous contribution).
	 */
	virtual double GetAllBound_CDrag_Visc(void);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the pressure coefficient.
	 */
	virtual double GetCPressure(unsigned short val_marker, unsigned short val_vertex);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the skin friction coefficient.
	 */
	virtual double GetCSkinFriction(unsigned short val_marker, unsigned short val_vertex);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the heat transfer coefficient.
	 */
	virtual double GetHeatTransferCoeff(unsigned short val_marker, unsigned short val_vertex);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_iSpecies - index of the chemical species
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the heat transfer coefficient.
	 */
	virtual double GetHeatTransferCoeff(unsigned short val_marker, unsigned short val_iSpecies, unsigned short val_vertex);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_iSpecies - index of the chemical species
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the heat transfer coefficient.
	 */
	virtual double GetViscForce(unsigned short val_marker, unsigned short val_iSpecies, unsigned short iDim, unsigned short val_vertex);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_iSpecies - index of the chemical species
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the heat transfer coefficient.
	 */
	virtual double GetPressureForce(unsigned short val_marker, unsigned short val_iSpecies, unsigned short iDim, unsigned short val_vertex);
    
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the y plus.
	 */
	virtual double GetYPlus(unsigned short val_marker, unsigned short val_vertex);
	
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the adjoint density at the infinity.
	 */
	virtual double GetPsiRho_Inf(void);
  
  /*!
	 * \brief A virtual member.
	 * \return Value of the adjoint density at the infinity.
	 */
	virtual double* GetPsiRhos_Inf(void);
  
	/*!
	 * \brief A virtual member.
	 * \return Value of the adjoint energy at the infinity.
	 */
	virtual double GetPsiE_Inf(void);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_dim - Index of the adjoint velocity vector.
	 * \return Value of the adjoint velocity vector at the infinity.
	 */
	virtual double GetPhi_Inf(unsigned short val_dim);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the geometrical sensitivity coefficient
	 *         (inviscid + viscous contribution).
	 */
	virtual double GetTotal_Sens_Geo(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the Mach sensitivity coefficient
	 *         (inviscid + viscous contribution).
	 */
	virtual double GetTotal_Sens_Mach(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the angle of attack sensitivity coefficient
	 *         (inviscid + viscous contribution).
	 */
	virtual double GetTotal_Sens_AoA(void);
    
	/*!
	 * \brief Set the total farfield pressure sensitivity coefficient.
	 * \return Value of the farfield pressure sensitivity coefficient
	 *         (inviscid + viscous contribution).
	 */
	virtual double GetTotal_Sens_Press(void);
    
	/*!
	 * \brief Set the total farfield temperature sensitivity coefficient.
	 * \return Value of the farfield temperature sensitivity coefficient
	 *         (inviscid + viscous contribution).
	 */
	virtual double GetTotal_Sens_Temp(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the density at the infinity.
	 */
	virtual double GetDensity_Inf(void);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_var - Index of the variable for the density.
	 * \return Value of the density at the infinity.
	 */
	virtual double GetDensity_Inf(unsigned short val_var);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the velocity at the infinity.
	 */
	virtual double GetModVelocity_Inf(void);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the density x energy at the infinity.
	 */
	virtual double GetDensity_Energy_Inf(void);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_var - Index of the variable for the energy.
	 * \return Value of the density multiply by  energy at the infinity.
	 */
	virtual double GetDensity_Energy_Inf(unsigned short val_var);
    
	/*!
	 * \brief Compute the density multiply by energy at the infinity.
	 * \param[in] val_var - Index of the variable for the energy.
	 * \return Value of the density multiply by  energy at the infinity.
	 */
	virtual double GetDensity_Energy_vib_Inf(unsigned short val_var);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the pressure at the infinity.
	 */
	virtual double GetPressure_Inf(void);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_dim - Index of the adjoint velocity vector.
	 * \return Value of the density x velocity at the infinity.
	 */
	virtual double GetDensity_Velocity_Inf(unsigned short val_dim);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_dim - Index of the velocity vector.
	 * \param[in] val_var - Index of the variable for the velocity.
	 * \return Value of the density multiply by the velocity at the infinity.
	 */
	virtual double GetDensity_Velocity_Inf(unsigned short val_dim, unsigned short val_var);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_dim - Index of the velocity vector.
	 * \return Value of the velocity at the infinity.
	 */
	virtual double GetVelocity_Inf(unsigned short val_dim);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the viscosity at the infinity.
	 */
	virtual double GetViscosity_Inf(void);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the sensitivity coefficient.
	 */
	virtual double GetCSensitivity(unsigned short val_marker, unsigned short val_vertex);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the density at the inlet.
	 */
	virtual double GetDensity_Inlet(void);
    
	/*!
	 * \overload
	 * \param[in] val_Fluid - Index of the fluid.
	 * \return Value of the density at the outlet.
	 */
	virtual double GetDensity_Inlet(unsigned short val_Fluid);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the density x energy at the inlet.
	 */
	virtual double GetDensity_Energy_Inlet(void);
    
	/*!
	 * \overload
	 * \param[in] val_Fluid - Index of the fluid.
	 * \return Value of the density x energy at the outlet.
	 */
	virtual double GetDensity_Energy_Inlet(unsigned short val_Fluid);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_dim - Index of the adjoint velocity vector.
	 * \return Value of the density x velocity at the inlet.
	 */
	virtual double GetDensity_Velocity_Inlet(unsigned short val_dim);
    
	/*!
	 * \overload
	 * \param[in] val_dim - Index of the adjoint velocity vector.
	 * \param[in] val_Fluid - Index of the fluid.
	 * \return Value of the density x velocity at the outlet.
	 */
	virtual double GetDensity_Velocity_Inlet(unsigned short val_dim,unsigned short val_Fluid);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the density at the outlet.
	 */
	virtual double GetDensity_Outlet(void);
    
	/*!
	 * \overload
	 * \param[in] val_Fluid - Index of the fluid.
	 * \return Value of the density at the outlet.
	 */
	virtual double GetDensity_Outlet(unsigned short val_Fluid);
    
	/*!
	 * \brief A virtual member.
	 * \return Value of the density x energy at the outlet.
	 */
	virtual double GetDensity_Energy_Outlet(void);
    
	/*!
	 * \overload
	 * \param[in] val_Fluid - Index of the fluid.
	 * \return Value of the density x energy at the outlet.
	 */
	virtual double GetDensity_Energy_Outlet(unsigned short val_Fluid);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] val_dim - Index of the adjoint velocity vector.
	 * \return Value of the density x velocity at the outlet.
	 */
	virtual double GetDensity_Velocity_Outlet(unsigned short val_dim);
    
	/*!
	 * \overload
	 * \param[in] val_dim - Index of the adjoint velocity vector.
	 * \param[in] val_Fluid - Index of the fluid.
	 * \return Value of the density x velocity at the outlet.
	 */
	virtual double GetDensity_Velocity_Outlet(unsigned short val_dim, unsigned short val_Fluid);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	virtual void SetFreeSurface_Distance(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief A virtual member.
	 * \return A pointer to an array containing a set of constants
	 */
	virtual double* GetConstants();
  
  /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
  virtual void GetSurface_Pressure(CGeometry *geometry, CConfig *config);

	/*!
	 * \brief A virtual member.
	 * \param[in] fea_geometry - Geometrical definition of the problem.
	 * \param[in] flow_solution - Container vector with all the solutions.
	 * \param[in] fea_config - Definition of the particular problem.
	 */
	virtual void SetFEA_Load(CSolver ***flow_solution, CGeometry **fea_geometry, CGeometry **flow_geometry, CConfig *fea_config, CConfig *flow_config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] solver1_geometry - Geometrical definition of the problem.
	 * \param[in] solver1_solution - Container vector with all the solutions.
	 * \param[in] solver1_config - Definition of the particular problem.
	 * \param[in] solver2_geometry - Geometrical definition of the problem.
	 * \param[in] solver2_solution - Container vector with all the solutions.
	 * \param[in] solver2_config - Definition of the particular problem.
	 */
	virtual void Copy_Zone_Solution(CSolver ***solver1_solution, CGeometry **solver1_geometry, CConfig *solver1_config,CSolver ***solver2_solution, CGeometry **solver2_geometry, CConfig *solver2_config);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] fea_geometry - Geometrical definition of the problem.
	 * \param[in] flow_solution - Container vector with all the solutions.
	 * \param[in] fea_config - Definition of the particular problem.
	 */
	virtual void SetInitialCondition(CGeometry **geometry, CSolver ***solver_container, CConfig *config, unsigned long ExtIter);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] flow_geometry - Geometrical definition of the problem.
	 * \param[in] flow_grid_movement - Geometrical definition of the problem.
	 * \param[in] flow_config - Geometrical definition of the problem.
	 * \param[in] fea_geometry - Definition of the particular problem.
	 */
	virtual void SetFlow_Displacement(CGeometry **flow_geometry, CVolumetricMovement *flow_grid_movement, CConfig *flow_config,
                                      CConfig *fea_config, CGeometry **fea_geometry, CSolver ***fea_solution);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver - Container vector with all of the solvers.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_iter - Current external iteration number.
	 */
	virtual void LoadRestart(CGeometry **geometry, CSolver ***solver, CConfig *config, int val_iter);
    
	/*!
	 * \brief Gauss method for solving a linear system.
	 * \param[in] A - Matrix Ax = b.
	 * \param[in] rhs - Right hand side.
	 * \param[in] nVar - Number of variables.
	 */
	void Gauss_Elimination(double** A, double* rhs, unsigned long nVar);
    
    /*!
	 * \brief Get the number of Species present in the flow.
	 */
	virtual unsigned short GetnSpecies(void);
    
	/*!
	 * \brief Get the number of Species present in the flow.
	 */
	virtual unsigned short GetnMonatomics(void);
    
	/*!
	 * \brief Get the number of Species present in the flow.
	 */
	virtual unsigned short GetnDiatomics(void);
    
    /*!
	 * \brief Prepares and solves the aeroelastic equations.
     * \param[in] surface_movement - Surface movement classes of the problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iter - Current sudo time iteration.
	 */
	void Aeroelastic(CSurfaceMovement *surface_movement, CGeometry *geometry, CConfig *config, unsigned long IntIter);

    
    /*!
	 * \brief Sets up the generalized eigenvectors and eigenvalues needed to solve the aeroelastic equations.
     * \param[in] PHI - Matrix of the generalized eigenvectors.
     * \param[in] lambda - The eigenvalues of the generalized eigensystem.
	 * \param[in] config - Definition of the particular problem.
	 */
    void SetUpTypicalSectionWingModel(double (&PHI)[2][2],double (&lambda)[2], CConfig *config);
    
    /*!
	 * \brief Solve the typical section wing model.
	 * \param[in] geometry - Geometrical definition of the problem.
     * \param[in] Cl - Coefficient of lift at particular iteration.
     * \param[in] Cm - Moment coefficient about z-axis at particular iteration.
	 * \param[in] config - Definition of the particular problem.
     * \param[in] iter - Sudo time iteration number.
     * \param[in] val_Marker - Surface that is being monitored.
     * \param[in] displacements - solution of typical section wing model.
	 */
    void SolveTypicalSectionWingModel(CGeometry *geometry, double Cl, double Cm, CConfig *config, unsigned long iter, unsigned short val_Marker, double (&displacements)[4]);

};

/*!
 * \class CEulerSolver
 * \brief Main class for defining the Euler's flow solver.
 * \ingroup Euler_Equations
 * \author F. Palacios.
 * \version 2.0.9
 */
class CEulerSolver : public CSolver {
protected:
	double Mach_Inf,	/*!< \brief Mach number at the infinity. */
	Mach_Inlet,		/*!< \brief Mach number at the inlet. */
	Mach_Outlet,		/*!< \brief Mach number at the outlet. */
	Density_Inf,	/*!< \brief Density at the infinity. */
	Density_Inlet,		/*!< \brief Density at the inlet. */
	Density_Outlet,		/*!< \brief Density at the outlet. */
	Density_Back,		/*!< \brief Density at infinity behind the Shock. */
	Energy_Inf,			/*!< \brief Energy at the infinity. */
	Energy_Inlet,		/*!< \brief Energy at the inlet. */
	Energy_Outlet,		/*!< \brief Energy at the outlet. */
	Energy_Back,		/*!< \brief Energy at the infinity behind the Shock. */
	Pressure_Inf,		/*!< \brief Pressure at the infinity. */
	Pressure_Inlet,		/*!< \brief Pressure at the inlet. */
	Pressure_Outlet,	/*!< \brief Pressure at the outlet. */
	Pressure_Back,		/*!< \brief Pressure at the infinity behind the Shock. */
	*Velocity_Inf,		/*!< \brief Flow Velocity vector at the infinity. */
	*Velocity_Inlet,	/*!< \brief Flow Velocity vector at the inlet. */
	*Velocity_Outlet,	/*!< \brief Flow Velocity vector at the outlet. */
	*Velocity_Back;		/*!< \brief Flow Velocity vector at the infinity behind the Shock. */
	double *CDrag_Inv,	/*!< \brief Drag coefficient (inviscid contribution) for each boundary. */
	*CLift_Inv,			/*!< \brief Lift coefficient (inviscid contribution) for each boundary. */
	*CSideForce_Inv,		/*!< \brief Sideforce coefficient (inviscid contribution) for each boundary. */
	*CMx_Inv,			/*!< \brief x Moment coefficient (inviscid contribution) for each boundary. */
	*CMy_Inv,			/*!< \brief y Moment coefficient (inviscid contribution) for each boundary. */
	*CMz_Inv,			/*!< \brief z Moment coefficient (inviscid contribution) for each boundary. */
	*CFx_Inv,			/*!< \brief x Force coefficient (inviscid contribution) for each boundary. */
	*CFy_Inv,			/*!< \brief y Force coefficient (inviscid contribution) for each boundary. */
	*CFz_Inv,			/*!< \brief z Force coefficient (inviscid contribution) for each boundary. */
    *Surface_CLift_Inv, /*!< \brief Lift coefficient (inviscid contribution) for each monitoring surface. */
    *Surface_CDrag_Inv, /*!< \brief Drag coefficient (inviscid contribution) for each monitoring surface. */
    *Surface_CMx_Inv,   /*!< \brief x Moment coefficient (inviscid contribution) for each monitoring surface. */
    *Surface_CMy_Inv,   /*!< \brief y Moment coefficient (inviscid contribution) for each monitoring surface. */
    *Surface_CMz_Inv,   /*!< \brief z Moment coefficient (inviscid contribution) for each monitoring surface. */
	*CEff_Inv,				/*!< \brief Efficiency (Cl/Cd) (inviscid contribution) for each boundary. */
	*CMerit_Inv,				/*!< \brief Rotor Figure of Merit (inviscid contribution) for each boundary. */
	*CT_Inv,			/*!< \brief Thrust coefficient (force in -x direction, inviscid contribution) for each boundary. */
	*CQ_Inv,			/*!< \brief Torque coefficient (moment in -x direction, inviscid contribution) for each boundary. */
	*CEquivArea_Inv,				/*!< \brief Equivalent area (inviscid contribution) for each boundary. */
	*CNearFieldOF_Inv,				/*!< \brief Near field pressure (inviscid contribution) for each boundary. */
	**CPressure,		/*!< \brief Pressure coefficient for each boundary and vertex. */
	**CHeatTransfer,		/*!< \brief Heat transfer coefficient for each boundary and vertex. */
	**YPlus,		/*!< \brief Yplus for each boundary and vertex. */
	*ForceInviscid,		/*!< \brief Inviscid force for each boundary. */
	*MomentInviscid,	/*!< \brief Inviscid moment for each boundary. */
	*FanFace_MassFlow,	/*!< \brief Mass flow rate for each boundary. */
	*Exhaust_MassFlow,	/*!< \brief Mass flow rate for each boundary. */
	*FanFace_Pressure,	/*!< \brief Fan face pressure for each boundary. */
	*FanFace_Mach,	/*!< \brief Fan face mach number for each boundary. */
	*FanFace_Area,	/*!< \brief Boundary total area. */
    *Exhaust_Area,	/*!< \brief Boundary total area. */
    FanFace_MassFlow_Total,	/*!< \brief Mass flow rate for each boundary. */
    Exhaust_MassFlow_Total,	/*!< \brief Mass flow rate for each boundary. */
	FanFace_Pressure_Total,	/*!< \brief Fan face pressure for each boundary. */
	FanFace_Mach_Total,	/*!< \brief Fan face mach number for each boundary. */
	InverseDesign;	/*!< \brief Inverse design functional for each boundary. */
	double AllBound_CDrag_Inv,	/*!< \brief Total drag coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CLift_Inv,			/*!< \brief Total lift coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CSideForce_Inv,			/*!< \brief Total sideforce coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CMx_Inv,			/*!< \brief Total x moment coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CMy_Inv,			/*!< \brief Total y moment coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CMz_Inv,			/*!< \brief Total z moment coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CFx_Inv,			/*!< \brief Total x force coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CFy_Inv,			/*!< \brief Total y force coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CFz_Inv,			/*!< \brief Total z force coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CEff_Inv,			/*!< \brief Efficient coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CMerit_Inv,			/*!< \brief Rotor Figure of Merit (inviscid contribution) for all the boundaries. */
	AllBound_CT_Inv,			/*!< \brief Total thrust coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CQ_Inv,			/*!< \brief Total torque coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CEquivArea_Inv,			/*!< \brief equivalent area coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CNearFieldOF_Inv;			/*!< \brief Near-Field press coefficient (inviscid contribution) for all the boundaries. */
	double Total_CDrag, /*!< \brief Total drag coefficient for all the boundaries. */
	Total_CLift,		/*!< \brief Total lift coefficient for all the boundaries. */
	Total_CSideForce,		/*!< \brief Total sideforce coefficient for all the boundaries. */
	Total_CMx,			/*!< \brief Total x moment coefficient for all the boundaries. */
	Total_CMy,			/*!< \brief Total y moment coefficient for all the boundaries. */
	Total_CMz,			/*!< \brief Total z moment coefficient for all the boundaries. */
	Total_CFx,			/*!< \brief Total x force coefficient for all the boundaries. */
	Total_CFy,			/*!< \brief Total y force coefficient for all the boundaries. */
	Total_CFz,			/*!< \brief Total z force coefficient for all the boundaries. */
	Total_CEff,			/*!< \brief Total efficiency coefficient for all the boundaries. */
	Total_CMerit,			/*!< \brief Total rotor Figure of Merit for all the boundaries. */
	Total_CT,		/*!< \brief Total thrust coefficient for all the boundaries. */
	Total_CQ,		/*!< \brief Total torque coefficient for all the boundaries. */
    Total_Q,    /*!< \brief Total heat load for all the boundaries. */
    Total_Maxq, /*!< \brief Maximum heat flux on all boundaries. */
	Total_CEquivArea,			/*!< \brief Total Equivalent Area coefficient for all the boundaries. */
	Total_CNearFieldOF,			/*!< \brief Total Near-Field Pressure coefficient for all the boundaries. */
    Total_CFreeSurface;			/*!< \brief Total Free Surface coefficient for all the boundaries. */
    double *Surface_CLift,   /*!< \brief Lift coefficient for each monitoring surface. */
    *Surface_CDrag,          /*!< \brief Drag coefficient for each monitoring surface. */
    *Surface_CMx,            /*!< \brief x Moment coefficient for each monitoring surface. */
    *Surface_CMy,            /*!< \brief y Moment coefficient for each monitoring surface. */
    *Surface_CMz;            /*!< \brief z Moment coefficient for each monitoring surface. */
	double *p1_Und_Lapl,	/*!< \brief Auxiliary variable for the undivided Laplacians. */
	*p2_Und_Lapl;			/*!< \brief Auxiliary variable for the undivided Laplacians. */
	double *PrimVar_i,	/*!< \brief Auxiliary vector for storing the solution at point i. */
	*PrimVar_j;			/*!< \brief Auxiliary vector for storing the solution at point j. */
	double **Precon_Mat_inv; /*!< \brief Auxiliary vector for storing the inverse of Roe-turkel preconditioner. */
	unsigned long nMarker;				/*!< \brief Total number of markers using the grid information. */
	bool space_centered,  /*!< \brief True if space centered scheeme used. */
	euler_implicit,			/*!< \brief True if euler implicit scheme used. */
	roe_turkel,         /*!< \brief True if computing preconditioning matrix for roe-turkel method. */
	least_squares;        /*!< \brief True if computing gradients by least squares. */
	double Gamma;									/*!< \brief Fluid's Gamma constant (ratio of specific heats). */
	double Gamma_Minus_One;				/*!< \brief Fluids's Gamma - 1.0  . */
    unsigned short nSection;    /*!< \brief Total number of airfoil sections to be cut from each specified marker. */
    vector<unsigned long> **point1_Airfoil;     /*!< \brief Vector of first points in the list of edges making up an airfoil section. */
    vector<unsigned long> **point2_Airfoil;     /*!< \brief Vector of second points in the list of edges making up an airfoil section. */
  
public:
    
	/*!
	 * \brief Constructor of the class.
	 */
	CEulerSolver(void);
    
	/*!
	 * \overload
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CEulerSolver(CGeometry *geometry, CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Destructor of the class.
	 */
	virtual ~CEulerSolver(void);
    
    /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_Solution(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_Solution_Gradient(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_Solution_Old(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
    virtual void Set_MPI_Solution_Limiter(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the density at the inlet.
	 * \return Value of the density at the infinity.
	 */
	double GetDensity_Inlet(void);
    
	/*!
	 * \brief Compute the density multiply by energy at the inlet.
	 * \return Value of the density multiply by energy at the inlet.
	 */
	double GetDensity_Energy_Inlet(void);
    
	/*!
	 * \brief Compute the density multiply by velocity at the inlet.
	 * \param[in] val_dim - Index of the velocity vector.
	 * \return Value of the density multiply by the velocity at the inlet.
	 */
	double GetDensity_Velocity_Inlet(unsigned short val_dim);
    
	/*!
	 * \brief Compute the density at the inlet.
	 * \return Value of the density at the infinity.
	 */
	double GetDensity_Outlet(void);
    
	/*!
	 * \brief Compute the density multiply by energy at the inlet.
	 * \return Value of the density multiply by energy at the inlet.
	 */
	double GetDensity_Energy_Outlet(void);
    
	/*!
	 * \brief Compute the density multiply by velocity at the inlet.
	 * \param[in] val_dim - Index of the velocity vector.
	 * \return Value of the density multiply by the velocity at the inlet.
	 */
	double GetDensity_Velocity_Outlet(unsigned short val_dim);
    
	/*!
	 * \brief Compute the density at the infinity.
	 * \return Value of the density at the infinity.
	 */
	double GetDensity_Inf(void);
    
	/*!
	 * \brief Compute the density at infinity  behind the Shock.
	 * \return Value of the density at infinity behind the Shock .
	 */
	double GetDensity_Back(void);
    
	/*!
	 * \brief Compute 2-norm of the velocity at the infinity.
	 * \return Value of the 2-norm of the velocity at the infinity.
	 */
	double GetModVelocity_Inf(void);
    
	/*!
	 * \brief Compute the density multiply by energy at the infinity.
	 * \return Value of the density multiply by  energy at the infinity.
	 */
	double GetDensity_Energy_Inf(void);
    
	/*!
	 * \brief Compute the density multiply by energy at infinity behind the Shock.
	 * \return Value of the density multiply by  energy at infinity behind the Shock.
	 */
	double GetDensity_Energy_Back(void);
    
	/*!
	 * \brief Compute the pressure at the infinity.
	 * \return Value of the pressure at the infinity.
	 */
	double GetPressure_Inf(void);
    
	/*!
	 * \brief Compute the pressure at infinity behind the Shock.
	 * \return Value of the pressure at infinity behind the Shock.
	 */
	double GetPressure_Back(void);
    
	/*!
	 * \brief Compute the density multiply by velocity at the infinity.
	 * \param[in] val_dim - Index of the velocity vector.
	 * \return Value of the density multiply by the velocity at the infinity.
	 */
	double GetDensity_Velocity_Inf(unsigned short val_dim);
    
	/*!
	 * \brief Compute the density multiply by velocity at infinity  behind the Shock.
	 * \param[in] val_dim - Index of the velocity vector.
	 * \return Value of the density multiply by the velocity at infinity  behind the Shock.
	 */
	double GetDensity_Velocity_Back(unsigned short val_dim);
    
	/*!
	 * \brief Get the velocity at the infinity.
	 * \param[in] val_dim - Index of the velocity vector.
	 * \return Value of the velocity at the infinity.
	 */
	double GetVelocity_Inf(unsigned short val_dim);
    
	/*!
	 * \brief Get the velocity at infinity behind the Shock.
	 * \param[in] val_dim - Index of the velocity vector.
	 * \return Value of the velocity at the Shock.
	 */
	double GetVelocity_Back(unsigned short val_dim);
    
	/*!
	 * \brief Compute the time step for solving the Euler equations.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] Iteration - Value of the current iteration.
	 */
	void SetTime_Step(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                      unsigned short iMesh, unsigned long Iteration);
    
	/*!
	 * \brief Compute the spatial integration using a centered scheme.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 */
	void Centered_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                           CConfig *config, unsigned short iMesh, unsigned short iRKStep);
    
	/*!
	 * \brief Compute the spatial integration using a upwind scheme.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Upwind_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                         CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Source term integration.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Source_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CNumerics *second_numerics,
                         CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Source term integration.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Source_Template(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                         CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Compute the velocity^2, SoundSpeed, Pressure, Enthalpy, Viscosity.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
     * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
	 */
	void Preprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config, unsigned short iMesh, unsigned short iRKStep, unsigned short RunTime_EqSystem);
  
  /*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Postprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config, unsigned short iMesh);
  
	/*!
	 * \brief Compute a pressure sensor switch.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetDissipation_Switch(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Parallelization of SetDissipation_Switch.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_Dissipation_Switch(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the gradient of the primitive variables using Green-Gauss method,
	 *        and stores the result in the <i>Gradient_Primitive</i> variable.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetPrimVar_Gradient_GG(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the gradient of the primitive variables using a Least-Squares method,
	 *        and stores the result in the <i>Gradient_Primitive</i> variable.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetPrimVar_Gradient_LS(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Compute the gradient of the primitive variables using a Least-Squares method,
	 *        and stores the result in the <i>Gradient_Primitive</i> variable.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_PrimVar_Gradient(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the limiter of the primitive variables.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetPrimVar_Limiter(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Compute the preconditioner for convergence acceleration by Roe-Turkel method.
	 * \param[in] iPoint - Index of the grid point
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetPreconditioner(CConfig *config, unsigned short iPoint);
    
	/*!
	 * \brief Compute the undivided laplacian for the solution, except the energy equation.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetUndivided_Laplacian(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Parallelization of Undivided Laplacian.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_Undivided_Laplacian(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Compute the max eigenvalue.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetMax_Eigenvalue(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Parallelization of the Max eigenvalue.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_MaxEigenvalue(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Impose via the residual the Euler wall boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Euler_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CConfig *config,
                       unsigned short val_marker);
    
	/*!
	 * \brief Impose the far-field boundary condition using characteristics.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Far_Field(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                      CConfig *config, unsigned short val_marker);
    
	/*!
	 * \brief Impose the symmetry boundary condition using the residual.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Sym_Plane(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config, unsigned short val_marker);
    
	/*!
	 * \brief Impose a subsonic inlet boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Inlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                  CConfig *config, unsigned short val_marker);
    
	/*!
	 * \brief Impose a supersonic inlet boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Supersonic_Inlet(CGeometry *geometry, CSolver **solver_container,
                             CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config, unsigned short val_marker);
    
	/*!
	 * \brief Impose the outlet boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
     
	 */
	void BC_Outlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                   CConfig *config, unsigned short val_marker);
  
	/*!
	 * \brief Update the solution using a Runge-Kutta scheme.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 */
	void ExplicitRK_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                              unsigned short iRKStep);
    
	/*!
	 * \brief Update the solution using the explicit Euler scheme.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	void ExplicitEuler_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config);
    
	/*!
	 * \brief Update the solution using an implicit Euler scheme.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	void ImplicitEuler_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config);
    
	/*!
	 * \brief Compute the pressure forces and all the adimensional coefficients.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Inviscid_Forces(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Provide the non dimensional lift coefficient (inviscid contribution).
	 * \param val_marker Surface where the coefficient is going to be computed.
	 * \return Value of the lift coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	double GetCLift_Inv(unsigned short val_marker);
    
    /*!
	 * \brief Provide the non dimensional z moment coefficient (inviscid contribution).
	 * \param val_marker Surface where the coefficient is going to be computed.
	 * \return Value of the z moment coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	double GetCMz_Inv(unsigned short val_marker);
    
    /*!
	 * \brief Provide the non dimensional lift coefficient.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the lift coefficient on the surface <i>val_marker</i>.
	 */
	double GetSurface_CLift(unsigned short val_marker);
    
    /*!
	 * \brief Provide the non dimensional drag coefficient.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the drag coefficient on the surface <i>val_marker</i>.
	 */
	double GetSurface_CDrag(unsigned short val_marker);
    
    /*!
	 * \brief Provide the non dimensional x moment coefficient.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the x moment coefficient on the surface <i>val_marker</i>.
	 */
	double GetSurface_CMx(unsigned short val_marker);
    
    /*!
	 * \brief Provide the non dimensional y moment coefficient.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the y moment coefficient on the surface <i>val_marker</i>.
	 */
	double GetSurface_CMy(unsigned short val_marker);
    
    /*!
	 * \brief Provide the non dimensional z moment coefficient.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the z moment coefficient on the surface <i>val_marker</i>.
	 */
	double GetSurface_CMz(unsigned short val_marker);
    
	/*!
	 * \brief Provide the non dimensional drag coefficient (inviscid contribution).
	 * \param val_marker Surface where the coeficient is going to be computed.
	 * \return Value of the drag coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	double GetCDrag_Inv(unsigned short val_marker);
    
	/*!
	 * \brief Provide the mass flow rate.
	 * \param val_marker Surface where the coeficient is going to be computed.
	 * \return Value of the mass flow rate on the surface <i>val_marker</i>.
	 */
	double GetFanFace_MassFlow(unsigned short val_marker);
    
    /*!
	 * \brief Provide the mass flow rate.
	 * \param val_marker Surface where the coeficient is going to be computed.
	 * \return Value of the mass flow rate on the surface <i>val_marker</i>.
	 */
	double GetExhaust_MassFlow(unsigned short val_marker);
    
	/*!
	 * \brief Provide the mass flow rate.
	 * \param val_marker Surface where the coeficient is going to be computed.
	 * \return Value of the fan face pressure on the surface <i>val_marker</i>.
	 */
	double GetFanFace_Pressure(unsigned short val_marker);
    
	/*!
	 * \brief Provide the mass flow rate.
	 * \param val_marker Surface where the coeficient is going to be computed.
	 * \return Value of the fan face mach on the surface <i>val_marker</i>.
	 */
	double GetFanFace_Mach(unsigned short val_marker);
    
	/*!
	 * \brief Provide the non dimensional sideforce coefficient (inviscid contribution).
	 * \param val_marker Surface where the coeficient is going to be computed.
	 * \return Value of the sideforce coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	double GetCSideForce_Inv(unsigned short val_marker);
    
	/*!
	 * \brief Provide the non dimensional efficiency coefficient (inviscid contribution).
	 * \param val_marker Surface where the coeficient is going to be computed.
	 * \return Value of the efficiency coefficient (inviscid contribution) on the surface <i>val_marker</i>.
	 */
	double GetCEff_Inv(unsigned short val_marker);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional sideforce coefficient.
	 * \return Value of the sideforce coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CSideForce(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional efficiency coefficient.
	 * \return Value of the efficiency coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CEff(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional Equivalent Area coefficient.
	 * \return Value of the Equivalent Area coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CEquivArea(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional Near-Field pressure coefficient.
	 * \return Value of the NearField pressure coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CNearFieldOF(void);
    
	/*!
	 * \brief Set the value of the Equivalent Area coefficient.
	 * \param[in] val_cequivarea - Value of the Equivalent Area coefficient.
	 */
	void SetTotal_CEquivArea(double val_cequivarea);
    
	/*!
	 * \brief Set the value of the Near-Field pressure oefficient.
	 * \param[in] val_cnearfieldpress - Value of the Near-Field pressure coefficient.
	 */
	void SetTotal_CNearFieldOF(double val_cnearfieldpress);
    
	/*!
	 * \brief Store the total (inviscid + viscous) non dimensional lift coefficient.
	 * \param[in] val_Total_CLift - Value of the total lift coefficient.
	 */
	void SetTotal_CLift(double val_Total_CLift);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional lift coefficient.
	 * \return Value of the lift coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CLift(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional drag coefficient.
	 * \return Value of the drag coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CDrag(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional x moment coefficient.
	 * \return Value of the moment x coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CMx(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional y moment coefficient.
	 * \return Value of the moment y coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CMy(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional z moment coefficient.
	 * \return Value of the moment z coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CMz(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional x force coefficient.
	 * \return Value of the force x coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CFx(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional y force coefficient.
	 * \return Value of the force y coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CFy(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional z force coefficient.
	 * \return Value of the force z coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CFz(void);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional thrust coefficient.
	 * \return Value of the rotor efficiency coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CT(void);
    
	/*!
	 * \brief Store the total (inviscid + viscous) non dimensional thrust coefficient.
	 * \param[in] val_Total_CT - Value of the total thrust coefficient.
	 */
	void SetTotal_CT(double val_Total_CT);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional torque coefficient.
	 * \return Value of the rotor efficiency coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CQ(void);
    
    /*!
	 * \brief Provide the total heat load.
	 * \return Value of the heat load (viscous contribution).
	 */
	double GetTotal_Q(void);
    
    /*!
	 * \brief Provide the total heat load.
	 * \return Value of the heat load (viscous contribution).
	 */
	double GetTotal_MaxQ(void);
    
	/*!
	 * \brief Store the total (inviscid + viscous) non dimensional torque coefficient.
	 * \param[in] val_Total_CQ - Value of the total torque coefficient.
	 */
	void SetTotal_CQ(double val_Total_CQ);
    
    /*!
	 * \brief Store the total heat load.
	 * \param[in] val_Total_Q - Value of the heat load.
	 */
	void SetTotal_Q(double val_Total_Q);
    
    /*!
	 * \brief Store the total heat load.
	 * \param[in] val_Total_Q - Value of the heat load.
	 */
	void SetTotal_MaxQ(double val_Total_MaxQ);
    
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional rotor Figure of Merit.
	 * \return Value of the rotor efficiency coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CMerit(void);
    
	/*!
	 * \brief Store the total (inviscid + viscous) non dimensional drag coefficient.
	 * \param[in] val_Total_CDrag - Value of the total drag coefficient.
	 */
	void SetTotal_CDrag(double val_Total_CDrag);
    
	/*!
	 * \brief Get the inviscid contribution to the lift coefficient.
	 * \return Value of the lift coefficient (inviscid contribution).
	 */
	double GetAllBound_CLift_Inv(void);
    
	/*!
	 * \brief Get the inviscid contribution to the drag coefficient.
	 * \return Value of the drag coefficient (inviscid contribution).
	 */
	double GetAllBound_CDrag_Inv(void);
    
	/*!
	 * \brief Get the inviscid contribution to the sideforce coefficient.
	 * \return Value of the sideforce coefficient (inviscid contribution).
	 */
	double GetAllBound_CSideForce_Inv(void);
    
	/*!
	 * \brief Get the inviscid contribution to the efficiency coefficient.
	 * \return Value of the efficiency coefficient (inviscid contribution).
	 */
	double GetAllBound_CEff_Inv(void);
    
	/*!
	 * \brief Provide the Pressure coefficient.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the pressure coefficient.
	 */
	double GetCPressure(unsigned short val_marker, unsigned short val_vertex);
  
	/*!
	 * \brief Provide the total (inviscid + viscous) non dimensional Free Surface coefficient.
	 * \return Value of the Free Surface coefficient (inviscid + viscous contribution).
	 */
	double GetTotal_CFreeSurface(void);
  
	/*!
	 * \brief Set the value of the Free Surface coefficient.
	 * \param[in] val_cfreesurface - Value of the Free Surface coefficient.
	 */
	void SetTotal_CFreeSurface(double val_cfreesurface);
  
	/*!
	 * \brief Set the total residual adding the term that comes from the Dual Time Strategy.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
	 */
	void SetResidual_DualTime(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                              unsigned short iRKStep, unsigned short iMesh, unsigned short RunTime_EqSystem);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] flow_geometry - Geometrical definition of the problem.
	 * \param[in] flow_grid_movement - Geometrical definition of the problem.
	 * \param[in] flow_config - Geometrical definition of the problem.
	 * \param[in] fea_geometry - Definition of the particular problem.
	 */
	void SetFlow_Displacement(CGeometry **flow_geometry, CVolumetricMovement *flow_grid_movement, CConfig *flow_config, CConfig *fea_config,
                              CGeometry **fea_geometry, CSolver ***fea_solution);
    
	/*!
	 * \brief Load a solution from a restart file.
	 * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver - Container vector with all of the solvers.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_iter - Current external iteration number.
	 */
	void LoadRestart(CGeometry **geometry, CSolver ***solver, CConfig *config, int val_iter);
    
	/*!
	 * \brief Set the initial condition for the Euler Equations.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] ExtIter - External iteration.
	 */
	void SetInitialCondition(CGeometry **geometry, CSolver ***solver_container, CConfig *config, unsigned long ExtIter);
  
  
	/*!
	 * \brief Recompute distance to the level set 0.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetFreeSurface_Distance(CGeometry *geometry, CConfig *config);
  
};

/*!
 * \class CNSSolver
 * \brief Main class for defining the Navier-Stokes flow solver.
 * \ingroup Navier_Stokes_Equations
 * \author F. Palacios.
 * \version 2.0.9
 */
class CNSSolver : public CEulerSolver {
private:
	double Viscosity_Inf;	/*!< \brief Viscosity at the infinity. */
	double Prandtl_Lam,   /*!< \brief Laminar Prandtl number. */
	Prandtl_Turb;         /*!< \brief Turbulent Prandtl number. */
	double *CDrag_Visc,	/*!< \brief Drag coefficient (viscous contribution) for each boundary. */
	*CLift_Visc,		/*!< \brief Lift coefficient (viscous contribution) for each boundary. */
	*CSideForce_Visc,		/*!< \brief Side force coefficient (viscous contribution) for each boundary. */
	*CMx_Visc,			/*!< \brief Moment x coefficient (viscous contribution) for each boundary. */
	*CMy_Visc,			/*!< \brief Moment y coefficient (viscous contribution) for each boundary. */
	*CMz_Visc,			/*!< \brief Moment z coefficient (viscous contribution) for each boundary. */
	*CFx_Visc,			/*!< \brief Force x coefficient (viscous contribution) for each boundary. */
	*CFy_Visc,			/*!< \brief Force y coefficient (viscous contribution) for each boundary. */
	*CFz_Visc,			/*!< \brief Force z coefficient (viscous contribution) for each boundary. */
    *Surface_CLift_Visc,/*!< \brief Lift coefficient (viscous contribution) for each monitoring surface. */
    *Surface_CDrag_Visc,/*!< \brief Drag coefficient (viscous contribution) for each monitoring surface. */
    *Surface_CMx_Visc,  /*!< \brief Moment x coefficient (viscous contribution) for each monitoring surface. */
    *Surface_CMy_Visc,  /*!< \brief Moment y coefficient (viscous contribution) for each monitoring surface. */
    *Surface_CMz_Visc,  /*!< \brief Moment z coefficient (viscous contribution) for each monitoring surface. */
	*CEff_Visc,			/*!< \brief Efficiency (Cl/Cd) (Viscous contribution) for each boundary. */
	*CMerit_Visc,			/*!< \brief Rotor Figure of Merit (Viscous contribution) for each boundary. */
	*CT_Visc,		/*!< \brief Thrust coefficient (viscous contribution) for each boundary. */
	*CQ_Visc,		/*!< \brief Torque coefficient (viscous contribution) for each boundary. */
    *Q_Visc,		/*!< \brief Heat load (viscous contribution) for each boundary. */
    *Maxq_Visc, /*!< \brief Maximum heat flux (viscous contribution) for each boundary. */
    
	**CSkinFriction;	/*!< \brief Skin friction coefficient for each boundary and vertex. */
	double *ForceViscous,	/*!< \brief Viscous force for each boundary. */
	*MomentViscous;			/*!< \brief Inviscid moment for each boundary. */
	double AllBound_CDrag_Visc, /*!< \brief Drag coefficient (viscous contribution) for all the boundaries. */
	AllBound_CLift_Visc,		/*!< \brief Lift coefficient (viscous contribution) for all the boundaries. */
	AllBound_CSideForce_Visc,		/*!< \brief Sideforce coefficient (viscous contribution) for all the boundaries. */
	AllBound_CMx_Visc,			/*!< \brief Moment x coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CMy_Visc,			/*!< \brief Moment y coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CMz_Visc,			/*!< \brief Moment z coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CEff_Visc,			/*!< \brief Efficient coefficient (Viscous contribution) for all the boundaries. */
	AllBound_CFx_Visc,			/*!< \brief Force x coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CFy_Visc,			/*!< \brief Force y coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CFz_Visc,			/*!< \brief Force z coefficient (inviscid contribution) for all the boundaries. */
	AllBound_CMerit_Visc,			/*!< \brief Rotor Figure of Merit coefficient (Viscous contribution) for all the boundaries. */
	AllBound_CT_Visc,		/*!< \brief Thrust coefficient (viscous contribution) for all the boundaries. */
	AllBound_CQ_Visc,		/*!< \brief Torque coefficient (viscous contribution) for all the boundaries. */
    AllBound_Q_Visc,		/*!< \brief Heat load (viscous contribution) for all the boundaries. */
    AllBound_Maxq_Visc; /*!< \brief Maximum heat flux (viscous contribution) for all boundaries. */
    
public:
    
	/*!
	 * \brief Constructor of the class.
	 */
	CNSSolver(void);
    
	/*!
	 * \overload
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CNSSolver(CGeometry *geometry, CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Destructor of the class.
	 */
	~CNSSolver(void);
    
	/*!
	 * \brief Compute the viscosity at the infinity.
	 * \return Value of the viscosity at the infinity.
	 */
	double GetViscosity_Inf(void);
    
	/*!
	 * \brief Compute the time step for solving the Navier-Stokes equations with turbulence model.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] Iteration - Index of the current iteration.
	 */
	void SetTime_Step(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                      unsigned short iMesh, unsigned long Iteration);
    
	/*!
	 * \brief Restart residual and compute gradients.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
     * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
	 */
	void Preprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config, unsigned short iMesh, unsigned short iRKStep, unsigned short RunTime_EqSystem);
    
    /*!
	 * \brief Impose a constant heat-flux condition at the wall.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_HeatFlux_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config, unsigned short val_marker);
    
    /*!
	 * \brief Impose the Navier-Stokes boundary condition (strong).
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Isothermal_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                            unsigned short val_marker);
    
	/*!
	 * \brief Compute the viscous forces and all the addimensional coefficients.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Viscous_Forces(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Get the non dimensional lift coefficient (viscous contribution).
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the lift coefficient (viscous contribution) on the surface <i>val_marker</i>.
	 */
	double GetCLift_Visc(unsigned short val_marker);
    
    /*!
	 * \brief Get the non dimensional z moment coefficient (viscous contribution).
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the z moment coefficient (viscous contribution) on the surface <i>val_marker</i>.
	 */
	double GetCMz_Visc(unsigned short val_marker);
  
  /*!
	 * \brief Get the non dimensional sideforce coefficient (viscous contribution).
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the sideforce coefficient (viscous contribution) on the surface <i>val_marker</i>.
	 */
	double GetCSideForce_Visc(unsigned short val_marker);
    
	/*!
	 * \brief Get the non dimensional drag coefficient (viscous contribution).
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \return Value of the drag coefficient (viscous contribution) on the surface <i>val_marker</i>.
	 */
	double GetCDrag_Visc(unsigned short val_marker);
    
	/*!
	 * \brief Get the total non dimensional lift coefficient (viscous contribution).
	 * \return Value of the lift coefficient (viscous contribution).
	 */
	double GetAllBound_CLift_Visc(void);
  
  /*!
	 * \brief Get the total non dimensional sideforce coefficient (viscous contribution).
	 * \return Value of the lift coefficient (viscous contribution).
	 */
	double GetAllBound_CSideForce_Visc(void);
    
	/*!
	 * \brief Get the total non dimensional drag coefficient (viscous contribution).
	 * \return Value of the drag coefficient (viscous contribution).
	 */
	double GetAllBound_CDrag_Visc(void);
    
	/*!
	 * \brief Compute the viscous residuals.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 */
	void Viscous_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                          CConfig *config, unsigned short iMesh, unsigned short iRKStep);
    
	/*!
	 * \brief Get the skin friction coefficient.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the skin friction coefficient.
	 */
	double GetCSkinFriction(unsigned short val_marker, unsigned short val_vertex);
    
	/*!
	 * \brief Get the skin friction coefficient.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the heat transfer coefficient.
	 */
	double GetHeatTransferCoeff(unsigned short val_marker, unsigned short val_vertex);
	
	/*!
	 * \brief Get the y plus.
	 * \param[in] val_marker - Surface marker where the coefficient is computed.
	 * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
	 * \return Value of the y plus.
	 */
	double GetYPlus(unsigned short val_marker, unsigned short val_vertex);
};

/*!
 * \class CTurbSolver
 * \brief Main class for defining the turbulence model solver.
 * \ingroup Turbulence_Model
 * \author A. Bueno.
 * \version 2.0.9
 */
class CTurbSolver : public CSolver {
protected:
	double *FlowSolution_i,	/*!< \brief Store the flow solution at point i. */
	*FlowSolution_j,        /*!< \brief Store the flow solution at point j. */
	*lowerlimit,            /*!< \brief contains lower limits for turbulence variables. */
	*upperlimit;            /*!< \brief contains upper limits for turbulence variables. */
	double Gamma;									/*!< \brief Fluid's Gamma constant (ratio of specific heats). */
	double Gamma_Minus_One;				/*!< \brief Fluids's Gamma - 1.0  . */
    
public:
    
	/*!
	 * \brief Constructor of the class.
	 */
	CTurbSolver(void);
    
	/*!
	 * \brief Destructor of the class.
	 */
	virtual ~CTurbSolver(void);
    
	/*!
	 * \brief Constructor of the class.
	 */
	CTurbSolver(CConfig *config);
    
    /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_Solution(CGeometry *geometry, CConfig *config);
  
  /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_Solution_Old(CGeometry *geometry, CConfig *config);
  
  /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	void Set_MPI_Solution_Gradient(CGeometry *geometry, CConfig *config);
    
    /*!
	 * \brief Impose the send-receive boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
    void Set_MPI_Solution_Limiter(CGeometry *geometry, CConfig *config);
    
	/*!
	 * \brief Impose the Symmetry Plane boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Sym_Plane(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config, unsigned short val_marker);
    
    /*!
	 * \brief Impose via the residual the Euler wall boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Euler_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CConfig *config,
                       unsigned short val_marker);
    
	/*!
	 * \brief Update the solution using an implicit solver.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 */
	void ImplicitEuler_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config);
  
  /*!
	 * \brief Set the total residual adding the term that comes from the Dual Time-Stepping Strategy.
	 * \param[in] geometry - Geometric definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
	 */
	void SetResidual_DualTime(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                            unsigned short iRKStep, unsigned short iMesh, unsigned short RunTime_EqSystem);
  
};

/*!
 * \class CTurbSASolver
 * \brief Main class for defining the turbulence model solver.
 * \ingroup Turbulence_Model
 * \author A. Bueno.
 * \version 2.0.9
 */

class CTurbSASolver: public CTurbSolver {
private:
	double nu_tilde_Inf;
	
public:
	/*!
	 * \brief Constructor of the class.
	 */
	CTurbSASolver(void);
    
	/*!
	 * \overload
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CTurbSASolver(CGeometry *geometry, CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Destructor of the class.
	 */
	~CTurbSASolver(void);
    
	/*!
	 * \brief Restart residual and compute gradients.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
     * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
	 */
	void Preprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config, unsigned short iMesh, unsigned short iRKStep, unsigned short RunTime_EqSystem);
    
	/*!
	 * \brief A virtual member.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Postprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                        unsigned short iMesh);
    
	/*!
	 * \brief Compute the spatial integration using a upwind scheme.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
    
	void Upwind_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CConfig *config,
                         unsigned short iMesh);
    
	/*!
	 * \brief Compute the viscous residuals for the turbulent equation.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 */
	void Viscous_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                          CConfig *config, unsigned short iMesh, unsigned short iRKStep);
    
	/*!
	 * \brief Source term computation.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Source_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CNumerics *second_numerics,
                         CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Source term computation.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Source_Template(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                         CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Impose the Navier-Stokes wall boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_HeatFlux_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                          unsigned short val_marker);
    
    /*!
	 * \brief Impose the Navier-Stokes wall boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Isothermal_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                            unsigned short val_marker);
    
	/*!
	 * \brief Impose the Far Field boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Far_Field(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                      unsigned short val_marker);
    
	/*!
	 * \brief Impose the inlet boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Inlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                  unsigned short val_marker);
    
	/*!
	 * \brief Impose the outlet boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
    
	void BC_Outlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                   unsigned short val_marker);
  
  /*!
	 * \brief Load a solution from a restart file.
	 * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver - Container vector with all of the solvers.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_iter - Current external iteration number.
	 */
	void LoadRestart(CGeometry **geometry, CSolver ***solver, CConfig *config, int val_iter);

    
};

/*!
 * \class CTurbSSTSolver
 * \brief Main class for defining the turbulence model solver.
 * \ingroup Turbulence_Model
 * \author A. Campos, F. Palacios, T. Economon
 * \version 2.0.9
 */

class CTurbSSTSolver: public CTurbSolver {
private:
	double *constants,  /*!< \brief Constants for the model. */
	kine_Inf,           /*!< \brief Free-stream turbulent kinetic energy. */
	omega_Inf;          /*!< \brief Free-stream specific dissipation. */
    
public:
	/*!
	 * \brief Constructor of the class.
	 */
	CTurbSSTSolver(void);
    
	/*!
	 * \overload
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CTurbSSTSolver(CGeometry *geometry, CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Destructor of the class.
	 */
	~CTurbSSTSolver(void);
    
	/*!
	 * \brief Restart residual and compute gradients.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
     * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
	 */
	void Preprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config, unsigned short iMesh, unsigned short iRKStep, unsigned short RunTime_EqSystem);
    
	/*!
	 * \brief Computes the eddy viscosity.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Postprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                        unsigned short iMesh);
    
	/*!
	 * \brief Compute the spatial integration using a upwind scheme.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Upwind_Residual(CGeometry *geometry, CSolver **solver_container,
                         CNumerics *numerics, CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Compute the viscous residuals for the turbulent equation.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
	 */
	void Viscous_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                          CConfig *config, unsigned short iMesh, unsigned short iRKStep);
    
	/*!
	 * \brief Source term computation.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Source_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CNumerics *second_numerics,
                         CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Source term computation.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iMesh - Index of the mesh in multigrid computations.
	 */
	void Source_Template(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                         CConfig *config, unsigned short iMesh);
    
	/*!
	 * \brief Impose the Navier-Stokes wall boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_HeatFlux_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                          unsigned short val_marker);
    
    /*!
	 * \brief Impose the Navier-Stokes wall boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Isothermal_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                            unsigned short val_marker);
    
	/*!
	 * \brief Impose the Far Field boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Far_Field(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                      unsigned short val_marker);
    
	/*!
	 * \brief Impose the inlet boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
	void BC_Inlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                  unsigned short val_marker);
    
	/*!
	 * \brief Impose the outlet boundary condition.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] solver - Description of the numerical method.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_marker - Surface marker where the boundary condition is applied.
	 */
    
	void BC_Outlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config,
                   unsigned short val_marker);
    
	/*!
	 * \brief Get the constants for the SST model.
	 * \return A pointer to an array containing a set of constants
	 */
	double* GetConstants();
    
};

#include "solver_structure.inl"