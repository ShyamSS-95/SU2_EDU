/*!
 * \file option_structure.hpp
 * \brief Defines classes for referencing options for easy input in CConfig
 * \author Aerospace Design Laboratory (Stanford University).
 * \version 1.2.0
 *
 * Many of the classes in this file are templated, and therefore must
 * be declared and defined here; to keep all elements together, there
 * is no corresponding .cpp file at this time.
 *
 * SU2 EDU, Copyright (C) 2014 Aerospace Design Laboratory (Stanford University).
 *
 * SU2 EDU is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 EDU is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2 EDU. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*!
 * \class CCreateMap
 * \brief creates a map from a list by overloading operator()
 * \tparam T - the key type in the map
 * \tparam U - the mapped value type in the map
 * \author Boost.Assign and anonymous person on stackoverflow
 *
 * We need this to create static const maps that map strings to enum
 * types.  The implementation is based on the Boost.Assign library.  This
 * particular version is taken from
 * http://stackoverflow.com/questions/138600/initializing-a-static-stdmapint-int-in-c
 */
template <typename T, typename U>
class CCreateMap {
private:
  std::map<T, U> m_map;
public:
  CCreateMap(const T& key, const U& val) {
    m_map[key] = val;
  }
  CCreateMap<T, U>& operator()(const T& key, const U& val) {
    m_map[key] = val;
    return *this;
  }
  operator std::map<T, U>() {
    return m_map;
  }
};

/*!
 * \brief utility function for converting strings to uppercase
 * \param[in,out] str - string we want to convert
 */
