CXX=g++
CXXOPTFLAGS=$(RDOPTFLAGS)
CXXDEBUGFLAGS=-g
#CXXOPTFLAGS=-g -DVERBOSE_CANON -DVERYVERBOSE_CANON
BASECXXFLAGS=$(CXXOPTFLAGS) $(BOOSTINC) $(RDKITINCFLAGS) $(VFLIBINC)
DEBUGCXXFLAGS=$(CXXDEBUGFLAGS) $(BOOSTINC) $(RDKITINCFLAGS) $(VFLIBINC)
SOFLAGS=-fPIC -shared -rdynamic
SOFLAGS=-fPIC -shared



# -----------
# Python
# -----------
PYTHONINC=-I$(PYTHON_ROOT)/include/python$(PYTHON_VERSION)


# -----------
# Boost
# -----------
BOOSTINC=-I/usr/local/include/$(BOOSTBASE)
BOOSTLOGLIB=-lboost_log-gcc-s -lboost_thread-gcc-mt
BOOSTLOGLIB_S=-lboost_log-gcc-s -lboost_thread-gcc-mt
#BOOSTINC=-I/home2/glandrum/boost_gcc34/include/$(BOOSTBASE)
#BOOSTLOGLIB=-L/home2/glandrum/boost_gcc34/lib -lboost_log-gcc-s -lboost_thread-gcc-mt-s
#BOOSTLOGLIB_S=-L/home2/glandrum/boost_gcc34/lib -lboost_log-gcc-s -lboost_thread-gcc-mt-s
#BOOSTINC=-I$(RDBASE)/External/boost/include/$(BOOSTBASE)
#BOOSTLOGLIB_S=-L/c/boost/lib/ -lboost_log-mgw-s-$(BOOSTVERSION)

# -----------
# Xerces
# -----------
XERCESLOC=$(RDBASE)/External/xerces-c
XERCESINC=-I$(XERCESLOC)/include
#XERCESLIB=-L$(XERCESLOC)/lib -lxerces-c1_5_2 -lpthread
XERCESLIB=-L$(XERCESLOC)/lib -lxerces-c1_5_2

# -----------
# vflib
# -----------
VFLIBLOC=$(RDBASE)/External/vflib-2.0
VFLIBINC=-I$(VFLIBLOC)/include
VFLIB=-L$(VFLIBLOC)/lib -lvf

# -----------
# Lapack++
# -----------
LAPACKLOC=$(RDBASE)/External/Lapack++
LAPACKINC=-I$(LAPACKLOC)/include
ifdef RDF77LIB
F77LIB=-l$(RDF77LIB)
else
F77LIB=
endif
LAPACKLIB=-L$(LAPACKLOC) -llapack++ -llamatrix++ -lblas++ -llapack -lblas  -lm $(F77LIB)

# -----------
# Our stuff
# -----------
RDCODEDIR=$(RDBASE)/Code
RDLIBDIR=$(RDCODEDIR)/GraphMol/libs

RDGENERAL=-L$(RDCODEDIR)/RDGeneral -lRDGeneral $(BOOSTLOGLIB_S)
RDGENERAL_S=-L$(RDCODEDIR)/RDGeneral -lRDGeneral_s $(BOOSTLOGLIB_S)


RDGEOMETRY=-L$(RDCODEDIR)/Geometry -lRDGeometry
RDGEOMETRY_S=-L$(RDCODEDIR)/Geometry -lRDGeometry_s

GRAPHLIBBASE=GraphMol
RDGRAPHLIB=$(RDLIBDIR)/lib$(GRAPHLIBBASE).so
RDGRAPHLIB_S=$(RDLIBDIR)/lib$(GRAPHLIBBASE)_s.a
RDQUERY=-L$(RDCODEDIR)/Query -lQuery
RDBITVECS=-L$(RDCODEDIR)/DataStructs -lDataStructs
RDCHEMFEATS=-L$(RDCODEDIR)/ChemicalFeatures -lChemicalFeatures
RDKIT=-L$(RDLIBDIR) -l$(GRAPHLIBBASE) $(RDBITVECS) $(LAPACKLIB)
RDKIT_S=-L$(RDLIBDIR) -l$(GRAPHLIBBASE)_s $(RDBITVECS) $(LAPACKLIB)
RDKITINCFLAGS=-I$(RDBASE)/Code/GraphMol -I$(RDBASE)/Code

SMILESLIBBASE=SmilesParse
RDSMILESLIB=$(RDLIBDIR)/lib$(SMILESLIBBASE).so
RDSMILESLIB_S=$(RDLIBDIR)/lib$(SMILESLIBBASE)_s.a
RDSMILES=-L$(RDLIBDIR) -l$(SMILESLIBBASE)
RDSMILES_S=-L$(RDLIBDIR) -l$(SMILESLIBBASE)_s

CDXMLLIBBASE=CDXMLParse
RDCDXMLLIB=$(RDLIBDIR)/lib$(CDXMLLIBBASE).so
RDCDXML=-L$(RDLIBDIR) -l$(CDXMLLIBBASE)

SUBSTRUCTLIBBASE=Substruct
RDSUBSTRUCTLIB=$(RDLIBDIR)/lib$(SUBSTRUCTLIBBASE).so
RDSUBSTRUCTLIB_S=$(RDLIBDIR)/lib$(SUBSTRUCTLIBBASE)_s.a
RDSUBSTRUCT=-L$(RDLIBDIR) -l$(SUBSTRUCTLIBBASE)
RDSUBSTRUCT_S=-L$(RDLIBDIR) -l$(SUBSTRUCTLIBBASE)_s

