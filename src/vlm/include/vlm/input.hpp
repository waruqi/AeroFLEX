
#ifndef INPUT_HPP
#define INPUT_HPP

#include "Eigen/Dense"
#include <map>
#include <string>
#include <tuple>

/** @file input.hpp */

using namespace Eigen;

namespace vlm {

namespace input {

/** @brief Object holding case and physics-oriented parameters */
struct simParam {

  /** @brief Geometric angle of attack in degrees */
  double aoa;

  /** @brief Geometric angle of side slip in degrees */
  double sideslip;

  /** @brief Free stream magnitude velocity */
  double vinf;

  /** @brief Density of the fluid */
  double rho;

  /** @brief Reference chord length */
  double cref;

  /** @brief Reference surface area */
  double sref;

  /** @brief Origin to which the x and z moment are computed */
  Vector3d origin;

  /** @brief Viscous relaxation value applied on the vortex filament kernel */
  double coreRadius;

  /** @brief Input format of the database (FILE, POLAR, NONE) */
  std::string databaseFormat;

  /** @brief Equation of the lift polar (only required of databaseFormat is set
   * to POLAR)*/
  std::string liftPolar;

  /** @brief Method computing the free stream vector in the plane's referential
   *  @return Free stream vector */
  Vector3d freeStream() const;

  /** @brief Method computing the free stream vector in the plane's referential
   * and according to a local angle of attack
   *  @param alpha Local angle of attack
   *  @return Local free stream vector */
  Vector3d freeStream(const double alpha) const;
};

/** @brief Object holding input/output information */
struct ioParam {

  /** @brief Prefix that will be applied to all output files */
  std::string baseName;

  /** @brief Path of the directory to which the solution will be outputted */
  std::string outDir;

  /** @brief Path to the mesh file */
  std::string meshFile;

  /** @brief Path to the database file (if required) */
  std::string databaseFile;
};

/** @brief Object holding solver parameters */
struct solverParam {

  /** @brief Time domain of the simulation (steady or time-dependent) */
  std::string timeDomain;

  /** @brief Type of solver utilised (linear or non linear) */
  std::string type;

  /** @brief Tolerance of the non linear iterative solver */
  double tolerance;

  /** @brief Interpolation type for viscous database */
  std::string interpolation;

  /** @brief Linear solver type */
  std::string linearSolver;

  /** @brief Relaxation for the iterative scheme */
  double relaxation;

  /** @brief Max number of iterations for the iterative scheme */
  int max_iter;
};

/** @brief Main struct holding parameters on the current case */
struct settings {

  /** @brief Object holding case and physics-oriented parameters */
  simParam sim;

  /** @brief Object holding input/output information */
  ioParam io;

  /** @brief Object holding solver parameters */
  solverParam solver;
};

/** @brief Object holding the connectivity obtained from the mesh file */
struct meshData {

  /** @brief Map holding the nodes */
  std::map<unsigned int, Vector3d> nodes;

  /** @brief Map holding the IDs of the nodes belonging to a vortex ring*/
  std::map<unsigned int, std::vector<int>> vortexIDs;

  /** @brief Map holding the IDs of the nodes belonging to a doublet panel */
  std::map<unsigned int, std::vector<int>> doubletIDs;

  /** @brief Map holding the IDs of the vortex rings belonging to a wing station
   */
  std::map<unsigned int, std::vector<int>> stationIDs;

  /** @brief Map holding the IDs of the wing stations belonging to a wing
   * surface */
  std::map<unsigned int, std::vector<int>> wingIDs;

  /** @brief Map holding the IDs of the doublet panels belonging to a patch
   * surface */
  std::map<unsigned int, std::vector<int>> patchIDs;
};

/** @brief Function wrapper that imports user parameters from the .ini
 * configuration file
 *  @param path Path to the configuration file
 *  @return Tuple holding the three parameters objects */
std::tuple<ioParam, simParam, solverParam>
importConfigFile(const std::string path);

/** @brief Function that checks for disrepencies in the imported mesh
 *  @param mesh meshData object that holds information on the input mesh */
void meshCheck(const meshData &mesh);

/** @brief Function wrapper that import connectivity data specified in the mesh
 * file
 *  @param names input/output parameters object
 *  @return meshData object holding all the information on the current mesh */
meshData importMeshFile(const ioParam &names);

} // namespace input
} // namespace vlm

#endif
