#define _USE_MATH_DEFINES
#include <sil/sil.hpp>
#include "random.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <complex>

float pi {M_PI};
    
void onlyGreen(sil::Image image) 
{
    for (glm::vec3 & color : image.pixels()) 
    {
        color.r = 0.f /*mets la composante rouge à 0. 1 couleur = glm::vec3 */ ;
        color.b = 0.f;
    }
    image.save("output/01_onlyGreen.png");
}

void changeRedBlue(sil::Image image) 
{
    for (glm::vec3 & color : image.pixels()) 
    {
        std::swap(color.r, color.b);
    }
    image.save("output/02_changeRedBlue.png");
}

void blackAndWhite(sil::Image & image) 
{
    for (glm::vec3 & color : image.pixels()) 
    {
        float moy = (color.r + color.g + color.b) / 3;
        color.r = moy;
        color.g = moy;
        color.b = moy;
    }
}

void negative(sil::Image image) 
{
    for (glm::vec3 & color : image.pixels()) 
    {
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
    image.save("output/04_negative.png");
}

void gradient(sil::Image image) 
{
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            image.pixel(x, y) += x / (image.width() - 1.0);

            /* Autre façon de faire, en utilisant la valeur précédente en incrémentant :
            image.pixel(x, y).r += image.pixel(x-1, 0).r + 1.f/(image.width() -1);
            Attention : faire démarrer x à 1 et conv la division en float
            y = 0 car on s'en fiche de la ligne ici */
        }
    }
    image.save("output/05_gradient.png");
}

void mirror1(sil::Image image) 
{
    for (int i{0}; i < image.height()*image.width(); i+=image.width())
    {
        std::reverse(image.pixels().begin() + i, image.pixels().begin() + i + image.width()); 
    }
    image.save("output/06_mirror1.png");
}

void mirror2(sil::Image image) /*2e version*/
{
    for (float x{0}; x < image.width()/2.f; x++)
    {
        for (float y{0}; y < image.height(); y++)
        {   float tmp_r {image.pixel(x,y).r};
            float tmp_g {image.pixel(x,y).g};
            float tmp_b {image.pixel(x,y).b};

            //on peut utiliser swap(a,b) en pratique
            image.pixel(x,y).r = image.pixel(image.width()-(x+1),y).r;
            image.pixel(x,y).g = image.pixel(image.width()-(x+1),y).g;
            image.pixel(x,y).b = image.pixel(image.width()-(x+1),y).b;
            image.pixel(image.width()-(x+1),y).r = tmp_r;
            image.pixel(image.width()-(x+1),y).g = tmp_g;
            image.pixel(image.width()-(x+1),y).b = tmp_b;
        }
    }
    image.save("output/06_mirror2.png");
}

void noise(sil::Image image) 
{
    int noiseLvl = random_int(15000, 20000);
    
    for (int i{0}; i < noiseLvl; i++)
    {
        int x = random_int(0, image.width());
        int y = random_int(0, image.height());

        image.pixel(x, y).r = random_float(0, 1);
        image.pixel(x, y).g = random_float(0, 1);
        image.pixel(x, y).b = random_float(0, 1);
    }
    image.save("output/07_noise.png");
}

void rotation90(sil::Image image) 
{
    sil::Image newImageRotation90{image.height(), image.width()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            newImageRotation90.pixel(image.height() - 1 - y, x) = image.pixel(x, y);
        }
    }
    newImageRotation90.save("output/08_rotation90.png");
}

void RGBSplit(sil::Image image, sil::Image result)
{
    // On passe sur tous les x et tous les y, et on accède au pixel correspondant :
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x<30){  // pour gerer les premieres colonnes
                result.pixel(x,y).r = image.pixel(0,y).r;
            }else{
                result.pixel(x,y).r = image.pixel(x-30,y).r;
            }

            if (x>image.width()-31){  //pour gerer les dernieres colonnes
                result.pixel(x,y).b = image.pixel(299,y).b;
            }else{
                result.pixel(x,y).b = image.pixel(x+30,y).b;
            }
            result.pixel(x,y).g = image.pixel(x,y).g;
        }
    }
    result.save("output/09_RGBSplit.png");
}

