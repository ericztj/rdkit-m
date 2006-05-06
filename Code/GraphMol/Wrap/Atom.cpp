// $Id: Atom.cpp 4978 2006-02-18 00:59:33Z glandrum $
//
//  Copyright (C) 2003-2006 Rational Discovery LLC
//
//   @@ All Rights Reserved  @@
//

#define NO_IMPORT_ARRAY
#include <boost/python.hpp>
#include <string>

#include <GraphMol/RDKitBase.h>
#include <RDGeneral/types.h>
#include <Geometry/point.h>

#include "seqs.hpp"
#include <algorithm>


namespace python = boost::python;
namespace RDKit{

  
  int AtomHasProp(const Atom *atom, const char *key) {
    int res = atom->hasProp(key);
    return res;
  }

  std::string AtomGetProp(const Atom *atom, const char *key) {
    if (!atom->hasProp(key)) {
      PyErr_SetString(PyExc_KeyError,key);
      throw python::error_already_set();
    }
    std::string res;
    atom->getProp(key, res);
    return res;
  }
  /* We should start using the conformer stuff for this - so commenting this out
  std::vector<double> AtomGetPosition(Atom *atom) {
    RDGeom::Point3D pt = atom->getPos();
    std::vector<double> res;
    res.reserve(3);
    res.push_back(pt.x);
    res.push_back(pt.y);
    res.push_back(pt.z);
    return res;
  }
  */

  python::tuple AtomGetNeighbors(Atom *atom){
    python::list res;
    const ROMol *parent = &atom->getOwningMol();
    ROMol::ADJ_ITER begin,end;
    boost::tie(begin,end) = parent->getAtomNeighbors(atom);
    while(begin!=end){
      res.append(python::ptr(parent->getAtomWithIdx(*begin)));
      begin++;
    }
    return python::tuple(res);
  }

  python::tuple AtomGetBonds(Atom *atom){
    python::list res;
    const ROMol *parent = &atom->getOwningMol();
    ROMol::OEDGE_ITER begin,end;
    ROMol::GRAPH_MOL_BOND_PMAP::const_type pMap = parent->getBondPMap();
    boost::tie(begin,end) = parent->getAtomBonds(atom);
    while(begin!=end){
      Bond *tmpB = pMap[*begin];
      res.append(python::ptr(tmpB));
      begin++;
    }
    return python::tuple(res);
  }

