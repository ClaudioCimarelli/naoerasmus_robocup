/**
* @file LibCodeRelease.cpp
*/

#include "../LibraryBase.h"
#include "../../Util/Eigen/Eigen/src/Core/util/ForwardDeclarations.h"
#include <cstdlib>
#include <ctime>

namespace Behavior2015
{
  #include "LibCodeRelease.h"
  
  LibCodeRelease::LibCodeRelease():
	shootDetected(false),
    angleToGoal(0.f),
  	distanceToOwnGoal(0.f),
  	shootAngle(0_deg),
  	detectedShootDirection(0_deg)
  { srand (static_cast <unsigned> (time(0))); }
  

  void LibCodeRelease::preProcess()
  {
    angleToGoal = (theRobotPose.inverse() * Vector2f(theFieldDimensions.xPosOpponentGroundline, 0.f)).angle();
    distanceToOwnGoal = theRobotPose.translation.x() - theFieldDimensions.xPosOwnGroundline;
    
    // randomly decide between shooting left, straight or right
    // TODO: this should only apply for PenaltyKicker! need to add exception for other roles if possible
    float random_number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (random_number < 0.4) {
        shootAngle = angleToGoal + 28_deg;
    } else if (random_number > 0.6) {
        shootAngle = angleToGoal - 28_deg;
    } else {
        shootAngle = angleToGoal;
    }

    shootDetected = theBallModel.estimate.velocity.norm() != 0;
    if(shootDetected){
    	detectedShootDirection = theBallModel.estimate.velocity.angle();
    }
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
