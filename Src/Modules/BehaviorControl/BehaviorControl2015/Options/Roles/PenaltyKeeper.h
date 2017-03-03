option(PenaltyKeeper) {

	initial_state(start) {
		transition
		    {
		      if(state_time > 15000){
		    	  //Stand();
		    	  goto detectShot;
		      }
		    }
		    action
		    {
		    	WalkToTarget(Pose2f(0.f, 30.f, 0.f), Pose2f(0.f, 450.f,0.f));
		    	if(libCodeRelease.timeSinceBallWasSeen() < 900 && state_time>5500)
					LookAtBall();
				else
					LookAround(0.1f, 0.6f);
		    }
	}

	state(detectShot){
		transition
			{//
			if(libCodeRelease.shootDetected && (theBallModel.estimate.position.x() < 350.f))
				goto saveShot;

			if(libCodeRelease.timeSinceBallWasSeen() > 1500)
				goto searchForBall;
			}
			action
			{
				LookAtBall();
			 /* if((state_time > 6700) && (theObstacleModel.obstacles[0].center(1,0) > 3.000000)) Shot on the right
			  				  WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(150.f,150.f)); Step left
			  			  if((state_time > 6700) && (theObstacleModel.obstacles[0].center(1,0) < -3.600000)) Shot on the left
			  			     WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(-150.f,-150.f)); Step right*/
			}

	}

	state(saveShot){
		transition{
			if((state_time > 10000 && action_done)){
				//Stand();
			}
		}
		action{
		/*If I see the Robot step aside, I move in the other direction*/
			/*WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(-100.f,-100.f)); Step right*/
			/*WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(100.f,100.f)); Step left*/
/*

		if(std::abs(libCodeRelease.detectedShootDirection)<260.f)
			SpecialAction(SpecialActionRequest::diveCenter);
		else if (libCodeRelease.detectedShootDirection>=260.f)
			SpecialAction(SpecialActionRequest::diveLeft);
		else
			SpecialAction(SpecialActionRequest::diveRight);
*/
			SpecialAction(SpecialActionRequest::diveCenter);
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
	          LookAround(0.2f, 0.1f);
	        }
	      }

}