  bool AtomIsInRing(const Atom *atom){
    if(!atom->getOwningMol().getRingInfo()->isInitialized()){
      MolOps::findSSSR(atom->getOwningMol());
    }
    return atom->getOwningMol().getRingInfo()->numAtomRings(atom->getIdx())!=0;
  }
  bool AtomIsInRingSize(const Atom *atom,int size){
    if(!atom->getOwningMol().getRingInfo()->isInitialized()){
      MolOps::findSSSR(atom->getOwningMol());
    }
    return atom->getOwningMol().getRingInfo()->isAtomInRingOfSize(atom->getIdx(),size);
  }

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getTotalNumHs_ol, getTotalNumHs, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getImplicitValence_ol, getImplicitValence, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getExplicitValence_ol, getExplicitValence, 0, 1)


  // FIX: is there any reason at all to not just prevent the construction of Atoms?
  std::string atomClassDoc="The class to store Atoms.\n\
Note that, though it is possible to create one, having an Atom on its own\n\
(i.e not associated with a molecule) is not particularly useful.\n";
struct atom_wrapper {
  static void wrap(){
    python::class_<Atom>("Atom",atomClassDoc.c_str(),python::init<std::string>())

      .def(python::init<unsigned int>("Constructor, takes either an int (atomic number) or a string (atomic symbol).\n"))

      .def("GetAtomicNum",&Atom::getAtomicNum,
	   "Returns the atomic number.")

      .def("SetAtomicNum",&Atom::setAtomicNum,
	   "Sets the atomic number, takes an integer value as an argument")

      .def("GetSymbol",&Atom::getSymbol,
	   "Returns the atomic number (a string)\n")

      .def("GetIdx",&Atom::getIdx,
	   "Returns the atom's index (ordering in the molecule)\n")

      .def("GetDegree",&Atom::getDegree,
	   "Returns the degree of the atom in the molecule.\n\n"
	   "  The degree of an atom is defined to be its number of\n"
	   "  directly-bonded neighbors.\n"
	   "  The degree is independent of bond orders.\n")

      .def("GetTotalNumHs",&Atom::getTotalNumHs,
	   getTotalNumHs_ol(python::args("includeNeighbors"),
			    "Returns the total number of Hs (explicit and implicit) on the atom.\n\n"
			    "  ARGUMENTS:\n\n"
			    "    - includeNeighbors: (optional) toggles inclusion of neighboring H atoms in the sum.\n"
			    "      Defaults to 0.\n"))

      .def("GetNumImplicitHs",&Atom::getNumImplicitHs,
	   "Returns the total number of implicit Hs on the atom.\n")

      .def("GetExplicitValence",&Atom::getExplicitValence,
	   getExplicitValence_ol(python::args("forceCalc"),
				 "Returns the number of explicit Hs on the atom.\n\n"
				 "  ARGUMENTS:\n\n"
				 "    - forceCalc: (optional) forces the value to be calculated, even if already cached.\n"
				 "      Defaults to 0.\n"))

      .def("GetImplicitValence",&Atom::getImplicitValence,
	   getImplicitValence_ol(python::args("forceCalc"),
				 "Returns the number of implicit Hs on the atom.\n\n"
				 "  ARGUMENTS:\n\n"
				 "    - forceCalc: (optional) forces the value to be calculated, even if already cached.\n"
				 "      Defaults to 0.\n"))

      .def("GetFormalCharge",&Atom::getFormalCharge)
      .def("SetFormalCharge",&Atom::setFormalCharge)


      .def("SetNoImplicit",&Atom::setNoImplicit,
	   "Sets a marker on the atom that *disallows* implicit Hs.\n"
	   "  This holds even if the atom would otherwise have implicit Hs added.\n")
      .def("GetNoImplicit",&Atom::getNoImplicit,
	   "Returns whether or not the atom is *allowed* to have implicit Hs.\n")

      .def("SetNumExplicitHs",&Atom::setNumExplicitHs)
      .def("GetNumExplicitHs",&Atom::getNumExplicitHs)
      .def("SetIsAromatic",&Atom::setIsAromatic)
      .def("GetIsAromatic",&Atom::getIsAromatic)
      .def("SetMass",&Atom::setMass)
      .def("GetMass",&Atom::getMass)

      // NOTE: these may be used at some point in the future, but they
      //  aren't now, so there's no point in confusing things.
      //.def("SetDativeFlag",&Atom::setDativeFlag)
      //.def("GetDativeFlag",&Atom::getDativeFlag)
      //.def("ClearDativeFlag",&Atom::clearDativeFlag)

      .def("SetChiralTag",&Atom::setChiralTag)
      .def("GetChiralTag",&Atom::getChiralTag)

      .def("SetHybridization",&Atom::setHybridization,
	   "Sets the hybridization of the atom.\n"
	   "  The argument should be a HybridizationType\n")
      .def("GetHybridization",&Atom::getHybridization,
	   "Returns the atom's hybridization.\n")

      .def("GetOwningMol",&Atom::getOwningMol,
	   "Returns the Mol that owns this atom.\n",
	   python::return_value_policy<python::reference_existing_object>())

      //.def("GetPosition", AtomGetPosition,
      //     "Get the position of the atom\n")

      .def("GetNeighbors",AtomGetNeighbors,
	   "Returns a read-only sequence of the atom's neighbors\n")

      .def("GetBonds",AtomGetBonds,
	   "Returns a read-only sequence of the atom's bonds\n")

      // FIX: Query stuff
      .def("Match",(bool (Atom::*)(const Atom *) const)&Atom::Match,
	   "Returns whether or not this atom matches another Atom.\n\n"
	   "  Each Atom (or query Atom) has a query function which is\n"
	   "  used for this type of matching.\n\n"
	   "  ARGUMENTS:\n"
	   "    - other: the other Atom to which to compare\n")

      .def("IsInRingSize",AtomIsInRingSize,
	   "Returns whether or not the atom is in a ring of a particular size.\n\n"
	   "  ARGUMENTS:\n"
	   "    - size: the ring size to look for\n") 

      .def("IsInRing",AtomIsInRing,
	   "Returns whether or not the atom is in a ring\n\n")


      .def("GetProp", AtomGetProp,
           "Returns the value of the property.\n\n"
	   "  ARGUMENTS:\n"
	   "    - key: the name of the property to return (a string).\n\n"
	   "  RETURNS: a string\n\n"
	   "  NOTE:\n"
	   "    - If the property has not been set, a KeyError exception will be raised.\n")

      .def("HasProp", AtomHasProp,
           "Queries a Atom to see if a particular property has been assigned.\n\n"
	   "  ARGUMENTS:\n"
	   "    - key: the name of the property to check for (a string).\n")
      ;
    python::enum_<Atom::HybridizationType>("HybridizationType")
      .value("UNSPECIFIED",Atom::UNSPECIFIED)
      .value("SP",Atom::SP)
      .value("SP2",Atom::SP2)
      .value("SP3",Atom::SP3)
      .value("SP3D",Atom::SP3D)
      .value("SP3D2",Atom::SP3D2)
      .value("OTHER",Atom::OTHER)
      ;
    python::enum_<Atom::ChiralType>("ChiralType")
      .value("CHI_UNSPECIFIED",Atom::CHI_UNSPECIFIED)
      .value("CHI_TETRAHEDRAL_CW",Atom::CHI_TETRAHEDRAL_CW)
      .value("CHI_TETRAHEDRAL_CCW",Atom::CHI_TETRAHEDRAL_CCW)
      .value("CHI_OTHER",Atom::CHI_OTHER)
      ;

  };
};
}// end of namespace
void wrap_atom() {
  RDKit::atom_wrapper::wrap();
}
