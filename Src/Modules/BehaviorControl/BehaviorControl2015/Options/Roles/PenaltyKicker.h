/** Kicker for panalty and one shot kicking*/
option(PenaltyKicker) {
    
    
    
    initial_state(start){
        transition {

            if(state_time > 5000)
                goto turnToBall;
            if(libCodeRelease.timeSinceBallWasSeen() > 1800)
				goto searchForBall;
        }
        action {
            theHeadControlMode = HeadControl::lookAround;
        }
    }

    // Striker turns to the ball's direction
    state(turnToBall)
    {
      transition
      {
        if (std::abs(theBallModel.estimate.position.angle()) < 5_deg) // If the ball is in front of the robot
          goto walkToBall; // Striker can walk to the ball
        if (libCodeRelease.timeSinceBallWasSeen() > 1200) // If the ball hasn't been seen for too long
		  goto searchForBall; // Robot looks for the ball
      }
      action
      {
        theHeadControlMode = HeadControl::lookAtBall; // Robot keeps his head looking forward
        WalkToTarget( Pose2f(40.f, 0.f, 0.f)  // Robot rotates to the ball's position
                    , Pose2f(theBallModel.estimate.position.angle()
                    , 0.f, 0.f));
      }
    }

        
    state(walkToBall) {
        transition {

            if(theBallModel.estimate.position.x() < 400.f){
                if (libCodeRelease.randomDirection < 0.5)
                    goto alignBehindBallRight;
                else
                    //goto alignBehindBallLeft
                    goto alignBehindBallRight;
            }
            if (std::abs(theBallModel.estimate.position.angle()) > 5_deg)
				goto turnToBall;


            if(libCodeRelease.timeSinceBallWasSeen() > 1200)
				goto searchForBall;
        }
        action {
            //theHeadControlMode = HeadControl::lookAtBall;
            WalkToTarget(Pose2f(0.f,25.f,10.f), Pose2f(0.f, theBallModel.estimate.position.x(), theBallModel.estimate.position.y()));
        }
    }


    state(alignBehindBallRight) {
        transition {
        	if(libCodeRelease.between(theBallModel.estimate.position.y(), 45.f, 55.f)
        	                && libCodeRelease.between(theBallModel.estimate.position.x(), 165.f, 170.f))
        	                goto kickRight;
        	if(theBallModel.estimate.position.x() > 850.f){
        		goto walkToBall;
        	}
            if(libCodeRelease.timeSinceBallWasSeen() > 1200)
                goto searchForBall;

        }
        action {
        		WalkToTarget(Pose2f(0.f, 10.f, 10.f), Pose2f(0.f, theBallModel.estimate.position.x() - 165.f, theBallModel.estimate.position.y() - 50.f));
            }
    }
        
    state(kickRight) {
        transition {

            if((theBallModel.estimate.position.x() > 390.f && (libCodeRelease.shootDetected)) || (state_time>3000))
                goto wait;

            if(libCodeRelease.between(theBallModel.estimate.position.x(), 130.f,410.f) && !(libCodeRelease.shootDetected)&& (state_time>1000))
            	goto alignBehindBallRight;

            if(libCodeRelease.timeSinceBallWasSeen() > 1200)
                goto searchForBall;
        }
        action {
        	 if(theBallModel.estimate.position.x() < 250.f && (state_time>700)){
				WalkToTarget(Pose2f(0.f, 1.f, 0.f), Pose2f(0.f, theBallModel.estimate.position.x() - 270.f,0.f));
			}
        	 else{
				theHeadControlMode = HeadControl::lookAtBall;
				InWalkKick(WalkRequest::left, Pose2f(0.f, theBallModel.estimate.position.x() + 155.f, theBallModel.estimate.position.y() - 52.f));
			 }
        }
    }

    /*state(alignBehindBallLeft) {
        transition {
            if(libCodeRelease.between(theBallModel.estimate.position.y(), 42.f, 62.f)
                && libCodeRelease.between(theBallModel.estimate.position.x(), 165.f, 180.f)
                && std::abs(libCodeRelease.angleToGoal) > 25_deg)
                goto kickLeft;
        }
        action {
            if(libCodeRelease.timeSinceBallWasSeen() > 500){
                theHeadControlMode = HeadControl::lookAround;
                Stand();
            } else {
                theHeadControlMode = HeadControl::lookAtBall;
                WalkToTarget(Pose2f(0.3f, 0.3f, 0.3f), Pose2f(libCodeRelease.angleToGoal + 26_deg, theBallModel.estimate.position.x() - 175.f, theBallModel.estimate.position.y() - 177.f));
            }
        }
    }


    state(kickLeft) {
        transition {
            if(libCodeRelease.shootDetected){
                Stand();
                goto wait;
            }
            if(libCodeRelease.timeSinceBallWasSeen() > 200)
                goto searchForBall;
        }
        action {
            theHeadControlMode = HeadControl::lookAtBall;
            InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal + 26_deg, theBallModel.estimate.position.x() - 45.f, theBallModel.estimate.position.y() + 55.f));
        }
    }
*/

    state(searchForBall) {
        transition {
            if(libCodeRelease.timeSinceBallWasSeen() < 500)
                goto turnToBall;
        }
        action {
        	if(state_time > 6000)
        		WalkAtSpeedPercentage(Pose2f(0.3f, 0.f, 0.f));
            theHeadControlMode = HeadControl::none;
            LookAround(0.1f, 0.7f);
        }
    }

        
    state(wait) {
        transition {
            if(libCodeRelease.timeSinceBallWasSeen() > 10000){
                goto searchForBall;
            }
        }
        action {
            theHeadControlMode = HeadControl::lookAtBall;
            if(state_time < 3500)
            	WalkToTarget(Pose2f(0.f, 30.f, 0.f), Pose2f(0.f, -350.f,0.f));
            else
            	Stand();
        }
    }
    

}