void brightness(sil::Image image) 
{
    int answer{0};
    std::cout << "lighten (1) or darken (0) ?" << std::endl;
    std::cin >> answer ;

    switch (answer)
    {
    case 1:
        for (glm::vec3 & color : image.pixels()) 
        {
            color.r = sqrt(color.r);
            color.g = sqrt(color.g);
            color.b = sqrt(color.b);
        }
        break;
        image.save("output/10_brightnessLighten.png");
    
    default:
        for (glm::vec3 & color : image.pixels()) 
        {
            color.r = pow (color.r, 2);
            color.g = pow (color.g, 2);
            color.b = pow (color.b, 2);
        }
        break;
        image.save("output/10_brightnessDarken.png");
    }
}

void disk(sil::Image image,int centerX, int centerY, int thickness){
    // On passe sur tous les x et tous les y, et on accède au pixel correspondant :
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {   
            if(sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY))<=thickness){  
                image.pixel(x,y).r = 1.f;
                image.pixel(x,y).g = 1.f;
                image.pixel(x,y).b = 1.f;
            }           
        }
    }
    image.save("output/11_disk.png");
}

void circle (sil::Image & image, int centerX, int centerY, int thickness) {  //coordonnee du centre du cerclee 
    // On passe sur tous les x et tous les y, et on accède au pixel correspondant :
    for (int x{0}; x < image.width(); x++)//300
    {
        for (int y{0}; y < image.height(); y++)//345
        {   
            if(sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY))<=100.f && sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY))>=100.f-thickness){  //le centre du cercle a pour coordonnees(255,255)
                image.pixel(x,y).r = 1.f;
                image.pixel(x,y).g = 1.f;
                image.pixel(x,y).b = 1.f;
            }
        }
    }
}

void rosace (sil::Image & image,int thickness){  
    circle(image,image.width()/2, image.height()/2,thickness);

    for(int i {0}; i<6 ; i++){
        circle(image,image.width()/2 + 100*cos(i*((2*pi)/6)), image.height()/2 + 100*sin(i*((2*pi)/6)) ,thickness);
    }
    image.save("output/13_rosace.png");
}

void mosaic(sil::Image image) 
{
    sil::Image mosaicCanvas{5*image.width(), 5*image.height()};
    
    for (int mosaicCanvasRow{0}; mosaicCanvasRow < 5; mosaicCanvasRow++)
    {
        for (int mosaicCanvasCol{0}; mosaicCanvasCol < 5; mosaicCanvasCol++)
        {
            for (int entryImageX{0}; entryImageX < image.width(); entryImageX++)
            {
                for (int entryImageY{0}; entryImageY < image.height(); entryImageY++)
                {
                    mosaicCanvas.pixel(mosaicCanvasRow*image.width() + entryImageX, mosaicCanvasCol*image.height() + entryImageY) = image.pixel(entryImageX, entryImageY);
                }
            }
        }
    }
    mosaicCanvas.save("output/14_mosaic.png");
}

void mirrorMosaic(sil::Image image) 
{
    sil::Image mirroredMosaicCanvas{5*image.width(), 5*image.height()};

    for (int mirroredMosaicCanvasRow{0}; mirroredMosaicCanvasRow < 5; mirroredMosaicCanvasRow++) 
    {
        for (int mirroredMosaicCanvasCol{0}; mirroredMosaicCanvasCol < 5; mirroredMosaicCanvasCol++) 
        {
            for (int entryImageX{0}; entryImageX < image.width(); entryImageX++)
            {
                for (int entryImageY{0}; entryImageY < image.height(); entryImageY++)
                {
                    int startingPointX{};
                    int startingPointY{};

                    if (mirroredMosaicCanvasRow % 2 == 1) {
                        startingPointX = image.width()- entryImageX - 1;
                    } else {
                        startingPointX = entryImageX;
                    }
                    if (mirroredMosaicCanvasCol % 2 == 1) {
                        startingPointY= image.height() - entryImageY - 1;
                    } else {
                        startingPointY= entryImageY;
                    }
                    mirroredMosaicCanvas.pixel(mirroredMosaicCanvasRow*image.width() + entryImageX, mirroredMosaicCanvasCol*image.height() + entryImageY) = image.pixel(startingPointX, startingPointY);
                }
            }
        }
    }
    mirroredMosaicCanvas.save("output/15_mirrorMosaic.png");
}

