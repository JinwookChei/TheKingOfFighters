#pragma once

class Player;
class Button final
    : public UIComponent {
 public:
  Button();

  ~Button();

  void BeginPlay() override;

  void Render(struct IRenderTexture* renderTexture) override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void SetPlayer(Player* player);

  void SetDir(const Vector& dir);

 private:
  IImage* image_;

  Player* player_;

  Vector dir_;

  Vector mousePosition_;
};