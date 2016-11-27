option(PenaltyKeeper) {

	initial_state(start) {
		transition
		    {
		      if(state_time > 1000){
		    	WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(250.f,0.f));
		        goto detectShot;
		      }
		    }
		    action
		    {
		      theHeadControlMode = HeadControl::lookForward;
		      Stand();
		    }
	}

	state(detectShot){
		transition
			{
			  if((state_time > 6700) && (theObstacleModel.obstacles[0].center(1,0) > 3.000000)) /*Shot on the right*/
				  WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(150.f,150.f)); /*Step left*/
			  if((state_time > 6700) && (theObstacleModel.obstacles[0].center(1,0) < -3.600000)) /*Shot on the left*/
			     WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(-150.f,-150.f)); /*Step right*/
			  if(libCodeRelease.shootDetected)
				goto saveShot;
			}
			action
			{
			  theHeadControlMode = HeadControl::lookForward;
			}

	}

	state(saveShot){
		transition{
			if((state_time > 10000 && action_done)){
				Stand();
			}
		}
		action{
		/*If I see the Robot step aside, I move in the other direction*/
			/*WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(-100.f,-100.f)); Step right*/
			/*WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(100.f,100.f)); Step left*/

		if(std::abs(libCodeRelease.detectedShootDirection)<3_deg)
			SpecialAction(SpecialActionRequest::diveCenter);
		else if (libCodeRelease.detectedShootDirection>=3_deg)
			SpecialAction(SpecialActionRequest::diveLeft);
		else
			SpecialAction(SpecialActionRequest::diveRight);

		}
	}

}
