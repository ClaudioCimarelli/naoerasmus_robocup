/**
* @file LibCodeRelease.h
*/

class LibCodeRelease : public LibraryBase
{
public:
  /** Constructor for initializing all members*/
  LibCodeRelease();

  void preProcess() override;

  void postProcess() override;
  
  
  bool between(float value, float min, float max);
    
  int timeSinceBallWasSeen();

  bool shootDetected;
  float angleToGoal;
  float distanceToOwnGoal;
  float shootAngle;
  float detectedShootDirection;
  float randomDirection;
  unsigned shootTime;

};
