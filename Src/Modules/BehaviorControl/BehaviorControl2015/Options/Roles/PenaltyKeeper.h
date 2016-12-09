option(PenaltyKeeper) {

	initial_state(start) {
		transition
		    {
			if(libCodeRelease.timeSinceBallWasSeen() > 3000)
			    	        goto searchForBall;
		      if(state_time > 1000){
		    	WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(550.f,0.f));
		    	Stand();
		        goto detectShot;
		      }
		    }
		    action
		    {
		      theHeadControlMode = HeadControl::lookAtBall;
		      Stand();
		    }
	}

	state(detectShot){
		transition
			{
//
			if(libCodeRelease.shootDetected)
				goto saveShot;
			}
			action
			{
				if(libCodeRelease.timeSinceBallWasSeen() > 300){
					theHeadControlMode = HeadControl::lookAround;
					LookAround(0.2f);
				}
				else
					theHeadControlMode = HeadControl::lookAtBall;
			 /* if((state_time > 6700) && (theObstacleModel.obstacles[0].center(1,0) > 3.000000)) Shot on the right
			  				  WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(150.f,150.f)); Step left
			  			  if((state_time > 6700) && (theObstacleModel.obstacles[0].center(1,0) < -3.600000)) Shot on the left
			  			     WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(-150.f,-150.f)); Step right*/
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

		if(std::abs(libCodeRelease.detectedShootDirection)<300.f)
			SpecialAction(SpecialActionRequest::diveCenter);
		else if (libCodeRelease.detectedShootDirection>=300.f)
			SpecialAction(SpecialActionRequest::diveLeft);
		else
			SpecialAction(SpecialActionRequest::diveRight);

		}
	}

	state(searchForBall)
	      {
	        transition
	        {
	          if(libCodeRelease.timeSinceBallWasSeen() < 300)
	            goto detectShot;
	        }
	        action
	        {
	          theHeadControlMode = HeadControl::lookAround;
	        }
	      }

}
