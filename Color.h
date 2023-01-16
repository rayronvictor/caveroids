#ifndef COLOR_H
#define COLOR_H

class Color
{
    public:
        Color(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);

        void SetRGBA(float r, float g, float b, float a);
        void ConvertToGrayscale();

        // operadores
        Color& operator= (const Color&);

        Color operator+ (const Color&) const;
        Color operator- (const Color&) const;
        Color operator+= (const Color&);
        Color operator-= (const Color&);

        bool operator== (const Color&) const;
        bool operator!= (const Color&) const;

        // cores
        // tons de cinza
        static const Color Black;
        static const Color Gray;
        static const Color White;

        // cores padrão
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Purple;
        static const Color Orange;
        static const Color Magenta;
        static const Color Cyan;
        static const Color Gold;
        static const Color Silver;
        static const Color Bronze;

        // cores escuras
        static const Color DarkRed;
        static const Color DarkGreen;
        static const Color DarkBlue;
        static const Color DarkCyan;

        // cores claras
        static const Color Pink;
        static const Color LightGreen;
        static const Color LightBlue;

    public:
        float R;
        float G;
        float B;
        float A;
};

#endif
