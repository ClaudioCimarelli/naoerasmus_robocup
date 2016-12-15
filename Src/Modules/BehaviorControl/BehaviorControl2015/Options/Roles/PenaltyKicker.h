/** A test striker option without common decision */
option(PenaltyKicker)
{
  initial_state(start)
  {
    transition
    {
    	if(libCodeRelease.timeSinceBallWasSeen() > 5000)
    	        goto searchForBall;
    	if(state_time > 8000)
        goto walkToBall;
    }
    action
    {

      theHeadControlMode = HeadControl::lookAround;
      Stand();
    }
  }
  state(walkToBall)
    {
      transition
      {
        if(theBallModel.estimate.position.x() < 360.f){
        	if (libCodeRelease.randomDirection < 0.001)
        		goto alignBehindBallRight;
		    else
		    	goto alignBehindBallLeft;
        }
        else if(state_time > 3200)
        	goto start;
      }
      action
      {
    	theHeadControlMode = HeadControl::lookAtBall;
        WalkToTarget(Pose2f(10.f,10.f,10.f), theBallModel.estimate.position);
      }
    }


  state(alignBehindBallRight)
    {
      transition
      {
    	  if(libCodeRelease.timeSinceBallWasSeen() > 5000)
    	          goto searchForBall;
        if(libCodeRelease.between(theBallModel.estimate.position.y(), 20.f, 40.f)
            && libCodeRelease.between(theBallModel.estimate.position.x(), 165.f, 180.f)
            && std::abs(libCodeRelease.angleToGoal) > 25_deg)
          goto kickRight;
      }
      action
      {
    	  if(libCodeRelease.timeSinceBallWasSeen() > 500){
    		  theHeadControlMode = HeadControl::lookAround;
    		  Stand();
    	  }
    	  else{
    		  theHeadControlMode = HeadControl::lookAtBall;
    		  WalkToTarget(Pose2f(0.3f, 0.3f, 0.3f), Pose2f(libCodeRelease.angleToGoal - 26_deg, theBallModel.estimate.position.x() - 175.f, theBallModel.estimate.position.y() - 30.f));

    	  }
      }
    }

  state(kickRight)
  {
	transition
	{
		if(libCodeRelease.shootDetected){
			Stand();
			goto wait;
		}
        if(libCodeRelease.timeSinceBallWasSeen() > 200)
            goto searchForBall;

	}

    action
    {
    	
        theHeadControlMode = HeadControl::lookAtBall;
        //InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 100.f, theBallModel.estimate.position.y() - 145.f));
        InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 26_deg, theBallModel.estimate.position.x() - 45.f, theBallModel.estimate.position.y() - 55.f));

    }
  }

  state(alignBehindBallLeft)
      {
        transition
        {
          if(libCodeRelease.between(theBallModel.estimate.position.y(), 42.f, 62.f)
              && libCodeRelease.between(theBallModel.estimate.position.x(), 165.f, 180.f)
              && std::abs(libCodeRelease.angleToGoal) > 25_deg)
            goto kickLeft;
        }
        action
        {
            if(libCodeRelease.timeSinceBallWasSeen() > 500){
                theHeadControlMode = HeadControl::lookAround;
                Stand();
            }
            else {
                theHeadControlMode = HeadControl::lookAtBall;
                WalkToTarget(Pose2f(0.3f, 0.3f, 0.3f), Pose2f(libCodeRelease.angleToGoal + 26_deg, theBallModel.estimate.position.x() - 175.f, theBallModel.estimate.position.y() - 177.f));
            }
        }
      }

    state(kickLeft)
    {
        transition
        {
            if(libCodeRelease.shootDetected){
                Stand();
                goto wait;
            }
            if(libCodeRelease.timeSinceBallWasSeen() > 200)
                goto searchForBall;
            
        }

      action
      {
        theHeadControlMode = HeadControl::lookAtBall;
        InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal + 26_deg, theBallModel.estimate.position.x() - 45.f, theBallModel.estimate.position.y() + 55.f));

      }
    }


    state(searchForBall)
      {
        transition
        {
          if(libCodeRelease.timeSinceBallWasSeen() < 500)
            goto walkToBall;
        }
        action
        {
        	theHeadControlMode = HeadControl::none;
        	LookAround(0.2f);
        }
      }

  state(wait){
	  transition{
		  if(libCodeRelease.timeSinceBallWasSeen() > 5000)
		      	          goto searchForBall;
	  }
	  action{
		  theHeadControlMode = HeadControl::lookForward;

	  }
  }
  
  state(searchForGoal)
  {
        transition
        {
          if(state_time > 8000)
            goto alignBehindBallRight;
        }
        action
        {
          Stand();
          theHeadControlMode = HeadControl::lookAround;
        }
   }
}