void glitch(sil::Image image) 
{
    int glitchLvl = random_int(20, 100);

    for (int repetitions = 0; repetitions < glitchLvl; repetitions++)
    {
        int startingPointX = random_int(0, image.width() - 40);
        int startingPointY = random_int(0, image.height() - 10);
        int newPointX = random_int(0, image.width() - 40);
        int newPointY = random_int(0, image.height() - 10);
        
        int widthRectangle = random_int(10, 40);
        int heightRectangle = random_int(1, 10);

        for (int w{0}; w < widthRectangle; w++)
        {
            for (int h{0}; h < heightRectangle; h++)
            {
                std::swap(image.pixel(w + newPointX, h + newPointY), image.pixel(startingPointX + w, startingPointY + h));
            }
        }
    }
    image.save("output/16_glitch.png");
}

void fractal(sil::Image image){
    for (float x{-(static_cast<float>(image.width())/200.f)}; x <= (static_cast<float>(image.width())/200.f); x= x+0.01f)
    {
        for (float y{-(static_cast<float>(image.height())/200.f)}; y <= (static_cast<float>(image.height())/200.f); y= y+0.01f)
        {
            std::complex<float>  c{x, y};
            std::complex<float> z{0.f, 0.f}; // Définis le nombre z = 0 + 0*i
            float counter {0.f};
            for (int i{0}; i<50; i++){
                z = z*z+c;
                counter += 1.f;
                if(std::abs(z) > 2){  
                    break;
                }
            }
            image.pixel(x*100.f+(static_cast<float>(image.width())/2.f),y*100.f+(static_cast<float>(image.height())/2.f)).r = counter/50.f;
            image.pixel(x*100.f+(static_cast<float>(image.width())/2.f),y*100.f+(static_cast<float>(image.height())/2.f)).b = counter/50.f;
            image.pixel(x*100.f+(static_cast<float>(image.width())/2.f),y*100.f+(static_cast<float>(image.height())/2.f)).g = counter/50.f; 
        }     
    }
    image.save("output/17_fractal.png");
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
} 
    
void vortex(sil::Image image, sil::Image result)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {   
            double distance {sqrt((x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.height()/2))};
            glm::vec2 newPosition {rotated({x,y},{image.width()/2, image.height()/2},distance/10)}; 
            if(newPosition.x>=0 && newPosition.x<image.width() && newPosition.y<image.height() &&newPosition.y>=0){
                result.pixel(x,y) = image.pixel(newPosition.x, newPosition.y);
            }
        }
    }
    result.save("output/18_vortex.png");
} 
    
void tramage(sil::Image image)
{
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = 
    {
        {    -0.5,       0,  -0.375,   0.125 },
        {    0.25,   -0.25,   0.375, - 0.125 },
        { -0.3125,  0.1875, -0.4375,  0.0625 },
        {  0.4375, -0.0625,  0.3125, -0.1875 },
    };
    
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (image.pixel(x, y).r + bayer_matrix_4x4[x % 4][y % 4] > 0.5f)
            {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 1;
                image.pixel(x, y).b = 1;
            } else {
                image.pixel(x, y).r = 0;
                image.pixel(x, y).g = 0;
                image.pixel(x, y).b = 0;
            }
        }
    }
    image.save("output/19_tramage.png");
} 
    
void normalisation(sil::Image image)
{
    sil::Image grayscaledCopy = image;
    blackAndWhite(grayscaledCopy);

    float darkestPixelValue{1.f};
    float brightestPixelValue{0.f};
    
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (grayscaledCopy.pixel(x, y).r < darkestPixelValue)
            {
                darkestPixelValue = grayscaledCopy.pixel(x, y).r;
            }
            
            else if (grayscaledCopy.pixel(x, y).r > brightestPixelValue)
            {
                brightestPixelValue = grayscaledCopy.pixel(x, y).r;
            }
        }
    }

    float deltaValue = brightestPixelValue - darkestPixelValue;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = (image.pixel(x, y).r - darkestPixelValue)*(1.f/deltaValue);
            image.pixel(x, y).g = (image.pixel(x, y).g - darkestPixelValue)*(1.f/deltaValue);
            image.pixel(x, y).b = (image.pixel(x, y).b - darkestPixelValue)*(1.f/deltaValue);
        }
    }
    image.save("output/20_normalisation.png");
}

