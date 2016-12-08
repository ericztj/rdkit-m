rdkit_library(Fingerprints
              Fingerprints.cpp PatternFingerprints.cpp MorganFingerprints.cpp AtomPairs.cpp MACCS.cpp
              LINK_LIBRARIES Subgraphs SubstructMatch SmilesParse GraphMol
                ${RDKit_THREAD_LIBS} )

rdkit_headers(AtomPairs.h
              Fingerprints.h
              MorganFingerprints.h
              MACCS.h
              DEST GraphMol/Fingerprints)



