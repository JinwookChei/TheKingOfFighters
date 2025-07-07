#pragma once

struct EffectInfo {
  unsigned long long imageTag_ = 0;

  unsigned long long effectTag_ = 0;

  unsigned long long soundTag_ = 0;

  std::vector<unsigned int> indices_;

  std::vector<unsigned long long> intervals_;

  bool loop_ = false;

  Vector imageLocalScale_{1.0f, 1.0f};

  Color8Bit transColor_;

  bool isAlphaEffect_ = false;

  float alpha_ = 0.0f;

  void* searchHandle_ = nullptr;
};


class Effect;
class Level;

class EffectManager final {
 public:
  JO_API EffectManager();
  JO_API ~EffectManager();

  JO_API static EffectManager* Instance();

  JO_API bool Initialize();

  JO_API bool RegistEffect(unsigned long long effectTag, unsigned long long imageTag, unsigned long long soundTag, unsigned int startIndex, unsigned int endIndex, unsigned long long interval, bool loop, const Vector& imageLocalScale, const Color8Bit& transColor, bool isAlphaEffect = false, float alpha = 0.0f);
  											  
  JO_API bool RegistEffect(unsigned long long effectTag, unsigned long long imageTag, unsigned long long soundTag, const std::vector<unsigned int>& indices, unsigned long long interval, bool loop, const Vector& imageLocalScale, const Color8Bit& transColor, bool isAlphaEffect = false, float alpha = 0.0f);
											  
  JO_API bool RegistEffect(unsigned long long effectTag, unsigned long long imageTag, unsigned long long soundTag, const std::vector<unsigned int>& indices, const std::vector<unsigned long long> intervals, bool loop, const Vector& imageLocalScale, const Color8Bit& transColor, bool isAlphaEffect = false, float alpha = 0.0f);

  JO_API Effect* SpawnEffect(Level* level, unsigned long long effectTag, const Vector& position);

 private:
  HashTable effectTable_;
};
