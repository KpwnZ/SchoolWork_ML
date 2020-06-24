#include "utils.h"
#include <random>

ColorBox::ColorBox(ColorPoint pt) : mainColor(pt) { }

void ColorBox::clear() {
    colors.clear();
}

ColorPoint ColorBox::getMainColor() {
    return mainColor;
}

void ColorBox::addColor(ColorPoint pt) {
    colors.push_back(pt);
}

void ColorBox::update() {
    if(colors.size() == 0) return;

    double r = colors[0].r,
           g = colors[0].g,
           b = colors[0].b;
    
    for(int i = 1; i < colors.size(); i++) {
        r = r + (colors[i].r) / (i + 1);
        g = g + (colors[i].g) / (i + 1);
        b = b + (colors[i].b) / (i + 1);
    }

    mainColor = {r, g, b};
}

ColorCollection::ColorCollection(cv::Mat &image) {
    cv::MatConstIterator_<cv::Vec3b> it = image.begin<cv::Vec3b>();
    cv::MatConstIterator_<cv::Vec3b> end = image.end<cv::Vec3b>();
    while (it != end) {
        allColors.push_back({static_cast<double>((*it)[0]), static_cast<double>((*it)[1]), static_cast<double>((*it)[2])});
        it++;
    }
}

double ColorCollection::dis2(ColorPoint p1, ColorPoint p2) {
    return (pow((p1.r - p2.r), 2) + pow((p1.g - p2.g), 2) + pow((p1.b - p2.b), 2));
}

void ColorCollection::kMeans(int k) {
    std::random_device rd;
    int sample_size = allColors.size();

    // init k sample
    for (int i = 0; i < k; i++) {
        int r = rd() % sample_size;
        ColorBox clr(allColors[r]);
        allBoxes.push_back(clr);
    }

    int epoches = 3;
    for(int ep = 0; ep < epoches; ep++) {

        for(ColorBox box : allBoxes) {
            box.clear();
        }

        for(ColorPoint clr : allColors) {
            // init: index = 0
            int index = 0;
            double minDis = dis2(clr, allBoxes[0].getMainColor());
            
            for(int i = 1; i < k; i++) {
                double dis = dis2(clr, allBoxes[i].getMainColor());
                if(dis <= minDis) {
                    index = i;
                    minDis = dis;
                }
            }

            // add the color to the index;
            allBoxes[index].addColor({clr.r, clr.g, clr.b});
        }

        // update 
        for(ColorBox box : allBoxes) {
            box.update();
        }
    }

    for(ColorBox box : allBoxes) {
        ColorPoint clr = box.getMainColor();
        std::cout << clr.r << " " << clr.g << " " << clr.b << "\n";
    }
}

std::string ColorCollection::cpt2Hex(ColorPoint pt) {
    return "";
}

std::vector<ColorBox> ColorCollection::getAllBoxes() {
    return this -> allBoxes;
}
