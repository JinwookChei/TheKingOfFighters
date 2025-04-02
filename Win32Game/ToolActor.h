#pragma once

enum CollisionBoxType;

class ToolActor
	: public Actor
{
 public:
  ToolActor();
  ~ToolActor();


  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool Initialize(UI* ui);

  ImageRenderer* GetImageRenderer() const;

  IImage* GetImage() const;

  unsigned int GetImageIndex() const;

  //void SetImageIndex(unsigned int index);

  void AddPositionOffSet(const Vector& offSet);

  CollisionComponent* GetCollisionBox(CollisionBoxType boxType);

  void CollisionUpdate();

 private:
  UI* bindUI_;

  ImageRenderer* pRender_;

  CollisionComponent* hitBoxTop_;

  CollisionComponent* hitBoxBottom_;

  CollisionComponent* attackBox_;

  CollisionComponent* pushBox_;

  CollisionComponent* grabBox_;

};