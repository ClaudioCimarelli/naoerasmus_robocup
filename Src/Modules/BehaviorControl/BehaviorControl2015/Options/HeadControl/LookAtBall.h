/** Look at the direction where the ball is located, at a slight downward angle towards the floor
    such that it is capable to follow its movements. As soon as the ball changes location, try to
    follow the ball movement accordingly. */
option(LookAtBall, (float) (0.38f) tilt)
{
  /** Simply point the head to the location where the estimated ball position is */
  initial_state(lookatBall)
  {
    action
    {
      const Vector3f ballPos(theBallModel.estimate.position.x(), theBallModel.estimate.position.y(), 0.0);
      SetHeadTargetOnGround(ballPos);
      //TODO SetHeadPanTilt
    }
  }
}
