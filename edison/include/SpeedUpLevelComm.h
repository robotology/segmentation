/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_ENUM_SpeedUpLevelComm
#define YARP_THRIFT_GENERATOR_ENUM_SpeedUpLevelComm

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

enum SpeedUpLevelComm {
  NO_SPEEDUP_COMM = 0,
  MED_SPEEDUP_COMM = 1,
  HIGH_SPEEDUP_COMM = 2
};

class SpeedUpLevelCommVocab;

class SpeedUpLevelCommVocab : public yarp::os::idl::WireVocab {
public:
  virtual int fromString(const std::string& input) override;
  virtual std::string toString(int input) const override;
};


#endif
