#pragma once

class Level;

struct EffectInfo {

  IImage* image_ = nullptr;

  unsigned long long effectTag_ = 0;

  unsigned int startFrame_ = 0;

  unsigned int endFrame_ = 0;

  unsigned int interval_ = 0;

  float velocity_ = 0.0f;

  float reach_ = 0.0f;

  Vector direction_{0.0f, 0.0f};
};

class EffectManager final {
 public:
  EffectManager();
  ~EffectManager();

  static EffectManager* Instance();

  bool Initialize(Level* level);

  bool RegistEffect(IImage* image, 
	  unsigned long long effectTag, 
	  unsigned int startFrame, 
	  unsigned int endFrame, 
	  unsigned int interval, 
	  float velocity, 
	  float reach, 
	  const Vector& direction);

  void SpawnEffect(unsigned int tag, const Vector& position, Actor* owner);

 private:
  Level* level_;

  HashTable effectTable_;

  LINK_ITEM* effectHead_;
  LINK_ITEM* effectTail_;

};
