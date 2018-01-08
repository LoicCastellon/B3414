function [] = partie2()
    gris = ([0:255]/255)'*[1 1 1];

%     [imFloue,mapFloue]= imread('image_floue.png');
%     figure(1);
%     image(imFloue);
%     colormap(gris);
%     
%     [imRef,mapRef]= imread('image_ref.png');
%     figure(2);
%     image(imRef);
%     colormap(gris);
%     
%     [imThorg,mapThorg]= imread('Thorg.png');
%     figure(3);
%     image(imThorg);
%     colormap(gris);
%     
%     figure(4);
%     image(ImageFiltreGaussien(imThorg,0.0002));
%     colormap(gris);
%     
%     figure(5);
%     image(ImageFiltreGaussien(imThorg,0.0004));
%     colormap(gris);
%     
%     figure(6);
%     image(ImageFrequence(imFloue));
%     colormap(gris);
%     
%     figure(7);
%     image(ImageFrequence(imRef));
%     colormap(gris);
%     
%     figure(8);
%     image(ImageFrequence(imThorg));
%     colormap(gris);
    
%RETAURATION
    imFloue= imread('image_floue.png');
    imRef= imread('image_ref.png');
    figure(1)
    image(ImageIdealeWiener(imFloue,imRef));
    colormap(gris);
end

function [imRetour] = ImageFiltreGaussien(im,K)
    im = double(im);
    IM = fft2(im);
    IM = fftshift(IM);
    
    H = zeros(size(IM));
    [L,C]=size(H);
    for u=1:L
        for v=1:C
            uu=u-L/2;
            vv=v-C/2;
            H(u,v) = exp(-K*(uu*uu+vv*vv));
        end
    end
    imRetour = real(ifft2(fftshift(IM.*H)));
end

function [imageRetour]= ImageFrequence(im)
    im=double(im);
    IM=fft2(im) ;
    IM=fftshift(IM) ;
    logIM=log(abs(IM)+1) ;
    maxi=max(max(logIM)) ;
    mini=min(min(logIM)) ;
    imageRetour = (logIM-mini)/(maxi-mini)*255;
end

function [imageRetour]= ImageSousEchantillonee(im)
    im=double(im);
    [L,C]=size(im);
    L=L/4;
    C=C/4;
    imageRetour = zeros(L,C);
    for x=1:L
        for y=1:C
            imageRetour(x,y)=im(x*4,y*4);
        end
    end
end

function [imageRetour]= ImageIdealeSimpliste(im)
    IM = fft2(im);
        IM = fftshift(IM);
    h = zeros(size(IM));
        hauteur = 3;
        largeur = 13;
        h(1:hauteur,1:largeur) = 1/(hauteur*largeur);
    H = fft2(h);
    IM_RETOUR = IM./H;
    imageRetour = real(ifft2(fftshift(IM_RETOUR)));
end

function [imageRetour]= ImageIdealeWiener(im,imRef)
    h = zeros(size(im));
        hauteur = 3;
        largeur = 13;
        h(1:hauteur,1:largeur) = 1/(hauteur*largeur);
    H = fft2(h);
    
    IM_REF = fft2(imRef);
    dr = ifft2(IM_REF.*H);
    BRUIT = fft2(dr - round(dr));

    Pbruit = BRUIT.*BRUIT;
    Pideal = IM_REF.*IM_REF;

    W = abs(H) .* abs(H) ./ (H .* ((abs(H) .* abs(H)) + (Pbruit ./ Pideal)));
   
    IM = fft2(im);
    IM_RETOUR = IM.*W;
    
	imageRetour = real(ifft2(IM_RETOUR));
end