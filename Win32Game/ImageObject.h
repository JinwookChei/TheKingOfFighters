#pragma once

 class ImageObject final
     : public UIComponent {
  public:
   ImageObject();

   ~ImageObject();

   void BeginPlay() override;

   void Tick(unsigned long long curTick) override;

   ImageRenderer* GetOwnerImageRenderer() const;

  protected:
   void Render(struct IRenderTexture* renderTexture) override;

  private:
   ImageRenderer* ownerImageRender_;

   Vector prevMousePosition_;
 };
