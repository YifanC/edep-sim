//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//---------------------------------------------------------------------------
//
// ClassName:   QGSP_BERT_HP
//
// Author: 2002 J.P. Wellisch
//
// Modified:
// 19.01.2021 D.Rivera: imported into artg4tk based on :
//            geant4.10.06.p01/source/physics_lists/lists/include/QGSP_BERT_HP.hh
// 21.06.2023 D.Rivera: imported into edep-sim
// 21.06.2023 D.Rivera: imported into edep-sim
//
//----------------------------------------------------------------------------
//
#ifndef lists_MyQGSP_BERT_ArHP_hh
#define lists_MyQGSP_BERT_ArHP_hh

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class MyQGSP_BERT_ArHP : public G4VModularPhysicsList {
public:
  MyQGSP_BERT_ArHP(G4int ver = 1);

  MyQGSP_BERT_ArHP(const MyQGSP_BERT_ArHP&) = delete;
  MyQGSP_BERT_ArHP& operator=(const MyQGSP_BERT_ArHP&) = delete;

  void SetCuts() override;
};

#endif /* lists_MyQGSP_BERT_ArHP_hh */
