#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <stdlib.h>
#endif


class MyImage : public wxImage
{
    public:
        MyImage(const wxString& fileName);
        MyImage(wxImage image);
        MyImage(int largeur, int hauteur);
        MyImage();

        void negative();
        void Desaturate();
        void Threshold(int seuil);
        void Mirroir(bool horiz = true);
        MyImage* Rotation90();
        void posterize();
        int histogramme();

        virtual ~MyImage();


        inline void GetPixel(unsigned char* data, int width, int height, int x,int y, unsigned char& r,unsigned char& g,unsigned char& b);
        inline void SetPixel(unsigned char* data, int width, int height, int x, int y, unsigned char& r,unsigned char& g,unsigned char& b);

    protected:

    private:
};

#endif // MYIMAGE_H