void convolutions (sil::Image image, sil::Image result)
{
    int withKernel {};
    std::cout << "Entrez la longueur de votre kernel pour votre convolutions (nombre impair) : " ;
    std::cin >> withKernel;

    while(withKernel%2==0){
        std::cout << "Probleme, vous avez entrez un nombre pair. Veuillez recommencer. " << std::endl;
        std::cout << "Entrez la dimension de votre kernel pour votre convolutions (nombre impair) :" << std::endl;
        std::cin >> withKernel;
    }
    
    for (int x{0}; x < image.width(); x++)//300
    {
        for (int y{0}; y < image.height(); y++)//345
        {   
            float red_moy {};
            float blue_moy {};
            float green_moy {};
            for(int n{x-withKernel/2} ; n<=x+withKernel/2; n++){
                for(int z{y-withKernel/2} ; z<=y+withKernel/2; z++){
                    if(n>=0 && n<image.width() && z>=0 && z<image.height()){
                        red_moy += image.pixel(n,z).r;
                        blue_moy += image.pixel(n,z).b;
                        green_moy += image.pixel(n,z).g;
                    }
                }
            }
            result.pixel(x,y).r = red_moy/(static_cast<float>(withKernel)*static_cast<float>(withKernel));
            result.pixel(x,y).b = blue_moy/(static_cast<float>(withKernel)*static_cast<float>(withKernel));
            result.pixel(x,y).g = green_moy/(static_cast<float>(withKernel)*static_cast<float>(withKernel));

        }
    }
    result.save("output/21_convolutions.png");
}

void algoGeneriqueDeConvolution(std::vector<std::vector<float>> kernel, int ligneKernel, int colonneKernel, sil::Image & image, sil::Image & result)
{
    if((ligneKernel*colonneKernel)%2 == 1){
        float total {0.f}; 
        for(int i{0} ; i<ligneKernel ; i++){
            for(int j{0} ; j<colonneKernel ; j++){
                total = total +  kernel[i][j];
            }
        } 
  
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {   
                float red_moy {};
                float blue_moy {};
                float green_moy {};  
                int indiceLigneMatrice {ligneKernel-1};    
                int indiceColonneMatrice {0};     
                for(int n{x-colonneKernel/2} ; n<=x+colonneKernel/2; n++){
                    for(int z{y-ligneKernel/2} ; z<=y+ligneKernel/2; z++){
                        if(n>=0 && n<image.width() && z>=0 && z<image.height()){
                            red_moy += image.pixel(n,z).r*kernel[indiceLigneMatrice][indiceColonneMatrice];
                            blue_moy += image.pixel(n,z).b*kernel[indiceLigneMatrice][indiceColonneMatrice];
                            green_moy += image.pixel(n,z).g*kernel[indiceLigneMatrice][indiceColonneMatrice];
                            indiceLigneMatrice --;
                        }
                    }
                    indiceColonneMatrice ++;
                    indiceLigneMatrice = ligneKernel-1;
                }
                if(total!=0){
                    result.pixel(x,y).r = red_moy/total;
                    result.pixel(x,y).b = blue_moy/total;
                    result.pixel(x,y).g = green_moy/total;
                }else{
                    result.pixel(x,y).r = red_moy;
                    result.pixel(x,y).b = blue_moy;
                    result.pixel(x,y).g = green_moy;
                }
            }
        }
    }else{
        std::cout << "Probleme : algoGeneriqueDeConvolution ne peut etre appliquer sur une matrice de ce format.";
    }
 
}

