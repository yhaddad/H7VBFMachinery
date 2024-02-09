// -*- C++ -*-
//
// HiggsMTScale.cc is a part of Herwig - A multi-purpose Monte Carlo event generator
// Copyright (C) 2002-2017 The Herwig Collaboration
//
// Herwig is licenced under version 3 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HiggsMTScale class.
//

#include "HiggsMTScale.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"


#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace Herwig;

HiggsMTScale::HiggsMTScale() {}

HiggsMTScale::~HiggsMTScale() {}

IBPtr HiggsMTScale::clone() const {
  return new_ptr(*this);
}

IBPtr HiggsMTScale::fullclone() const {
  return new_ptr(*this);
}

Energy2 HiggsMTScale::renormalizationScale() const {

  Energy mHiggs = ZERO;
  Energy ptHiggs = ZERO;
  bool gotone = false;

  auto iData = mePartonData().begin() + 2;
  auto iMom = meMomenta().begin() + 2;
  for ( ; iData != mePartonData().end(); ++iData, ++iMom ) {
    if ( (*iData)->id() == 25 ) {
      mHiggs = (*iData)->mass();
      ptHiggs = iMom->perp();
      gotone = true;
      break;
    }
  }

  if ( !gotone )
    throw Exception() << "HiggsMTScale::renormalizationScale(): No Higgs could be found. Check your setup."
		      << Exception::runerror;

  return (mHiggs/2.)*sqrt(sqr(mHiggs/2.)+sqr(ptHiggs));
  
}

Energy2 HiggsMTScale::factorizationScale() const {
  return renormalizationScale();
}

// If needed, insert default implementations of virtual function defined
// in the InterfacedBase class here (using ThePEG-interfaced-impl in Emacs).


void HiggsMTScale::persistentOutput(PersistentOStream &) const {
}

void HiggsMTScale::persistentInput(PersistentIStream &, int) {
}


// *** Attention *** The following static variable is needed for the type
// description system in ThePEG. Please check that the template arguments
// are correct (the class and its base class), and that the constructor
// arguments are correct (the class name and the name of the dynamically
// loadable library where the class implementation can be found).
DescribeClass<HiggsMTScale,MatchboxScaleChoice>
  describeHerwigHiggsMTScale("Herwig::HiggsMTScale", "HiggsMTScale.so");

void HiggsMTScale::Init() {

  static ClassDocumentation<HiggsMTScale> documentation
    ("HiggsMTScale implements scale choices related to transverse momenta.");

}
