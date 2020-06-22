#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

typedef struct {
    double r;
    double g;
    double b;
} ColorPoint;

class ColorBox {
    private:
        std::vector<ColorPoint> colors;
        ColorPoint mainColor;
    public:
        ColorBox(ColorPoint pt);
        ColorPoint getMainColor();
        void addColor(ColorPoint clr);
        void clear();
        void update();
};

class ColorCollection {
    private:
        std::vector<ColorPoint> allColors;
        std::vector<ColorBox> allBoxes;
    public:
        ColorCollection(cv::Mat &image);
        void kMeans(int k);
        double dis2(ColorPoint p1, ColorPoint p2);
        std::vector<ColorBox> getAllBoxes();
        std::string cpt2Hex(ColorPoint pt);
};


