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
    
void seulementLeVert(sil::Image image) 
{
    for (glm::vec3 & color : image.pixels()) 
    {
        color.r = 0.f /*mets la composante rouge à 0. 1 couleur = glm::vec3 */ ;
        color.b = 0.f;
    }
    
    image.save("output/01_seulementLeVert.png");
}

void echangeRougeBleu(sil::Image image) 
{
    for (glm::vec3 & color : image.pixels()) 
    {
        std::swap(color.r, color.b);
    }
    image.save("output/02_echangeRougeBleu.png");
}

void noirEtBlanc(sil::Image & image) 
{
    for (glm::vec3 & color : image.pixels()) 
    {
        float moy = (color.r + color.g + color.b) / 3;
        color.r = moy;
        color.g = moy;
        color.b = moy;
    }
    image.save("output/03_noirEtBlanc.png");
}

void negatif(sil::Image image) 
{
    for (glm::vec3 & color : image.pixels()) 
    {
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
    image.save("output/04_negatif.png");
}

void degrade(sil::Image image) 
{
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            image.pixel(x, y).r += x / (image.width() - 1.0);
            image.pixel(x, y).g += x / (image.width() - 1.0);
            image.pixel(x, y).b += x / (image.width() - 1.0);

            /* Autre façon de faire, en utilisant la valeur précédente en incrémentant :
            image.pixel(x, y).r += image.pixel(x-1, 0).r + 1.f/(image.width() -1);
            Attention : faire démarrer x à 1 et conv la division en float
            y = 0 car on s'en fiche de la ligne ici */
        }
    }
    image.save("output/05_degrade.png");
}

void miroirReverse(sil::Image image) 
{
    for (int i{0}; i < image.height()*image.width(); i+=image.width())
    {
        std::reverse(image.pixels().begin() + i, image.pixels().begin() + i + image.width()); 
    }
    image.save("output/06_miroirReverse.png");
}

void miroir2(sil::Image image) /*2e version*/
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
    image.save("output/06_miroir2.png");
}

void bruit(sil::Image image) 
{
    int noiseLvl = random_int(1, 5000);
    
    for (int i{0}; i < noiseLvl; i++)
    {
        int x = random_int(0, image.width());
        int y = random_int(0, image.height());

        image.pixel(x, y).r = random_float(0, 1);
        image.pixel(x, y).g = random_float(0, 1);
        image.pixel(x, y).b = random_float(0, 1);
    }
    image.save("output/07_bruit.png");
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

void luminosite(sil::Image image) 
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
    
    default:
        for (glm::vec3 & color : image.pixels()) 
        {
            color.r = pow (color.r, 2);
            color.g = pow (color.g, 2);
            color.b = pow (color.b, 2);
        }
        break;
    }
    image.save("output/10_Luminosity.png");
}

void disque(sil::Image image){
    // On passe sur tous les x et tous les y, et on accède au pixel correspondant :
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {   
            if(sqrt((x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.width()/2))<=100){  
                image.pixel(x,y).r = 1.f;
                image.pixel(x,y).g = 1.f;
                image.pixel(x,y).b = 1.f;
            }           
        }
    }
    image.save("output/11_disque.png");
}

void cercle (sil::Image & image, int abcisse, int ordonnee, int thickness) {  //coordonnee du centre du cerclee 
    // On passe sur tous les x et tous les y, et on accède au pixel correspondant :
    for (int x{0}; x < image.width(); x++)//300
    {
        for (int y{0}; y < image.height(); y++)//345
        {   
            if(sqrt((x-abcisse)*(x-abcisse)+(y-ordonnee)*(y-ordonnee))<=100.f && sqrt((x-abcisse)*(x-abcisse)+(y-ordonnee)*(y-ordonnee))>=100.f-thickness){  //le centre du cercle a pour coordonnees(255,255)
                image.pixel(x,y).r = 1.f;
                image.pixel(x,y).g = 1.f;
                image.pixel(x,y).b = 1.f;
            }
        }
    }
    image.save("output/12_cercle.png");
}

void rosace (sil::Image & image,int thickness){  
    cercle(image,image.width()/2, image.height()/2,thickness);

    for(int i {0}; i<6 ; i++){
        cercle(image,image.width()/2 + 100*cos(i*((2*pi)/6)), image.height()/2 + 100*sin(i*((2*pi)/6)) ,thickness);
    }
    image.save("output/13_rosace.png");
}

