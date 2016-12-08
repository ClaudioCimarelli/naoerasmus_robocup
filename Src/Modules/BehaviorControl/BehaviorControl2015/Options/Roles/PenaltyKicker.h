/** A test striker option without common decision */
option(PenaltyKicker)
{
  initial_state(start)
  {
    transition
    {
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
        if(theBallModel.estimate.position.norm() < 360.f){
        	if (libCodeRelease.randomDirection < 0.5)
        		goto alignBehindBallRight;
		    else
		    	goto alignBehindBallRight;
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
        if(libCodeRelease.between(theBallModel.estimate.position.y(), 40.f, 60.f)
            && libCodeRelease.between(theBallModel.estimate.position.x(), 190.f, 210.f)
            && std::abs(libCodeRelease.angleToGoal) > 23_deg)
          goto kickRight;
      }
      action
      {
        WalkToTarget(Pose2f(30.f, 30.f, 30.f), Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() - 65.f));
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
      InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 155.f, theBallModel.estimate.position.y() - 55.f));
    }
  }

  state(alignBehindBallLeft)
      {
        transition
        {
          if(libCodeRelease.between(theBallModel.estimate.position.y(), 70.f, 90.f)
              && libCodeRelease.between(theBallModel.estimate.position.x(), 160.f, 180.f)
              && std::abs(libCodeRelease.angleToGoal) > 23_deg)
            goto kickLeft;
        }
        action
        {
          //TODO parameter to kick better estimates
          WalkToTarget(Pose2f(30.f, 30.f, 30.f), Pose2f(libCodeRelease.angleToGoal + 25_deg, theBallModel.estimate.position.x() - 170.f, theBallModel.estimate.position.y() - 100.f));
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
        //TODO parameter to kick better estimates
        InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal + 25_deg, theBallModel.estimate.position.x() - 120.f, theBallModel.estimate.position.y() - 100.f));

      }
    }


  state(wait){
	  action{
		  theHeadControlMode = HeadControl::lookForward;

	  }
  }
}
