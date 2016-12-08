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
<<<<<<< HEAD
      theHeadControlMode = HeadControl::lookAround;
=======
      theHeadControlMode = HeadControl::lookAtBall;
>>>>>>> refs/remotes/origin/develop
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
    	theHeadControlMode = HeadControl::lookAtBall;
        WalkToTarget(Pose2f(10.f,10.f,10.f), theBallModel.estimate.position);
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
        WalkToTarget(Pose2f(30.f, 30.f, 30.f), Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() - 30.f));
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
      InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
    }
  }

  state(alignBehindBallLeft)
      {
        transition
        {
          if(libCodeRelease.between(theBallModel.estimate.position.y(), 70.f, 90.f)
              && libCodeRelease.between(theBallModel.estimate.position.x(), 140.f, 160.f)
              && std::abs(libCodeRelease.angleToGoal) > 23_deg)
            goto kickLeft;
        }
        action
        {
          //TODO parameter to kick better estimates
<<<<<<< HEAD
          WalkToTarget(Pose2f(30.f, 30.f, 30.f), Pose2f(libCodeRelease.angleToGoal + 25_deg, theBallModel.estimate.position.x() - 140.f, theBallModel.estimate.position.y() - 100.f));
=======
          WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(libCodeRelease.angleToGoal + 25_deg, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() - 80.f));
>>>>>>> refs/remotes/origin/develop
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
