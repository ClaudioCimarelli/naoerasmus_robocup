/**
* @file LibCodeRelease.cpp
*/

#include "../LibraryBase.h"
#include "../../Util/Eigen/Eigen/src/Core/util/ForwardDeclarations.h"

namespace Behavior2015
{
  #include "LibCodeRelease.h"
  
  LibCodeRelease::LibCodeRelease():
    angleToGoal(0.f),
  	distanceToOwnGoal(0.f),
  	shootAngle(5_deg)
  {}
  
  void LibCodeRelease::preProcess()
  {
    angleToGoal = (theRobotPose.inverse() * Vector2f(theFieldDimensions.xPosOpponentGroundline, 0.f)).angle();
    distanceToOwnGoal = theRobotPose.translation.x() - theFieldDimensions.xPosOwnGroundline;
  }

  void LibCodeRelease::postProcess()
  {
  }
  
  int LibCodeRelease::timeSinceBallWasSeen()
  {
    return theFrameInfo.getTimeSince(theBallModel.timeWhenLastSeen);
  }
  
  bool LibCodeRelease::between(float value, float min, float max)
  {
    return value >= min && value <= max;
  }  
}