void mosaique(sil::Image image) 
{
    sil::Image canvasMosaic{5*image.width(), 5*image.height()};
    
    for (int canvasCol{0}; canvasCol < 5*image.height(); canvasCol += image.height())
    {
        for (int canvasRow{0}; canvasRow < 5*image.width(); canvasRow += image.width())
        {
            for (int entryImageX{0}; entryImageX < image.width(); entryImageX++)
            {
                for (int yImageEntry{0}; yImageEntry < image.height(); yImageEntry++)
                {
                    canvasMosaic.pixel(entryImageX + canvasRow, yImageEntry + canvasCol) = image.pixel(entryImageX, yImageEntry);
                }
            }
        }
    }
    canvasMosaic.save("output/14_mosaique.png");
}

void mosaiqueMiroir(sil::Image image) 
{
    sil::Image canvasMirroredMosaic{5*image.width(), 5*image.height()};
    int startingPointx{};
    int startingPointy{};

    for (int mirroredCanvasRow{0}; mirroredCanvasRow < 5; mirroredCanvasRow++) 
    {
        for (int mirroredCanvasCol=0; mirroredCanvasCol<5; mirroredCanvasCol++) 
        {
            for (int xEntryImage{0}; xEntryImage < image.width(); xEntryImage++)
            {
                for (int yEntryImage{0}; yEntryImage < image.height(); yEntryImage++)
                {
                    if (mirroredCanvasRow%2 == 1) {
                        startingPointx = image.width()-xEntryImage-1;
                    } else {
                        startingPointx = xEntryImage;
                    }
                    if (mirroredCanvasCol%2 == 1) {
                        startingPointy = image.height()-yEntryImage-1;
                    } else {
                        startingPointy = yEntryImage;
                    }
                    canvasMirroredMosaic.pixel(mirroredCanvasRow*image.width()+xEntryImage, mirroredCanvasCol*image.height()+yEntryImage) = image.pixel(startingPointx, startingPointy);
                }
            }
        }
    }
    canvasMirroredMosaic.save("output/15_mosaiqueMiroir.png");
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

void fractale(sil::Image image){
    for (float x{-(static_cast<float>(image.width())/200.f)}; x <= (static_cast<float>(image.width())/200.f); x= x+0.01f)
    {
        for (float y{-(static_cast<float>(image.height())/200.f)}; y <= (static_cast<float>(image.height())/200.f); y= y+0.01f)
        {
            std::complex<float>  c{x, y};
            std::complex<float> z{0.f, 0.f}; // Définis le nombre z = 0 + 0*i
            float compteur {0.f};
            for (int i{0}; i<50; i++){
                z = z*z+c;
                compteur += 1.f;
                if(std::abs(z) > 2){  
                    break;
                }
            }
            image.pixel(x*100.f+(static_cast<float>(image.width())/2.f),y*100.f+(static_cast<float>(image.height())/2.f)).r = compteur/50.f;
            image.pixel(x*100.f+(static_cast<float>(image.width())/2.f),y*100.f+(static_cast<float>(image.height())/2.f)).b = compteur/50.f;
            image.pixel(x*100.f+(static_cast<float>(image.width())/2.f),y*100.f+(static_cast<float>(image.height())/2.f)).g = compteur/50.f; 
        }     
    }
    image.save("output/17_fractale.png");
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
            glm::vec2 nouvelle_position {rotated({x,y},{image.width()/2, image.height()/2},distance/10)}; 
            if(nouvelle_position.x>=0 && nouvelle_position.x<image.width() && nouvelle_position.y<image.height() &&nouvelle_position.y>=0){
                result.pixel(x,y) = image.pixel(nouvelle_position.x, nouvelle_position.y);
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

    noirEtBlanc(image);
    
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (image.pixel(x, y).r > 1 - bayer_matrix_4x4[x % 4][y % 4])
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
    noirEtBlanc(grayscaledCopy);

    size_t const pixelCount = image.height()*image.width();
    
    size_t const dwarf_count = 20;

    std::vector<int> calories;

    // std::srand permet de fixer la "seed" du générateur aléatoire (pour avoir des résultats reproductibles)
    std::srand(42);
    
    for (int i = 0; i < dwarf_count; ++i)
    {
      calories.push_back(rand() % 24000 + 100);
    }

    // affichage optionnel des calories transportées par chaque nain
    for (int const c : calories)
    {
      std::cout << c << ", ";
    }
    std::cout << std::endl;

    // TODO: afficher la quantité de provisions la plus grande transportée par un nain
    
    int max_provision{0};
    int max_nain{0};

    int min_provision{24100};
    int min_nain{0};
    
    for (int i{0}; i < calories.size(); i++) {
        int valeur_courante = calories[i];

        if (valeur_courante > max_provision) {
            max_provision = valeur_courante;
            max_nain = i;
        }

        if (valeur_courante < min_provision) {
            min_provision = valeur_courante;
            min_nain = i;
        }
    }

    int max_provision2{};
    int max_provision3{};

    std::sort(calories.begin(), calories.end());

    max_provision = calories[calories.size()-1];
    max_provision2 = calories[calories.size()-2];
    max_provision3 = calories[calories.size()-3];
    min_provision = calories[0];

    std::cout << "La plus grande provision est de " << max_provision << " calories" << std::endl;
    std::cout << "Elle est détenue par le nain " << max_nain+1 << std::endl;
    std::cout << "La plus petite provision est de " << min_provision << " calories" << std::endl;
    std::cout << "Elle est détenue par le nain " << min_nain+1 << std::endl;

    image.save("output/20_normalisation.png");
}

void convolutions (sil::Image image, sil::Image result)
{
    int kernel {};
    std::cout << "Entrez la dimension de votre kernel (nombre impair) : " ;
    std::cin >> kernel;

    while(kernel%2==0){
        std::cout << "Probleme, vous avez entrez un nombre pair. Veuillez recommencer. " << std::endl;
        std::cout << "Entrez la dimension de votre kernel (nombre impair) :" << std::endl;
        std::cin >> kernel;
    }
    
    for (int x{0}; x < image.width(); x++)//300
    {
        for (int y{0}; y < image.height(); y++)//345
        {   
            float red_moy {};
            float blue_moy {};
            float green_moy {};
            for(int n{x-kernel/2} ; n<=x+kernel/2; n++){
                for(int z{y-kernel/2} ; z<=y+kernel/2; z++){
                    if(n>=0 && n<image.width() && z>=0 && z<image.height()){
                        red_moy += image.pixel(n,z).r;
                        blue_moy += image.pixel(n,z).b;
                        green_moy += image.pixel(n,z).g;
                    }
                }
            }
            result.pixel(x,y).r = red_moy/(static_cast<float>(kernel)*static_cast<float>(kernel));
            result.pixel(x,y).b = blue_moy/(static_cast<float>(kernel)*static_cast<float>(kernel));
            result.pixel(x,y).g = green_moy/(static_cast<float>(kernel)*static_cast<float>(kernel));

        }
    }
    result.save("output/21_convolutions.png");
}

void algoGeneriqueDeConvolution(std::vector<std::vector<float>> kernel, int ligneKernel, int colonneKernel, sil::Image image, sil::Image & result)
{
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

    algoGeneriqueDeConvolution(matriceColonne,tailleKernel,1,image,result);
    sil::Image result2{300, 345};
    algoGeneriqueDeConvolution(matriceLigne,1,tailleKernel,result,result2);
    result2.save("output/23_filtresSeparables.png");
}

void differenceDeGaussiennes (std::vector<std::vector<float>> kernel1, int longueurKernel1, sil::Image image, sil::Image & result){
    sil::Image result1{500, 500};
    sil::Image result2{500, 500};

    //creation du kernel2
    std::vector<std::vector<float>> kernel2 {};
    int longueurKernel2 {longueurKernel1+10};
    std::vector<float> tmp {}; 
    for(int i{1} ; i<= longueurKernel2 ; i++){
        for(int j{1} ; j<= longueurKernel2 ; j++){
            tmp.push_back({1.f/(static_cast<float>(longueurKernel2)*static_cast<float>(longueurKernel2))});
        }
        kernel2.push_back(tmp); 
    }
    
    filtresSeparables(kernel1,longueurKernel1,image,result1);
    // filtresSeparables(kernel2,longueurKernel2,image,result2);
    // for (int x{0}; x < image.width(); x++)
    // {
    //     for (int y{0}; y < image.height(); y++)
    //     { 
    //         result.pixel(x,y) = result1.pixel(x,y) - result2.pixel(x,y);
    //     }
    // }
    // noirEtBlanc(result);
    // for (int x{0}; x < image.width(); x++)
    // {
    //     for (int y{0}; y < image.height(); y++)
    //     { 
    //         if(result.pixel(x,y).r >=0.2f){
    //             result.pixel(x,y).r = 0.f;
    //             result.pixel(x,y).b = 0.f;
    //             result.pixel(x,y).g = 0.f;
    //         }else{
    //             result.pixel(x,y).r = 1.f;
    //             result.pixel(x,y).b = 1.f;
    //             result.pixel(x,y).g = 1.f;
    //         }
    //     }
    // }
    // result.save("output/24_differenceDeGaussienne.png");
}

int main()
{
    sil::Image logo{"images/logo.png"};
    sil::Image photo{"images/photo.jpg"};
    sil::Image lowContrast{"images/photo_faible_contraste.jpg"};

    sil::Image blackRectangle{300, 200};
    sil::Image image_noire{500, 500};  
    sil::Image result{300, 345};

    // seulementLeVert(logo);
    // echangeRougeBleu(logo);
    // { /*noirEtBlanc*/
        // sil::Image logo{"images/logo.png"};
        // noirEtBlanc(logo);
        // }
    // negatif(logo);
    // degrade(blackRectangle);
    // miroirReverse(logo); 
    // miroir2(logo);
    // bruit(logo);
    // rotation90(logo);
    // RGBSplit(logo, result);
    // luminosite(photo);
    // disque(image_noire);  
    // { /*CERCLE*/
    //     float thickness {};
    //     std::cout << "Entrez l'epaisseur du cercle que vous souhaitez :" ;
    //     std::cin >> thickness;
    //     cercle(image_noire, 255, 255,thickness);
    // }
    // { /*ROSACE*/
    //     float thickness {};
    //     std::cout << "Entrez l'epaisseur pour les cercles que vous souhaitez :" ;
    //     std::cin >> thickness;
    //     sil::Image image_noire{500, 500};
    //     rosace(image_noire,thickness);
    // }
    // mosaique(logo);  
    // mosaiqueMiroir(logo);
    { /*Fractale*/
        fractale(image_noire);
    }

    // glitch(logo);
    // vortex(logo,result);
    // tramage(photo);

    // { 
    //    /*CONVOLUTION*/
    //     std::vector<std::vector<float>> kernel {{1.f/9.f,1.f/9.f,1.f/9.f},{1.f/9.f,1.f/9.f,1.f/9.f},{1.f/9.f,1.f/9.f,1.f/9.f}};
    //     convolutions(logo, result);
    //    /*AlgoGeneriqueDeConvolution*/
    //     std::vector<std::vector<float>> kernel {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
    //     algoGeneriqueDeConvolution(kernel,3,3,logo,result);
    //     result.save("output/22_algoGeneriqueDeConvolution.png");
    //   /*FiltresSeparables*/
    //    {
    //     sil::Image logo{"images/logo.png"};
    //     sil::Image result{300, 345};

    //     //creation du kernel
    //     std::vector<std::vector<float>> kernel {};
    //     int longueur_kernel {};
    //     std::cout << "Entrez la longueur du kartel que vous souhaitez (nombre impair): " ;
    //     std::cin >> longueur_kernel; 

    //     while(longueur_kernel%2==0){
    //     std::cout << "Probleme, vous avez entrez un nombre pair. Veuillez recommencer. " << std::endl;
    //     std::cout << "Entrez la dimension de votre kernel (nombre impair) : " ;
    //     std::cin >> longueur_kernel;
    //     }
         
    //     std::vector<float> tmp {}; 
    //     for(int i{1} ; i<= longueur_kernel ; i++){
    //        for(int j{1} ; j<= longueur_kernel ; j++){
    //            tmp.push_back({1.f/(static_cast<float>(longueur_kernel)*static_cast<float>(longueur_kernel))});
    //        }
    //        kernel.push_back(tmp); 
    //     }

    //    filtresSeparables(kernel,longueur_kernel,logo, result);
       
    //   /*DifferenceDeGaussienne*/
    //     sil::Image photo{"images/photo.jpg"};
    //     sil::Image resultPhoto{500, 500};
    //     differenceDeGaussiennes(kernel, longueur_kernel,photo, resultPhoto);
    //    }
    //
    // // }
}