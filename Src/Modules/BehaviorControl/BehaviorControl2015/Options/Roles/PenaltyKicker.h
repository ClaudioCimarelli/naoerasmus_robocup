/** A test striker option without common decision */
option(PenaltyKicker)
{
  initial_state(start)
  {
    transition
    {
      if(state_time > 1000)
        goto walkToBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      Stand();
    }
  }
  state(walkToBall)
    {
      transition
      {
        if(theBallModel.estimate.position.norm() < 320.f){
        	if (libCodeRelease.randomDirection < 0.5)
        		goto alignBehindBallRight;
		    else
		    	goto alignBehindBallLeft;
        }


      }
      action
      {
        theHeadControlMode = HeadControl::lookForward;
        WalkToTarget(Pose2f(80.f, 80.f, 80.f), theBallModel.estimate.position);
      }
    }


  state(alignBehindBallRight)
    {
      transition
      {
        if(libCodeRelease.between(theBallModel.estimate.position.y(), 20.f, 50.f)
            && libCodeRelease.between(theBallModel.estimate.position.x(), 140.f, 170.f)
            && std::abs(libCodeRelease.angleToGoal) > 23_deg)
          goto kickRight;
      }
      action
      {
        theHeadControlMode = HeadControl::lookForward;
        WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() - 30.f));
      }
    }

  state(kickRight)
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
      theHeadControlMode = HeadControl::lookForward;
      InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));

    }
  }

  state(alignBehindBallLeft)
      {
        transition
        {
          if(libCodeRelease.between(theBallModel.estimate.position.y(), 90.f, 110.f)
              && libCodeRelease.between(theBallModel.estimate.position.x(), 130.f, 150.f)
              && std::abs(libCodeRelease.angleToGoal) > 25_deg)
            goto kickLeft;
        }
        action
        {
          //libCodeRelease.preProcess();
          theHeadControlMode = HeadControl::lookForward;
          //TODO parameter to kick better estimates
          WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(libCodeRelease.angleToGoal + 26_deg, theBallModel.estimate.position.x() - 140.f, theBallModel.estimate.position.y() - 100.f));
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
        theHeadControlMode = HeadControl::lookForward;
        //TODO parameter to kick better estimates
        InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal + 28_deg, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() - 115.f));

      }
    }


  state(wait){
	  action{
		  theHeadControlMode = HeadControl::lookForward;

	  }
  }
}