inline void StringToUpperCase(string & str) {
  std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

/*!
 * \brief utility function for converting strings to uppercase
 * \param[in] str - string we want a copy of converted to uppercase
 * \returns a copy of str in uppercase
 */
inline string StringToUpperCase(const string & str) {
  string upp_str(str);
  std::transform(upp_str.begin(), upp_str.end(), upp_str.begin(), ::toupper);
  return upp_str;
}

/*!
 * \brief different software components of SU2
 */
enum SU2_COMPONENT {
  SU2_EDU = 1,	/*!< \brief Running the SU2_EDU software. */
  SU2_PRT = 4,	/*!< \brief Running the SU2_PRT software. */
  SU2_SOL = 9,	/*!< \brief Running the SU2_SOL software. */
};

const unsigned int MAX_PARAMETERS = 10;		/*!< \brief Maximum number of parameters for a design variable definition. */
const unsigned int MAX_NUMBER_MARKER = 5000;	/*!< \brief Maximum number of markers. */
const unsigned int MAX_NUMBER_PERIODIC = 10;	/*!< \brief Maximum number of periodic boundary conditions. */
const unsigned int MAX_STRING_SIZE = 200;	/*!< \brief Maximum number of domains. */
const unsigned int MAX_NUMBER_FFD = 10;	/*!< \brief Maximum number of FFDBoxes for the FFD. */
const unsigned int MAX_SOLS = 6;		/*!< \brief Maximum number of solutions at the same time (dimension of solution container array). */
const unsigned int MAX_TERMS = 6;		/*!< \brief Maximum number of terms in the numerical equations (dimension of solver container array). */
const unsigned int MAX_ZONES = 3; /*!< \brief Maximum number of zones. */
const unsigned int NO_RK_ITER = 0;		/*!< \brief No Runge-Kutta iteration. */
const unsigned int MESH_0 = 0;			/*!< \brief Definition of the finest grid level. */
const unsigned int MESH_1 = 1;			/*!< \brief Definition of the finest grid level. */
const unsigned int ZONE_0 = 0;			/*!< \brief Definition of the first grid domain. */
const unsigned int ZONE_1 = 1;			/*!< \brief Definition of the first grid domain. */

const double PRANDTL = 0.72;	        	/*!< \brief Fluid's Prandtl constant (air). */
const double PRANDTL_TURB = 0.90;	/*!< \brief Fluid's turbulent Prandtl constant (air). */
const double AVOGAD_CONSTANT = 6.0221415E26;	/*!< \brief Avogardro's constant, number of particles in one kmole. */
const double BOLTZMANN_CONSTANT = 1.3806503E-23; /*! \brief Boltzmann's constant [J K^-1] */
const double UNIVERSAL_GAS_CONSTANT = 8314.462175; /*! \brief Universal gas constant [J kmol^-1 K^-1] */
const double ELECTRON_CHARGE = 1.60217646E-19;	/*!< \brief Electronic charge constant. */
const double ELECTRON_MASS = 9.10938188E-31;	/*!< \brief Mass of an electron. */
const double FREE_PERMITTIVITY = 8.8541878176E-12; /*!< \brief Premittivity of free space. */
const double MAGNETIC_CONSTANT = 1.25663706E-6;  /*!< \brief magnetic permeability of free space. */
const double STANDART_GRAVITY = 9.80665;        /*!< \brief Acceleration due to gravity at surface of earth. */
const double EPS = 1.0E-16;			/*!< \brief Error scale. */
const double TURB_EPS = 1.0E-16;		/*!< \brief Turbulent Error scale. */
const double ONE2 = 0.5;			/*!< \brief One divided by two. */
const double TWO3 = 2.0 / 3.0;			/*!< \brief Two divided by three. */
const double FOUR3 = 4.0 / 3.0;			/*!< \brief Four divided by three. */
const double PI_NUMBER = 4.0 * atan(1.0);	/*!< \brief Pi number. */
const int MASTER_NODE = 0;			/*!< \brief Master node for MPI parallelization. */
const int SINGLE_NODE = 1;			/*!< \brief There is only a node in the MPI parallelization. */
const int AUX_NODE = 1;			/*!< \brief Computational node that is used for IO stuff. */

/** General output & CGNS defines **/
const unsigned int N_ELEM_TYPES = 7;
const unsigned int N_POINTS_LINE = 2;
const unsigned int N_POINTS_TRIANGLE = 3;
const unsigned int N_POINTS_QUADRILATERAL = 4;
const unsigned int N_POINTS_TETRAHEDRON = 4;
const unsigned int N_POINTS_HEXAHEDRON = 8;
const unsigned int N_POINTS_PYRAMID = 5;
const unsigned int N_POINTS_WEDGE = 6;

/*!
 * \brief Boolean answers
 */
enum ANSWER {
  NONE = 0,
  NO = 0,    /*!< \brief Boolean definition of no. */
  YES = 1	/*!< \brief Boolean definition of yes. */
};

/*!
 * \brief Verbosity level
 */
enum VERB_LEVEL {
  VERB_NONE = 1,   /*!< \brief No verbosity. */
  VERB_MEDIUM = 1,   /*!< \brief Medium level of verbosity. */
  VERB_HIGH = 2			/*!< \brief High level of verbosity. */
};

/*!
 * \brief types of MPI communications
 */
enum COMM_TYPE {
  SEND = 1,					/*!< \brief Boolean definition of send (parallelization). */
  RECEIVE = 2				/*!< \brief Boolean definition of receive (parallelization). */
};

/*!
 * \brief different solver types for the CFD component
 */
enum ENUM_SOLVER {
  NO_SOLVER = 0,			/*!< \brief Definition of no solver. */
  EULER = 1,				/*!< \brief Definition of the Euler's solver. */
  NAVIER_STOKES = 2,			/*!< \brief Definition of the Navier-Stokes' solver. */
  RANS = 3,				/*!< \brief Definition of the Reynolds-averaged Navier-Stokes' (RANS) solver. */
  POISSON_EQUATION = 4,       	/*!< \brief Definition of the poisson potential solver. */
  WAVE_EQUATION = 10,	/*!< \brief Definition of the wave solver. */
  HEAT_EQUATION = 29,								/*!< \brief Definition of the heat solver. */
  LINEAR_ELASTICITY = 11,	/*!< \brief Definition of the FEA solver. */
  FLUID_STRUCTURE_EULER = 12,	/*!< \brief Definition of the FEA solver. */
  FLUID_STRUCTURE_NAVIER_STOKES = 13,	/*!< \brief Definition of the FEA solver. */
  FLUID_STRUCTURE_RANS = 14,	/*!< \brief Definition of the FEA solver. */
  ADJ_EULER = 18,			/*!< \brief Definition of the continuous adjoint Euler's solver. */
  ADJ_NAVIER_STOKES = 19,		/*!< \brief Definition of the continuous adjoint Navier-Stokes' solver. */
  ADJ_RANS = 20,				/*!< \brief Definition of the continuous adjoint Reynolds-averaged Navier-Stokes' (RANS) solver. */
  LIN_EULER = 21,			/*!< \brief Definition of the linear Euler's solver. */
  LIN_NAVIER_STOKES = 22,		/*!< \brief Definition of the linear Navier-Stokes' solver. */
  TEMPLATE_SOLVER = 30,                  /*!< \brief Definition of template solver. */
  TNE2_EULER = 31,
  TNE2_NAVIER_STOKES = 32,
  ADJ_TNE2_EULER = 33,
  ADJ_TNE2_NAVIER_STOKES = 34
};
/* BEGIN_CONFIG_ENUMS */
static const map<string, ENUM_SOLVER> Solver_Map = CCreateMap<string, ENUM_SOLVER>
("NONE", NO_SOLVER)
("EULER", EULER)
("NAVIER_STOKES", NAVIER_STOKES)
("RANS", RANS)
("POISSON_EQUATION", POISSON_EQUATION)
("ADJ_EULER", ADJ_EULER)
("ADJ_NAVIER_STOKES", ADJ_NAVIER_STOKES)
("ADJ_RANS", ADJ_RANS )
("LIN_EULER", LIN_EULER)
("LIN_NAVIER_STOKES", LIN_NAVIER_STOKES)
("TNE2_EULER", TNE2_EULER)
("TNE2_NAVIER_STOKES", TNE2_NAVIER_STOKES)
("ADJ_TNE2_EULER", ADJ_TNE2_EULER)
("ADJ_TNE2_NAVIER_STOKES", ADJ_TNE2_NAVIER_STOKES)
("WAVE_EQUATION", WAVE_EQUATION)
("HEAT_EQUATION", HEAT_EQUATION)
("LINEAR_ELASTICITY", LINEAR_ELASTICITY)
("FLUID_STRUCTURE_EULER", FLUID_STRUCTURE_EULER)
("FLUID_STRUCTURE_NAVIER_STOKES", FLUID_STRUCTURE_NAVIER_STOKES)
("FLUID_STRUCTURE_RANS", FLUID_STRUCTURE_RANS)
("TEMPLATE_SOLVER", TEMPLATE_SOLVER);

/*!
 * \brief different regime modes
 */
enum ENUM_REGIME {
  COMPRESSIBLE = 0,			/*!< \brief Definition of compressible solver. */
  INCOMPRESSIBLE = 1,				/*!< \brief Definition of incompressible solver. */
  FREESURFACE = 2			/*!< \brief Definition of freesurface solver (incompressible). */
  
};
static const map<string, ENUM_REGIME> Regime_Map = CCreateMap<string, ENUM_REGIME>
("COMPRESSIBLE", COMPRESSIBLE)
("INCOMPRESSIBLE", INCOMPRESSIBLE)
("FREESURFACE", FREESURFACE);

/*!
 * \brief different types of systems
 */
enum RUNTIME_TYPE {
  RUNTIME_FLOW_SYS = 2,			/*!< \brief One-physics case, the code is solving the flow equations(Euler and Navier-Stokes). */
  RUNTIME_TURB_SYS = 3,			/*!< \brief One-physics case, the code is solving the turbulence model. */
  RUNTIME_POISSON_SYS = 4,			/*!< \brief One-physics case, the code is solving the poissonal potential equation. */
  RUNTIME_ADJPOT_SYS = 5,		/*!< \brief One-physics case, the code is solving the adjoint potential flow equation. */
  RUNTIME_ADJFLOW_SYS = 6,		/*!< \brief One-physics case, the code is solving the adjoint equations is being solved (Euler and Navier-Stokes). */
  RUNTIME_ADJTURB_SYS = 7,		/*!< \brief One-physics case, the code is solving the adjoint turbulence model. */
  RUNTIME_WAVE_SYS = 8,		/*!< \brief One-physics case, the code is solving the wave equation. */
  RUNTIME_LINPOT_SYS = 9,		/*!< \brief One-physics case, the code is solving the linear potential flow equations. */
  RUNTIME_LINFLOW_SYS = 10,		/*!< \brief One-physics case, the code is solving the linear equations is being solved (Euler and Navier-Stokes). */
  RUNTIME_MULTIGRID_SYS = 14,   	/*!< \brief Full Approximation Storage Multigrid system of equations. */
  RUNTIME_FEA_SYS = 20,		/*!< \brief One-physics case, the code is solving the FEA equation. */
  RUNTIME_HEAT_SYS = 21,		/*!< \brief One-physics case, the code is solving the heat equation. */
  RUNTIME_TRANS_SYS = 22,			/*!< \brief One-physics case, the code is solving the turbulence model. */
  RUNTIME_TNE2_SYS = 23,  /*!< \brief One-physics case, the code is solving the two-temperature model. */
  RUNTIME_ADJTNE2_SYS = 24  /*!< \brief One-physics case, the code is solving the two-temperature model. */
};

const int FLOW_SOL = 0;		/*!< \brief Position of the mean flow solution in the solver container array. */
const int ADJFLOW_SOL = 1;	/*!< \brief Position of the continuous adjoint flow solution in the solver container array. */
const int LINFLOW_SOL = 1;	/*!< \brief Position of the linearized flow solution in the solution solver array. */

const int TURB_SOL = 2;		/*!< \brief Position of the turbulence model solution in the solver container array. */
const int ADJTURB_SOL = 3;	/*!< \brief Position of the continuous adjoint turbulence solution in the solver container array. */
const int LINTURB_SOL = 3;	/*!< \brief Position of the linearized turbulence model in the solver container array. */

const int TNE2_SOL = 0;		/*!< \brief Position of the mean flow solution in the solution container array. */
const int ADJTNE2_SOL = 1;	/*!< \brief Position of the continuous adjoint flow solution in the solution container array. */
const int LINTNE2_SOL = 1;	/*!< \brief Position of the linearized flow solution in the solution container array. */

const int TRANS_SOL = 4;	/*!< \brief Position of the transition model solution in the solver container array. */
const int POISSON_SOL = 2;		/*!< \brief Position of the electronic potential solution in the solver container array. */
const int WAVE_SOL = 1;		/*!< \brief Position of the wave equation in the solution solver array. */
const int HEAT_SOL = 2;		/*!< \brief Position of the heat equation in the solution solver array. */
const int FEA_SOL = 1;		/*!< \brief Position of the FEA equation in the solution solver array. */

const int TEMPLATE_SOL = 0;     /*!< \brief Position of the template solution. */

const int CONV_TERM = 0;	/*!< \brief Position of the convective terms in the numerics container array. */
const int VISC_TERM = 1;        /*!< \brief Position of the viscous terms in the numerics container array. */
const int SOURCE_FIRST_TERM = 2;        /*!< \brief Position of the first source term in the numerics container array. */
const int SOURCE_SECOND_TERM = 3;   /*!< \brief Position of the second source term in the numerics container array. */
const int CONV_BOUND_TERM = 4;       /*!< \brief Position of the convective boundary terms in the numerics container array. */
const int VISC_BOUND_TERM = 5;       /*!< \brief Position of the viscous boundary terms in the numerics container array. */

/*!
 * \brief types of mathematical problem to solve
 */
enum ENUM_MATH_PROBLEM {
  DIRECT_PROBLEM = 0,		/*!< \brief Direct problem */
  ADJOINT_PROBLEM = 1,		/*!< \brief Adjoint problem */
  LINEARIZED_PROBLEM = 2 /*< \brief Linearized numerical method */
};
static const map<string, ENUM_MATH_PROBLEM> Math_Problem_Map = CCreateMap<string, ENUM_MATH_PROBLEM>
("DIRECT", DIRECT_PROBLEM)
("ADJOINT", ADJOINT_PROBLEM)
("LINEARIZED", LINEARIZED_PROBLEM);


/*!
 * \brief types of spatial discretizations
 */
enum ENUM_SPACE {
  NO_CONVECTIVE = 0, /*!< \brief No convective scheme is used. */
  SPACE_CENTERED = 1,		/*!< \brief Space centered convective numerical method. */
  SPACE_UPWIND = 2		/*!< \brief Upwind convective numerical method. */
};
static const map<string, ENUM_SPACE> Space_Map = CCreateMap<string, ENUM_SPACE>
("NONE", NO_CONVECTIVE)
("SPACE_CENTERED", SPACE_CENTERED)
("SPACE_UPWIND", SPACE_UPWIND);

/*!
 * \brief types of spatial discretizations
 */
enum ENUM_GASMODEL {
  NO_MODEL = 0, /*!< \brief _____. */
  ARGON = 1,		/*!< \brief _____. */
  AIR7 = 2,		/*!< \brief _______. */
  AIR21 = 3,		/*!< \brief _______. */
  O2 = 4,
  N2 = 5,
  AIR5 = 6,
  ARGON_SID = 7,
  ONESPECIES = 8
  
};
static const map<string, ENUM_GASMODEL> GasModel_Map = CCreateMap<string, ENUM_GASMODEL>
("NONE", NO_MODEL)
("ARGON", ARGON)
("AIR-7", AIR7)
("AIR-21", AIR21)
("O2", O2)
("N2", N2)
("AIR-5", AIR5)
("ARGON-SID",ARGON_SID)
("ONESPECIES", ONESPECIES);

/*!
 * \brief types of unsteady mesh motion
 */
enum ENUM_GRIDMOVEMENT {
  NO_MOVEMENT = 0, /*!< \brief Simulation on a static mesh. */
  DEFORMING = 1,		/*!< \brief Simulation with dynamically deforming meshes (plunging/pitching/rotation). */
  RIGID_MOTION = 2,		/*!< \brief Simulation with rigid mesh motion (plunging/pitching/rotation). */
  FLUID_STRUCTURE = 3,		/*!< \brief Fluid structure defromation. */
  EXTERNAL = 4,  /*!< \brief Arbitrary grid motion specified by external files at each time step. */
  EXTERNAL_ROTATION = 5,  /*!< \brief Arbitrary grid motion specified by external files at each time step with rigid rotation. */
  AEROELASTIC = 6,    /*!< \brief Simulation with aeroelastic motion. */
  MOVING_WALL = 7,    /*!< \brief Simulation with moving walls (translation/rotation). */
  ROTATING_FRAME = 8,    /*!< \brief Simulation in a rotating frame. */
  ELASTICITY = 9,    /*!< \brief Linear Elasticity. */
  AEROELASTIC_RIGID_MOTION = 10 /*!< \brief Simulation with rotation and aeroelastic motion. */
  
};
static const map<string, ENUM_GRIDMOVEMENT> GridMovement_Map = CCreateMap<string, ENUM_GRIDMOVEMENT>
("NONE", NO_MOVEMENT)
("DEFORMING", DEFORMING)
("RIGID_MOTION", RIGID_MOTION)
("FLUID_STRUCTURE", FLUID_STRUCTURE)
("EXTERNAL", EXTERNAL)
("EXTERNAL_ROTATION", EXTERNAL_ROTATION)
("AEROELASTIC", AEROELASTIC)
("ROTATING_FRAME", ROTATING_FRAME)
("ELASTICITY", ELASTICITY)
("MOVING_WALL", MOVING_WALL)
("AEROELASTIC_RIGID_MOTION", AEROELASTIC_RIGID_MOTION);

/*!
 * \brief type of wind gusts
 */
enum ENUM_GUST_TYPE {
  NO_GUST = 0,      /*!< \brief _______. */
  TOP_HAT = 1,      /*!< \brief Top-hat function shaped gust  */
  SINE = 2,         /*!< \brief  Sine shaped gust */
  ONE_M_COSINE = 3, /*!< \brief  1-cosine shaped gust */
  VORTEX = 4,       /*!< \brief  A gust made from vortices */
  EOG = 5           /*!< \brief  An extreme operating gust */
};
static const map<string, ENUM_GUST_TYPE> Gust_Type_Map = CCreateMap<string, ENUM_GUST_TYPE>
("NONE", NO_GUST)
("TOP_HAT", TOP_HAT)
("SINE", SINE)
("ONE_M_COSINE", ONE_M_COSINE)
("VORTEX", VORTEX)
("EOG", EOG);

/*!
 * \brief type of wind direction
 */
enum ENUM_GUST_DIR {
  X_DIR = 0,        /*!< \brief _______. */
  Y_DIR = 1, 		 /*!< \brief _______. */
};
static const map<string, ENUM_GUST_DIR> Gust_Dir_Map = CCreateMap<string, ENUM_GUST_DIR>
("X_DIR", X_DIR)
("Y_DIR", Y_DIR);

// If you add to ENUM_CENTERED, you must also add the option to ENUM_CONVECTIVE
/*!
 * \brief types of centered spatial discretizations
 */
enum ENUM_CENTERED {
  NO_CENTERED = 0,    /*!< \brief No centered scheme is used. */
  JST = 1,            /*!< \brief Jameson-Smith-Turkel centered numerical method. */
  LAX = 2,            /*!< \brief Lax-Friedrich centered numerical method. */
  JST_KE = 4          /*!< \brief Kinetic Energy preserving Jameson-Smith-Turkel centered numerical method. */
};
static const map<string, ENUM_CENTERED> Centered_Map = CCreateMap<string, ENUM_CENTERED>
("NONE", NO_CENTERED)
("JST", JST)
("JST_KE", JST_KE)
("LAX-FRIEDRICH", LAX);


// If you add to ENUM_UPWIND, you must also add the option to ENUM_CONVECTIVE
/*!
 * \brief types of upwind spatial discretizations
 */
enum ENUM_UPWIND {
  NO_UPWIND = 0,              /*!< \brief No upwind scheme is used. */
  ROE = 1,                    /*!< \brief Roe's upwind numerical method. */
  SCALAR_UPWIND = 2,          /*!< \brief Scalar upwind numerical method. */
  AUSM = 3,                   /*!< \brief AUSM numerical method. */
  HLLC = 4,                   /*!< \brief HLLC numerical method. */
  SW = 5,                     /*!< \brief Steger-Warming method. */
  MSW = 6,                    /*!< \brief Modified Steger-Warming method. */
  TURKEL = 7,                 /*!< \brief Roe-Turkel's upwind numerical method. */
  AUSMPWPLUS = 8,             /*!< \brief AUSMPW+ numerical method. */
  CUSP = 9,                   /*!< \brief Convective upwind and split pressure numerical method. */
  CONVECTIVE_TEMPLATE = 10    /*!< \brief Template for new numerical method . */
};
static const map<string, ENUM_UPWIND> Upwind_Map = CCreateMap<string, ENUM_UPWIND>
("NONE", NO_UPWIND)
("ROE", ROE)
("TURKEL_PREC", TURKEL)
("AUSM", AUSM)
("AUSMPW+", AUSMPWPLUS)
("HLLC", HLLC)
("SW", SW)
("MSW", MSW)
("CUSP", CUSP)
("SCALAR_UPWIND", SCALAR_UPWIND)
("CONVECTIVE_TEMPLATE", CONVECTIVE_TEMPLATE);

/*!
 * \brief Spatial numerical order integration
 */
enum ENUM_SPATIAL_ORDER {
  FIRST_ORDER = 0,        /*!< \brief First order */
  SECOND_ORDER = 1,        /*!< \brief Second order. */
  SECOND_ORDER_LIMITER = 2 /*!< \brief Second order with limiter. */
};
static const map<string, ENUM_SPATIAL_ORDER> SpatialOrder_Map = CCreateMap<string, ENUM_SPATIAL_ORDER>
("1ST_ORDER", FIRST_ORDER)
("2ND_ORDER", SECOND_ORDER)
("2ND_ORDER_LIMITER", SECOND_ORDER_LIMITER);

/*!
 * \brief types of slope limiters
 */
enum ENUM_LIMITER {
  VENKATAKRISHNAN = 0,	/*!< \brief Slope limiter using Venkatakrisnan method. */
  MINMOD = 1,           /*!< \brief Slope limiter using minmod method. */
  SHARP_EDGES = 2       /*!< \brief Slope limiter using sharp edges. */
};
static const map<string, ENUM_LIMITER> Limiter_Map = CCreateMap<string, ENUM_LIMITER>
("VENKATAKRISHNAN", VENKATAKRISHNAN)
("MINMOD", MINMOD)
("SHARP_EDGES", SHARP_EDGES);

/*!
 * \brief types of viscous term discretizations
 */
enum ENUM_VISCOUS {
  NO_VISCOUS = 0,               /*!< \brief No viscous term computation. */
  AVG_GRAD = 1,			/*!< \brief Average of gradients method for viscous term computation. */
  AVG_GRAD_CORRECTED = 2,	/*!< \brief Average of gradients with correction for viscous term computation. */
  GALERKIN = 3			/*!< \brief Galerkin method for viscous term computation. */
};
static const map<string, ENUM_VISCOUS> Viscous_Map = CCreateMap<string, ENUM_VISCOUS>
("NONE", NO_VISCOUS)
("AVG_GRAD", AVG_GRAD)
("AVG_GRAD_CORRECTED", AVG_GRAD_CORRECTED)
("GALERKIN", GALERKIN);

/*!
 * \brief types of source term methods to use
 */
enum ENUM_SOURCE {
  NO_SOURCE = 0,                /*!< \brief No source term. */
  PIECEWISE_CONSTANT = 1,	/*!< \brief Numerical method for source term in flow equations. */
  CHARGE_DIST = 2,		/*!< \brief Numerical method for source term in charge distribution. */
  SOURCE_TEMPLATE = 4           /*!< \brief Template for New numerical method for source term. */
};
static const map<string, ENUM_SOURCE> Source_Map = CCreateMap<string, ENUM_SOURCE>
("NONE", NO_SOURCE)
("PIECEWISE_CONSTANT", PIECEWISE_CONSTANT)
("CHARGE_DIST", CHARGE_DIST)
("TEMPLATE_SOURCE_METHOD", SOURCE_TEMPLATE);

/*!
 * \brief types of methods used to calculate source term Jacobians
 */
enum ENUM_SOURCEJAC {
  NO_JACOBIAN = 0,             /*!< \brief No source term Jacobian. */
  FINITE_DIFF = 1,	/*!< \brief Numerical method for source term in flow equations. */
  AUTO_DIFF = 2		/*!< \brief Numerical method for source term in charge distribution. */
};
static const map<string, ENUM_SOURCEJAC> SourceJac_Map = CCreateMap<string, ENUM_SOURCEJAC>
("NO_JACOBIAN", NO_JACOBIAN)
("FINITE_DIFF", FINITE_DIFF)
("AUTO_DIFF", AUTO_DIFF);

/*!
 * \brief types of turbulent models
 */
enum ENUM_TURB_MODEL {
  NO_TURB_MODEL = 0,            /*!< \brief No turbulence model. */
  SA = 1,                       /*!< \brief Kind of Turbulent model (Spalart-Allmaras). */
  SST = 2,       		/*!< \brief Kind of Turbulence model (Menter SST). */
  ML  = 3       		/*!< \brief Kind of Turbulence model (Machine Learning). */
};
static const map<string, ENUM_TURB_MODEL> Turb_Model_Map = CCreateMap<string, ENUM_TURB_MODEL>
("NONE", NO_TURB_MODEL)
("SA", SA)
("SST", SST)
("ML", ML);

/*!
 * \brief types of transition models
 */
enum ENUM_TRANS_MODEL {
  NO_TRANS_MODEL = 0,            /*!< \brief No transition model. */
  LM = 1												/*!< \brief Kind of transition model (LM for Spalart-Allmaras). */
};
static const map<string, ENUM_TRANS_MODEL> Trans_Model_Map = CCreateMap<string, ENUM_TRANS_MODEL>
("NONE", NO_TRANS_MODEL)
("LM", LM);

/*!
 * \brief type of time integration schemes
 */
enum ENUM_TIME_INT {
  RUNGE_KUTTA_EXPLICIT = 1,	/*!< \brief Explicit Runge-Kutta time integration definition. */
  EULER_EXPLICIT = 2,   	/*!< \brief Explicit Euler time integration definition. */
  EULER_IMPLICIT = 3   	/*!< \brief Implicit Euler time integration definition. */
};
static const map<string, ENUM_TIME_INT> Time_Int_Map = CCreateMap<string, ENUM_TIME_INT>
("RUNGE-KUTTA_EXPLICIT", RUNGE_KUTTA_EXPLICIT)
("EULER_EXPLICIT", EULER_EXPLICIT)
("EULER_IMPLICIT", EULER_IMPLICIT);

/*!
 * \brief types of schemes to compute the flow gradient
 */
enum ENUM_FLOW_GRADIENT {
  GREEN_GAUSS = 1,		/*!< \brief Gradients computation using Green Gauss theorem. */
  WEIGHTED_LEAST_SQUARES = 2	/*!< \brief Gradients computation using Weighted Least Squares. */
};
static const map<string, ENUM_FLOW_GRADIENT> Gradient_Map = CCreateMap<string, ENUM_FLOW_GRADIENT>
("GREEN_GAUSS", GREEN_GAUSS)
("WEIGHTED_LEAST_SQUARES", WEIGHTED_LEAST_SQUARES);

/*!
 * \brief types of action to take on a geometry structure
 */
enum GEOMETRY_ACTION {
  ALLOCATE = 0,     /*!<  \brief Allocate geometry structure. */
  UPDATE = 1       /*!<  \brief Update geometry structure (grid moving, adaptation, etc.). */
};

/*!
 * \brief types of action to perform when doing the geometry evaluation
 */
enum GEOMETRY_MODE {
  FUNCTION = 0,     /*!<  \brief Geometrical analysis. */
  GRADIENT = 1      /*!<  \brief Geometrical analysis and gradient using finite differences. */
};
static const map<string, GEOMETRY_MODE> GeometryMode_Map = CCreateMap<string, GEOMETRY_MODE>
("FUNCTION", FUNCTION)
("GRADIENT", GRADIENT);

/*!
 * \brief types of boundary conditions
 */
enum BC_TYPE {
  EULER_WALL = 1,		/*!< \brief Boundary Euler wall definition. */
  FAR_FIELD = 2,		/*!< \brief Boundary far-field definition. */
  SYMMETRY_PLANE = 3,   	/*!< \brief Boundary symmetry plane definition. */
  INLET_FLOW = 5,		/*!< \brief Boundary inlet flow definition. */
  OUTLET_FLOW = 6,		/*!< \brief Boundary outlet flow definition. */
  PERIODIC_BOUNDARY = 7,	/*!< \brief Periodic boundary definition. */
  NEARFIELD_BOUNDARY = 8,	/*!< \brief Near-Field boundary definition. */
  ELECTRODE_BOUNDARY = 9,	/*!< \brief Electrode boundary definition. */
  DIELEC_BOUNDARY = 10,	/*!< \brief Dipoisson boundary definition. */
  CUSTOM_BOUNDARY = 11,         /*!< \brief custom boundary definition. */
  INTERFACE_BOUNDARY = 12,	/*!< \brief Domain interface boundary definition. */
  DIRICHLET = 13,		/*!< \brief Boundary Euler wall definition. */
  NEUMANN = 14,		/*!< \brief Boundary Neumann definition. */
  DISPLACEMENT_BOUNDARY = 15,		/*!< \brief Boundary displacement definition. */
  LOAD_BOUNDARY = 16,		/*!< \brief Boundary Load definition. */
  FLOWLOAD_BOUNDARY = 17,		/*!< \brief Boundary Load definition. */
  ELEC_DIELEC_BOUNDARY = 22,	/*!< \brief Dipoisson boundary definition for the poissonal potential. */
  ELEC_NEUMANN = 23,		/*!< \brief Boundary Neumann definition. */
  SUPERSONIC_INLET = 24,		/*!< \brief Boundary supersonic inlet definition. */
  NACELLE_INFLOW = 25,		/*!< \brief Boundary nacelle inflow. */
  NACELLE_EXHAUST = 26,		/*!< \brief Boundary nacelle exhaust. */
  ISOTHERMAL = 28,      /*!< \brief No slip isothermal wall boundary condition. */
  HEAT_FLUX  = 29,      /*!< \brief No slip constant heat flux wall boundary condition. */
  PRESSURE_BOUNDARY = 30,   	/*!< \brief Pressure boundary condition. */
  HEAT_FLUX_NONCATALYTIC = 31, /*!< \brief No-slip, constant heat flux, noncatalytic bc. */
  HEAT_FLUX_CATALYTIC= 32, /*!< \brief No-slip, constant heat flux, catalytic bc. */
  ISOTHERMAL_NONCATALYTIC = 33, /*!< \brief No-slip, constant temperature, noncatalytic bc. */
  ISOTHERMAL_CATALYTIC = 34, /*!< \brief No-slip, constant temperature, catalytic bc. */
  ACTDISK_INLET = 35,	/*!< \brief Actuator disk inlet boundary definition. */
  ACTDISK_OUTLET = 36,	/*!< \brief Actuator disk outlet boundary definition. */
  SEND_RECEIVE = 99		/*!< \brief Boundary send-receive definition. */
};

/*!
 * \brief types inlet boundary treatments
 */
enum INLET_TYPE {
  TOTAL_CONDITIONS = 1,		/*!< \brief User specifies total pressure, total temperature, and flow direction. */
  MASS_FLOW = 2           /*!< \brief User specifies density and velocity (mass flow). */
};
static const map<string, INLET_TYPE> Inlet_Map = CCreateMap<string, INLET_TYPE>
("TOTAL_CONDITIONS", TOTAL_CONDITIONS)
("MASS_FLOW", MASS_FLOW);

/*!
 * \brief types of geometric entities based on VTK nomenclature
 */
enum GEO_TYPE {
  VERTEX = 1,   		/*!< \brief VTK nomenclature for defining a vertex element. */
  LINE = 3,			/*!< \brief VTK nomenclature for defining a line element. */
  TRIANGLE = 5, 		/*!< \brief VTK nomenclature for defining a triangle element. */
  RECTANGLE = 9,		/*!< \brief VTK nomenclature for defining a rectangle element. */
  TETRAHEDRON = 10,     	/*!< \brief VTK nomenclature for defining a tetrahedron element. */
  HEXAHEDRON = 12,      	/*!< \brief VTK nomenclature for defining a hexahedron element. */
  WEDGE = 13,     		/*!< \brief VTK nomenclature for defining a wedge element. */
  PYRAMID = 14  		/*!< \brief VTK nomenclature for defining a pyramid element. */
};

/*!
 * \brief types of objective functions
 */
enum ENUM_OBJECTIVE {
  DRAG_COEFFICIENT = 1, 	      /*!< \brief Drag objective function definition. */
  LIFT_COEFFICIENT = 2, 	      /*!< \brief Lift objective function definition. */
  SIDEFORCE_COEFFICIENT = 3,	  /*!< \brief Side force objective function definition. */
  EFFICIENCY = 4,		            /*!< \brief Efficiency objective function definition. */
  INVERSE_DESIGN_PRESSURE = 5,	/*!< \brief Pressure objective function definition (inverse design). */
  INVERSE_DESIGN_HEATFLUX = 6,  /*!< \brief Heat flux objective function definition (inverse design). */
  TOTAL_HEATFLUX = 7,           /*!< \brief Total heat flux. */
  MAXIMUM_HEATFLUX = 8,         /*!< \brief Maximum heat flux. */
  MOMENT_X_COEFFICIENT = 9,	    /*!< \brief Pitching moment objective function definition. */
  MOMENT_Y_COEFFICIENT = 10,    /*!< \brief Rolling moment objective function definition. */
  MOMENT_Z_COEFFICIENT = 11,    /*!< \brief Yawing objective function definition. */
  EQUIVALENT_AREA = 12,		      /*!< \brief Equivalent area objective function definition. */
  NEARFIELD_PRESSURE = 13,	    /*!< \brief NearField Pressure objective function definition. */
  FORCE_X_COEFFICIENT = 14,	    /*!< \brief X-direction force objective function definition. */
  FORCE_Y_COEFFICIENT = 15,	    /*!< \brief Y-direction force objective function definition. */
  FORCE_Z_COEFFICIENT = 16,	    /*!< \brief Z-direction force objective function definition. */
  THRUST_COEFFICIENT = 17,		  /*!< \brief Thrust objective function definition. */
  TORQUE_COEFFICIENT = 18,		  /*!< \brief Torque objective function definition. */
  FIGURE_OF_MERIT = 19,		      /*!< \brief Rotor Figure of Merit objective function definition. */
  FREE_SURFACE = 20,				    /*!< \brief Free Surface objective function definition. */
  MAX_THICKNESS = 21,           /*!< \brief Maximum thickness. */
  MIN_THICKNESS = 22,           /*!< \brief Minimum thickness. */
  MAX_THICK_SEC1 = 23,          /*!< \brief Maximum thickness in section 1. */
  MAX_THICK_SEC2 = 24,          /*!< \brief Maximum thickness in section 2. */
  MAX_THICK_SEC3 = 25,          /*!< \brief Maximum thickness in section 3. */
  MAX_THICK_SEC4 = 26,          /*!< \brief Maximum thickness in section 4. */
  MAX_THICK_SEC5 = 27           /*!< \brief Maximum thickness in section 5. */
};
static const map<string, ENUM_OBJECTIVE> Objective_Map = CCreateMap<string, ENUM_OBJECTIVE>
("DRAG", DRAG_COEFFICIENT)
("LIFT", LIFT_COEFFICIENT)
("SIDEFORCE", SIDEFORCE_COEFFICIENT)
("EFFICIENCY", EFFICIENCY)
("INVERSE_DESIGN_PRESSURE", INVERSE_DESIGN_PRESSURE)
("INVERSE_DESIGN_HEATFLUX", INVERSE_DESIGN_HEATFLUX)
("MOMENT_X", MOMENT_X_COEFFICIENT)
("MOMENT_Y", MOMENT_Y_COEFFICIENT)
("MOMENT_Z", MOMENT_Z_COEFFICIENT)
("EQUIVALENT_AREA", EQUIVALENT_AREA)
("NEARFIELD_PRESSURE", NEARFIELD_PRESSURE)
("FORCE_X", FORCE_X_COEFFICIENT)
("FORCE_Y", FORCE_Y_COEFFICIENT)
("FORCE_Z", FORCE_Z_COEFFICIENT)
("THRUST", THRUST_COEFFICIENT)
("TORQUE", TORQUE_COEFFICIENT)
("TOTAL_HEATFLUX", TOTAL_HEATFLUX)
("MAXIMUM_HEATFLUX", MAXIMUM_HEATFLUX)
("FIGURE_OF_MERIT", FIGURE_OF_MERIT)
("FREE_SURFACE", FREE_SURFACE)
("MAX_THICKNESS", MAX_THICKNESS)
("MIN_THICKNESS", MIN_THICKNESS)
("MAX_THICK_SEC1", MAX_THICK_SEC1)
("MAX_THICK_SEC2", MAX_THICK_SEC2)
("MAX_THICK_SEC3", MAX_THICK_SEC3)
("MAX_THICK_SEC4", MAX_THICK_SEC4)
("MAX_THICK_SEC5", MAX_THICK_SEC5);

/*!
 * \brief types of Continuous equations
 */
enum ENUM_CONTINUOUS_EQNS {
  EULER_EQNS= 1, 	/*!< \brief Euler equations. */
  NAVIER_STOKES_EQNS = 2 	/*!< \brief Navier Stokes equations. */
};
static const map<string, ENUM_CONTINUOUS_EQNS> ContinuousEqns_Map = CCreateMap<string, ENUM_CONTINUOUS_EQNS>
("EULER", EULER_EQNS)
("NAVIER_STOKES", NAVIER_STOKES_EQNS);

/*!
 * \brief types of Discrete equations
 */
enum ENUM_DISCRETE_EQNS {
  NONE_EQNS= 1, 	/*!< \brief No equations. */
  SA_EQNS = 2, 	/*!< \brief Spallart-Almaras equations. */
  SST_EQNS = 2 	/*!< \brief SST equations. */
};
static const map<string, ENUM_DISCRETE_EQNS> DiscreteEqns_Map = CCreateMap<string, ENUM_DISCRETE_EQNS>
("NONE", NONE_EQNS)
("SA", SA_EQNS)
("SST", SST_EQNS);

/*!
 * \brief types of sensitivities to compute
 */
enum ENUM_SENS {
  SENS_GEOMETRY = 1,    	/*!< \brief Geometrical sensitivity. */
  SENS_MACH = 2,		/*!< \brief Mach number sensitivity. */
  SENS_AOA = 3, 		/*!< \brief Angle of attack sensitivity. */
  SENS_AOS = 4  		/*!< \brief Angle of Sideslip sensitivity. */
};
static const map<string, ENUM_SENS> Sens_Map = CCreateMap<string, ENUM_SENS>
("SENS_GEOMETRY", SENS_GEOMETRY)
("SENS_MACH", SENS_MACH)
("SENS_AOA", SENS_AOA)
("SENS_AOS", SENS_AOS);

/*!
 * \brief types of linearized objective functions
 */
enum ENUM_LINEAR_OBJ {
  DELTA_DRAG_COEFFICIENT = 1,	/*!< \brief Linearized Drag objective function definition. */
  DELTA_LIFT_COEFFICIENT = 2	/*!< \brief Linearized Lift objective function definition. */
};
static const map<string, ENUM_LINEAR_OBJ> Linear_Obj_Map = CCreateMap<string, ENUM_LINEAR_OBJ>
("DELTA_DRAG", DELTA_DRAG_COEFFICIENT)
("DELTA_LIFT", DELTA_LIFT_COEFFICIENT);

/*!
 * \brief types of grid adaptation/refinement
 */
enum ENUM_ADAPT {
  NO_ADAPT = 0,                 /*!< \brief No grid adaptation. */
  FULL = 1,			/*!< \brief Do a complete grid refinement of all the computational grids. */
  FULL_FLOW = 2,		/*!< \brief Do a complete grid refinement of the flow grid. */
  FULL_ADJOINT = 3,		/*!< \brief Do a complete grid refinement of the adjoint grid. */
  FULL_LINEAR = 4,		/*!< \brief Do a complete grid refinement of the linear grid. */
  GRAD_FLOW = 5,		/*!< \brief Do a gradient based grid adaptation of the flow grid. */
  GRAD_ADJOINT = 6,		/*!< \brief Do a gradient based grid adaptation of the adjoint grid. */
  GRAD_FLOW_ADJ = 7,		/*!< \brief Do a gradient based grid adaptation of the flow and adjoint grid. */
  ROBUST = 8,			/*!< \brief Apply a robust grid adaptation (residual based). */
  COMPUTABLE = 9,		/*!< \brief Apply a computable error grid adaptation. */
  REMAINING = 10,		/*!< \brief Apply a remaining error grid adaptation. */
  COMPUTABLE_ROBUST = 11,	/*!< \brief Apply a computable robust grid adaptation (using linearized problem). */
  WAKE = 12,			/*!< \brief Do a grid refinement on the wake. */
  SMOOTHING = 14,		/*!< \brief Do a grid smoothing of the geometry. */
  SUPERSONIC_SHOCK = 15,	/*!< \brief Do a grid smoothing. */
  PERIODIC = 16,	/*!< \brief Do a grid smoothing. */
  TWOPHASE = 17			/*!< \brief Do a grid refinement on the free surface interphase. */
};
static const map<string, ENUM_ADAPT> Adapt_Map = CCreateMap<string, ENUM_ADAPT>
("NONE", NO_ADAPT)
("FULL", FULL)
("FULL_FLOW", FULL_FLOW)
("FULL_ADJOINT", FULL_ADJOINT)
("FULL_LINEAR", FULL_LINEAR)
("GRAD_FLOW", GRAD_FLOW)
("GRAD_ADJOINT", GRAD_ADJOINT)
("GRAD_FLOW_ADJ", GRAD_FLOW_ADJ)
("ROBUST", ROBUST)
("COMPUTABLE", COMPUTABLE)
("REMAINING", REMAINING)
("COMPUTABLE_ROBUST", COMPUTABLE_ROBUST)
("WAKE", WAKE)
("SMOOTHING", SMOOTHING)
("SUPERSONIC_SHOCK", SUPERSONIC_SHOCK)
("PERIODIC", PERIODIC)
("TWOPHASE", TWOPHASE);

/*!
 * \brief types of input file formats
 */
enum ENUM_INPUT {
  SU2 = 1,                       /*!< \brief SU2 input format. */
  CGNS = 2,                     /*!< \brief CGNS input format for the computational grid. */
  NETCDF_ASCII = 3      	/*!< \brief ASCII NETCDF input format for the computational grid. */
};
static const map<string, ENUM_INPUT> Input_Map = CCreateMap<string, ENUM_INPUT>
("SU2", SU2)
("CGNS", CGNS)
("NETCDF_ASCII", NETCDF_ASCII);

const int CGNS_STRING_SIZE = 33;/*!< \brief Length of strings used in the CGNS format. */

/*!
 * \brief type of solution output file formats
 */
enum ENUM_OUTPUT {
  TECPLOT = 1,  		/*!< \brief Tecplot format for the solution output. */
  EXCEL = 2,			/*!< \brief Excel format for the solution output. */
  CSV = 3,			/*!< \brief Comma-separated values format for the solution output. */
  TECPLOT_BINARY = 4,  		/*!< \brief Tecplot binary format for the solution output. */
  CGNS_SOL = 5,  		/*!< \brief CGNS format for the solution output. */
  PARAVIEW = 6  		/*!< \brief Paraview format for the solution output. */
};
static const map<string, ENUM_OUTPUT> Output_Map = CCreateMap<string, ENUM_OUTPUT>
("TECPLOT", TECPLOT)
("EXCEL", EXCEL)
("CSV", CSV)
("TECPLOT_BINARY", TECPLOT_BINARY)
("CGNS", CGNS_SOL)
("PARAVIEW", PARAVIEW);

/*!
 * \brief type of solution output variables
 */
enum ENUM_OUTPUT_VARS {
  DENSITY = 1,      /*!< \brief Density. */
  VEL_X = 2,        /*!< \brief X-component of velocity. */
  VEL_Y = 3,        /*!< \brief Y-component of velocity. */
  VEL_Z = 4,        /*!< \brief Z-component of velocity. */
  PRESSURE = 5, 		/*!< \brief Static pressure. */
  MACH = 6,         /*!< \brief Mach number. */
  TEMPERATURE = 7,  /*!< \brief Temperature. */
  LAM_VISC = 8,     /*!< \brief Laminar viscosity. */
  EDDY_VISC = 9     /*!< \brief Eddy viscosity. */
};
static const map<string, ENUM_OUTPUT_VARS> Output_Vars_Map = CCreateMap<string, ENUM_OUTPUT_VARS>
("DENSITY", DENSITY)
("VEL_X", VEL_X)
("VEL_Y", VEL_Y)
("VEL_Z", VEL_Z)
("PRESSURE", PRESSURE)
("MACH", MACH)
("TEMPERATURE", TEMPERATURE)
("LAM_VISC", LAM_VISC)
("EDDY_VISC", EDDY_VISC);

/*!
 * \brief types of design parameterizations
 */
enum ENUM_PARAM {
  FFD_SETTING = 0,		/*!< \brief No surface deformation. */
  HICKS_HENNE = 1,		/*!< \brief Hicks-Henne bump function for airfoil deformation. */
  NACA_4DIGITS = 6,		/*!< \brief The four digits NACA airfoil family as design variables. */
  DISPLACEMENT = 8,		/*!< \brief Surface movement as design variable. */
  ROTATION = 9,			/*!< \brief Surface rotation as design variable. */
  FFD_CONTROL_POINT = 10,	/*!< \brief Free form deformation for 3D design (change a control point). */
  FFD_DIHEDRAL_ANGLE = 11,	/*!< \brief Free form deformation for 3D design (change the dihedral angle). */
  FFD_TWIST_ANGLE = 12,		/*!< \brief Free form deformation for 3D design (change the twist angle). */
  FFD_ROTATION = 13,		/*!< \brief Free form deformation for 3D design (rotation around a line). */
  FFD_CAMBER = 14,		/*!< \brief Free form deformation for 3D design (camber change). */
  FFD_THICKNESS = 15,		/*!< \brief Free form deformation for 3D design (thickness change). */
  PARABOLIC = 17,		/*!< \brief Parabolic airfoil definition as design variables. */
  OBSTACLE = 18,		        /*!< \brief Obstacle for free surface optimization. */
  STRETCH = 19,		        /*!< \brief Stretch one side of a channel. */
  SURFACE_FILE = 20,		   /*!< Nodal coordinates set using a surface file. */
  COSINE_BUMP = 21,		/*!< \brief Gauss bump function for airfoil deformation. */
  FOURIER = 22,		/*!< \brief Fourier function for airfoil deformation. */
  SPHERICAL = 23,		/*!< \brief Spherical geometry parameterization with spline-based radial profile. */
  AIRFOIL = 24,		/*!< \brief Airfoil definition as design variables. */
  FFD_CONTROL_POINT_2D = 25,	/*!< \brief Free form deformation for 2D design (change a control point). */
  FFD_CAMBER_2D = 26,		/*!< \brief Free form deformation for 3D design (camber change). */
  FFD_THICKNESS_2D = 27		/*!< \brief Free form deformation for 3D design (thickness change). */
};
static const map<string, ENUM_PARAM> Param_Map = CCreateMap<string, ENUM_PARAM>
("FFD_SETTING", FFD_SETTING)
("FFD_CONTROL_POINT_2D", FFD_CONTROL_POINT_2D)
("FFD_CAMBER_2D", FFD_CAMBER_2D)
("FFD_THICKNESS_2D", FFD_THICKNESS_2D)
("HICKS_HENNE", HICKS_HENNE)
("SPHERICAL", SPHERICAL)
("NACA_4DIGITS", NACA_4DIGITS)
("DISPLACEMENT", DISPLACEMENT)
("ROTATION", ROTATION)
("FFD_CONTROL_POINT", FFD_CONTROL_POINT)
("FFD_DIHEDRAL_ANGLE", FFD_DIHEDRAL_ANGLE)
("FFD_TWIST_ANGLE", FFD_TWIST_ANGLE)
("FFD_ROTATION", FFD_ROTATION)
("FFD_CAMBER", FFD_CAMBER)
("FFD_THICKNESS", FFD_THICKNESS)
("PARABOLIC", PARABOLIC)
("OBSTACLE", OBSTACLE)
("STRETCH", STRETCH)
("COSINE_BUMP", COSINE_BUMP)
("FOURIER", FOURIER)
("AIRFOIL", AIRFOIL)
("SURFACE_FILE", SURFACE_FILE);

/*!
 * \brief types of solvers for solving linear systems
 */
enum ENUM_LINEAR_SOLVER {
  STEEPEST_DESCENT = 1,		/*!< \brief Steepest descent method for point inversion algoritm (Free-Form). */
  NEWTON = 2,			/*!< \brief Newton method for point inversion algorithm (Free-Form). */
  QUASI_NEWTON = 3,		/*!< \brief Quasi Newton method for point inversion algorithm (Free-Form). */
  CONJUGATE_GRADIENT = 4,	/*!< \brief Preconditionated conjugate gradient method for grid deformation. */
  FGMRES = 5,    	/*!< \brief Flexible Generalized Minimal Residual method. */
  BCGSTAB = 6,	/*!< \brief BCGSTAB - Biconjugate Gradient Stabilized Method (main solver). */
  RFGMRES = 7,  /*!< \brief Flexible Generalized Minimal Residual method with restart. */
  MULTIGRID = 8,    	/*!< \brief Linear Multigrid solver. */
  SMOOTHER_LUSGS = 9,  /*!< \brief LU_SGS smoother. */
  SMOOTHER_JACOBI = 10,  /*!< \brief Jacobi smoother. */
  SMOOTHER_ILU = 11,  /*!< \brief ILU smoother. */
  SMOOTHER_LINELET = 12  /*!< \brief Linelet smoother. */
};
static const map<string, ENUM_LINEAR_SOLVER> Linear_Solver_Map = CCreateMap<string, ENUM_LINEAR_SOLVER>
("STEEPEST_DESCENT", STEEPEST_DESCENT)
("NEWTON", NEWTON)
("QUASI_NEWTON", QUASI_NEWTON)
("CONJUGATE_GRADIENT", CONJUGATE_GRADIENT)
("BCGSTAB", BCGSTAB)
("FGMRES", FGMRES)
("RFGMRES", RFGMRES)
("MULTIGRID", MULTIGRID)
("SMOOTHER_LUSGS", SMOOTHER_LUSGS)
("SMOOTHER_JACOBI", SMOOTHER_JACOBI)
("SMOOTHER_LINELET", SMOOTHER_LINELET)
("SMOOTHER_ILU0", SMOOTHER_ILU);

/*!
 * \brief types of sensitivity smoothing
 */
enum ENUM_SENS_SMOOTHING {
  NO_SMOOTH = 0,		/*!< \brief No smoothing. */
  SOBOLEV = 1,		/*!< \brief Sobolev gradient smoothing. */
  BIGRID = 2	/*!< \brief Bi-grid technique smoothing. */
};
static const map<string, ENUM_SENS_SMOOTHING> Sens_Smoothing_Map = CCreateMap<string, ENUM_SENS_SMOOTHING>
("NONE", NO_SMOOTH)
("SOBOLEV", SOBOLEV)
("BIGRID", BIGRID);

/*!
 * \brief types of preconditioners for the linear solver
 */
enum ENUM_LINEAR_SOLVER_PREC {
  JACOBI = 1,		/*!< \brief Jacobi preconditioner. */
  LU_SGS = 2,		/*!< \brief LU SGS preconditioner. */
  LINELET = 3,  /*!< \brief Line implicit preconditioner. */
  ILU = 4       /*!< \brief ILU(0) preconditioner. */
};
static const map<string, ENUM_LINEAR_SOLVER_PREC> Linear_Solver_Prec_Map = CCreateMap<string, ENUM_LINEAR_SOLVER_PREC>
("JACOBI", JACOBI)
("LU_SGS", LU_SGS)
("LINELET", LINELET)
("ILU0", ILU);

/*!
 * \brief types of analytic definitions for various geometries
 */
enum ENUM_GEO_ANALYTIC {
  NO_GEO_ANALYTIC = 0,          /*!< \brief No analytic definition of the geometry. */
  NACA0012_AIRFOIL = 1, 	/*!< \brief Use the analytical definition of the NACA0012 for doing the grid adaptation. */
  NACA4412_AIRFOIL = 2, 	/*!< \brief Use the analytical definition of the NACA4412 for doing the grid adaptation. */
  CYLINDER = 3, 		/*!< \brief Use the analytical definition of a cylinder for doing the grid adaptation. */
  BIPARABOLIC = 4       	/*!< \brief Use the analytical definition of a biparabolic airfoil for doing the grid adaptation. */
};
static const map<string, ENUM_GEO_ANALYTIC> Geo_Analytic_Map = CCreateMap<string, ENUM_GEO_ANALYTIC>
("NONE", NO_GEO_ANALYTIC)
("NACA0012_AIRFOIL", NACA0012_AIRFOIL)
("NACA4412_AIRFOIL", NACA4412_AIRFOIL)
("CYLINDER", CYLINDER)
("BIPARABOLIC", BIPARABOLIC);

/*!
 * \brief types of axis orientation
 */
enum ENUM_AXIS_ORIENTATION {
  X_AXIS = 0,   /*!< \brief X axis orientation. */
  Y_AXIS = 1, 	/*!< \brief Y axis orientation. */
  Z_AXIS = 2    /*!< \brief Z axis orientation. */
};
static const map<string, ENUM_AXIS_ORIENTATION> Axis_Orientation_Map = CCreateMap<string, ENUM_AXIS_ORIENTATION>
("X_AXIS", X_AXIS)
("Y_AXIS", Y_AXIS)
("Z_AXIS", Z_AXIS);

/*!
 * \brief types of schemes for unsteady computations
 */
enum ENUM_UNSTEADY {
  STEADY = 0,             /*!< \brief A steady computation. */
  TIME_STEPPING = 1,		/*!< \brief Use a time stepping strategy for unsteady computations. */
  DT_STEPPING_1ST = 2,	/*!< \brief Use a dual time stepping strategy for unsteady computations (1st order). */
  DT_STEPPING_2ND = 3,	/*!< \brief Use a dual time stepping strategy for unsteady computations (2nd order). */
  ROTATIONAL_FRAME = 4,   /*!< \brief Use a rotational source term. */
  TIME_SPECTRAL = 5       	/*!< \brief Use a time spectral source term. */
  
};
static const map<string, ENUM_UNSTEADY> Unsteady_Map = CCreateMap<string, ENUM_UNSTEADY>
("NO", STEADY)
("TIME_STEPPING", TIME_STEPPING)
("DUAL_TIME_STEPPING-1ST_ORDER", DT_STEPPING_1ST)
("DUAL_TIME_STEPPING-2ND_ORDER", DT_STEPPING_2ND)
("TIME_SPECTRAL", TIME_SPECTRAL)
("ROTATIONAL_FRAME", ROTATIONAL_FRAME);

/*!
 * \brief types of criteria to determine when the solution is converged
 */
enum ENUM_CONVERGE_CRIT {
  CAUCHY = 1,			/*!< \brief Cauchy criteria to establish the convergence of the code. */
  RESIDUAL = 2			/*!< \brief Residual criteria to establish the convergence of the code. */
};
static const map<string, ENUM_CONVERGE_CRIT> Converge_Crit_Map = CCreateMap<string, ENUM_CONVERGE_CRIT>
("CAUCHY", CAUCHY)
("RESIDUAL", RESIDUAL);

/*!
 * \brief types of element stiffnesses imposed for FEA mesh deformation
 */
enum ENUM_DEFORM_STIFFNESS {
  CONSTANT_STIFFNESS = 0,               /*!< \brief Impose a constant stiffness for each element (steel). */
  INVERSE_VOLUME = 1,			/*!< \brief Impose a stiffness for each element that is inversely proportional to cell volume. */
  WALL_DISTANCE = 2			/*!< \brief Impose a stiffness for each element that is proportional to the distance from the deforming surface. */
};
static const map<string, ENUM_DEFORM_STIFFNESS> Deform_Stiffness_Map = CCreateMap<string, ENUM_DEFORM_STIFFNESS>
("CONSTANT_STIFFNESS", CONSTANT_STIFFNESS)
("INVERSE_VOLUME", INVERSE_VOLUME)
("WALL_DISTANCE", WALL_DISTANCE);

/* END_CONFIG_ENUMS */












class COptionBase{
private:
public:
  COptionBase(){};
  virtual  ~COptionBase() = 0;
  //  virtual string SetValue(string){SU2MPI::PrintAndFinalize("shouldn't be here"); return "";};
  virtual string SetValue(vector<string>) = 0;
  virtual void SetDefault() = 0;
  
  string optionCheckMultipleValues(vector<string> & option_value, string type_id, string option_name){
    if (option_value.size() != 1){
      string newString;
      newString.append(option_name);
      newString.append(": multiple values for type ");
      newString.append(type_id);
      return newString;
    }
    return "";
  }
  
  string badValue(vector<string> & option_value, string type_id, string option_name){
    string newString;
    newString.append(option_name);
    newString.append(": improper option value for type ");
    newString.append(type_id);
    return newString;
  }
};

inline COptionBase::~COptionBase(){}


template <class Tenum>
class COptionEnum : public COptionBase{
  
  map<string, Tenum> m;
  unsigned short & field; // Reference to the feildname
  Tenum def; // Default value
  string name; // identifier for the option
  
public:
  COptionEnum(string option_field_name, const map<string, Tenum> m, unsigned short & option_field, Tenum default_value) : field(option_field){
    this->m = m;
    this->def = default_value;
    this->name = option_field_name;
  }
  
  ~COptionEnum(){};
  string SetValue(vector<string> option_value){
    // Check if there is more than one string
    string out = optionCheckMultipleValues(option_value, "enum", this->name);
    if (out.compare("") != 0){
      return out;
    }
    
    // Check to see if the enum value is in the map
    if (this->m.find(option_value[0]) == m.end()){
      string str;
      str.append(this->name);
      str.append(": invalid option value ");
      str.append(option_value[0]);
      return str;
    }
    // If it is there, set the option value
    Tenum val = this->m[option_value[0]];
    this->field = val;
    return "";
  }
  
  void SetDefault(){
    this->field = this->def;
  }
};

class COptionDouble : public COptionBase{
  double & field; // Reference to the fieldname
  double def; // Default value
  string name; // identifier for the option
  
public:
  COptionDouble(string option_field_name, double & option_field, double default_value) : field(option_field){
    this->def = default_value;
    this->name = option_field_name;
  }
  
  ~COptionDouble(){};
  string SetValue(vector<string> option_value){
    // check if there is more than one value
    string out = optionCheckMultipleValues(option_value, "double", this->name);
    if (out.compare("") != 0){
      return out;
    }
    istringstream is(option_value[0]);
    double val;
    if (is >> val){
      this->field = val;
      return "";
    }
    return badValue(option_value, "double", this->name);
  }
  void SetDefault(){
    this->field = this->def;
  }
};

class COptionString : public COptionBase{
  string & field; // Reference to the fieldname
  string def; // Default value
  string name; // identifier for the option
  
public:
  COptionString(string option_field_name, string & option_field, string default_value) : field(option_field){
    this->def = default_value;
    this->name = option_field_name;
  }
  
  ~COptionString(){};
  string SetValue(vector<string> option_value){
    // check if there is more than one value
    string out = optionCheckMultipleValues(option_value, "double", this->name);
    if (out.compare("") != 0){
      return out;
    }
    this->field.assign(option_value[0]);
    return "";
  }
  void SetDefault(){
    this->field = this->def;
  }
};

class COptionInt : public COptionBase{
  int & field; // Reference to the feildname
  int def; // Default value
  string name; // identifier for the option
  
public:
  COptionInt(string option_field_name, int & option_field, int default_value) : field(option_field){
    this->def = default_value;
    this->name = option_field_name;
  }
  
  ~COptionInt(){};
  string SetValue(vector<string> option_value){
    string out = optionCheckMultipleValues(option_value, "int", this->name);
    if (out.compare("") != 0){
      return out;
    }
    istringstream is(option_value[0]);
    int val;
    if (is >> val){
      this->field = val;
      return "";
    }
    return badValue(option_value, "int", this->name);
  }
  void SetDefault(){
    this->field = this->def;
  }
};

class COptionULong : public COptionBase{
  unsigned long & field; // Reference to the feildname
  unsigned long def; // Default value
  string name; // identifier for the option
  
public:
  COptionULong(string option_field_name, unsigned long & option_field, unsigned long default_value) : field(option_field){
    this->def = default_value;
    this->name = option_field_name;
  }
  
  ~COptionULong(){};
  string SetValue(vector<string> option_value){
    string out = optionCheckMultipleValues(option_value, "unsigned long", this->name);
    if (out.compare("") != 0){
      return out;
    }
    istringstream is(option_value[0]);
    unsigned long val;
    if (is >> val){
      this->field = val;
      return "";
    }
    return badValue(option_value, "unsigned long", this->name);
  }
  void SetDefault(){
    this->field = this->def;
  }
};

class COptionUShort : public COptionBase{
  unsigned short & field; // Reference to the feildname
  unsigned short def; // Default value
  string name; // identifier for the option
  
public:
  COptionUShort(string option_field_name, unsigned short & option_field, unsigned short default_value) : field(option_field){
    this->def = default_value;
    this->name = option_field_name;
  }
  
  ~COptionUShort(){};
  string SetValue(vector<string> option_value){
    string out = optionCheckMultipleValues(option_value, "unsigned short", this->name);
    if (out.compare("") != 0){
      return out;
    }
    istringstream is(option_value[0]);
    unsigned short val;
    if (is >> val){
      this->field = val;
      return "";
    }
    return badValue(option_value, "unsigned short", this->name);
  }
  void SetDefault(){
    this->field = this->def;
  }
};

class COptionLong : public COptionBase{
  long & field; // Reference to the feildname
  long def; // Default value
  string name; // identifier for the option
  
public:
  COptionLong(string option_field_name, long & option_field, long default_value) : field(option_field){
    this->def = default_value;
    this->name = option_field_name;
  }
  
  ~COptionLong(){};
  string SetValue(vector<string> option_value){
    string out = optionCheckMultipleValues(option_value, "long", this->name);
    if (out.compare("") != 0){
      return out;
    }
    istringstream is(option_value[0]);
    long val;
    if (is >> val){
      this->field = val;
      return "";
    }
    return badValue(option_value, "long", this->name);
  }
  void SetDefault(){
    this->field = this->def;
  }
};


class COptionBool : public COptionBase{
  bool & field; // Reference to the feildname
  bool def; // Default value
  string name; // identifier for the option
  
public:
  COptionBool(string option_field_name, bool & option_field, bool default_value) : field(option_field){
    this->def = default_value;
    this->name = option_field_name;
  }
  
  ~COptionBool(){};
  string SetValue(vector<string> option_value){
    // check if there is more than one value
    string out = optionCheckMultipleValues(option_value, "bool", this->name);
    if (out.compare("") != 0){
      return out;
    }
    if (option_value[0].compare("YES") == 0){
      this->field = true;
      return "";
    }
    if (option_value[0].compare("NO") == 0){
      this->field = false;
      return "";
    }
    return badValue(option_value, "bool", this->name);
  }
  void SetDefault(){
    this->field = this->def;
  }
};

template <class Tenum>
class COptionEnumList : public COptionBase{
  
  map<string, Tenum> m;
  unsigned short * & field; // Reference to the feildname
  string name; // identifier for the option
  unsigned short & size;
  
public:
  COptionEnumList(string option_field_name, const map<string, Tenum> m, unsigned short * & option_field, unsigned short & list_size) : field(option_field) , size(list_size){
    this->m = m;
    this->name = option_field_name;
  }
  
  ~COptionEnumList(){};
  string SetValue(vector<string> option_value){
    if (option_value.size() == 1 && option_value[0].compare("NONE")==0){
      this->size = 0;
      return "";
    }
    // size is the length of the option list
    this->size = option_value.size();
    unsigned short * enums = new unsigned short[size];
    for(int i  = 0; i < this->size; i++){
      // Check to see if the enum value is in the map
      if (this->m.find(option_value[i]) == m.end()){
        string str;
        str.append(this->name);
        str.append(": invalid option value ");
        str.append(option_value[0]);
        return str;
      }
      // If it is there, set the option value
      enums[i] = this->m[option_value[0]];
    }
    this->field = enums;
    return "";
  }
  
  void SetDefault(){
    // No default to set
    size = 0;
  }
};

class COptionDoubleArray : public COptionBase{
  double * & field; // Reference to the feildname
  string name; // identifier for the option
  const int size;
  double * default_value;
  
public:
  COptionDoubleArray(string option_field_name, const int list_size, double * & option_field, double * default_value) : field(option_field), size(list_size){
    this->name = option_field_name;
    this->default_value = default_value;
  }
  
  ~COptionDoubleArray(){};
  string SetValue(vector<string> option_value){
    // Check that the size is correct
    if (option_value.size() != this->size){
      string newstring;
      newstring.append(this->name);
      newstring.append(": wrong number of arguments: ");
      stringstream ss;
      ss << this->size;
      newstring.append(ss.str());
      newstring.append(" expected, ");
      stringstream ss2;
      ss2 << option_value.size();
      newstring.append(ss2.str());
      newstring.append(" found");
      return newstring;
    }
    double * vals = new double[this->size];
    for(int i  = 0; i < this->size; i++){
      istringstream is(option_value[i]);
      double val;
      if (!(is >> val)){
        delete [] vals;
        return badValue(option_value, "double array", this->name);
      }
      vals[i] = val;
    }
    this->field = vals;
    return "";
  }
  
  void SetDefault(){
    this->field = this->default_value;
  }
};

class COptionDoubleList : public COptionBase{
  double * & field; // Reference to the feildname
  string name; // identifier for the option
  unsigned short & size;
  
public:
  COptionDoubleList(string option_field_name, unsigned short & list_size, double * & option_field) : field(option_field), size(list_size){
    this->name = option_field_name;
  }
  
  ~COptionDoubleList(){};
  string SetValue(vector<string> option_value){
    // The size is the length of option_value
    unsigned long option_size = option_value.size();
    if (option_size == 1 && option_value[0].compare("NONE")==0){
      // No options
      this->size = 0;
      return "";
    }
    
    this->size = option_size;
    
    // Parse all of the options
    double * vals = new double[option_size];
    for(int i  = 0; i < option_size; i++){
      istringstream is(option_value[i]);
      double val;
      if (!(is >> val)){
        delete [] vals;
        return badValue(option_value, "double list", this->name);
      }
      vals[i] = val;
    }
    this->field = vals;
    return "";
  }
  
  void SetDefault(){
    this->size = 0; // There is no default value for list
  }
};

class COptionUShortList : public COptionBase{
  unsigned short * & field; // Reference to the feildname
  string name; // identifier for the option
  unsigned short & size;
  
public:
  COptionUShortList(string option_field_name, unsigned short & list_size, unsigned short * & option_field) : field(option_field), size(list_size){
    this->name = option_field_name;
  }
  
  ~COptionUShortList(){};
  string SetValue(vector<string> option_value){
    // The size is the length of option_value
    unsigned long option_size = option_value.size();
    if (option_size == 1 && option_value[0].compare("NONE")==0){
      // No options
      this->size = 0;
      return "";
    }
    this->size = option_size;
    
    // Parse all of the options
    unsigned short * vals = new unsigned short[option_size];
    for(int i  = 0; i < option_size; i++){
      istringstream is(option_value[i]);
      unsigned short val;
      if (!(is >> val)){
        delete [] vals;
        return badValue(option_value, "unsigned short", this->name);
      }
      vals[i] = val;
    }
    this->field = vals;
    return "";
  }
  
  void SetDefault(){
    this->size = 0; // There is no default value for list
  }
};

class COptionStringList : public COptionBase{
  string * & field; // Reference to the feildname
  string name; // identifier for the option
  unsigned short & size;
  
public:
  COptionStringList(string option_field_name, unsigned short & list_size, string * & option_field) : field(option_field), size(list_size){
    this->name = option_field_name;
  }
  
  ~COptionStringList(){};
  string SetValue(vector<string> option_value){
    // The size is the length of option_value
    unsigned long option_size = option_value.size();
    if (option_size == 1 && option_value[0].compare("NONE")==0){
      this->size = 0;
      return "";
    }
    this->size = option_size;
    
    // Parse all of the options
    string * vals = new string[option_size];
    for(int i  = 0; i < option_size; i++){
      vals[i].assign(option_value[i]);
    }
    this->field = vals;
    return "";
  }
  
  void SetDefault(){
    this->size = 0; // There is no default value for list
  }
};

class COptionConvect : public COptionBase{
  string name; // identifier for the option
  unsigned short & space;
  unsigned short & centered;
  unsigned short & upwind;
  
public:
  COptionConvect(string option_field_name, unsigned short & space_field, unsigned short & centered_field, unsigned short & upwind_field) : space(space_field), centered(centered_field), upwind(upwind_field){
    this->name = option_field_name;
  }
  
  ~COptionConvect(){};
  string SetValue(vector<string> option_value){
    
    string out = optionCheckMultipleValues(option_value, "unsigned short", this->name);
    if (out.compare("") != 0){
      return out;
    }
    
    if (Centered_Map.count(option_value[0])) {
      this->space = Space_Map.find("SPACE_CENTERED")->second;
      this->centered = Centered_Map.find(option_value[0])->second;
      this->upwind = NO_UPWIND;
      return "";
    }
    if (Upwind_Map.count(option_value[0])) {
      this->space = Space_Map.find("SPACE_UPWIND")->second;
      this->upwind = Upwind_Map.find(option_value[0])->second;
      this->centered = NO_CENTERED;
      return "";
    }
    // Make them defined in case something weird happens
    this->centered = NO_CENTERED;
    this->upwind = NO_UPWIND;
    this->space = SPACE_CENTERED;
    return badValue(option_value, "convect", this->name);
    
  }
  
  void SetDefault(){
    this->centered = NO_CENTERED;
    this->upwind = NO_UPWIND;
    this->space = SPACE_CENTERED;
  }
};

class COptionMathProblem : public COptionBase{
  string name; // identifier for the option
  bool & adjoint;
  bool & oneshot;
  bool & linearized;
  bool & restart;
  bool adjoint_def;
  bool oneshot_def;
  bool linearized_def;
  bool restart_def;
  
public:
  COptionMathProblem(string option_field_name, bool & adjoint_field, bool adjoint_default, bool & oneshot_field, bool oneshot_default, bool & linearized_field, bool linearized_default, bool & restart_field, bool restart_default) : adjoint(adjoint_field), oneshot(oneshot_field), linearized(linearized_field), restart(restart_field) {
    this->name = option_field_name;
    this->adjoint_def = adjoint_default;
    this->oneshot_def = oneshot_default;
    this->linearized_def = linearized_default;
    this->restart_def = restart_default;
  }
  
  ~COptionMathProblem(){};
  string SetValue(vector<string> option_value){
    string out = optionCheckMultipleValues(option_value, "unsigned short", this->name);
    if (out.compare("") != 0){
      return out;
    }
    if (Math_Problem_Map.find(option_value[0]) == Math_Problem_Map.end()){
      return badValue(option_value, "math problem", this->name);
    }
    if (option_value[0] == "DIRECT") {
      this->adjoint = false;
      this->oneshot = false;
      this->linearized = false;
      this->restart = false;
      return "";
    }
    if (option_value[0] == "ADJOINT") {
      this->adjoint= true;
      this->restart= true;
      this->oneshot = false;
      this->linearized = false;
      return "";
    }
    if (option_value[0] == "LINEARIZED") {
      this->linearized = true;
      this->restart = true;
      this->adjoint= false;
      this->oneshot = false;
      return "";
    }
    return "option in math problem map not considered in constructor";
  }
  
  void SetDefault(){
    this->adjoint = this->adjoint_def;
    this->oneshot = this->oneshot_def;
    this->linearized = this->linearized_def;
    this->restart = this->restart_def;
  }
};

class COptionDVParam : public COptionBase{
  string name; // identifier for the option
  unsigned short & nDV;
  double ** & paramDV;
  unsigned short* & design_variable;
  
public:
  COptionDVParam(string option_field_name, unsigned short & nDV_field, double** & paramDV_field, unsigned short * & design_variable_field) : nDV(nDV_field), paramDV(paramDV_field), design_variable(design_variable_field){
    this->name = option_field_name;
  }
  
  ~COptionDVParam(){};
  string SetValue(vector<string> option_value){
    if ((option_value.size() == 1) && (option_value[0].compare("NONE") == 0)){
      this->nDV = 0;
      return "";
    }
    
    // Cannot have ; at the beginning or the end
    if (option_value[0].compare(";") == 0){
      string newstring;
      newstring.append(this->name);
      newstring.append(": may not have beginning semicolon");
      return newstring;
    }
    if (option_value[option_value.size()-1].compare(";") == 0){
      string newstring;
      newstring.append(this->name);
      newstring.append(": may not have ending semicolon");
      return newstring;
    }
    
    
    // use the ";" token to determine the number of design variables
    // This works because semicolon is not one of the delimiters in tokenize string
    this->nDV = 0;
    //unsigned int num_semi = 0;
    for (unsigned int i = 0; i < static_cast<unsigned int>(option_value.size()); i++) {
      if (option_value[i].compare(";") == 0) {
        this->nDV++;
        //        num_semi++;
      }
    }
    
    // One more design variable than semicolon
    this->nDV++;
    
    if ( (this->nDV > 0) && (this->design_variable == NULL) ) {
      string newstring;
      newstring.append(this->name);
      newstring.append(": Design_Variable array has not been allocated. Check that DV_KIND appears before DV_PARAM in configuration file.");
      return newstring;
    }
    /*
     #if 0
     cout << "Found " << (*nDV_) << " DV parameters" << endl;
     cout << "DV param value = ";
     for (unsigned int i = 0; i < value.size(); i++)
     cout << value[i] << ", ";
     cout << endl;
     #endif
     */
    
    
    
    this->paramDV = new double*[this->nDV];
    for (unsigned short iDV = 0; iDV < this->nDV; iDV++){
      this->paramDV[iDV] = new double[MAX_PARAMETERS];
    }
    
    unsigned short nParamDV = 0;
    stringstream ss;
    unsigned int i = 0;
    for (unsigned short iDV = 0; iDV < this->nDV; iDV++) {
      switch (this->design_variable[iDV]) {
        case FFD_SETTING: nParamDV = 0; break;
        case FFD_CONTROL_POINT_2D: nParamDV = 5; break;
        case FFD_CAMBER_2D: nParamDV = 2; break;
        case FFD_THICKNESS_2D: nParamDV = 2; break;
        case HICKS_HENNE: nParamDV = 2; break;
        case SPHERICAL: nParamDV = 3; break;
        case COSINE_BUMP: nParamDV = 3; break;
        case FOURIER: nParamDV = 3; break;
        case DISPLACEMENT: nParamDV = 3; break;
        case ROTATION: nParamDV = 6; break;
        case NACA_4DIGITS: nParamDV = 3; break;
        case PARABOLIC: nParamDV = 2; break;
        case OBSTACLE: nParamDV = 2; break;
        case AIRFOIL: nParamDV = 2; break;
        case STRETCH: nParamDV = 2; break;
        case FFD_CONTROL_POINT: nParamDV = 7; break;
        case FFD_DIHEDRAL_ANGLE: nParamDV = 7; break;
        case FFD_TWIST_ANGLE: nParamDV = 7; break;
        case FFD_ROTATION: nParamDV = 7; break;
        case FFD_CAMBER: nParamDV = 3; break;
        case FFD_THICKNESS: nParamDV = 3; break;
        case SURFACE_FILE: nParamDV = 0; break;
        default : {
          string newstring;
          newstring.append(this->name);
          newstring.append(": undefined design variable type found in configuration file.");
          return newstring;
        }
      }
      
      // ?? Not sure what's going on. Didn't touch it.
      for (unsigned short iParamDV = 0; iParamDV < nParamDV; iParamDV++) {
        ss << option_value[i] << " ";
        ss >> this->paramDV[iDV][iParamDV];
        i++;
      }
      if (iDV < (this->nDV-1)) {
        if (option_value[i].compare(";") != 0) {
          string newstring;
          newstring.append(this->name);
          newstring.append(": a design variable in the configuration file has the wrong number of parameters");
          return newstring;
        }
        i++;
      }
    }
    
    // Need to return something...
    return "";
  }
  
  void SetDefault(){
    this->nDV = 0;
    this->paramDV = NULL;
    // Don't mess with the Design_Variable because it's an input, not modified
  }
};


// Class where the option is represented by (String, double, string, double, ...)
class COptionStringDoubleList : public COptionBase{
  string name; // identifier for the option
  unsigned short & size; // how many strings are there (same as number of doubles)
  
  string * & s_f; // Reference to the string fields
  double* & d_f; // reference to the double fields
  
public:
  COptionStringDoubleList(string option_field_name, unsigned short & list_size, string * & string_field, double* & double_field) : size(list_size), s_f(string_field), d_f(double_field){
    this->name = option_field_name;
  }
  
  ~COptionStringDoubleList(){};
  string SetValue(vector<string> option_value){
    // There must be an even number of entries (same number of strings and doubles
    unsigned long totalVals = option_value.size();
    if ((totalVals % 2) != 0){
      if ((totalVals == 1) && (option_value[0].compare("NONE") == 0)){
        // It's okay to say its NONE
        this->size = 0;
        return "";
      }
      string newstring;
      newstring.append(this->name);
      newstring.append(": must have an even number of entries");
      return newstring;
    }
    unsigned long nVals = totalVals / 2;
    this->size = nVals;
    this->s_f = new string[nVals];
    this->d_f = new double[nVals];
    
    for (int i = 0; i < nVals; i++){
      this->s_f[i].assign(option_value[2*i]); // 2 because have double and string
      istringstream is(option_value[2*i + 1]);
      double val;
      if (!(is >> val)){
        return badValue(option_value, "string double", this->name);
      }
      this->d_f[i] = val;
    }
    // Need to return something...
    return "";
  }
  
  void SetDefault(){
    this->size = 0; // There is no default value for list
  }
};

class COptionInlet : public COptionBase{
  string name; // identifier for the option
  unsigned short & size;
  string * & marker;
  double * & ttotal;
  double * & ptotal;
  double ** & flowdir;
  
public:
  COptionInlet(string option_field_name, unsigned short & nMarker_Inlet, string* & Marker_Inlet, double* & Ttotal, double* & Ptotal, double** & FlowDir) : size(nMarker_Inlet), marker(Marker_Inlet), ttotal(Ttotal), ptotal(Ptotal), flowdir(FlowDir){
    this->name = option_field_name;
  }
  
  ~COptionInlet(){};
  string SetValue(vector<string> option_value){
    
    unsigned long totalVals = option_value.size();
    if ((totalVals == 1) && (option_value[0].compare("NONE") == 0)){
      this->size = 0;
      this->marker = NULL;
      this->ttotal = NULL;
      this->ptotal = NULL;
      this->flowdir = NULL;
      return "";
    }
    
    if (totalVals % 6 != 0){
      string newstring;
      newstring.append(this->name);
      newstring.append(": must have a number of entries divisible by 6");
      this->size = 0;
      this->marker = NULL;
      this->ttotal = NULL;
      this->ptotal = NULL;
      this->flowdir = NULL;
      return newstring;
    }
    
    unsigned long nVals = totalVals / 6;
    this->size = nVals;
    this->marker = new string[nVals];
    this->ttotal = new double[nVals];
    this->ptotal = new double[nVals];
    this->flowdir = new double*[nVals];
    for (int i = 0; i < nVals; i++){
      this->flowdir[i] = new double[3];
    }
    
    stringstream ss;
    for (int i = 0; i < nVals; i++){
      this->marker[i].assign(option_value[6*i]);
      ss << option_value[6*i + 1] << " ";
      if(!(ss >> this->ttotal[i])){
        return badValue(option_value, "inlet", this->name);
      }
      ss << option_value[6*i + 2] << " ";
      if(!(ss >> this->ptotal[i])){
        return badValue(option_value, "inlet", this->name);
      }
      ss << option_value[6*i + 3] << " ";
      if (!(ss >> this->flowdir[i][0])){
        return badValue(option_value, "inlet", this->name);
      }
      ss << option_value[6*i + 4] << " ";
      if (!(ss >> this->flowdir[i][1])){
        return badValue(option_value, "inlet", this->name);
      }
      ss << option_value[6*i + 5] << " ";
      if (!(ss >> this->flowdir[i][2])){
        return badValue(option_value, "inlet", this->name);
      }
    }
    
    return "";
  }
  
  void SetDefault(){
    this->marker = NULL;
    this->ttotal = NULL;
    this->ptotal = NULL;
    this->flowdir = NULL;
    this->size = 0; // There is no default value for list
  }
};

//Inlet condition where the input direction is assumed
class COptionInletFixed : public COptionBase{
  string name; // identifier for the option
  unsigned short & size;
  string * & marker;
  double * & ttotal;
  double * & ptotal;
  
public:
  COptionInletFixed(string option_field_name, unsigned short & nMarker_Inlet, string* & Marker_Inlet, double* & Ttotal, double* & Ptotal) : size(nMarker_Inlet), marker(Marker_Inlet), ttotal(Ttotal), ptotal(Ptotal){
    this->name = option_field_name;
  }
  
  ~COptionInletFixed(){};
  string SetValue(vector<string> option_value){
    
    unsigned long totalVals = option_value.size();
    if ((totalVals == 1) && (option_value[0].compare("NONE") == 0)){
      this->size = 0;
      this->marker = NULL;
      this->ttotal = NULL;
      this->ptotal = NULL;
      return "";
    }
    
    if (totalVals % 3 != 0){
      string newstring;
      newstring.append(this->name);
      newstring.append(": must have a number of entries divisible by 3");
      this->size = 0;
      this->marker = NULL;
      this->ttotal = NULL;
      this->ptotal = NULL;
      return newstring;
    }
    
    unsigned long nVals = totalVals / 3;
    this->size = nVals;
    this->marker = new string[nVals];
    this->ttotal = new double[nVals];
    this->ptotal = new double[nVals];
    stringstream ss;
    for (int i = 0; i < nVals; i++){
      this->marker[i].assign(option_value[3*i]);
      ss << option_value[3*i + 1] << " ";
      if (!(ss >> this->ttotal[i])){
        return badValue(option_value, "inlet fixed", this->name);
      }
      ss << option_value[3*i + 2] << " ";
      if (!(ss >> this->ptotal[i])){
        return badValue(option_value, "inlet fixed", this->name);
      }
    }
    return "";
  }
  
  void SetDefault(){
    this->marker = NULL;
    this->ttotal = NULL;
    this->ptotal = NULL;
    this->size = 0; // There is no default value for list
  }
};

class COptionPeriodic : public COptionBase{
  string name; // identifier for the option
  unsigned short & size;
  string * & marker_bound;
  string * & marker_donor;
  double ** & rot_center;
  double ** & rot_angles;
  double ** & translation;
  
public:
  COptionPeriodic(const string option_field_name, unsigned short & nMarker_PerBound,
                  string* & Marker_PerBound, string* & Marker_PerDonor,
                  double** & RotCenter, double** & RotAngles, double** & Translation) : size(nMarker_PerBound), marker_bound(Marker_PerBound), marker_donor(Marker_PerDonor), rot_center(RotCenter), rot_angles(RotAngles), translation(Translation){
    this->name = option_field_name;
  }
  
  ~COptionPeriodic(){};
  string SetValue(vector<string> option_value){
    
    const int mod_num = 11;
    
    unsigned long totalVals = option_value.size();
    if ((totalVals == 1) && (option_value[0].compare("NONE") == 0)){
      this->size = 0;
      this->marker_bound = NULL;
      this->marker_donor = NULL;
      this->rot_center = NULL;
      this->rot_angles = NULL;
      this->translation = NULL;
      return "";
    }
    
    if (totalVals % mod_num != 0){
      string newstring;
      newstring.append(this->name);
      newstring.append(": must have a number of entries divisible by 11");
      this->size = 0;
      this->marker_bound = NULL;
      this->marker_donor = NULL;
      this->rot_center = NULL;
      this->rot_angles = NULL;
      this->translation = NULL;
      return newstring;
    }
    
    unsigned long nVals = 2 * (totalVals / mod_num); // To account for periodic and donor
    this->size = nVals;
    this->marker_bound = new string[nVals];
    this->marker_donor = new string[nVals];
    this->rot_center = new double*[nVals];
    this->rot_angles = new double*[nVals];
    this->translation = new double*[nVals];
    for (int i = 0; i < nVals; i++){
      this->rot_center[i] = new double[3];
      this->rot_angles[i] = new double[3];
      this->translation[i] = new double[3];
    }
    
    double deg2rad = PI_NUMBER/180.0;
    stringstream ss;
    for (int i = 0; i < (nVals/2); i++){
      this->marker_bound[i].assign(option_value[mod_num*i]);
      this->marker_donor[i].assign(option_value[mod_num*i+1]);
      ss << option_value[mod_num*i + 2] << " ";
      if (!(ss >> this->rot_center[i][0])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*i + 3] << " ";
      if (!(ss >> this->rot_center[i][1])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*i + 4] << " ";
      if (!(ss >> this->rot_center[i][2])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*i + 5] << " ";
      if (!(ss >> this->rot_angles[i][0])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*i + 6] << " ";
      if (!(ss >> this->rot_angles[i][1])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*i + 7] << " ";
      if (!(ss >> this->rot_angles[i][2])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*i + 8] << " ";
      if (!(ss >> this->translation[i][0])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*i + 9] << " ";
      if (!(ss >> this->translation[i][1])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*i + 10] << " ";
      if (!(ss >> this->translation[i][2])){
        return badValue(option_value, "periodic", this->name);
      }
      this->rot_angles[i][0] *= deg2rad;
      this->rot_angles[i][1] *= deg2rad;
      this->rot_angles[i][2] *= deg2rad;
    }
    
    for (unsigned long i = (nVals/2); i < nVals; i++){
      this->marker_bound[i].assign(option_value[mod_num*(i-nVals/2)+1]);
      this->marker_donor[i].assign(option_value[mod_num*(i-nVals/2)]);
      ss << option_value[mod_num*(i-nVals/2) + 2] << " ";
      if (!(ss >> this->rot_center[i][0])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*(i-nVals/2) + 3] << " ";
      if (!(ss >> this->rot_center[i][1])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*(i-nVals/2) + 4] << " ";
      if (!(ss >> this->rot_center[i][2])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*(i-nVals/2) + 5] << " ";
      if (!(ss >> this->rot_angles[i][0])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*(i-nVals/2) + 6] << " ";
      if (!(ss >> this->rot_angles[i][1])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*(i-nVals/2) + 7] << " ";
      if (!(ss >> this->rot_angles[i][2])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*(i-nVals/2) + 8] << " ";
      if (!(ss >> this->translation[i][0])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*(i-nVals/2) + 9] << " ";
      if (!(ss >> this->translation[i][1])){
        return badValue(option_value, "periodic", this->name);
      }
      ss << option_value[mod_num*(i-nVals/2) + 10] << " ";
      if (!(ss >> this->translation[i][2])){
        return badValue(option_value, "periodic", this->name);
      }
      /*--- Mirror the rotational angles and translation vector (rotational 
       center does not need to move) ---*/
      this->rot_center[i][0] *= 1.0;
      this->rot_center[i][1] *= 1.0;
      this->rot_center[i][2] *= 1.0;
      this->rot_angles[i][0] *= -deg2rad;
      this->rot_angles[i][1] *= -deg2rad;
      this->rot_angles[i][2] *= -deg2rad;
      this->translation[i][0] *= -1.0;
      this->translation[i][1] *= -1.0;
      this->translation[i][2] *= -1.0;
    }
    
    return "";
  }
  
  void SetDefault(){
    this->size = 0;
    this->marker_bound = NULL;
    this->marker_donor = NULL;
    this->rot_center = NULL;
    this->rot_angles = NULL;
    this->translation = NULL;
  }
};

class COptionActuatorDisk : public COptionBase{
  string name; // identifier for the option
  unsigned short & inlet_size;
  unsigned short & outlet_size;
  string * & marker_inlet;
  string * & marker_outlet;
  double ** & origin;
  double * & root_radius;
  double * & tip_radius;
  double * & ct;
  double * & omega;
  
public:
  COptionActuatorDisk(const string name, unsigned short & nMarker_ActDisk_Inlet, unsigned short & nMarker_ActDisk_Outlet, string * & Marker_ActDisk_Inlet, string * & Marker_ActDisk_Outlet, double ** & ActDisk_Origin, double * & ActDisk_RootRadius, double * & ActDisk_TipRadius, double * & ActDisk_CT, double * & ActDisk_Omega) : inlet_size(nMarker_ActDisk_Inlet),outlet_size(nMarker_ActDisk_Outlet), marker_inlet(Marker_ActDisk_Inlet), marker_outlet(Marker_ActDisk_Outlet), origin(ActDisk_Origin), root_radius(ActDisk_RootRadius), tip_radius(ActDisk_TipRadius), ct(ActDisk_CT), omega(ActDisk_Omega) {
    this->name = name;
  }
  
  ~COptionActuatorDisk(){};
  string SetValue(vector<string> option_value){
    const int mod_num = 9;
    unsigned long totalVals = option_value.size();
    if ((totalVals == 1) && (option_value[0].compare("NONE") == 0)){
      this->SetDefault();
      return "";
    }
    
    if (totalVals % mod_num != 0){
      string newstring;
      newstring.append(this->name);
      newstring.append(": must have a number of entries divisible by 9");
      this->SetDefault();
      return newstring;
    }
    
    unsigned long nVals = totalVals / mod_num;
    this->inlet_size = nVals;
    this->outlet_size = nVals;
    this->marker_inlet = new string[this->inlet_size];
    this->marker_outlet = new string[this->outlet_size];
    this->root_radius = new double[this->inlet_size];
    this->tip_radius = new double[this->inlet_size];
    this->ct = new double[this->outlet_size];
    this->omega = new double[this->inlet_size];
    
    this->origin = new double*[this->inlet_size];
    for (int i = 0; i < this->inlet_size; i++){
      this->origin[i] = new double[3];
    }
    
    string tname = "actuator disk";
    stringstream ss;
    for (int i = 0; i < this->inlet_size; i++){
      this->marker_inlet[i].assign(option_value[mod_num*i]);
      this->marker_outlet[i].assign(option_value[mod_num*i+1]);
      ss << option_value[mod_num*i + 2] << " ";
      if (!(ss >> this->origin[i][0])){
        return badValue(option_value, tname, this->name);
      }
      ss << option_value[mod_num*i + 3] << " ";
      if (!(ss >> this->origin[i][1])){
        return badValue(option_value, tname, this->name);
      }
      ss << option_value[mod_num*i + 4] << " ";
      if (!(ss >> this->origin[i][2])){
        return badValue(option_value, tname, this->name);
      }
      ss << option_value[mod_num*i + 5] << " ";
      if (!(ss >> this->root_radius[i])){
        return badValue(option_value, tname, this->name);
      }
      ss << option_value[mod_num*i + 6] << " ";
      if (!(ss >> this->tip_radius[i])){
        return badValue(option_value, tname, this->name);
      }
      ss << option_value[mod_num*i + 7] << " ";
      if (!(ss >> this->ct[i])){
        return badValue(option_value, tname, this->name);
      }
      ss << option_value[mod_num*i + 8] << " ";
      if (!(ss >> this->omega[i])){
        return badValue(option_value, tname, this->name);
      }
    }
    return "";
  }
  void SetDefault(){
    this->inlet_size = 0;
    this->outlet_size = 0;
    this->marker_inlet = NULL;
    this->marker_outlet = NULL;
    this->origin = NULL;
    this->root_radius = NULL;
    this->tip_radius = NULL;
    this->ct = NULL;
    this->omega = NULL;
  }
};




/*!
 * \class CAnyOptionRef
 * \brief provides a means of referencing variables of any type
 * \author J. Hicken
 *
 * In order to build a map that associates option names (strings) with
 * options, we need a way of referencing artbitrary types; otherwise,
 * we would need a separate map for ints, doubles, etc.  This class is
 * an abstract base class designed to accommodate this requirement.
 */
class CAnyOptionRef {
public:
  virtual ~CAnyOptionRef() = 0;
  virtual void WriteValue() = 0;
  virtual void SetValue(const vector<string> & value) = 0;
};
inline CAnyOptionRef::~CAnyOptionRef() {}

/*!
 * \class COptionRef
 * \brief a typed version of the base class for standard types
 * \tparam T - an arbitary standard type (short, int, double, etc)
 * \author J. Hicken
 *
 * This class can accommodate scalars and arrays of constant length.
 * If your option requies a variable length, use class CListOptionRef.
 * Why not use CListOptionRef for arrays?  You could, but COptionRef
 * lets you set default values for arrays (because it does not do any
 * memory management).
 */
template <class T>
class COptionRef : public CAnyOptionRef {
private:
  unsigned short ndim_; /*!< \brief number of array dimensions */
  unsigned int* dim_; /*!< \brief length of each array dimension */
  T* ref_; /*!< \brief pointer to the option */
  
  /*!< \brief function pointer used (if necessary) to set the value of the option */
  void (*user_set_value_)(T* ref, const vector<string> & value);
  
public:
  
  /*!
   * \brief constructor for scalar options
   * \param[in] value - variable to create a reference to
   */
  COptionRef(T & value) {
    ndim_ = 0;
    dim_ = new unsigned int[ndim_];
    ref_ = &value;
    user_set_value_ = NULL;
  }
  
  /*!
   * \brief constructor for 1D fixed length array options
   * \param[in] value_ptr - pointer to variable to create a reference to
   * \param[in] size - length of the array option
   */
  COptionRef(T * & value_ptr, const int & size) {
    ndim_ = 1;
    dim_ = new unsigned int[ndim_];
    if (size <= 0) {
      cerr << "COptionRef::COptionRef(T&, const int &): "
      << "invalid input: size = " << size << endl;
      throw(-1);
    }
    dim_[0] = size;
    ref_ = value_ptr;
    user_set_value_ = NULL;
  }
  
  /*!
   * \brief constructor for scalar options that require special parsing
   * \param[in] value - variable to create a reference to
   * \param[in] set_value - function that sets options based on vector of strings
   *
   * If the option requires a special parsing of the configuration
   * file, this constructor can be used to set a pointer to a function
   * that performs the necessary parsing
   */
  COptionRef(T & value, void (*set_value)(T*, const vector<string>&)) {
    ndim_ = 0;
    dim_ = new unsigned int[ndim_];
    ref_ = &value;
    user_set_value_ = set_value;
  }
  
  /*!
   * \brief class destructor
   */
  ~COptionRef() {
    if (ndim_ > 0) {
      delete [] dim_;
    }
    user_set_value_ = NULL;
  }
  
  /*!
   * \brief sets the value of the referenced option using vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    stringstream ss;
    if (user_set_value_ == NULL) {
      if (ndim_ == 0) {
        ss << value[0];
        ss >> (*ref_);
      } else if (ndim_ == 1) {
        if (value.size() != dim_[0]) {
          cerr << "COptionRef::SetValue(const vector<string>&): "
          << "number of input values does not match size of option array."
          << endl;
          throw(-1);
        }
        for (unsigned int i = 0; i < dim_[0]; i++) {
          ss << value[i] << " ";
          ss >> (ref_[i]);
        }
      } else {
        cerr << "COptionRef::SetValue(const vector<string>&): "
        << "cannot handle 2d arrays yet" << endl;
        throw(-1);
      }
    } else {
      // this option requires a special function for parsing
      (*user_set_value_)(ref_, value);
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    if (ndim_ == 0) {
      cout << *ref_ << endl;
    } else if (ndim_ == 1) {
      for (unsigned int i = 0; i < dim_[0]; i++)
        cout << ref_[i] << ", ";
      cout << endl;
    }
  }
};

/*!
 * \class CListOptionRef
 * \brief for options of variable array length
 * \author J. Hicken
 */
template <class T>
class CListOptionRef : public CAnyOptionRef {
private:
  T** ref_; /*!< \brief pointer to the memory holding the list option */
  unsigned short* ref_size_; /*!< \brief number of items in list */
  
public:
  
  /*!
   * \brief constructor for list-type options
   * \param[in] value - variable we want to create a reference to
   * \param[in] size - number of elements the list WILL have
   */
  CListOptionRef(unsigned short & size, T* & value) {
    ref_ = &value;
    *ref_ = NULL;
    size = 0;
    ref_size_ = &size;
  }
  
  /*!
   * \brief sets the value of the referenced convection option using vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    stringstream ss;
    *ref_size_ = static_cast<unsigned short>(value.size());
    if (*ref_ != NULL) {
      cerr << "Error in CListOptionRef(SetValue): "
      << "list option has already been allocated."
      << endl;
      throw(-1);
    }
    (*ref_) = new T[*ref_size_];
    for (unsigned short i = 0; i < *ref_size_; i++) {
      ss << value[i] << " ";
      ss >> (*ref_)[i];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    for (unsigned short i = 0; i < *ref_size_; i++)
      cout << (*ref_)[i] << ", ";
    cout << endl;
  }
};

/*!
 * \class CEnumOptionRef
 * \brief a typed version of the base class for options associated with enumerations
 * \tparam T - the type of option (usually unsigned short)
 * \tparam Tenum - an enumeration assocatied with T
 * \author J. Hicken
 */
template <class T, class Tenum>
class CEnumOptionRef : public CAnyOptionRef {
private:
  T** ref_; /*!< \brief pointer to memory for the option */
  unsigned short* ref_dim_; /*!< \brief number of elemets in ref_ for array enums*/
  const map<string, Tenum> * Tmap_; /*!< \brief map between strings and enums */
  
public:
  
  /*!
   * \brief constructor for scalar enum options
   * \param[in] value - variable to create a reference to
   * \param[in] Tmap - map between strings and enums
   */
  CEnumOptionRef(T & value, const map<string, Tenum> & Tmap) {
    ref_ = new T*;
    *ref_ = &value;
    ref_dim_ = NULL;
    Tmap_ = &Tmap;
  }
  
  /*!
   * \brief constructor for list enum options
   * \param[in] value - variable to create a reference to
   * \param[in] Tmap - map between strings and enums
   * \param[in] size - length of the array option
   */
  CEnumOptionRef(unsigned short & size, T* & value, const map<string, Tenum> & Tmap) {
    ref_ = &value;
    ref_dim_ = &size;
    Tmap_ = &Tmap;
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    if (ref_dim_ == NULL) {
      cout << *(*ref_) << endl;
    } else {
      for (unsigned int i = 0; i < *ref_dim_; i++)
        cout << (*ref_)[i] << ", ";
      cout << endl;
    }
  }
  
  /*!
   * \brief sets the value of the referenced enum option using vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    
    int rank = MASTER_NODE;
    
    typename map<string,Tenum>::const_iterator it;
    if (ref_dim_ == NULL) {
      // this is a scalar enum option
      it = Tmap_->find(StringToUpperCase(value[0]));
      if (it == Tmap_->end()) {
        if (rank == MASTER_NODE) {
          cerr << "ERROR: Cannot find value " << value[0] << " in given map." << endl;
          cerr << "Please check the name of the variable in the config file." << endl;
        }
        exit(1);
      }
      *(*ref_) = it->second;
    } else {
      // this is an array enum option
      (*ref_dim_) = static_cast<unsigned short>(value.size());
      (*ref_) = new T[*ref_dim_];
      for (unsigned short i = 0; i < *ref_dim_; i++) {
        it = Tmap_->find(StringToUpperCase(value[i]));
        if (it == Tmap_->end()) {
          if (rank == MASTER_NODE) {
            cerr << "ERROR: Cannot find value " << value[i] << " in given map." << endl;
            cerr << "Please check the name of the variable in the config file." << endl;
          }
          exit(1);
        }
        (*ref_)[i] = it->second;
      }
    }
  }
  
};

/*!
 * \class CMarkerOptionRef
 * \brief a typed version of the base class for marker options
 * \author J. Hicken
 */
class CMarkerOptionRef : public CAnyOptionRef {
private:
  string** marker_ref_; /*!< \brief pointer to the memory for the marker option */
  unsigned short* num_marker_; /*!< \brief number of markers */
  
public:
  
  /*!
   * \brief constructor for marker options
   * \param[in] value - variable to create a reference to
   * \param[in] size - variable refering to the number of markers
   */
  CMarkerOptionRef(string* & value, unsigned short & size) {
    marker_ref_ = &value;
    *marker_ref_ = NULL;
    num_marker_ = &size;
  }
  
  /*!
   * \brief sets the value of the referenced marker option using vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if (value.size() == 0) {
      cerr << "Error in CMarkerOptionRef::SetValue(): "
      << "marker option in config file with no value" << endl;
      cerr << "Use NONE for no markers." << endl;
      throw(-1);
    }
    if (marker_ref_ != NULL) delete [] (*marker_ref_);
    (*marker_ref_) = new string[value.size()];
    for (unsigned int i = 0; i < value.size(); i++)
      (*marker_ref_)[i] = value[i];
    if ( (value.size() == 1) && ((*marker_ref_)[0] == "NONE") ) {
      *num_marker_ = 0;
    } else {
      *num_marker_ = value.size();
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    for (unsigned int i = 0; i < *num_marker_; i++)
      cout << (*marker_ref_)[i] << ", ";
    cout << endl;
  }
};

/*!
 * \class CMarkerPeriodicRef
 * \brief Specialized option for periodic boundary markers
 * \author J. Hicken
 */
class CMarkerPeriodicRef : public CAnyOptionRef {
private:
  unsigned short* nMarker_PerBound_; /*!< \brief Number of periodic boundary markers. */
  string** Marker_PerBound_; /*!< \brief Periodic boundaries markers. */
  string** Marker_PerDonor_; /*!< \brief Rotationally periodic boundary donor markers. */
  double*** Periodic_RotCenter_; /*!< \brief Rotational center for each periodic boundary. */
  double*** Periodic_RotAngles_; /*!< \brief Rotation angles for each periodic boundary. */
  double*** Periodic_Translation_; /*!< \brief Translation vector for each periodic boundary. */
  
public:
  
  /*!
   * \brief constructor for periodic marker option
   * \param[in] nMarker_PerBound - number of periodic boundary markers
   * \param[in] Marker_PerBound - periodic boundary markers
   * \param[in] Marker_PerDonor - boundary marker of rotationally periodic donor
   * \param[in] Periodic_RotCenter - rotational center for each periodic boundary
   * \param[in] Periodic_RotAngles - rotational angles for each periodic boundary
   * \param[in] Periodic_Translation - translation vector for each periodic boundary
   */
  CMarkerPeriodicRef(unsigned short & nMarker_PerBound, string* & Marker_PerBound,
                     string* & Marker_PerDonor, double** & Periodic_RotCenter,
                     double** & Periodic_RotAngles, double** & Periodic_Translation) {
    nMarker_PerBound_ = &nMarker_PerBound;
    Marker_PerBound_ = &Marker_PerBound;
    *Marker_PerBound_ = NULL;
    Marker_PerDonor_ = &Marker_PerDonor;
    *Marker_PerDonor_ = NULL;
    Periodic_RotCenter_ = &Periodic_RotCenter;
    *Periodic_RotCenter_ = NULL;
    Periodic_RotAngles_ = &Periodic_RotAngles;
    *Periodic_RotAngles_ = NULL;
    Periodic_Translation_ = &Periodic_Translation;
    *Periodic_Translation_ = NULL;
  }
  
  /*!
   * \brief sets the value of the periodic boundary parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_PerBound_ != NULL) || (*Marker_PerDonor_ != NULL) ||
        (*Periodic_RotCenter_ != NULL) || (*Periodic_RotAngles_ != NULL) ||
        (*Periodic_Translation_ != NULL) ) {
      cerr << "Error in CMarkerPeriodicRef::SetValue(): "
      << "one or more periodic-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 11 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_PerBound_ = 0;
        return;
      }
      cerr << "Error in CMarkerPeriodicRef::SetValue(): "
      << "incorrect number of MARKER_PERIODIC parameters in the configuration file."
      << endl;
      throw(-1);
    }
    *nMarker_PerBound_ = static_cast<unsigned short>(value.size())/11;
    (*Marker_PerBound_)      = new string[*nMarker_PerBound_];
    (*Marker_PerDonor_)      = new string[*nMarker_PerBound_];
    (*Periodic_RotCenter_)   = new double*[*nMarker_PerBound_];
    (*Periodic_RotAngles_)   = new double*[*nMarker_PerBound_];
    (*Periodic_Translation_) = new double*[*nMarker_PerBound_];
    for (unsigned short iMarker_PerBound = 0; iMarker_PerBound < *nMarker_PerBound_; iMarker_PerBound++) {
      (*Periodic_RotCenter_)[iMarker_PerBound]   = new double[3];
      (*Periodic_RotAngles_)[iMarker_PerBound]   = new double[3];
      (*Periodic_Translation_)[iMarker_PerBound] = new double[3];
    }
    
    stringstream ss;
    unsigned short i = 0;
    double deg2rad = PI_NUMBER/180.0;
    for (unsigned short iMarker_PerBound = 0; iMarker_PerBound < *nMarker_PerBound_; iMarker_PerBound++) {
      ss << value[i++] << " ";
      ss >> (*Marker_PerBound_)[iMarker_PerBound];
      ss << value[i++] << " ";
      ss >> (*Marker_PerDonor_)[iMarker_PerBound];
      ss << value[i++] << " ";
      ss >> (*Periodic_RotCenter_)[iMarker_PerBound][0];
      ss << value[i++] << " ";
      ss >> (*Periodic_RotCenter_)[iMarker_PerBound][1];
      ss << value[i++] << " ";
      ss >> (*Periodic_RotCenter_)[iMarker_PerBound][2];
      ss << value[i++] << " ";
      ss >> (*Periodic_RotAngles_)[iMarker_PerBound][0];
      ss << value[i++] << " ";
      ss >> (*Periodic_RotAngles_)[iMarker_PerBound][1];
      ss << value[i++] << " ";
      ss >> (*Periodic_RotAngles_)[iMarker_PerBound][2];
      ss << value[i++] << " ";
      ss >> (*Periodic_Translation_)[iMarker_PerBound][0];
      ss << value[i++] << " ";
      ss >> (*Periodic_Translation_)[iMarker_PerBound][1];
      ss << value[i++] << " ";
      ss >> (*Periodic_Translation_)[iMarker_PerBound][2];
      
      /*--- Convert the angles from degrees to radians ---*/
      (*Periodic_RotAngles_)[iMarker_PerBound][0] *= deg2rad;
      (*Periodic_RotAngles_)[iMarker_PerBound][1] *= deg2rad;
      (*Periodic_RotAngles_)[iMarker_PerBound][2] *= deg2rad;
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "CMarkerPeriodicRef::WriteValue(): not implemented yet" << endl;
  }
  
};

/*!
 * \class CMarkerPeriodicRef
 * \brief Specialized option for periodic boundary markers
 * \author J. Hicken
 */
class CMarkerActuatorDiskRef : public CAnyOptionRef {
private:
  unsigned short* nMarker_ActDisk_Inlet_; /*!< \brief Number of periodic boundary markers. */
  unsigned short* nMarker_ActDisk_Outlet_; /*!< \brief Number of periodic boundary markers. */
  
  string** Marker_ActDisk_Inlet_; /*!< \brief Name of the inlet surface for the actuator disk. */
  string** Marker_ActDisk_Outlet_; /*!< \brief Name of the outlet surface for the actuator disk. */
  double*** ActDisk_Origin_; /*!< \brief Origin of the actuator disk. */
  double** ActDisk_RootRadius_; /*!< \brief Root radius of the actuator disk. */
  double** ActDisk_TipRadius_; /*!< \brief Tip radius of the actuator disk. */
  double** ActDisk_CT_; /*!< \brief _____________________________. */
  double** ActDisk_Omega_; /*!< \brief _____________________________. */
  
public:
  
  /*!
   * \brief constructor for periodic marker option
   * \param[in] nMarker_ActDisk_Inlet - ________________________
   * \param[in] nMarker_ActDisk_Outlet - ________________________
   * \param[in] Marker_ActDisk_Inlet - ________________________
   * \param[in] Marker_ActDisk_Outlet - ________________________
   * \param[in] ActDisk_Origin - ________________________
   * \param[in] ActDisk_RootRadius -________________________
   * \param[in] ActDisk_TipRadius - ________________________
   * \param[in] ActDisk_CT - ________________________
   * \param[in] ActDisk_Omega - ________________________
   */
  CMarkerActuatorDiskRef(unsigned short & nMarker_ActDisk_Inlet, unsigned short & nMarker_ActDisk_Outlet,
                         string* & Marker_ActDisk_Inlet, string* & Marker_ActDisk_Outlet,
                         double** & ActDisk_Origin, double* & ActDisk_RootRadius, double* & ActDisk_TipRadius,
                         double* & ActDisk_CT, double* & ActDisk_Omega) {
    nMarker_ActDisk_Inlet_ = &nMarker_ActDisk_Inlet;
    nMarker_ActDisk_Outlet_ = &nMarker_ActDisk_Outlet;
    
    Marker_ActDisk_Inlet_ = &Marker_ActDisk_Inlet;
    *Marker_ActDisk_Inlet_ = NULL;
    
    Marker_ActDisk_Outlet_ = &Marker_ActDisk_Outlet;
    *Marker_ActDisk_Outlet_ = NULL;
    
    ActDisk_Origin_ = &ActDisk_Origin;
    *ActDisk_Origin_ = NULL;
    
    ActDisk_RootRadius_ = &ActDisk_RootRadius;
    *ActDisk_RootRadius_ = NULL;
    
    ActDisk_TipRadius_ = &ActDisk_TipRadius;
    *ActDisk_TipRadius_ = NULL;
    
    ActDisk_CT_ = &ActDisk_CT;
    *ActDisk_CT_ = NULL;
    
    ActDisk_Omega_ = &ActDisk_Omega;
    *ActDisk_Omega_ = NULL;
  }
  
  /*!
   * \brief sets the value of the periodic boundary parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_ActDisk_Inlet_ != NULL) || (*Marker_ActDisk_Outlet_ != NULL) ||
        (*ActDisk_Origin_ != NULL) ||
        (*ActDisk_RootRadius_ != NULL) || (*ActDisk_TipRadius_ != NULL) ||
        (*ActDisk_CT_ != NULL) || (*ActDisk_Omega_ != NULL) ) {
      cerr << "Error in CMarkerPeriodicRef::SetValue(): "
      << "one or more periodic-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 9 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_ActDisk_Inlet_ = 0;
        return;
      }
      if (value[0].compare("NONE") == 0) {
        *nMarker_ActDisk_Outlet_ = 0;
        return;
      }
      cerr << "Error in CMarkerActuatorDiskRef::SetValue(): "
      << "incorrect number of MARKER_ACTDISK parameters in the configuration file."
      << endl;
      throw(-1);
    }
    
    *nMarker_ActDisk_Inlet_ = static_cast<unsigned short>(value.size())/9;
    *nMarker_ActDisk_Outlet_ = static_cast<unsigned short>(value.size())/9;
    
    (*Marker_ActDisk_Inlet_)  = new string[*nMarker_ActDisk_Inlet_];
    (*Marker_ActDisk_Outlet_) = new string[*nMarker_ActDisk_Outlet_];
    
    (*ActDisk_Origin_)  = new double*[*nMarker_ActDisk_Inlet_];
    for (unsigned short iMarker_ActDisk = 0; iMarker_ActDisk < *nMarker_ActDisk_Inlet_; iMarker_ActDisk++) {
      (*ActDisk_Origin_)[iMarker_ActDisk] = new double[3];
    }
    
    (*ActDisk_RootRadius_)  = new double[*nMarker_ActDisk_Inlet_];
    (*ActDisk_TipRadius_)   = new double[*nMarker_ActDisk_Inlet_];
    (*ActDisk_CT_)      = new double[*nMarker_ActDisk_Inlet_];
    (*ActDisk_Omega_)   = new double[*nMarker_ActDisk_Inlet_];
    
    stringstream ss;
    unsigned short i = 0;
    for (unsigned short iMarker_ActDisk = 0; iMarker_ActDisk < *nMarker_ActDisk_Inlet_; iMarker_ActDisk++) {
      ss << value[i++] << " ";
      ss >> (*Marker_ActDisk_Inlet_)[iMarker_ActDisk];
      ss << value[i++] << " ";
      ss >> (*Marker_ActDisk_Outlet_)[iMarker_ActDisk];
      ss << value[i++] << " ";
      ss >> (*ActDisk_Origin_)[iMarker_ActDisk][0];
      ss << value[i++] << " ";
      ss >> (*ActDisk_Origin_)[iMarker_ActDisk][1];
      ss << value[i++] << " ";
      ss >> (*ActDisk_Origin_)[iMarker_ActDisk][2];
      ss << value[i++] << " ";
      ss >> (*ActDisk_RootRadius_)[iMarker_ActDisk];
      ss << value[i++] << " ";
      ss >> (*ActDisk_TipRadius_)[iMarker_ActDisk];
      ss << value[i++] << " ";
      ss >> (*ActDisk_CT_)[iMarker_ActDisk];
      ss << value[i++] << " ";
      ss >> (*ActDisk_Omega_)[iMarker_ActDisk];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "CMarkerActuatorDiskRef::WriteValue(): not implemented yet" << endl;
  }
  
};

/*!
 * \class CMarkerInletRef
 * \brief Specialized option for inlet boundary markers
 * \author J. Hicken
 */
class CMarkerInletRef : public CAnyOptionRef {
private:
  unsigned short* nMarker_Inlet_; /*!< \brief the number of inlet marker boundaries */
  string** Marker_Inlet_;         /*!< \brief string names of inlet boundaries */
  double** Ttotal_;               /*!< \brief specified total temperatures for inlet boundaries */
  double** Ptotal_;               /*!< \brief specified total pressures for inlet boundaries */
  double*** FlowDir_;             /*!< \brief specified flow direction vector (unit vector) for inlet boundaries */
  
public:
  
  /*!
   * \brief constructor for inlet marker option
   * \param[in] nMarker_Inlet - the number of inlet marker boundaries
   * \param[in] Marker_Inlet - string names of inlet boundaries
   * \param[in] Ttotal - specified total temperatures for inlet boundaries
   * \param[in] Ptotal - specified total pressures for inlet boundaries
   * \param[in] FlowDir - specified flow direction vector (unit vector) for inlet boundaries
   */
  CMarkerInletRef(unsigned short & nMarker_Inlet, string* & Marker_Inlet, double* & Ttotal,
                  double* & Ptotal, double** & FlowDir) {
    nMarker_Inlet_ = &nMarker_Inlet;
    Marker_Inlet_ = &Marker_Inlet;
    *Marker_Inlet_ = NULL;
    Ttotal_ = &Ttotal;
    *Ttotal_ = NULL;
    Ptotal_ = &Ptotal;
    *Ptotal_ = NULL;
    FlowDir_ = &FlowDir;
    *FlowDir_ = NULL;
  }
  
  /*!
   * \brief sets the value of the inlet parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_Inlet_ != NULL) || (*Ttotal_ != NULL) || (*Ptotal_ != NULL) ||
        (*FlowDir_ != NULL) ) {
      cerr << "Error in CMarkerInletRef::SetValue(): "
      << "one or more inlet-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 6 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_Inlet_ = 0;
        return;
      }
      cerr << "Error in CMarkerInletRef::SetValue(): "
      << "incorrect number of MARKER_INLET parameters in the configuration file."
      << endl;
      throw(-1);
    }
    *nMarker_Inlet_ = static_cast<unsigned short>(value.size())/6;
    (*Marker_Inlet_) = new string[*nMarker_Inlet_];
    (*Ttotal_)       = new double[*nMarker_Inlet_];
    (*Ptotal_)       = new double[*nMarker_Inlet_];
    (*FlowDir_)      = new double*[*nMarker_Inlet_];
    for (unsigned short iMarker = 0; iMarker < *nMarker_Inlet_; iMarker++)
      (*FlowDir_)[iMarker]   = new double[3];
    
    stringstream ss;
    unsigned short i = 0;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Inlet_; iMarker++) {
      ss << value[i++] << " ";
      ss >> (*Marker_Inlet_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*Ttotal_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*Ptotal_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*FlowDir_)[iMarker][0];
      ss << value[i++] << " ";
      ss >> (*FlowDir_)[iMarker][1];
      ss << value[i++] << " ";
      ss >> (*FlowDir_)[iMarker][2];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "CMarkerInletRef::WriteValue(): not implemented yet" << endl;
  }
  
};

/*!
 * \class CMarkerInletRef_
 * \brief Specialized option for inlet boundary markers (no flow direction)
 * \author J. Hicken
 */
class CMarkerInletRef_ : public CAnyOptionRef {
private:
  unsigned short* nMarker_Inlet_; /*!< \brief the number of inlet marker boundaries */
  string** Marker_Inlet_;         /*!< \brief string names of inlet boundaries */
  double** Ttotal_;               /*!< \brief specified total temperatures for inlet boundaries */
  double** Ptotal_;               /*!< \brief specified total pressures for inlet boundaries */
  
public:
  
  /*!
   * \brief constructor for inlet marker option
   * \param[in] nMarker_Inlet - the number of inlet marker boundaries
   * \param[in] Marker_Inlet - string names of inlet boundaries
   * \param[in] Ttotal - specified total temperatures for inlet boundaries
   * \param[in] Ptotal - specified total pressures for inlet boundaries
   * \param[in] FlowDir - specified flow direction vector (unit vector) for inlet boundaries
   */
  CMarkerInletRef_(unsigned short & nMarker_Inlet, string* & Marker_Inlet, double* & Ttotal,
                   double* & Ptotal) {
    nMarker_Inlet_ = &nMarker_Inlet;
    Marker_Inlet_ = &Marker_Inlet;
    *Marker_Inlet_ = NULL;
    Ttotal_ = &Ttotal;
    *Ttotal_ = NULL;
    Ptotal_ = &Ptotal;
    *Ptotal_ = NULL;
  }
  
  /*!
   * \brief sets the value of the inlet parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_Inlet_ != NULL) || (*Ttotal_ != NULL) || (*Ptotal_ != NULL) ) {
      cerr << "Error in CMarkerInletRef_::SetValue(): "
      << "one or more inlet-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 3 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_Inlet_ = 0;
        return;
      }
      cerr << "Error in CMarkerInletRef_::SetValue(): "
      << "incorrect number of MARKER_INLET parameters in the configuration file."
      << endl;
      throw(-1);
    }
    *nMarker_Inlet_ = static_cast<unsigned short>(value.size())/3;
    (*Marker_Inlet_) = new string[*nMarker_Inlet_];
    (*Ttotal_)       = new double[*nMarker_Inlet_];
    (*Ptotal_)       = new double[*nMarker_Inlet_];
    
    stringstream ss;
    unsigned short i = 0;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Inlet_; iMarker++) {
      ss << value[i++] << " ";
      ss >> (*Marker_Inlet_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*Ttotal_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*Ptotal_)[iMarker];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "Inlet markers (" << (*nMarker_Inlet_) << ")" << endl;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Inlet_; iMarker++)
      cout << "name = " << (*Marker_Inlet_)[iMarker]
      << ": temp. = " << (*Ttotal_)[iMarker]
      << ": pressure. = " << (*Ptotal_)[iMarker] << endl;
  }
  
};

/*!
 * \class CMarkerDirichletRef
 * \brief Specialized option for Dirichlet for poissonal solver boundary markers
 * \author A. Lonkar
 */
class CMarkerDirichletRef : public CAnyOptionRef {
private:
  unsigned short* nMarker_Dirichlet_; /*!< \brief the number of Dirichlet marker boundaries */
  string** Marker_Dirichlet_;         /*!< \brief string names of Dirichlet boundaries */
  double** Value_Dirichlet_;               /*!< \brief specified values for Dirichlet boundaries */
  
public:
  
  /*!
   * \brief constructor for inlet marker option
   * \param[in] nMarker_Dirichlet_Elec - the number of Dirichlet marker boundaries
   * \param[in] nMarker_Dirichlet_Elec - string names of Dirichlet boundaries
   * \param[in] Dirichlet_Value - specified value for the dirichlet boundaries
   */
  
  CMarkerDirichletRef(unsigned short & nMarker_Dirichlet_Elec, string* & Marker_Dirichlet_Elec, double* & Dirichlet_Value) {
    nMarker_Dirichlet_ = &nMarker_Dirichlet_Elec;
    Marker_Dirichlet_ = &Marker_Dirichlet_Elec;
    *Marker_Dirichlet_ = NULL;
    Value_Dirichlet_ = &Dirichlet_Value;
    *Value_Dirichlet_ = NULL;
  }
  
  /*!
   * \brief sets the value of the Dirichlet parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_Dirichlet_ != NULL) || (*Value_Dirichlet_ != NULL)) {
      cerr << "Error in CMarkerDirichletRef::SetValue(): "
      << "one or more Dirichlet-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 2 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_Dirichlet_ = 0;
        return;
      }
      cerr << "Error in CMarkerDirichletRef::SetValue(): "
      << "incorrect number of MARKER_DIRICHLET_ELEC parameters in the configuration file."
      << endl;
      throw(-1);
    }
    *nMarker_Dirichlet_ = static_cast<unsigned short>(value.size())/2;
    (*Marker_Dirichlet_) = new string[*nMarker_Dirichlet_];
    (*Value_Dirichlet_)       = new double[*nMarker_Dirichlet_];
    
    stringstream ss;
    unsigned short i = 0;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Dirichlet_; iMarker++) {
      ss << value[i++] << " ";
      ss >> (*Marker_Dirichlet_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*Value_Dirichlet_)[iMarker];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "CMarkerDirichletRef::WriteValue(): not implemented yet" << endl;
  }
  
};

/*!
 * \class CMarkerOutletRef
 * \brief Specialized option for outlet boundary markers
 * \author J. Hicken
 */
class CMarkerOutletRef : public CAnyOptionRef {
private:
  unsigned short* nMarker_Outlet_; /*!< \brief the number of outlet marker boundaries */
  string** Marker_Outlet_;         /*!< \brief string names of outlet boundaries */
  double** Pressure_;              /*!< \brief specified back pressures (static) for outlet boundaries */
  
public:
  
  /*!
   * \brief constructor for outlet marker option
   * \param[in] nMarker_Outlet - the number of outlet marker boundaries
   * \param[in] Marker_Outlet - string names of outlet boundaries
   * \param[in] Pressure - specified back pressures (static) for outlet boundaries
   */
  CMarkerOutletRef(unsigned short & nMarker_Outlet, string* & Marker_Outlet, double* & Pressure) {
    nMarker_Outlet_ = &nMarker_Outlet;
    Marker_Outlet_ = &Marker_Outlet;
    *Marker_Outlet_ = NULL;
    Pressure_ = &Pressure;
    *Pressure_ = NULL;
  }
  
  /*!
   * \brief sets the value of the outlet parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_Outlet_ != NULL) || (*Pressure_ != NULL) ) {
      cerr << "Error in CMarkerOutletRef::SetValue(): "
      << "one or more outlet-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 2 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_Outlet_ = 0;
        return;
      }
      cerr << "Error in CMarkerOutletRef::SetValue(): "
      << "incorrect number of MARKER_OUTLET parameters in the configuration file."
      << endl;
      throw(-1);
    }
    *nMarker_Outlet_  = static_cast<unsigned short>(value.size())/2;
    (*Marker_Outlet_) = new string[*nMarker_Outlet_];
    (*Pressure_)      = new double[*nMarker_Outlet_];
    stringstream ss;
    unsigned short i = 0;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Outlet_; iMarker++) {
      ss << value[i++] << " ";
      ss >> (*Marker_Outlet_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*Pressure_)[iMarker];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "Outlet markers (" << (*nMarker_Outlet_) << ")" << endl;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Outlet_; iMarker++)
      cout << "name = " << (*Marker_Outlet_)[iMarker]
      << ": back press. = " << (*Pressure_)[iMarker] << endl;
  }
  
};

/*!
 * \class CMarkerDisplacementRef
 * \brief Specialized option for Displacement boundary markers
 * \author F. Palacios
 */
class CMarkerDisplacementRef : public CAnyOptionRef {
private:
  unsigned short* nMarker_Displacement_; /*!< \brief the number of Displacement marker boundaries */
  string** Marker_Displacement_;         /*!< \brief string names of Displacement boundaries */
  double** Displ_;              /*!< \brief specified Displacement for Displacement boundaries */
  
public:
  
  /*!
   * \brief constructor for outlet marker option
   * \param[in] nMarker_Displacement - the number of Displacement marker boundaries
   * \param[in] Marker_Displacement - string names of Displacement boundaries
   * \param[in] Displ - specified back Displacement for Displacement boundaries
   */
  CMarkerDisplacementRef(unsigned short & nMarker_Displacement, string* & Marker_Displacement, double* & Displ) {
    nMarker_Displacement_ = &nMarker_Displacement;
    Marker_Displacement_ = &Marker_Displacement;
    *Marker_Displacement_ = NULL;
    Displ_ = &Displ;
    *Displ_ = NULL;
  }
  
  /*!
   * \brief sets the value of the Displacement parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_Displacement_ != NULL) || (*Displ_ != NULL) ) {
      cerr << "Error in CMarkerDisplacementRef::SetValue(): "
      << "one or more Displacement-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 2 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_Displacement_ = 0;
        return;
      }
      cerr << "Error in CMarkerDisplacementRef::SetValue(): "
      << "incorrect number of MARKER_Displacement parameters in the configuration file."
      << endl;
      throw(-1);
    }
    *nMarker_Displacement_  = static_cast<unsigned short>(value.size())/2;
    (*Marker_Displacement_) = new string[*nMarker_Displacement_];
    (*Displ_)      = new double[*nMarker_Displacement_];
    stringstream ss;
    unsigned short i = 0;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Displacement_; iMarker++) {
      ss << value[i++] << " ";
      ss >> (*Marker_Displacement_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*Displ_)[iMarker];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "Displacement markers (" << (*nMarker_Displacement_) << ")" << endl;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Displacement_; iMarker++)
      cout << "name = " << (*Marker_Displacement_)[iMarker]
      << ": displ. = " << (*Displ_)[iMarker] << endl;
  }
  
};


/*!
 * \class CMarkerLoadRef
 * \brief Specialized option for Load boundary markers
 * \author F. Palacios
 */
class CMarkerLoadRef : public CAnyOptionRef {
private:
  unsigned short* nMarker_Load_; /*!< \brief the number of load marker boundaries */
  string** Marker_Load_;         /*!< \brief string names of load boundaries */
  double** Force_;              /*!< \brief specified load for load boundaries */
  
public:
  
  /*!
   * \brief constructor for outlet marker option
   * \param[in] nMarker_Load - the number of load marker boundaries
   * \param[in] Marker_Load - string names of load boundaries
   * \param[in] Force - specified back load for load boundaries
   */
  CMarkerLoadRef(unsigned short & nMarker_Load, string* & Marker_Load, double* & Force) {
    nMarker_Load_ = &nMarker_Load;
    Marker_Load_ = &Marker_Load;
    *Marker_Load_ = NULL;
    Force_ = &Force;
    *Force_ = NULL;
  }
  
  /*!
   * \brief sets the value of the Load parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_Load_ != NULL) || (*Force_ != NULL) ) {
      cerr << "Error in CMarkerLoadRef::SetValue(): "
      << "one or more Load-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 2 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_Load_ = 0;
        return;
      }
      cerr << "Error in CMarkerLoadRef::SetValue(): "
      << "incorrect number of MARKER_LOAD parameters in the configuration file."
      << endl;
      throw(-1);
    }
    *nMarker_Load_  = static_cast<unsigned short>(value.size())/2;
    (*Marker_Load_) = new string[*nMarker_Load_];
    (*Force_)      = new double[*nMarker_Load_];
    stringstream ss;
    unsigned short i = 0;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Load_; iMarker++) {
      ss << value[i++] << " ";
      ss >> (*Marker_Load_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*Force_)[iMarker];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "Load markers (" << (*nMarker_Load_) << ")" << endl;
    for (unsigned short iMarker = 0; iMarker < *nMarker_Load_; iMarker++)
      cout << "name = " << (*Marker_Load_)[iMarker]
      << ": force. = " << (*Force_)[iMarker] << endl;
  }
  
};

/*!
 * \class CMarkerFlowLoadRef
 * \brief Specialized option for FlowLoad boundary markers
 * \author F. Palacios
 */
class CMarkerFlowLoadRef : public CAnyOptionRef {
private:
  unsigned short* nMarker_FlowLoad_; /*!< \brief the number of FlowLoad marker boundaries */
  string** Marker_FlowLoad_;         /*!< \brief string names of FlowLoad boundaries */
  double** FlowForce_;              /*!< \brief specified FlowLoad for FlowLoad boundaries */
  
public:
  
  /*!
   * \brief constructor for outlet marker option
   * \param[in] nMarker_FlowLoad - the number of FlowLoad marker boundaries
   * \param[in] Marker_FlowLoad - string names of FlowLoad boundaries
   * \param[in] FlowForce - specified back FlowLoad for FlowLoad boundaries
   */
  CMarkerFlowLoadRef(unsigned short & nMarker_FlowLoad, string* & Marker_FlowLoad, double* & FlowForce) {
    nMarker_FlowLoad_ = &nMarker_FlowLoad;
    Marker_FlowLoad_ = &Marker_FlowLoad;
    *Marker_FlowLoad_ = NULL;
    FlowForce_ = &FlowForce;
    *FlowForce_ = NULL;
  }
  
  /*!
   * \brief sets the value of the FlowLoad parameters given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if ( (*Marker_FlowLoad_ != NULL) || (*FlowForce_ != NULL) ) {
      cerr << "Error in CMarkerFlowLoadRef::SetValue(): "
      << "one or more FlowLoad-marker option arrays have already been allocated."
      << endl;
      throw(-1);
    }
    if (static_cast<int>(value.size()) % 2 != 0) {
      if (value[0].compare("NONE") == 0) {
        *nMarker_FlowLoad_ = 0;
        return;
      }
      cerr << "Error in CMarkerFlowLoadRef::SetValue(): "
      << "incorrect number of MARKER_FlowLoad parameters in the configuration file."
      << endl;
      throw(-1);
    }
    *nMarker_FlowLoad_  = static_cast<unsigned short>(value.size())/2;
    (*Marker_FlowLoad_) = new string[*nMarker_FlowLoad_];
    (*FlowForce_)      = new double[*nMarker_FlowLoad_];
    stringstream ss;
    unsigned short i = 0;
    for (unsigned short iMarker = 0; iMarker < *nMarker_FlowLoad_; iMarker++) {
      ss << value[i++] << " ";
      ss >> (*Marker_FlowLoad_)[iMarker];
      ss << value[i++] << " ";
      ss >> (*FlowForce_)[iMarker];
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "FlowLoad markers (" << (*nMarker_FlowLoad_) << ")" << endl;
    for (unsigned short iMarker = 0; iMarker < *nMarker_FlowLoad_; iMarker++)
      cout << "name = " << (*Marker_FlowLoad_)[iMarker]
      << ": FlowForce. = " << (*FlowForce_)[iMarker] << endl;
  }
  
};


/*!
 * \class CConvOptionRef
 * \brief a typed version of the base class for convection discretization options
 * \author J. Hicken
 */
class CConvOptionRef : public CAnyOptionRef {
private:
  unsigned short* space_ref_; /*!< \brief pointer to the space discretization type */
  unsigned short* centered_ref_; /*!< \brief pointer to the centered discretization type */
  unsigned short* upwind_ref_; /*!< \brief pointer to the upwind discretization type */
  
public:
  
  /*!
   * \brief constructor for convection options
   * \param[in] space - space discretization variable to create a reference to
   * \param[in] centered - centered discretization variable to create a reference to
   * \param[in] upwind - upwind discretization variable to create a reference to
   */
  CConvOptionRef(unsigned short & space, unsigned short & centered,
                 unsigned short & upwind) {
    space_ref_ = &space;
    centered_ref_ = &centered;
    upwind_ref_ = &upwind;
  }
  
  /*!
   * \brief sets the value of the referenced convection option using vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if (Centered_Map.count(value[0])) {
      *space_ref_ = Space_Map.find("SPACE_CENTERED")->second;
      *centered_ref_ = Centered_Map.find(value[0])->second;
      *upwind_ref_ = NO_UPWIND;
    } else if (Upwind_Map.count(value[0])) {
      *space_ref_ = Space_Map.find("SPACE_UPWIND")->second;
      *upwind_ref_ = Upwind_Map.find(value[0])->second;
      *centered_ref_ = NO_CENTERED;
    } else {
      cerr << "Error in CConvOptionRef::SetValue(): "
      << value[0] << " is an invalid space discretization" << endl;
      cerr << "Please, check that the config file is compatible with SU2 3.1.0 \"eagle\"" << endl;
      throw(-1);
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "space discretization: " << *space_ref_ << endl;
    cout << "centered discretization: " << *centered_ref_ << endl;
    cout << "upwind discretization: " << *upwind_ref_ << endl;
  }
};

/*!
 * \class CMathProblemRef
 * \brief this very specialized option for MATH_PROBLEM set several variables
 * \author J. Hicken
 */
class CMathProblemRef : public CAnyOptionRef {
private:
  bool* Adjoint_; /*!< \brief pointer to the Adjoint variable */
  bool* OneShot_; /*!< \brief pointer to the OneShot variable */
  bool* Linearized_; /*!< \brief pointer to the Linearized variable */
  bool* Restart_Flow_; /*!< \brief pointer to the Restart_Flow variable */
  
public:
  
  /*!
   * \brief constructor for math problem option
   * \param[in] Adj - is the adjoint being solved
   * \param[in] OneShot - is a one shot problem being solved
   * \param[in] Linearized - is a linearized problem being solved
   * \param[in] Restart_Flow - restart flow solution for adjoint and linearized problems
   */
  CMathProblemRef(bool & Adjoint, bool & OneShot, bool & Linearized,
                  bool & Restart_Flow) {
    Adjoint_ = &Adjoint;
    OneShot_ = &OneShot;
    Linearized_ = &Linearized;
    Restart_Flow_ = &Restart_Flow;
  }
  
  /*!
   * \brief sets the value of the math problem given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    if (value[0] == "DIRECT") {
      *Adjoint_ = false; *OneShot_ = false; *Linearized_ = false; *Restart_Flow_ = false;
    } else if (value[0] == "ADJOINT") {
      *Adjoint_ = true; *Restart_Flow_ = true;
    }
    if (value[0] == "LINEARIZED") {
      *Linearized_ = true; *Restart_Flow_ = true;
    }
  }
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    cout << "Adjoint_ = " << *Adjoint_;
    cout << ": OneShot_ = " << *OneShot_;
    cout << ": Linearized_ = " << *Linearized_;
    cout << ": Restart_Flow_ = " << *Restart_Flow_ << endl;
  }
};

/*!
 * \class CDVParamOptionRef
 * \brief Specialized option for grid deformation parameters
 * \author J. Hicken
 */
class CDVParamOptionRef : public CAnyOptionRef {
private:
  unsigned short* nDV_; /*!< \brief Number of variables. */
  double*** ParamDV_; /*!< \brief Parameters of the variables. */
  unsigned short** Design_Variable_; /*!< \brief design variable types; should already be allocated */
  
public:
  
  /*!
   * \brief constructor for DVParam option
   * \param[in] nDV - number of design variables
   * \param[in] ParamDV - the paramters of each design variable
   * \param[in] Design_Variable - DV types
   */
  CDVParamOptionRef(unsigned short & nDV, double** & ParamDV,
                    unsigned short* & Design_Variable) {
    nDV_ = &nDV;
    ParamDV_ = &ParamDV;
    Design_Variable_ = &Design_Variable;
  }
  
  /*!
   * \brief sets the value of the design variables given the vector of strings
   * \param[in] value - a set of strings used to define the option
   */
  void SetValue(const vector<string> & value) {
    
    // use the ";" token to determine the number of design variables
    *nDV_ = 0;
    unsigned int num_semi = 0;
    for (unsigned int i = 0; i < static_cast<unsigned int>(value.size()); i++) {
      if (value[i].compare(";") == 0) {
        (*nDV_)++;
        num_semi++;
      }
    }
    // if ";" are at both ends, we over-counted
    if ( (value[0].compare(";") == 0) && (value[value.size()-1].compare(";") == 0) )
      (*nDV_)--;
    // if no ";" at either end, we under-counted
    if ( (value[0].compare(";") != 0) && (value[value.size()-1].compare(";") != 0) )
      (*nDV_)++;
    
    if ( (*nDV_ > 0) && (*Design_Variable_ == NULL) ) {
      cerr << "Error in CDVParamOptionRef::SetValue(): "
      << "Design_Variable array has not been allocated." << endl;
      cerr << "Check that DV_KIND appears before DV_PARAM in configuration file." << endl;
      throw(-1);
    }
    
#if 0
    cout << "Found " << (*nDV_) << " DV parameters" << endl;
    cout << "DV param value = ";
    for (unsigned int i = 0; i < value.size(); i++)
      cout << value[i] << ", ";
    cout << endl;
#endif
    
    
    
    (*ParamDV_) = new double*[*nDV_];
    for (unsigned short iDV = 0; iDV < *nDV_; iDV++)
      (*ParamDV_)[iDV] = new double[MAX_PARAMETERS];
    
    unsigned short nParamDV = 0;
    stringstream ss;
    unsigned int i = 0;
    for (unsigned short iDV = 0; iDV < *nDV_; iDV++) {
      switch ((*Design_Variable_)[iDV]) {
        case FFD_SETTING: nParamDV = 0; break;
        case FFD_CONTROL_POINT_2D: nParamDV = 5; break;
        case FFD_CAMBER_2D: nParamDV = 2; break;
        case FFD_THICKNESS_2D: nParamDV = 2; break;
        case HICKS_HENNE: nParamDV = 2; break;
        case SPHERICAL: nParamDV = 3; break;
        case COSINE_BUMP: nParamDV = 3; break;
        case FOURIER: nParamDV = 3; break;
        case DISPLACEMENT: nParamDV = 3; break;
        case ROTATION: nParamDV = 6; break;
        case NACA_4DIGITS: nParamDV = 3; break;
        case PARABOLIC: nParamDV = 2; break;
        case OBSTACLE: nParamDV = 2; break;
        case AIRFOIL: nParamDV = 2; break;
        case STRETCH: nParamDV = 2; break;
        case FFD_CONTROL_POINT: nParamDV = 7; break;
        case FFD_DIHEDRAL_ANGLE: nParamDV = 7; break;
        case FFD_TWIST_ANGLE: nParamDV = 7; break;
        case FFD_ROTATION: nParamDV = 7; break;
        case FFD_CAMBER: nParamDV = 3; break;
        case FFD_THICKNESS: nParamDV = 3; break;
        case SURFACE_FILE: nParamDV = 0; break;
        default : {
          cerr << "Error in CDVParamOptionRef::SetValue(): "
          << "undefined design variable type found in configuration file." << endl; break;
        }
      }
      for (unsigned short iParamDV = 0; iParamDV < nParamDV; iParamDV++) {
        ss << value[i] << " ";
        ss >> (*ParamDV_)[iDV][iParamDV];
        i++;
      }
      if (iDV < (*nDV_)-1) {
        if (value[i].compare(";") != 0) {
          cerr << "Error in CDVParamOptionRef::SetValue(): "
          << "a design variable in the configuration file "
          << "has the wrong number of parameters" << endl;
          throw(-1);
        }
        i++;
      }
    }
  }
  
  
  /*!
   * \brief write the value of the option to std out (mostly for debugging)
   */
  void WriteValue() {
    
    for (unsigned short iDV = 0; iDV < *nDV_; iDV++) {
      unsigned short nParamDV = 0;
      switch ((*Design_Variable_)[iDV]) {
        case FFD_SETTING: nParamDV = 0; break;
        case FFD_CONTROL_POINT_2D: nParamDV = 5; break;
        case FFD_CAMBER_2D: nParamDV = 2; break;
        case FFD_THICKNESS_2D: nParamDV = 2; break;
        case HICKS_HENNE: nParamDV = 2; break;
        case SPHERICAL: nParamDV = 3; break;
        case COSINE_BUMP: nParamDV = 3; break;
        case FOURIER: nParamDV = 3; break;
        case DISPLACEMENT: nParamDV = 3; break;
        case ROTATION: nParamDV = 6; break;
        case NACA_4DIGITS: nParamDV = 3; break;
        case PARABOLIC: nParamDV = 2; break;
        case FFD_CONTROL_POINT: nParamDV = 7; break;
        case FFD_DIHEDRAL_ANGLE: nParamDV = 7; break;
        case FFD_TWIST_ANGLE: nParamDV = 7; break;
        case FFD_ROTATION: nParamDV = 7; break;
        case FFD_CAMBER: nParamDV = 3; break;
        case FFD_THICKNESS: nParamDV = 3; break;
        default : {
          cerr << "Error in CDVParamOptionRef::SetValue(): "
          << "undefined design variable type found in configuration file." << endl; break;
        }
      }
      cout << "DV param type: " << (*Design_Variable_)[iDV] << ": values = ";
      for (unsigned short iParamDV = 0; iParamDV < nParamDV; iParamDV++)
        cout << (*ParamDV_)[iDV][iParamDV] << ", ";
      cout << endl;
    }
  }
};
