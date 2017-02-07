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
  	detectedShootDirection(0_deg),
	randomDirection(0.f),
	shootTime(theFrameInfo.time - 2000)
  { srand (static_cast <unsigned> (time(0))); }
  

  void LibCodeRelease::preProcess()
  {
    angleToGoal = (theRobotPose.inverse() * Vector2f(theFieldDimensions.xPosOpponentGroundline, 0.f)).angle();
    distanceToOwnGoal = theRobotPose.translation.x() - theFieldDimensions.xPosOwnGroundline;
    
    randomDirection = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    {
    	bool shootDetectedTemp(false);
    	shootDetectedTemp = theBallModel.estimate.velocity.norm() != 0;
		if(shootDetectedTemp){
			detectedShootDirection = theBallModel.estimate.velocity.y();
			shootTime = theFrameInfo.time;
		}
		if(theFrameInfo.getTimeSince(shootTime)<1300 || shootDetectedTemp)
			shootDetected = true;
		else
			shootDetected = false;
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