CATALOGLIBBASE=Catalogs
RDCATALOGLIB=$(RDCODEDIR)/Catalogs/lib$(CATALOGLIBBASE).a
RDCATALOGS=-L$(RDCODEDIR)/Catalogs -l$(CATALOGLIBBASE)

FRAGCATLIBBASE=FragCat
RDFRAGCATLIB=$(RDLIBDIR)/lib$(FRAGCATLIBBASE).so
RDFRAGCAT=-L$(RDLIBDIR) -l$(FRAGCATLIBBASE)
RDFRAGCATLIB_S=$(RDLIBDIR)/lib$(FRAGCATLIBBASE)_s.a
RDFRAGCAT_S=-L$(RDLIBDIR) -l$(FRAGCATLIBBASE)_s

DEPICTORLIBBASE=Depictor
RDDEPICTORLIB=$(RDLIBDIR)/lib$(DEPICTORLIBBASE).so
RDDEPICTOR=-L$(RDLIBDIR) -l$(DEPICTORLIBBASE)
RDDEPICTORLIB_S=$(RDLIBDIR)/lib$(DEPICTORLIBBASE)_s.a
RDDEPICTOR_S=-L$(RDLIBDIR) -l$(DEPICTORLIBBASE)_s

FILEPARSELIBBASE=FileParsers
RDFILEPARSELIB=$(RDLIBDIR)/lib$(FILEPARSELIBBASE).so
RDFILEPARSELIB_S=$(RDLIBDIR)/lib$(FILEPARSELIBBASE)_s.a
RDFILEPARSE=-L$(RDLIBDIR) -l$(FILEPARSELIBBASE)
RDFILEPARSE_S=-L$(RDLIBDIR) -l$(FILEPARSELIBBASE)_s

MOLTRANSFORMSBASE=MolTransforms
RDMOLTRANSFORMSLIB=$(RDLIBDIR)/lib$(MOLTRANSFORMSBASE).so
RDMOLTRANSFORMS=-L$(RDBASE)/Code/GraphMol/MolTransforms -l$(MOLTRANSFORMSBASE)

SUBGRAPHSBASE=Subgraphs
RDSUBGRAPHSLIB=$(RDLIBDIR)/lib$(SUBGRAPHSBASE).so
RDSUBGRAPHSLIB_S=$(RDLIBDIR)/lib$(SUBGRAPHSBASE)_s.a
RDSUBGRAPHS=-L$(RDLIBDIR) -l$(SUBGRAPHSBASE)
RDSUBGRAPHS_S=-L$(RDLIBDIR) -l$(SUBGRAPHSBASE)_s

FINGERPRINTSBASE=Fingerprints
RDFINGERPRINTSLIB=$(RDLIBDIR)/lib$(FINGERPRINTSBASE).so
RDFINGERPRINTSLIB_S=$(RDLIBDIR)/lib$(FINGERPRINTSBASE)_s.a
RDFINGERPRINTS=-L$(RDLIBDIR) -l$(FINGERPRINTSBASE)
RDFINGERPRINTS_S=-L$(RDLIBDIR) -l$(FINGERPRINTSBASE)_s

DEPICTORBASE=Depictor
RDDEPICTORLIB=$(RDLIBDIR)/lib$(DEPICTORBASE).so
RDDEPICTOR=-L$(RDLIBDIR) -l$(DEPICTORBASE)


PYTHONWRAP=$(RDBASE)/Python/Chem/rdmol.so


OPTIMIZERBASE=Optimizer
RDOPTIMIZER=-L$(RDBASE)/Code/Numerics/Optimizer -l$(OPTIMIZERBASE)

FORCEFIELDBASE=ForceFields
RDFORCEFIELDS=-L$(RDBASE)/Code/ForceField -l$(FORCEFIELDBASE)

FORCEFIELDHELPERSBASE=ForceFieldHelpers
RDFORCEFIELDHELPERS=-L$(RDBASE)/Code/GraphMol/ForceFieldHelpers -l$(FORCEFIELDHELPERSBASE)

DISTGEOMBASE=DistGeom
RDDISTGEOM=-L$(RDBASE)/Code/DistGeom -l$(DISTGEOMBASE)

FEATTREESBASE=FeatTrees
RDFEATTREES=-L$(RDBASE)/Code/FeatTrees -l$(FEATTREESBASE)

EIGENSOLVERSBASE=EigenSolvers
RDEIGENSOLVERS=-L$(RDBASE)/Code/Numerics/EigenSolvers -l$(EIGENSOLVERSBASE)

ALIGNMENTBASE=Alignment
RDALIGNMENT=-L$(RDBASE)/Code/Numerics/Alignment -l$(ALIGNMENTBASE)

DGEOMHELPERSBASE=DistGeomHelpers
RDDGEOMHELPERS=-L$(RDBASE)/Code/GraphMol/DistGeomHelpers -l$(DGEOMHELPERSBASE)

SHAPEHELPERSBASE=ShapeHelpers
RDSHAPEHELEPRS=-L$(RDBASE)/Code/GraphMol/ShapeHelpers -l$(SHAPEHELPERSBASE)

MOLALIGNBASE=MolAlign
RDMOLALIGN=-L$(RDBASE)/Code/GraphMol/MolAlign -l$(MOLALIGNBASE)

MOLDESCRIPTORSBASE=Descriptors
RDMOLDESCRIPTORS=-L$(RDBASE)/Code/GraphMol/Descriptors -l$(MOLDESCRIPTORSBASE)

