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
        if(libCodeRelease.timeSinceBallWasSeen() > 7000)
          goto searchForBall;
        if(theBallModel.estimate.position.norm() < 300.f)
          goto alignBehindBall;
      }
      action
      {
        theHeadControlMode = HeadControl::lookForward;
        WalkToTarget(Pose2f(80.f, 80.f, 80.f), theBallModel.estimate.position);
      }
    }


  state(alignBehindBall)
    {
      transition
      {
        if(libCodeRelease.timeSinceBallWasSeen() > 7000)
          goto searchForBall;
        if(libCodeRelease.between(theBallModel.estimate.position.y(), 20.f, 50.f)
            && libCodeRelease.between(theBallModel.estimate.position.x(), 140.f, 170.f)
            && std::abs(libCodeRelease.angleToGoal) < 2_deg)
          goto kick;
      }
      action
      {
        theHeadControlMode = HeadControl::lookForward;
        WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() - 30.f));
      }
    }

  state(kick)
  {
	transition
	{
		if((state_time > 10 && action_done)){
			theHeadControlMode = HeadControl::lookForward;
			//Stand();
		}

	}

    action
    {
      Annotation("Alive and Kickin'");
      theHeadControlMode = HeadControl::lookForward;
      InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
    }
  }

  state(searchForBall)
  {
    transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() < 300)
        goto turnToBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkAtSpeedPercentage(Pose2f(1.f, 0.f, 0.f));
    }
  }

  state(turnToBall)
    {
      transition
      {
        if(libCodeRelease.timeSinceBallWasSeen() > 7000)
          goto searchForBall;
        if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
          goto walkToBall;
      }
      action
      {
        theHeadControlMode = HeadControl::lookForward;
        WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
      }
    }
}