void filtresSeparables (std::vector<std::vector<float>> kernel, int tailleKernel, sil::Image image, sil::Image & result){ 
    std::vector<std::vector<float>> matriceColonne {};  
    std::vector<std::vector<float>> matriceLigne {};  

    for(int i{1} ; i<= tailleKernel ; i++){
        matriceColonne.push_back({1.f/static_cast<float>(tailleKernel)});
    }

    std::vector<float> tmp {};  
    for(int i{1} ; i<= tailleKernel ; i++){
        tmp.push_back({1.f/static_cast<float>(tailleKernel)});
    }
    matriceLigne.push_back(tmp);  

    sil::Image result2{image.width(), image.height()};
    algoGeneriqueDeConvolution(matriceColonne,tailleKernel,1,image,result2);
    algoGeneriqueDeConvolution(matriceLigne,1,tailleKernel,result2,result);
}

void differenceDeGaussiennes (std::vector<std::vector<float>> kernel1, int widthKernel1, float tau, sil::Image image, sil::Image & result){
    sil::Image result1{500, 500};
    sil::Image result2{500, 500};

    //creation du kernel2
    std::vector<std::vector<float>> kernel2 {};
    int widthKernel2 {widthKernel1+10};
    std::vector<float> tmp {}; 
    for(int i{1} ; i<= widthKernel2 ; i++){
        for(int j{1} ; j<= widthKernel2 ; j++){
            tmp.push_back({1.f/(static_cast<float>(widthKernel2)*static_cast<float>(widthKernel2))});
        }
        kernel2.push_back(tmp); 
    }
    
    filtresSeparables(kernel1,widthKernel1,image,result1);
    filtresSeparables(kernel2,widthKernel2,image,result2);
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        { 
            result.pixel(x,y).r = (1.f+tau)*result1.pixel(x,y).r - tau*result2.pixel(x,y).r;
            result.pixel(x,y).g = (1.f+tau)*result1.pixel(x,y).g - tau*result2.pixel(x,y).g;
            result.pixel(x,y).b = (1.f+tau)*result1.pixel(x,y).b - tau*result2.pixel(x,y).b;
        }
    }
    blackAndWhite(result);
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        { 
            if(result.pixel(x,y).r >=0.2f){
                result.pixel(x,y).r = 1.f;
                result.pixel(x,y).b = 1.f;
                result.pixel(x,y).g = 1.f;
            }else{
                result.pixel(x,y).r = 0.f;
                result.pixel(x,y).b = 0.f;
                result.pixel(x,y).g = 0.f;
            }
        }
    }
    result.save("output/24_differenceDeGaussienne.png");
}

void pixelSorting(sil::Image image)
{
    int sortedRow = random_int(20, 200);
    int gap = random_int(100, 1000);

    for (int pxPosition{0}; pxPosition < image.height()*image.width(); pxPosition+= sortedRow + gap)
    {
        if (pxPosition + sortedRow < image.height()*image.width())
        {
            std::sort(image.pixels().begin() + pxPosition, image.pixels().begin() + pxPosition + sortedRow, [](glm::vec3 const& color1, glm::vec3 const& color2)
            {
                return ((color1.r + color1.g + color1.b) / 3) < ((color2.r + color2.g + color2.b) / 3);
            });
        }
        gap = random_int(100, 1000);
        sortedRow = random_int(20, 200);
    }
    image.save("output/25_pixelSorting.png");
}

