/** Kicker Support - task kick goal after penelaty kicker */
option(KickerSupport) {
    
    initial_state(start){
        transition {
            if(libCodeRelease.timeSinceBallWasSeen() < 200 && state_time>10000)
                goto turnToBall;
        }
        action {
        	//theHeadControlMode = HeadControl::lookForward;
        	if(libCodeRelease.timeSinceBallWasSeen() < 900 && state_time>9000)
        		LookAtBall();
        	else
        		LookAround(0.1f, 0.6f);
            //Stand();
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
        	if(theBallModel.estimate.position.x() < 700.f)
				goto alignBehindBall;
        	 if (std::abs(theBallModel.estimate.position.angle()) > 5_deg)
				goto turnToBall;
        	if (libCodeRelease.timeSinceBallWasSeen() > 1200) // If the ball hasn't been seen for too long
        		goto searchForBall; // Robot looks for the ball
        }
        action {
            //theHeadControlMode = HeadControl::lookAtBall;
        	LookAround(0.2f, 0.2f);
            WalkToTarget(Pose2f(0.f,25.f,10.f), Pose2f(0.f, theBallModel.estimate.position.x(), theBallModel.estimate.position.y()));
        }
    }

    /*state(turnRight) {
    		transition {
    			if(state_time>3500)
    				goto alignBehindBallRight;
    			if(theBallModel.estimate.position.x() > 950.f){
    				goto walkToBall;
    			}
    			if(libCodeRelease.timeSinceBallWasSeen() > 1200)
    				goto searchForBall;
    		}
    		action {
    			theHeadControlMode = HeadControl::lookAtBall;
    			//LookAround(0.1f, 0.6f);
    			WalkToTarget( Pose2f(30.f, 0.f, 10.f), Pose2f(35_deg, 0.f, 250.f));
    		}
    	}*/

    state(alignBehindBall) {
    		transition {
    			if(std::abs(theBallModel.estimate.position.y()) > 180.f && std::abs(libCodeRelease.angleToGoal) < 30_deg)
    				goto alignBehindGoal;
    			if(theBallModel.estimate.position.x() > 950.f){
    				goto walkToBall;
    			}
    			if(libCodeRelease.timeSinceBallWasSeen() > 1200)
    				goto searchForBall;
    		}
    		action {
    			theHeadControlMode = HeadControl::lookAtBall;
    			//LookAround(0.1f, 0.6f);
    			if(libCodeRelease.angleToGoal > 3_deg){

    				WalkToTarget( Pose2f(1.f, 0.f, 25.f), Pose2f(libCodeRelease.angleToGoal - 20_deg, 0.f, theBallModel.estimate.position.y() - 300.f));

    			}

    			else if(libCodeRelease.angleToGoal < -3_deg){

    				WalkToTarget( Pose2f(1.f, 0.f, 25.f), Pose2f(libCodeRelease.angleToGoal + 20_deg, 0.f, theBallModel.estimate.position.y() + 300.f));

    			}
    		}
    	}

    state(alignBehindGoal) {
		transition {
			if(std::abs(libCodeRelease.angleToGoal) < 20_deg)
				goto alignBehindBallRight;
			if(theBallModel.estimate.position.x() > 950.f){
				goto walkToBall;
			}
			if(libCodeRelease.timeSinceBallWasSeen() > 1200)
				goto searchForBall;
		}
		action {
			theHeadControlMode = HeadControl::lookAtBall;
			//LookAround(0.1f, 0.6f);
			if(libCodeRelease.angleToGoal > 5_deg){

				WalkToTarget( Pose2f(10.f, 0.f, 0.f), Pose2f(libCodeRelease.angleToGoal - 15_deg, 0.f, 0.f));

			}

			else if(libCodeRelease.angleToGoal < -5_deg){

				WalkToTarget( Pose2f(10.f, 0.f, 0.f), Pose2f(libCodeRelease.angleToGoal + 15_deg, 0.f, 0.f));

			}
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

            }
            action {
            	/*if (std::abs(theBallModel.estimate.position.angle()) > 10_deg)
            		WalkToTarget(Pose2f(40.f, 0.f, 0.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
    			//theHeadControlMode = HeadControl::lookAtBall;*/
            	WalkToTarget(Pose2f(0.f, 10.f, 10.f), Pose2f(0.f, theBallModel.estimate.position.x() - 165.f, theBallModel.estimate.position.y() - 50.f));
                }
        }

        
    state(kickRight) {
        transition {
        	if((theBallModel.estimate.position.x() > 600.f && (libCodeRelease.shootDetected)) || (state_time>4000))
				goto wait;
			if(libCodeRelease.between(theBallModel.estimate.position.x(), 230.f,610.f) && (!(libCodeRelease.shootDetected) || (state_time>1500)))
				goto alignBehindBallRight;
			if(libCodeRelease.timeSinceBallWasSeen() > 1200)
				goto searchForBall;
        }
        action {
        	if(theBallModel.estimate.position.x() < 250.f && (state_time>900)){
				WalkToTarget(Pose2f(0.f, 1.f, 0.f), Pose2f(0.f, theBallModel.estimate.position.x() - 300.f,0.f));
			}
			 else{
				theHeadControlMode = HeadControl::lookAtBall;
				InWalkKick(WalkRequest::left, Pose2f(0.f, theBallModel.estimate.position.x() + 155.f, theBallModel.estimate.position.y() - 52.f));
			 }
        }
    }


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
            if(libCodeRelease.timeSinceBallWasSeen() > 10000)
                goto searchForBall;
        }
        action {
        	theHeadControlMode = HeadControl::lookAtBall;
			if(state_time < 4000)
				WalkToTarget(Pose2f(0.f, 30.f, 0.f), Pose2f(0.f, -450.f,0.f));
			else
				Stand();
        }
    }
    
}
