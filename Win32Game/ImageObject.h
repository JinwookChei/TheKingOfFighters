#pragma once

 class ImageObject final
     : public UIComponent {
  public:
   ImageObject();

   ~ImageObject();

   void BeginPlay() override;

   void Tick(unsigned long long curTick) override;

   //ImageRenderer* GetOwnerImageRenderer() const;

   IImage* GetImage() const ;

   unsigned int GetImageIndex() const ;

  protected:
   void Render(struct IRenderTexture* renderTexture) override;

  private:
   //ImageRenderer* ownerImageRender_;
   IImage* image_;

   unsigned int imageIndex_;

   Vector prevMousePosition_;
 };