int main()
{
    sil::Image logo{"images/logo.png"};
    sil::Image photo{"images/photo.jpg"};
    sil::Image lowContrast{"images/photo_faible_contraste.jpg"};

    sil::Image blackRectangle{300, 200};
    sil::Image blackImagePhoto{500, 500};     //meme format que la photo
    sil::Image blackImageLogo{300, 345};      //meme format que le logo

    // onlyGreen(logo);
    // changeRedBlue(logo);
    // { /*noirEtBlanc*/
    //     sil::Image logo{"images/logo.png"};
    //     blackAndWhite(logo);
    //     logo.save("output/03_blackAndWhite.png");
    // }
    // negative(logo);
    // gradient(blackRectangle);
    // mirror1(logo); 
    // mirror2(logo);
    // noise(logo);
    // rotation90(logo);
    // RGBSplit(logo, blackImageLogo);
    // brightness(photo);
    // { /*DISK*/
    //     float thickness {};
    //     std::cout << "Entrez le rayon pour votre disque que vous souhaitez :" ;
    //     std::cin >> thickness;   
    //     disk(blackImagePhoto, 255, 255, thickness);
    // }
    // { /*CIRCLE*/
    //     float thickness {};
    //     std::cout << "Entrez l'epaisseur du cercle que vous souhaitez :" ;
    //     std::cin >> thickness;
    //     circle(blackImagePhoto, 255, 255,thickness);
    //     blackImagePhoto.save("output/12_circle.png");
    // }
    // { /*ROSACE*/
    //     float thickness {};
    //     std::cout << "Entrez l'epaisseur pour les cercles de votre rosace que vous souhaitez :" ;
    //     std::cin >> thickness;
    //     sil::Image blackImagePhoto{500, 500};
    //     rosace(blackImagePhoto,thickness);
    // }

    // mosaic(logo);  
    // mirrorMosaic(logo);
    // glitch(logo);
    // { /*Fractal*/
    //     fractal(blackImagePhoto);
    // }
    // vortex(logo,blackImageLogo);
    // tramage(photo);
    // normalisation(lowContrast);
    // blackAndWhite(logo); /*cet appel remet à jour 03_noirEtBlanc*/ 
    // { 
    //    {
    //     /*CONVOLUTION*/
    //     convolutions(logo, blackImageLogo);
    //    }
    //    {
    //     /*AlgoGeneriqueDeConvolution*/
    //     sil::Image logo{"images/logo.png"};
    //     sil::Image blackImageLogo{300, 345};
    //     std::vector<std::vector<float>> kernel {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};   
    //     algoGeneriqueDeConvolution(kernel,3,3,logo,blackImageLogo);
    //     blackImageLogo.save("output/22_algoGeneriqueDeConvolution.png");
    //    }
    //    {
    //     /*FiltresSeparables*/
    //     sil::Image logo{"images/logo.png"};
    //     sil::Image blackImageLogo{300, 345};
    //     sil::Image photo{"images/photo.jpg"};
    //     sil::Image blackImagePhoto{500, 500};

    //     //creation du kernel
    //     std::vector<std::vector<float>> kernel {};
    //     int longueurKernel {};
    //     std::cout << "Entrez la longueur du kertel que vous souhaitez pour votre filtresSeparables(nombre impair): " ;
    //     std::cin >> longueurKernel; 

    //     while(longueurKernel%2==0){
    //     std::cout << "Probleme, vous avez entrez un nombre pair. Veuillez recommencer. " << std::endl;
    //     std::cout << "Entrez la longueur du kertel que vous souhaitez pour votre filtresSeparables(nombre impair) : " ;
    //     std::cin >> longueurKernel;
    //     }
         
    //     std::vector<float> tmp {}; 
    //     for(int i{1} ; i<= longueurKernel ; i++){
    //        for(int j{1} ; j<= longueurKernel ; j++){
    //            tmp.push_back({1.f/(static_cast<float>(longueurKernel)*static_cast<float>(longueurKernel))});
    //        }
    //        kernel.push_back(tmp); 
    //     }
    //     filtresSeparables(kernel,longueurKernel,logo, blackImageLogo);
    //     blackImageLogo.save("output/23_filtresSeparables.png");
    //    }
    //    {
    //     /*DifferenceDeGaussienne*/
    //     sil::Image photo{"images/photo.jpg"};
    //     sil::Image blackImagePhoto{500, 500};

    //     //creation du kernel
    //     std::vector<std::vector<float>> kernel {};
    //     int widthKernel {3};
         
    //     std::vector<float> tmp {}; 
    //     for(int i{1} ; i<= widthKernel ; i++){
    //        for(int j{1} ; j<= widthKernel ; j++){
    //            tmp.push_back({1.f/(static_cast<float>(widthKernel)*static_cast<float>(widthKernel))});
    //        }
    //        kernel.push_back(tmp); 
    //     }

    //     int tau {};
    //     std::cout << "Veuillez indiquer le tau que vous souhaitez pour votre difference de Gaussienne : ";
    //     std::cin >> tau;

    //     differenceDeGaussiennes(kernel, widthKernel, tau, photo, blackImagePhoto);
    //    }
    // }

    // pixelSorting(logo);
}