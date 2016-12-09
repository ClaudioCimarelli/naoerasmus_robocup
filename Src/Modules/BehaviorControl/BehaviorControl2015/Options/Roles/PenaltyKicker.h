/** A test striker option without common decision */
option(PenaltyKicker)
{
  initial_state(start)
  {
    transition
    {
    	if(libCodeRelease.timeSinceBallWasSeen() > 5000)
    	        goto searchForBall;
      if(state_time > 5000)
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
                goto searchForGoal;
        }
        else if(state_time > 2500)
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
        if(libCodeRelease.between(theBallModel.estimate.position.y(), 50.f, 70.f)
            && libCodeRelease.between(theBallModel.estimate.position.x(), 195.f, 210.f)
            && std::abs(libCodeRelease.angleToGoal) > 23_deg)
          goto kickRight;
      }
      action
      {
    	  if(libCodeRelease.timeSinceBallWasSeen() > 500){
    		  theHeadControlMode = HeadControl::lookAround;
    		  Stand();
    	  }
    	  else{
    		  theHeadControlMode = HeadControl::lookForward;
    		  WalkToTarget(Pose2f(0.3f, 0.3f, 0.3f), Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() - 65.f));

    	  }
      }
    }

  state(kickRight)
  {
	transition
	{
		if(state_time > 30000 ||(state_time > 2000 && action_done)){
			Stand();
			goto wait;
		}
	}

    action
    {
    	if(libCodeRelease.timeSinceBallWasSeen() > 500){
    	    		  theHeadControlMode = HeadControl::lookAround;
    	    		  Stand();
    	}
    	else{
    		theHeadControlMode = HeadControl::lookAtBall;
    		InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() - 50.f));

	  }
    }
  }

  state(alignBehindBallLeft)
      {
        transition
        {
          if(libCodeRelease.between(theBallModel.estimate.position.y(), 30.f, 50.f)
              && libCodeRelease.between(theBallModel.estimate.position.x(), 180.f, 200.f)
              && std::abs(libCodeRelease.angleToGoal) > 23_deg)
            goto kickLeft;
        }
        action
        {
          WalkToTarget(Pose2f(30.f, 30.f, 30.f), Pose2f(libCodeRelease.angleToGoal + 25_deg, theBallModel.estimate.position.x() - 190.f, theBallModel.estimate.position.y() - 40.f));
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
        InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal + 25_deg, theBallModel.estimate.position.x() - 120.f, theBallModel.estimate.position.y() - 100.f));

      }
    }


    state(searchForBall)
      {
        transition
        {
          if(libCodeRelease.timeSinceBallWasSeen() < 300)
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
          if(state_time > 7000)
            goto alignBehindBallRight;
        }
        action
        {
          Stand();
          theHeadControlMode = HeadControl::lookAround;
        }
   }
}
