#define _USE_MATH_DEFINES
#include <sil/sil.hpp>
#include "random.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <glm/gtx/matrix_transform_2d.hpp>

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

void noirEtBlanc(sil::Image image) 
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
    sil::Image newImageMosaic{5*image.width(), 5*image.height()};
    
    for (int colnewImageMosaic{0}; colnewImageMosaic < 5*image.height(); colnewImageMosaic += image.height())
    {
        for (int rownewImageMosaic{0}; rownewImageMosaic < 5*image.width(); rownewImageMosaic += image.width())
        {
            for (int x{0}; x < image.width(); x++)
            {
                for (int y{0}; y < image.height(); y++)
                {
                    newImageMosaic.pixel(x + rownewImageMosaic, y + colnewImageMosaic) = image.pixel(x, y);
                }
            }
        }
    }
    newImageMosaic.save("output/14_mosaique.png");
}

void mosaiqueMiroir(sil::Image image) 
{
    sil::Image canvasMirroredMosaic{5*image.width(), 5*image.height()};
    int startingPointx{};
    int startingPointy{};

    for (int canvasRow{0}; canvasRow < 5; canvasRow++) 
    {
        for (int j=0; j<5; j++) 
        {
            for (int xEntryImage{0}; xEntryImage < image.width(); xEntryImage++)
            {
                for (int yEntryImage{0}; yEntryImage < image.height(); yEntryImage++)
                {
                    // Choix d'une symétrie verticale ou non
                    if (canvasRow%2 == 1) {
                        startingPointx = image.width()-xEntryImage-1;
                    } else {
                        startingPointx = xEntryImage;
                    }
                    // Choix d'une symétrie horizontale ou non
                    if (j%2 == 1) {
                        startingPointy = image.height()-yEntryImage-1;
                    } else {
                        startingPointy = yEntryImage;
                    }

                    // Affichage de l'image
                    canvasMirroredMosaic.pixel(canvasRow*image.width()+xEntryImage, j*image.height()+yEntryImage) = image.pixel(startingPointx, startingPointy);
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

glm::vec2 rotated(glm::vec2 v, float angle) // glm::vec2 correspond a la position d'un pixel
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{v, 1.f}};
    //retourne une nouvelle position du pixel
} 
    
void vortex(sil::Image image, sil::Image result2)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {   
            if(sqrt((x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.height()/2))<=image.height()/2-x && sqrt((x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.height()/2))>=image.height()/2-x){  
                glm::vec2 nouvelle_position {rotated({x,y},x+10.f)}; 
                if((nouvelle_position.x>=0 && nouvelle_position.x<image.width()) && (nouvelle_position.y>=0 && nouvelle_position.y<image.height())){
                    result2.pixel(x,y) = image.pixel(nouvelle_position.x, nouvelle_position.y);
                }
            } 
        }
    }
    result2.save("output/18_vortex.png");
} 
    
void tramage(sil::Image image)
{
    noirEtBlanc(image);
    
    for (glm::vec3 & color : image.pixels())
    {
        color.r+=random_float(0, 1) - .5;
        if (color.r > .5 )
        {
            color.r = 0;
            color.g = 0;
            color.b = 0;
        } else 
        {
            color.r = 1;
            color.g = 1;
            color.b = 1;
        }
    }
    image.save("output/19_tramage.png");
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
    
    for (int x{kernel/2}; x < image.width()-kernel/2; x++)//300
    {
        for (int y{kernel/2}; y < image.height()-kernel/2; y++)//345
        {   
            float red_moy {};
            float blue_moy {};
            float green_moy {};
            for(int n{x-kernel/2} ; n<=x+kernel/2; n++){
                for(int z{y-kernel/2} ; z<=y+kernel/2; z++){
                    red_moy += image.pixel(n,z).r;
                    blue_moy += image.pixel(n,z).b;
                    green_moy += image.pixel(n,z).g;
                }
            }
            result.pixel(x,y).r = red_moy/(static_cast<float>(kernel)*static_cast<float>(kernel));
            result.pixel(x,y).b = blue_moy/(static_cast<float>(kernel)*static_cast<float>(kernel));
            result.pixel(x,y).g = green_moy/(static_cast<float>(kernel)*static_cast<float>(kernel));
        }
    }
    result.save("output/21_convolutions.png");
}

int main()
{
    sil::Image logo{"images/logo.png"};
    sil::Image photo{"images/photo.jpg"};
    sil::Image lowContrast{"images/photo_faible_contraste.jpg"};

    sil::Image blackRectangle{300, 200};
    sil::Image image_noire{500, 500};  
    sil::Image result1{301, 346};
    sil::Image result2{300, 345};

    // seulementLeVert(logo);
    // echangeRougeBleu(logo);
    // noirEtBlanc(logo);
    // negatif(logo);
    // degrade(blackRectangle);
    // miroirReverse(logo); 
    // miroir2(logo);
    // bruit(logo);
    // rotation90(logo);
    // RGBSplit(logo, result2);
    // luminosite(photo);
    // disque(image_noire);  
    // { /*CERCLE*/
    //     float thickness {};
    //     std::cout << "Entrez l'epaisseur du cercle que vous souhaitez :" ;
    //     std::cin >> thickness;
    //     cercle(image_noire, 255, 255,thickness);
    // }
    // { /*ROSACE*/
    //     sil::Image image_noire{500, 500};
    //     rosace(image_noire,thickness);
    // }
    // mosaique(logo);  
    // mosaiqueMiroir(logo);
    // glitch(logo);
    // vortex(logo,result2);
    convolutions(logo, result1 );

    // vortex(logo,result2);
    tramage(photo);
    
    // convolutions(logo, result1 );
}