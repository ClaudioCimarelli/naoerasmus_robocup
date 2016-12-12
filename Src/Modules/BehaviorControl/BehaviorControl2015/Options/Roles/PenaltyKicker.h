/** A test striker option without common decision */
option(PenaltyKicker)
{
  initial_state(start)
  {
    transition
    {
    	if(libCodeRelease.timeSinceBallWasSeen() > 5000)
    	        goto searchForBall;
    	if(state_time > 2000)
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
        	/*if (libCodeRelease.randomDirection < 0.5)
        		goto alignBehindBallLeft;
		    else
		    	goto alignBehindBallRight;*/
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
        if(libCodeRelease.between(theBallModel.estimate.position.y(), 55.f, 70.f)
            && libCodeRelease.between(theBallModel.estimate.position.x(), 175.f, 190.f)
            && std::abs(libCodeRelease.angleToGoal) > 24_deg)
          goto kickRight;
      }
      action
      {
    	  if(libCodeRelease.timeSinceBallWasSeen() > 500){
    		  theHeadControlMode = HeadControl::lookAround;
    		  Stand();
    	  }
    	  else{
    		  theHeadControlMode = HeadControl::lookAround;
    		  WalkToTarget(Pose2f(0.3f, 0.3f, 0.3f), Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 185.f, theBallModel.estimate.position.y() - 65.f));

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
    	
        theHeadControlMode = HeadControl::lookAround;
        //InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 100.f, theBallModel.estimate.position.y() - 145.f));
        InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 60.f, theBallModel.estimate.position.y() - 75.f));

    }
  }

  state(alignBehindBallLeft)
      {
        transition
        {
          if(libCodeRelease.between(theBallModel.estimate.position.y(), 30.f, 50.f)
              && libCodeRelease.between(theBallModel.estimate.position.x(), 180.f, 200.f)
              && std::abs(libCodeRelease.angleToGoal) > 20_deg)
            goto kickLeft;
        }
        action
        {
          WalkToTarget(Pose2f(0.3f, 0.3f, 0.3f), Pose2f(libCodeRelease.angleToGoal + 21_deg, theBallModel.estimate.position.x() - 190.f, theBallModel.estimate.position.y() - 40.f));
        }
      }

    state(kickLeft)
    {
  	transition
  	{
  		if(state_time > 3000 ||(state_time > 10 && action_done)){
  			Stand();
  			goto wait;
  		}
  	}

      action
      {
        InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal + 21_deg, theBallModel.estimate.position.x() - 60.f, theBallModel.estimate.position.y() - 80.f));

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
          theHeadControlMode = HeadControl::lookAround;
        }
      }

  state(wait){
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
